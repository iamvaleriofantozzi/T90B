# Interfaccia Grafica e Menu del Firmware Originale T90B

Documentazione ricostruita dall'immagine applicativa originale (`analysis/t90-app.bin`, base `0x08005000`), dal decompilato [t90-pseudocode.c](../../analysis/t90-pseudocode.c) e dalle tabelle [ui-dispatch-runtime.tsv](ui-dispatch-runtime.tsv) e [ui-pointer-table.tsv](ui-pointer-table.tsv).

---

## 1. Display, Framebuffer e Pipeline di Rendering

| Parametro | Valore / Indirizzo | Evidenza nel firmware |
|---|---|---|
| Risoluzione | `160 × 40` px (`0xa0 × 0x28`) | `FUN_08011214`, `FUN_08011370` |
| Formato pixel | RGB565 (`16 bit/pixel`, `6400` pixel = `12800` byte) | DMA count `0x1900` halfword in `FUN_08011370` |
| Bus display | SPI1 + DMA (`FUN_080110a8`, `FUN_08011370`, `FUN_08011400`) | Flush completo e flush parziale `FUN_0801141c(x0, x1)` |
| Frequenza UI | **20 Hz (ogni 50 ms)** | Loop principale `FUN_080115f4` (`0x31 < tick - last`) → `ui_dispatch` (`0x08014ce0`) → `FUN_08011370()` → `iwdg_reload` |
| Rotazione 0° / 180° | Software nel framebuffer (`FUN_08011330`, `FUN_08009a24`) | Impostata da `FUN_080114f4(rota_state)`. In modalità `Auto` (`+0x53 == 2`), `FUN_0800d2bc` legge l'accelerometro e commuta dopo 6 campioni concordi |
| Retroilluminazione | Controllo ON/OFF | `FUN_08010f44(1)` / `FUN_08010f44(0)` |

### Primitive grafiche principali

- `FUN_08011214(x, y, w, h, color)` — rettangolo pieno con clipping
- `FUN_080105a4(x, y, w, h, r, fill, border_col, fill_col)` — rettangolo arrotondato (pieno o bordo)
- `FUN_08010952(x, y, len, color)` / `FUN_08010972(x, y, len, color)` — linea orizzontale / verticale
- `FUN_0801103a(x, y, w, h, rgb565_ptr)` — blit immagine RGB565 (logo, icone menu 16×16)
- `FUN_08011138(x, y, mono_ptr, w, h, fg, bg)` — blit bitmap monocromatica 1-bpp (icone stato, simboli, frecce)
- `FUN_08011294(x, y, w, h, fg, bg, match_col)` — inversione cromatica di regione (usata per evidenziare il campo in modifica)
- `FUN_08010f64(...)` — scroll verticale di una regione del framebuffer (animazione cifre in stato `3`)
- `FUN_080114d8(x, y, w, h)` — impostazione finestra di clipping
- `FUN_08011500(x, y, str, font, fg, bg)` / `FUN_080115a0(x, y, w, str, font, fg, bg)` — testo ASCII/GBK (allineato a sinistra / centrato)

### Palette colori RGB565

| RGB565 | RGB888 / Hex | Uso nell'interfaccia |
|---|---|---|
| `0x0000` | `#000000` Nero | Sfondo schermo |
| `0x2945` | `#292829` Grigio scuro | Box `SET`, pillole `V/A/W`, badge stato |
| `0x04DC` | `#0099e6` Azzurro | Setpoint, barra potenza, testi valori, radio button, preset attivo |
| `0xFC63` | `#ff8d18` Arancione | Temperatura principale, barre titolo, voce menu selezionata, icona movimento |
| `0xC638` | `#c5c6c5` Grigio chiaro | Bordi, etichette secondarie, valori `V/A/W` |
| `0x8430` | `#838583` Grigio medio | Traccia scrollbar |
| `0xD69A` | `#d5d2d5` Grigio chiaro | Cursore scrollbar |
| `0xF800` | `#ff0000` Rosso | Icona/testi errore, freccia animata avvio |
| `0xFFFF` | `#ffffff` Bianco | Schermata factory/QC test |

### Font bitmap in Flash

