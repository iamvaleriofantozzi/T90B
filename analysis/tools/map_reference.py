"""Build the static T90B evidence tables from Ghidra output and NSING documents."""

import argparse
import csv
import re
import struct
import xml.etree.ElementTree as ET
from pathlib import Path

BASE = 0x08005000
MANUAL = "NSING N32L40x UM v2.6.0, memory map"
RANGE = re.compile(r"0x(400[0-2]_[0-9A-F]{4})[ \t]+–[ \t]+0x(400[0-2]_[0-9A-F]{4})[ \t]+(\S+)")
LITERAL = re.compile(r"^ldr(?:\.\w+)? r\d+,\[(0x[0-9a-f]+)\]$")
INDIRECT = re.compile(r"^(?:bl?x r\d+|tb[bh] |(?:ldr|mov)(?:\.\w+)? pc,)")


def write_table(path, header, rows):
    with path.open("w", newline="") as output:
        writer = csv.writer(output, delimiter="\t", lineterminator="\n")
        writer.writerow(header)
        writer.writerows(rows)


def read_index(path, expected_count=None):
    with path.open() as source:
        rows = list(csv.DictReader(source, delimiter="\t"))
    addresses = {row["address"] for row in rows}
    if len(addresses) != len(rows) or (expected_count is not None and len(rows) != expected_count):
        raise ValueError(f"Unexpected function index: {path}")
    return rows, addresses


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("manual_text", type=Path)
    parser.add_argument("svd", type=Path)
    parser.add_argument("work_index", type=Path)
    args = parser.parse_args()
    _, original_addresses = read_index(Path("analysis/functions.tsv"), 415)
    work, work_addresses = read_index(args.work_index)
    if not original_addresses <= work_addresses:
        raise ValueError("The work index differs from the baseline")

    output = Path("docs/reconstruction")
    app = Path("analysis/t90-app.bin").read_bytes()
    assembly = dict(
        line.split("  ", 1)
        for line in Path("analysis/t90-disassembly.txt").read_text().splitlines()
    )
    manual_text = args.manual_text.read_text()
    memory_map = manual_text[manual_text.index("0x4002_4800 – 0x5FFF_FFFF"):].split("Bit banding", 1)[0]
    ranges = {
        int(start.replace("_", ""), 16): (int(end.replace("_", ""), 16), name)
        for start, end, name in RANGE.findall(memory_map)
        if name != "Reserved"
    }

    def flash_word(address):
        return struct.unpack_from("<I", app, address - BASE)[0]

    literal_refs = {}
    for address, instruction in assembly.items():
        match = LITERAL.fullmatch(instruction)
        if match:
            value = flash_word(int(match[1], 16))
            literal_refs.setdefault(value, []).append(address)

    rows = []
    mismatches = []
    for peripheral in ET.parse(args.svd).findall("./peripherals/peripheral"):
        name = peripheral.findtext("name")
        start = int(peripheral.findtext("baseAddress"), 0)
        if start not in ranges:
            mismatches.append(f"- `0x{start:08x}` {name}: base senza riscontro nella mappa estratta.")
            continue
        end, documented_name = ranges[start]
        if name not in documented_name.split("/"):
            mismatches.append(
                f"- `0x{start:08x}` {name}: il manuale identifica {documented_name}."
            )
            continue
        for register in peripheral.findall("./registers/register"):
            if register.find("dim") is not None:
                continue
            address = start + int(register.findtext("addressOffset"), 0)
            references = literal_refs.get(address)
            if address > end or not references:
                continue
            evidence = f"{MANUAL} + SVD N32L403; literal load a " + ", ".join(references)
            rows.append((f"0x{address:08x}", register.findtext("name"), name, evidence, "candidate"))
    rows.sort()
    write_table(output / "registers.tsv", ("address", "name", "peripheral", "evidence", "status"), rows)

    vector = flash_word(BASE + 4)
    watchdog = {
        "080098f8": ("iwdg_start", "080116a2 → 08009910 → 08009962; 080098fe scrive 0xCCCC in IWDG_KEY"),
        "08009974": ("iwdg_reload", "0801174c → 08009908 → 0800990a; 0800997a scrive 0xAAAA in IWDG_KEY"),
        "08009910": ("iwdg_configure", "080116a2 → 08009910; sequenza IWDG_KEY 0x5555, prescaler, reload, 0xAAAA, 0xCCCC"),
    }
    callback_slots = {}
    for slot in range(0x08016100, 0x08016140, 4):
        pointer = flash_word(slot)
        if pointer & 1:
            callback_slots[f"{pointer & ~1:08x}"] = slot

    function_rows = []
    for row in work:
        address, name = row["address"], row["function"]
        subsystem, evidence, status = "unknown", "entry point Ghidra in entrambi gli indici", "unknown"
        if int(address, 16) == vector & ~1:
            subsystem = "startup"
            evidence = "vettore 1 del payload; literal load e trasferimenti a 080052ce/080052d2"
            status = "candidate"
        if address in watchdog:
            name, detail = watchdog[address]
            subsystem, status = "watchdog", "confirmed"
            evidence = f"{detail}; NSING UM v2.6.0, capitolo IWDG"
        if address in callback_slots:
            slot = callback_slots[address]
            subsystem, status = "ui", "candidate"
            evidence = f"slot 0x{slot:08x} della tabella chiamata da 08014cee; ruolo della routine da verificare"
        elif address == "08014ce0":
            name, subsystem, status = "ui_dispatch", "ui", "confirmed"
            evidence = "08011744 → 08014ce0; 08014cf8 contiene 08016100; LDR indicizzato a 08014cea; BLX a 08014cee"
        elif address not in original_addresses:
            evidence = "entry point individuato nel progetto di lavoro"
        function_rows.append((address, name, subsystem, evidence, status))
    write_table(output / "functions.tsv", ("address", "symbol", "subsystem", "evidence", "status"), function_rows)

    indirect = []
    for address, instruction in assembly.items():
        if 0x08016100 <= int(address, 16) < 0x08016140 or not INDIRECT.match(instruction):
            continue
        prior = f"{int(address, 16) - 2:08x}"
        prior_literal = LITERAL.fullmatch(assembly.get(prior, ""))
        if instruction.startswith(("bx ", "blx ")) and prior_literal:
            destination = flash_word(int(prior_literal[1], 16))
            aligned = destination & ~1
            if destination & 1 and f"{aligned:08x}" in assembly:
                status = f"target statico `0x{aligned:08x}`, letterale Thumb `0x{destination:08x}`"
            else:
                status = "letterale presente, destinazione da verificare"
        elif address == "08014cee":
            status = "dispatch attraverso la tabella `0x08016100`; 15 target Thumb e uno slot nullo; vincoli sull’indice da verificare"
        elif instruction.startswith("ldr.w pc,[sp],"):
            status = "ritorno probabile tramite stack"
        elif instruction.startswith(("tbb ", "tbh ")):
            site = int(address, 16)
            table = site + 4
            register = instruction.rsplit(",", 1)[1].rstrip("]")
            bound = re.fullmatch(rf"cmp {register},#(0x[0-9a-f]+)", assembly.get(f"{site - 4:08x}", ""))
            guard = assembly.get(prior, "")
            status = f"tabella a `0x{table:08x}`, limiti e target da verificare"
            if bound and guard.startswith("bcs "):
                count = int(bound[1], 16)
                entry_size = 1 if instruction.startswith("tbb ") else 2
                data_start = table - BASE
                data = app[data_start:data_start + count * entry_size]
                targets = [table + 2 * int.from_bytes(data[i:i + entry_size], "little")
                           for i in range(0, len(data), entry_size)]
                if len(targets) == count and all(f"{target:08x}" in assembly for target in targets):
                    destinations = ", ".join(f"`0x{target:08x}`" for target in targets)
                    status = (f"`0x{table:08x}`–`0x{table + len(data) - 1:08x}`; "
                              f"{count} voci in ordine di indice: {destinations}")
        else:
            status = "origine del puntatore e target da verificare"
        indirect.append(f"| `0x{address}` | `{instruction}` | {status} |")
    introduction = """# Aree irrisolte

L'indice di lavoro conserva i 415 indirizzi originali. I puntatori Thumb a `0x08016100`–`0x0801613f` includono sette destinazioni aggiuntive; lo slot a `0x08016108` è nullo. Il dispatcher a `0x08014ce0` carica la base da `0x08014cf8` e chiama la destinazione indicizzata a `0x08014cee`. Il ruolo delle singole routine e i vincoli sull’indice restano da verificare.

Le corrispondenze dei registri indicano indirizzi caricati come costanti. L'operazione successiva e il ruolo sulla scheda richiedono riscontro.

## Trasferimenti indiretti e tabelle

| Indirizzo | Istruzione | Evidenza |
|---|---|---|
"""
    sections = [introduction + "\n".join(indirect),
                "## Confine codice e dati\n\n"
                "Le sei tabelle TBB delimitate sopra sono dati. Le tabelle dei puntatori UI a "
                "`0x08016050`–`0x080160ff` e `0x08016380`–`0x080163bf` sono documentate "
                "in [ui-pointer-table.tsv](ui-pointer-table.tsv). Nella prima, l’export originale "
                "aveva interpretato 88 mezze parole come istruzioni. Le tabelle sono state definite "
                "come dati nel progetto di lavoro mediante `DefineT90UiData.java`. "
                "I confini del pool dei "
                "letterali e delle aree non raggiunte dall’analisi restano aperti. Per esempio "
                "la sequenza dopo il trasferimento a `0x08005152` contiene la parola "
                "letta come destinazione a `0x08005154` e quella caricata in SP a "
                "`0x08005158`. Il ruolo dell’intervallo `0x08005000`–`0x08005147` "
                "oltre alle voci del vettore riconosciute da SeedT90 va verificato.",
                "## Basi SVD escluse dal confronto automatico\n\n" + "\n".join(mismatches)]
    (output / "unresolved.md").write_text("\n\n".join(sections) + "\n")


if __name__ == "__main__":
    main()
