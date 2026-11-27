# Riepilogo build sperimentale — ALIENTEK T90B

**Stato:** Build sperimentale con riscaldamento **DISABILITATO** (`T90B_HEATER_ENABLED=0`).  
**Sblocco bootloader completato:** tramite dump in sola lettura via `t90_msdmem` (`FLASH.BIN`) e disassemblaggio del bootloader (`0x080031c0` / `0x08002fb0`), è stato individuato il record di validazione da 8 byte riservato a **`0x08005800`** (`00 00 00 00 00 FF FF FF`). La sezione `.boot_meta 0x08005800` è ora riservata in `firmware/linker/t90b.ld`.

## Artefatti e riproducibilità

- **ELF**: `firmware/build/t90b.elf`
- **BIN**: `firmware/build/t90b.bin`
- **ATK**: `firmware/build/t90b.atk` (generato da `firmware/tools/pack_atk.py`)
- **Flasher HID macOS**: `firmware/tools/flash_atk.py` (`VID 0x19F5`, `PID 0x3245`, seriale `ATK-T90`)
- **SHA-256 (`t90b.bin`, verificato in `verify_differential.py`)**: `a4622399c295937aef59dab61430ebbf09e7cc5832e8336daecadcb9305b7bd1`
- **Toolchain**: `arm-none-eabi-gcc (GCC) 16.2.0` (`firmware/toolchain.lock`)
- **Base vettori**: `0x08005000` (`.isr_vector` a 82 voci verificata con `arm-none-eabi-objdump -h`)

## Comandi di build e verifica

```sh
make -C firmware clean all
shasum -a 256 firmware/build/t90b.bin
make -C firmware test
uv run --with unicorn==2.1.4 python3 firmware/sim/verify_differential.py
uv run --with hidapi python3 firmware/tools/flash_atk.py --info
```

## Pinout e protocollo bootloader verificati

- **Display LCD 40×160 (GC9106/GC9107, `SPI1`)**: `PB3` (`SPI1_SCK` AF1), `PB5` (`SPI1_MOSI` AF0), `PA10` (`CS`), `PD0` (`DC`), `PA6` (`BL` active-low).
- **Tasti**: il candidato usa `PA15` per A e `PB4` per B, entrambi active-low. Risposta sul dispositivo confermata dall’utente.
- **ADC1**: `PA1..PA5` (`ADC_IN2..6`), con `ADC_IN5` (`PA4`) per `Vin`, `ADC_IN4` (`PA3`) per NTC, `ADC_IN6` (`PA5`) per punta.
- **Heater PWM**: `PA7` (`TIM1_CH1` AF5), forzato a `TIM1_CCDAT1=0` e `TIM1_BKDT.MOE=0` con `T90B_HEATER_ENABLED=0`.
- **Protocollo USB HID bootloader (`0x19F5:0x3245`)**: report 64 byte (prefisso `0x00` su macOS), richiesta `0xAF`, risposta `0xDF`, checksum a 1 byte `(-sum(bytes)) & 0xFF`, ACK `0x00` = OK, chunk da 32 byte, payload XOR `0xFF`, header 13 byte.

## Funzionalità dimostrate e non dimostrate

- **Dimostrate (host / Unicorn / hardware HID)**:
  - Avvio sicuro da `0x08005000` in Unicorn, inizializzazione `.data`/`.bss`, azzeramento `TIM1_CCDAT1` e `TIM1_BKDT.MOE` in `board_init()`, reload IWDG (`0xAAAA`).
  - Macchina a stati UI (`ui_step`): gate fabbrica (`0xAA`), boot logo, standby, menu 16 voci, setpoint, sleep/wake, gestione guasti e blocco riarmo in `heater.c`.
  - Flash e ripristino reale su T90B (`Ver Info` originale `v 1.1.4`) di `t90.atk` tramite `firmware/tools/flash_atk.py` su macOS.