| Indirizzo | Glifi ASCII | Glifi CJK (GBK) | Uso tipico |
|---|---|---|---|
| `0x0801681c` | `6 × 8` | — | Indicatori preset `1 2 3` |
| `0x0801736c` | `7 × 9` | — | Pillole `V`, `A`, `W` |
| `0x080172b0` | `8 × 16` | — | Valori numerici negli editor, `Vol Info`, `Ver Info` |
| `0x080192e4` | `8 × 16` | `16 × 16` | Voci di menu, intestazioni, messaggi errore/stato |
| `0x080174a8` | `11 × 14` | — | Setpoint nella schermata principale |
| `0x08017814` | `23 × 28` | — | Temperatura reale grande (Main, Setpoint, Sleep/Stdby) |

---

## 2. Gestione Tasti e Input

Due tasti fisici scansionati da `FUN_08010e50` tramite la macchina a stati `FUN_08010d40`:

- **Tasto A** (`FUN_08010f24`, configurazione modalità `FUN_08010ef4`): decremento / su / annulla / esci.
- **Tasto B** (`FUN_08010f34`, configurazione modalità `FUN_08010f08`): incremento / giù / entra / conferma.
- **Scambio a 180°**: quando `settings[+0x52]` (`rota_state`) è diverso da `0`, le schermate scambiano logicamente i valori letti da A e B in modo che direzione fisica e grafica restino coerenti.
- **Modalità tasti**:
  - `mode = 1` (usata in stato `3`, regolazione temperatura): pressione con **auto-repeat** continuo.
  - `mode = 2` (usata in tutte le altre schermate): `1` = pressione breve (al rilascio), `2` = pressione lunga (~55 tick di scansione).
- **Combo simultanea `A+B`**: rilevata in `FUN_08010e50`, imposta entrambi gli eventi a `1` (`A == 1 && B == 1`) e blocca ulteriori eventi fino al rilascio completo di entrambi i tasti.

---

## 3. Macchina a Stati UI (`ui_dispatch` @ `0x08014ce0`)

Il dispatcher carica l'indice di stato corrente e invoca il puntatore Thumb corrispondente nella tabella `0x08016100`–`0x0801613f`. Il cambio di stato avviene tramite `FUN_08014cd4(new_state)`. L'inizializzazione iniziale è in `FUN_08014cfc`: se il byte di fabbrica `+5 != 0xAA` parte dallo stato `12` (Factory Test), altrimenti da `0` (Logo) o `1`/`9`.

