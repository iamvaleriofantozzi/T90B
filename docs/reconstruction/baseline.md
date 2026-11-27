# Baseline del firmware applicativo T90B

| File | Byte | SHA-256 |
|---|---:|---|
| `t90.atk` | 96545 | `29afcaca439177bf68cc1bbe3f91aeebfe8159db9916bd999dfa539b1e2c6c8b` |
| `analysis/t90-app.bin` | 96532 | `bc1da48244dddc68dc81d337ca2ef4dda3c477d5853dd6d5853cf4b1b342f125` |

Il contenitore proviene dalla [pagina firmware ALIENTEK Russia](https://alientek.ru/proshivki-dlja-alientek/). Il payload locale coincide con i byte del contenitore dopo l'intestazione di 13 byte, decodificati con XOR `0xff`. Base di caricamento `0x08005000`, SP iniziale `0x20004c70`, vettore di reset Thumb `0x080052cd`.

`wc -l` conferma 416 righe per `analysis/functions.tsv` (intestazione e 415 funzioni) e 17824 righe per `analysis/t90-disassembly.txt`.

Versione firmware installata e revisione della scheda fisica da rilevare sull'esemplare.

## Fonti per la mappa MMIO

- [Manuale NSING N32L40x v2.6.0, tabella 2-1](https://nsing.com.sg/api/dowfilebefore?did=2816), SHA-256 `bbd831c96e30d313791601aa4b96444809ab9d5625113f1a3522f2d6dd7b0f01`.
- [NSING DFP 1.0.2](https://www.keil.arm.com/packs/n32l40x_dfp-nsing/devices/), SHA-256 del pack `25aad277443ce25cb908852f40ddbdf4bb70ca7ef320a40e7b5e0b205ea15259`. File `svd/N32L403.svd`, SHA-256 `b4c21cb7c75955be74b403c0824e72238ff6f8bc16110d59ce12cdd81fc5b681`.

Ghidra 11.4.3 ha ricostruito gli stessi 415 indirizzi in `analysis/T90-work.gpr`. Per rigenerare le tabelle, esportare l'indice dal progetto di lavoro con `ExportT90.java`, convertire il manuale con `pdftotext -layout` ed eseguire `python3 analysis/tools/map_reference.py MANUALE.txt N32L403.svd INDICE.tsv`. Applicare `AnnotateT90.java` al progetto di lavoro passando `docs/reconstruction/registers.tsv`. La mappa identifica le basi del microcontrollore provvisorio. Il pinout e la revisione dell'esemplare restano da verificare.