- **Bloccate / Non dimostrate su hardware fisico**:
  - Esecuzione suite `renode-test firmware/sim/t90b.robot` (`renode` non presente sull'host macOS).
  - Restano aperte le prove termiche e la verifica delle altre schermate e impostazioni.

## Backup e prova LCD

Il bootloader originale da 20 KiB è in `analysis/backup/t90b-bootloader-08000000.bin` e coincide con l'inizio del dump flash. Il pacchetto ufficiale ripristinabile è `t90.atk`. La sua applicazione decodificata coincide con `analysis/t90-app.bin`. Il backup delle preferenze è in `analysis/backup/t90b-prefs-0801f000.bin`.

`make -C firmware lcd-test` genera `firmware/build/lcd-test/t90b.atk` con riscaldatore disabilitato. La build disegna tre rettangoli RGB e un riferimento bianco asimmetrico su fondo nero. Se le forme sono leggibili, si passa al disegno dei glifi e agli aggiornamenti della UI. Se compaiono ancora linee, si confrontano inizializzazione, finestre LCD e trasferimento dei pixel con le tracce originali.

`python3 firmware/sim/verify_differential.py firmware/build/lcd-test/t90b.bin` verifica lo stato sicuro di TIM1 all'avvio in Unicorn.

Il 27 novembre 2026 il bootloader HID ha confermato il flash del test LCD con `SET_BOOT: 00`. La foto mostra bande blu lungo l’asse lungo del display, senza i rettangoli attesi.

La seconda build riproduce la configurazione SPI e la pausa iniziale del riferimento. Invia comandi in frame da 8 bit e pixel RGB565 in frame da 16 bit, come nella traccia `reset-hse-ready-virtual-tick-spi.tsv`. I test host e il controllo TIM1 in Unicorn passano. Dopo il flash della seconda build il 27 novembre 2026, l’utente ha confermato sul T90B la presenza dei tre rettangoli RGB e del riquadro bianco. La visualizzazione del pattern è verificata su hardware.

La prima prova della UI con pixel a 16 bit ha mostrato glifi deformati. La build successiva compone un fotogramma RGB565 da 12.800 byte in RAM e lo invia in un’unica finestra LCD, seguendo l’ordine del firmware originale. Build, test host, controllo TIM1 in Unicorn e flash HID completati. L’utente ha confermato sul T90B la leggibilità delle righe `25` e `HEATER OFF`. L’apertura del menu con A+B, lo scorrimento e l’uscita sono stati osservati sul dispositivo. L’utente ha confermato il comportamento atteso dei tasti.

Per la verifica termica a freddo, un timeout ADC ora imposta `FAULT_SENSOR` e mostra `SENSOR ERROR`. Build a riscaldatore disabilitato verificata in Unicorn e caricata via HID. La conversione della temperatura è ancora approssimativa; la validazione termica rimane aperta.

Con il trigger ADC software abilitato e selezionato, l’utente ha osservato `25` e `HEATER OFF`. La conversione non ha segnalato timeout durante l’osservazione. La build `make -C firmware adc-test` mostra i conteggi grezzi di VIN, NTC e punta, con riscaldatore disabilitato. La verifica dei campioni sul dispositivo è ancora aperta.

La build diagnostica ADC è stata caricata sul T90B via HID. Prima del flash l’utente ha osservato `VOL LOW` intermittente con un alimentatore nominale da 60 W. Sono da confrontare i conteggi grezzi sul Mac e sull’alimentatore, insieme alla tensione USB-C se disponibile.

Prima prova ADC a freddo: l’utente ha riportato valori grezzi tra 0 e 2 sia sul Mac sia sull’alimentatore da 60 W. La build successiva imposta esplicitamente i clock ADC, attende RDY, calibra se CALFACT è zero e usa i canali regolari 3, 5 e 6 osservati nella traccia originale. Riscaldatore disabilitato. Letture da verificare sul dispositivo.

Nella foto `IMG_0723.HEIC` della diagnostica regolare/iniettata, il canale 2 mostra `610/610` e il 3 `1914/1919`; i canali 0, 1, 4, 5 e 6 mostrano `0/0`. L’alimentazione della foto è da confermare. Il canale 2 è un candidato per VIN. Da confrontare con una seconda acquisizione e con la tensione USB-C effettiva prima di cambiare la mappatura.

Confronto fotografico confermato (regolare/iniettato): su Mac, CH2 `610/610` e CH3 `1914/1919`; su alimentatore da 60 W, CH2 `0/1051` e CH3 `1916/1910`; gli altri canali sono `0/0` in entrambe le foto. La tabella nel binario originale a `0x0801651c` mappa l’indice 3 di `FUN_0800df14` al canale 2, letto in modalità iniettata. Con la formula di `FUN_0800dec0(3)` i due campioni iniettati danno 5269 e 9075 mV stimati. Tensione reale e causa dell’intermittenza ancora da verificare.

La foto `IMG_0725.HEIC` mostra 5,23 V sul misuratore e CH2 `602/602` sul T90B, pari a 5,192 V stimati (scarto 38 mV). L’alimentatore da 60 W non funzionava con il misuratore inserito; il campione a circa 9,08 V resta senza confronto indipendente. La nuova build normale usa CH2 iniettato per il controllo di tensione e tratta anche zero come tensione sotto soglia. Build, verifica PWM in Unicorn e flash passati. L’utente ha confermato `VOL LOW` sul Mac e la sua assenza con l’alimentatore da 60 W collegato direttamente.

La verifica a freddo della presenza della punta sul T90B è passata. Con l’alimentatore da 60 W, l’utente ha confermato `HEATER OFF` con punta inserita e `NO TIP` con punta rimossa. Il candidato usa CH4 iniettato e la soglia del firmware originale. La temperatura e la risposta termica restano da validare.

Diagnostica temperatura a freddo caricata via HID con riscaldatore disabilitato. Con punta inserita, l’utente ha osservato `NTC C 20` e `TIP ADC 0`. La tabella NTC del riferimento è a `0x08016236`. Nel ramo basso della conversione della punta (`FUN_0800cd74`), a ingresso zero il termine interpolato si annulla. Il firmware di riferimento applica poi la compensazione NTC in `FUN_08012f5c`. La risposta del canale punta a una variazione termica indipendente resta da osservare.

Durante il riscaldamento passivo con riscaldatore disabilitato, l’utente ha osservato `NTC C 28` e `TIP ADC 40`, rispetto a `20` e `0` a freddo. Questo conferma una variazione del segnale ADC della punta. La temperatura assoluta della punta resta da calibrare.

Dopo il riscaldamento passivo, `TIP ADC` è sceso gradualmente da 40 a 0 durante il raffreddamento. Risposta del sensore della punta verificata nel ciclo a freddo.

### Diagnostica in °C con riscaldatore disabilitato

Il flash HID della diagnostica è riuscito. A riposo il display indicava NTC 27 °C, punta 27 °C, ADC 0 e gruppo 1. Dopo circa due minuti di contatto diretto tra punta e pelle sotto l’ascella indicava NTC 28 °C, punta 33 °C, ADC 50 e gruppo 1. L’utente ha stimato circa 36 °C per la punta. Lo scarto indicativo è quindi di circa −3 °C. La misura di riferimento è approssimativa e l’offset è stato mantenuto. La conversione alle temperature di saldatura resta da verificare.

Il ciclo principale registra il tempo dell’ultima lettura valida dopo le conversioni ADC. Il controllo del riscaldatore blocca il PWM in presenza di un guasto. Con controllo armato, un intervallo superiore a 500 ms causa il blocco anche se nel frattempo arriva un nuovo campione valido. I test host verificano i casi di sensore in errore, NTC fuori intervallo, punta assente, tensione insufficiente e ritardo. La build compilata mantiene il riscaldatore disabilitato. Restano da verificare sul banco il comportamento temporale dell’uscita PWM e la risposta termica.

### Verifica a display dei blocchi del riscaldatore

Con la build `fault-test` e il riscaldatore disabilitato, il Mac ha dato `FAULT 8 / TRIP 8`. Con l’alimentatore da 60 W è comparso `FAULT 0 / TRIP 8`. Il codice 8 era memorizzato anche all’avvio su questo alimentatore, coerentemente con una tensione inizialmente sotto soglia. Premendo A con letture valide è comparso `ARMED / FAULT 0 / TRIP 0`. Premendo B, che simula un intervallo di 600 ms tra campioni, è comparso `DISARMED / FAULT 0 / TRIP 2`. A punta rimossa il display indicava `FAULT 1 / TRIP 9`. Dopo il reinserimento indicava `FAULT 0 / TRIP 9`. Premendo A è tornato a `ARMED / FAULT 0 / TRIP 0` con `HEATER OFF`. Il valore 9 combina i bit 1 (punta assente) e 8 (tensione insufficiente). La prova verifica il rilevamento e la memorizzazione dei guasti nel firmware. La verifica temporale dell’uscita fisica PWM resta aperta.

### Confronto simulato della conversione della punta

La funzione C della build diagnostica è stata compilata per l’host e confrontata con un modello dell’interpolazione originale, ricavato dalla routine a `0x0800cd74`, dai punti della curva 1 a `0x08015ee2` (secondo blocco) e dalla compensazione in `0x08012f5c`. Il modello usa le preferenze salvate di questa unità, con riferimento 33 °C e offset 0 °C. Sono stati verificati 523 250 casi combinando ADC 0–4024 (prima della soglia punta assente) e NTC da −30 a 99 °C. Le letture intere coincidevano in 518 861 casi. Nei 4 389 casi rimanenti lo scarto era di un grado. A NTC 27 °C, esempi coincidenti sono ADC 1000 → 158 °C, ADC 2000 → 287 °C e ADC 3000 → 416 °C. Il confronto riguarda la conversione numerica. L’accuratezza fisica alle temperature di saldatura resta da misurare.

### Conversione nel firmware normale

La schermata principale usa la conversione della punta compensata dall’NTC. In Unicorn, con NTC a 27 °C, il firmware normale ha mostrato 27 °C con ADC 0 e 158 °C con ADC 1000. Sono state verificate anche le schermate `VOL LOW`, `NO TIP` e `SENSOR ERROR`. Dopo il flash HID della build con riscaldatore disabilitato, l’utente ha osservato 28 °C nella prova a freddo con l’alimentatore da 60 W.

La temperatura ambiente riferita dopo la prova era circa 18 °C. Lo scarto indicativo di +10 °C lascia aperta la verifica a freddo. La schermata normale mostra la stima della punta. Per attribuire lo scarto occorre distinguere la lettura NTC dal contributo ADC della punta a equilibrio termico.

Con la diagnostica ricaricata, la prima lettura riportata è NTC 27 °C, punta 27 °C, ADC punta 0 e gruppo 1. Con ADC punta a zero lo scarto rispetto ai circa 18 °C ambientali è già presente nella lettura NTC. La routine originale `0x0800e0ec` usa la tabella a `0x08016236` con interpolazione in decimi di grado. Resta da confrontare la lettura NTC dopo stabilizzazione.

Durante la prova con punta in acqua riferita a circa 90 °C, l’utente ha osservato NTC 28 °C, punta 75 °C e ADC punta 390. La lettura è coerente con la curva 1 e la compensazione NTC. La differenza indicativa di 15 °C confronta la stima della punta con la temperatura riferita del bagno. La temperatura effettiva della superficie della punta e il raggiungimento dell’equilibrio termico restano da verificare.

Dopo cinque minuti in acqua a circa 90 °C, la diagnostica mostrava NTC 28 °C, punta 78 °C e ADC punta 410. L’utente ha confermato 88 °C come stima della temperatura della punta per questa prova. Lo scarto del display rispetto a tale stima è −10 °C.

### Confronto a caldo dopo il passaggio dal firmware originale

L’utente ha raggiunto la temperatura indicata dal firmware originale, fatto il flash della diagnostica e letto il display dopo circa 5–10 secondi. Le differenze sono calcolate come lettura della diagnostica meno temperatura di partenza sul firmware originale. L’NTC è stato riportato per i primi due punti.

| Originale (°C) | NTC (°C) | Diagnostica (°C) | ADC punta | Differenza (°C) |
| ---: | ---: | ---: | ---: | ---: |
| 80 | 30 | 72 | 355 | −8 |
| 100 | 30 | 92 | 500 | −8 |
| 150 | | 140 | 820 | −10 |
| 200 | | 185 | 1160 | −15 |
| 250 | | 230 | 1460 | −20 |
| 300 | | 280 | 1880 | −20 |
| 350 | | 320 | 2175 | −30 |
| 400 | | 370 | 2530 | −30 |
| 450 | | 415 | 2860 | −35 |

La lettura della diagnostica cresce a ogni punto. Lo scarto include il raffreddamento durante il flash e l’eventuale differenza tra le due conversioni. Il ritardo è stimato e manca una misura termica simultanea, quindi questi dati non determinano una correzione di calibrazione.

Ripetizione del punto a 200 °C. Assumendo campioni a 0, 5 e 10 secondi dalla prima lettura della diagnostica, sono stati osservati 186 °C / ADC 1160, 170 °C / ADC 1050 e 155 °C / ADC 950. Il calo osservato è 31 °C in 10 secondi, pari a 3,1 °C/s in media. A questo ritmo, una discesa da 200 a 186 °C richiederebbe circa 4,5 secondi. Il tempo esatto prima della prima lettura non è stato registrato. L’estrapolazione è indicativa e non determina una correzione di calibrazione.

### Curva originale della punta, gruppo 1

Il firmware originale contiene tre gruppi di 11 punti a partire da `0x08015ee2`. Il T90B in prova ha selezionato il gruppo 1 tramite PA13 e PA14. Il blocco corrispondente inizia a `0x08015f0e`. La routine `0x0800cd74` interpola linearmente fra i punti. Il tratto inferiore parte dal riferimento salvato di 33 °C a 0 mV. La routine `0x08012f5c` aggiunge la compensazione NTC e applica l'offset salvato, pari a 0 °C su questa unità. I valori della tabella precedono la compensazione.

| Segnale punta (mV) | Temperatura tabellare (°C) |
| ---: | ---: |
| 204 | 60 |
| 428 | 102 |
| 708 | 152 |
| 998 | 200 |
| 1273 | 246 |
| 1637 | 304 |
| 1933 | 354 |
| 2239 | 402 |
| 2528 | 452 |
| 2812 | 502 |
| 3136 | 534 |

### Prova a freddo del firmware normale con riarmo manuale

La build normale aggiornata è stata caricata via HID con riscaldatore disabilitato. L’utente ha osservato `HEATER OFF` all’avvio, `NO TIP` rimuovendo la punta e `HEATER OFF` dopo il reinserimento. La sequenza conferma il rilevamento della punta e il ripristino della schermata normale. Il riarmo manuale nel percorso normale è stato verificato con i test host. Lo stato interno di armamento non è esposto in questa schermata.