| Stato | Slot tabella | Routine | Nome schermata | Ruolo e transizioni |
|---:|---|---|---|---|
| `0` | `0x08016100` | `0x08013a74` | **Logo / Boot Splash** | Scorre il logo da `y=-39` a `y=0` (passo 2 px), attende 25 tick (~1,25 s). Se fault (`+0x1c & 0x7f`) → `9`; se `P_O Heat == 0` (Turn On) → `1`; altrimenti → `13`. `A+B` → `4` (Menu). |
| `1` | `0x08016104` | `0x08013bb4` | **Main UI (Lavoro)** | Schermata operativa principale (layout sotto). `A`/`B` breve → `3`; `A` lungo → cicla preset `1→2→3` (con beep `FUN_0800e27c(4)`); `B` lungo → `10` (Standby manuale); `A+B` → `4` (Menu). Fault → `9`; Sleep/Stdby automatico (`+0x2a == 3 || 4`) → `10`. |
| `2` | `0x08016108` | `0x00000000` | *(Slot NULL)* | Non usato; non deve mai essere selezionato. |
| `3` | `0x0801610c` | `0x08014d68` | **Regolazione Setpoint** | Box `SET` + cifra target `23×28` con **scroll verticale animato solo sulle cifre modificate** (`FUN_08010f64` + `FUN_0801141c`) + slider inferiore (`80–450 °C` o equivalente `°F`). Tasti in `mode=1`: `A` −`temp_step`, `B` +`temp_step`. `A+B` o timeout 50 tick (~2,5 s) salva setpoint e torna a `1`. |
| `4` | `0x08016110` | `0x08014a84` | **Menu / Sottomenu** | Wrapper che chiama `FUN_08011c54` (dettagliato in §4). |
| `5` | `0x08016114` | `0x08015704` | **1. Vol Info** | Sx: icona porta + badge protocollo (`PD`/`QC`/`DC`) + 3 box con `V`, `A`, `W` negoziati (`---A`/`---W` se non PD). Dx: box grande con tensione ingresso reale (`%d.%dV`) e resistenza punta (`%3.1fR`). Qualsiasi tasto → `4`. |
| `6` | `0x08016118` | `0x080141a4` | **Editor Numerico Generico** | Header arancione (`y=0..19`) + valore centrato azzurro (`y=22`) + frecce sx/dx `16×16` (lampeggio arancione per 3 tick). `A`/`B` breve regolano; `B` lungo o timeout 100 tick (~5 s) salva (`FUN_0800f08c`) → `4`; `A` lungo annulla → `4`. Per `Sleep/Stdby Time`: step adattivo (`1s` ≤10s, `10s` ≤60s, `60s` >60s) e valore `9999` visualizzato come `--` (disabilitato). |
| `7` | `0x0801611c` | `0x08013638` | **14. Restore** | Due pulsanti affiancati `Cancel` / `OK` (localizzati). `A`/`B` spostano la selezione; `B` lungo su `OK` ripristina i default (`FUN_0800f070`), ricalcola i limiti potenza (`FUN_08015dd8`), aggiorna i menu (`FUN_080117d8`) e mostra `Success!` per 30 tick (~1,5 s) prima di tornare a `4`. Timeout 80 tick (~4 s). |
| `8` | `0x08016120` | `0x080155a8` | **15. Ver Info** | Header arancione + `T90<A\|B\|C> V<x>.<y>.<z>` (versione default nel fw `108` → `V1.0.8`). Qualsiasi tasto o timeout 100 tick (~5 s) → `4`. |
| `9` | `0x08016124` | `0x08015b24` | **Schermata Fault** | Spegne immediatamente il riscaldatore (`FUN_0800f1cc(0)`). Icona avviso rossa `28×28` + messaggio localizzato (priorità sotto). `A+B` apre comunque il menu (`4`); al rientro del fault torna a `1` (se `P_O Heat == 0`) o `13`. |
| `10` | `0x08016128` | `0x08014a8c` | **Sleep / Standby** | Pillola `Sleep` o `Stdby` in alto a sinistra + temperatura attuale grande `23×28` + `°C`/`°F` + icona movimento. In `Sleep` (`+0x2a == 3`) imposta target = `sleep_temp`; in `Stdby` (`+0x2a == 2 || 4`) spegne il riscaldatore. Risveglio su movimento o pressione breve `A`/`B` (in standby manuale) → `1`; passaggio a `ShutDown` (`+0x2a == 5`) → `11`; fault → `9`. |
| `11` | `0x0801612c` | `0x08014030` | **ShutDown / Display Off** | Mostra icona `29×27` + `ShutDown` per 40 tick (~2 s), poi pulisce lo schermo e spegne la retroilluminazione (`FUN_08010f44(0)`). Movimento o pressione breve `A`/`B` riaccende il display e riparte da `0`. |
| `12` | `0x08016130` | `0x0801388c` | **Factory / QC Test** | Mostra bordo bianco `160×40` con `T12 <temp>` e `IN <V>V NTC <temp>` oppure `ERROR <codici>`. `A+B` imposta flag `+5 = 0xAA`, salva in flash (`FUN_08012418`) e passa a `0`. |
| `13` | `0x08016134` | `0x080145b0` | **Attesa Avvio (`P_O Heat` Off)** | Bitmap "premi tasto A" (variante dedicata se ruotato 180°) + freccia rossa animata `y=0 ↔ y=5` ogni 6 tick + icona movimento (che resetta il timer). `A` breve → `1`; `A+B` → `4`; timeout 200 tick (~10 s) → `11`; fault → `9`. |
| `14` | `0x08016138` | `0x08014720` | **8. Power Trim** | Header arancione + `%dV %d.%dA %dW OK` per il profilo `Work Vol` attivo. 3 campi selezionabili (`decine A`, `decimi A`, `OK`), sottolineati in navigazione e invertiti (`FUN_08011294`) in editing, range `0.1–6.0 A`. `B` lungo entra/esce editing o conferma su `OK` (salva + ricalcola PWM `FUN_08015dd8`); `A` lungo annulla → `4`. Timeout 100 tick (~5 s) salva → `4`. |
| `15` | `0x0801613c` | `0x0801525c` | **3. Temp Preset** | Header arancione + 3 temperature `%3d %3d %3d °C/°F`. `A`/`B` spostano la sottolineatura tra i 3 slot; `B` lungo entra/esce editing (blocco invertito, step `±10 °C`, range `80–450 °C`); `A` lungo (fuori editing) o timeout 100 tick (~5 s) salva → `4`. |

### Layout della Schermata Principale (Stato `1`, `0x08013bb4`)

```text
x: 0       37 41                111   125        159
  +----------+----------------------+--------------+ y=0
  |   SET    |                      |  [ %3dV ]    | y=12
  |   350    |      350  °C    [M]  |  [ %3.1fA ]  | y=26
  |  1 2 3   |  [===== PWM =====]   |  [ %3dW ]    | y=39
  +----------+----------------------+--------------+
```

- **Colonna sinistra (`x=0..36`)**: sfondo `0x2945`, icona `SET` (`28×8`), setpoint (`11×14`, azzurro `0x04DC`), indicatori preset `1`, `2`, `3` (`6×8`, attivo in azzurro).
- **Area centrale (`x=39..122`)**: temperatura reale (`23×28`, arancione `0xFC63`), icona `°C`/`°F` (`10×12`), icona movimento `8×8` a `(115, 1)`, barra potenza PWM (`82×7`, `x=39..122, y=33..39`, riempimento proporzionale a `duty_pct`).
- **Colonna destra (`x=125..159`)**: 3 pillole arrotondate (`35×12`, `0x2945`) con tensione (`%3dV`), corrente (`%3.1fA`) e potenza (`%3dW`) in font `7×9`.

### Priorità dei Fault (Stato `9`, `0x08015b24`)

La schermata controlla il registro fault (`+0x1c`) nell'ordine seguente e mostra il primo errore attivo (tabella stringhe `0x08016050`–`0x080160bf`):

1. Bit `0x20` → `MOS Err`
2. Bit `0x08` → `Sen Err`
3. Bit `0x04` → `NTC Err`
4. Bit `0x02` → `Vol low`
5. Bit `0x10` → `Short-Circ`
6. Bit `0x40` → `Tip Res-Err`
7. Bit `0x01` → `No tip`

---

## 4. Sistema di Menu (`FUN_08011868` + `FUN_08011c54`)

### Rendering e navigazione

- **Lista a 2 righe** (`FUN_0800cac4`): altezza 20 px per riga (`y=0` e `y=20`), con **scrollbar verticale** a `x=152..156` se la lista ha più di 2 voci.
- **Menu principale** (`FUN_0800c938`): icona **16×16 RGB565** (`0x08019954`–`0x0801b754`, 512 byte per voce) + testo (`8×16`/`16×16`). Voce attiva evidenziata da pillola arancione `0xFC63` con testo nero; inattiva in azzurro `0x04DC` su nero.
- **Sottomenu** (`FUN_0800c754`): radio button monocromatico `16×16` azzurro (vuoto/pieno) al posto dell'icona colorata.
- **Comandi**:
  - `A` breve: voce precedente (con wrap-around)
  - `B` breve: voce successiva (con wrap-around)
  - `B` lungo: entra nella voce / conferma opzione sottomenu
  - `A` lungo: torna al menu padre (o esce dal menu principale)
  - **Timeout inattività**: 100 tick (~5 s) chiude il menu ed esce (`FUN_0800ae2c`).
- **Localizzazione (4 lingue)**: `0 = 简体中文` (`0x08016340`), `1 = English` (`0x08016380`), `2 = 繁體中文` (`0x080163c0`), `3 = 日本語` (`0x08016400`), aggiornate dinamicamente da `FUN_0800cbd4`.

### Le 16 voci del menu principale

| # | Etichetta (EN) | Icona RGB565 | Callback / Sottomenu | Destinazione / Comportamento | Range / Opzioni | Default (`0x08015f68`) |
|---:|---|---|---|---|---|---|
| `0` | `0.Exit` | `0x08019954` | `FUN_0800ae2c` | Esce dal menu → stato `1` (o `13`/`9`) | — | — |
| `1` | `1.Vol Info` | `0x08019b54` | `FUN_0800b200` | Stato `5` (sola lettura) | Protocollo, V/A/W, Vin, R tip | — |
| `2` | `2.Temp Step` | `0x08019d54` | `FUN_0800b19c` | Stato `6` (`settings[+0x08]`) | `5` – `50`, step `1` | `10` |
| `3` | `3.Temp Preset` | `0x08019f54` | `FUN_0800b18c` | Stato `15` (`settings[+0x18..0x20]`) | 3 preset, `80` – `450 °C`, step `10 °C` | `200 / 350 / 450 °C` |
| `4` | `4.Sleep Temp` | `0x0801a154` | `FUN_0800b0e4` | Stato `6` (`settings[+0x0c]`) | `80` – `300 °C`, step `10 °C` | `200 °C` |
| `5` | `5.Sleep Time` | `0x0801a354` | `FUN_0800b138` | Stato `6` (`settings[+0x10]`) | `0` – `1200 s` (20M) + `--` (`9999`), step adattivo | `180 s` (`3M`) |
| `6` | `6.Stdby Time` | `0x0801a554` | `FUN_0800b090` | Stato `6` (`settings[+0x14]`) | `0` – `1200 s` (20M) + `--` (`9999`), step adattivo | `180 s` (`3M`) |
| `7` | `7.Work Vol` | `0x0801a754` | Sottomenu → `FUN_0800d27c` | `settings[+0x2c]` + ricalcolo limiti | 8 profili (`Auto`, `28V/5A 140W`, `20V/5A 100W`, `20V/3.3A 65W`, `12V/3.0A 36W`, `12V/2.0A 24W`, `9V/3.0A 27W`, `9V/2.0A 18W`); 6 profili (senza 140W/100W) se variante hw `0` | `0` (`Auto`) |
| `8` | `8.Power trim` | `0x0801a954` | `FUN_0800b080` | Stato `14` (`settings[+0x30 + work_vol*4]`) | `0.1` – `6.0 A` (in decimi di A: `1` – `60`) | `[50, 50, 50, 33, 30, 20, 30, 20]` |
| `9` | `9.Temp Unit` | `0x0801ab54` | Sottomenu → `0x0800d25c` | `settings[+0x51]` | `0 = (°C)`, `1 = (°F)` | `0` (`°C`) |
| `10` | `10.Language` | `0x0801ad54` | Sottomenu → `FUN_0800c918` | Blocco separato `+0x04` + `FUN_0800cbd4` | `0 = 简体中文`, `1 = English`, `2 = 繁體中文`, `3 = 日本語` | blocco persistente separato |
| `11` | `11.Rota 180°` | `0x0801af54` | Sottomenu → `FUN_0800cc88` | `settings[+0x52]` / `settings[+0x53]` | `0 = Rota 0°`, `1 = Rota 180°`, `2 = Auto` | `0` (`Rota 0°`) |
| `12` | `12.P_O Heat` | `0x0801b154` | Sottomenu → `FUN_0800cc68` | `settings[+0x50]` | `0 = Turn On` (scalda all'avvio), `1 = Turn Off` (attende tasto A) | `1` (`Turn Off`) |
| `13` | `13.Temp Calib` | `0x0801b354` | `FUN_0800afcc` | Stato `6` (`settings[+0x24]`) | `-50` – `+50 °C`, step `1` | `0 °C` |
| `14` | `14.Restore` | `0x0801b554` | `FUN_0800b020` | Stato `7` | `Cancel` / `OK` | — |
| `15` | `15.Ver Info` | `0x0801b754` | `FUN_0800b1f0` | Stato `8` (sola lettura) | `T90<A\|B\|C> V1.0.8` | `108` (`V1.0.8`) |

---

## 5. Layout della Struttura Impostazioni (`0x70` byte, default @ `0x08015f68`)

| Offset | Tipo | Campo | Default |
|---:|---|---|---|
| `+0x00` | `uint32` | Checksum / validazione (`FUN_0800f08c`) | calcolato su `0x6c` byte da `+0x04` |
| `+0x04` | `uint16` | Versione firmware (`108` = `V1.0.8`) | `108` |
| `+0x08` | `int32` | `temp_step` | `10` |
| `+0x0c` | `int32` | `sleep_temp` (°C) | `200` |
| `+0x10` | `int32` | `sleep_time` (s, `9999` = off) | `180` |
| `+0x14` | `int32` | `stdby_time` (s, `9999` = off) | `180` |
| `+0x18` | `int32[3]` | `temp_preset[0..2]` (°C) | `200, 350, 450` |
| `+0x24` | `int32` | `temp_calib` (°C) | `0` |
| `+0x2c` | `uint8` | `work_vol` (indice profilo alimentazione) | `0` (`Auto`) |
| `+0x30` | `int32[8]` | `power_trim[0..7]` (decimi di A) | `50, 50, 50, 33, 30, 20, 30, 20` |
| `+0x50` | `uint8` | `po_heat` (`0` = Turn On, `1` = Turn Off) | `1` |
| `+0x51` | `uint8` | `temp_unit` (`0` = °C, `1` = °F) | `0` |
| `+0x52` | `uint8` | `rota_state` (`0` = 0°, `1` = 180°) | `0` |
| `+0x53` | `uint8` | `rota_mode` (`0` = fisso, `2` = Auto) | `0` |
