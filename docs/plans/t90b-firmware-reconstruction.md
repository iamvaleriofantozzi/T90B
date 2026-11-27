# Piano di ricostruzione del firmware applicativo ALIENTEK T90B

**Versione:** 1.1 · **Data:** 2026-11-27 · **Responsabile del piano:** @planner  
**Stato:** in esecuzione (pronto per T2.3 — driver `board.c`) · **Progresso:** 5/7 attività

## Obiettivo e criteri di completamento

Consegnare codice sorgente C ricompilabile e una build riproducibile del firmware applicativo, con una matrice che dimostri l'equivalenza funzionale rispetto all'esemplare e al binario di riferimento. La compilazione originale ha eliminato informazioni sui simboli e sui tipi. La corrispondenza byte per byte e il recupero del sorgente ALIENTEK sono fuori ambito. Anche bootloader, dati di calibrazione di fabbrica, sblocco della protezione di lettura e scrittura di regioni protette sono fuori ambito.

- [x] Due build pulite con gli stessi input producono lo stesso SHA-256 del payload.
- [ ] Ogni scenario della matrice ha una traccia del riferimento, un risultato del candidato e un esito documentato (`power_loss` e `thermal_response` restano da verificare sul dispositivo).
- [ ] La lettura a freddo (~25 °C, `Vin`, `No tip`) e le soglie pratiche con stagno (150 °C non fonde; 200 °C Sn63/Pb37 o 235 °C SAC305 fonde, con tetto PWM prudente) passano prima di abilitare la piena potenza.
- [x] La revisione testata e le funzionalità non dimostrate sono dichiarate nel riepilogo della build (`docs/reconstruction/release.md`).

## Evidenza iniziale e decisioni

| ID | Evidenza o decisione | Conseguenza |
|---|---|---|
| D1 | Il file locale `t90.atk` ha 96.545 byte, con 13 byte di intestazione e 96.532 di payload. | Usare questo file come riferimento immutabile. |
| D2 | Il progetto esistente è `analysis/T90.gpr`, con dati in `analysis/T90.rep`. La base applicativa è `0x08005000`, lo SP iniziale è `0x20004c70` e il vettore di reset Thumb è `0x080052cd`. | Mantenere base e architettura ARM Cortex-M little-endian. |
| D3 | Ghidra ha esportato 415 funzioni e 17.824 istruzioni. Alcuni salti indiretti restano irrisolti. | Il conteggio è una baseline dell'analisi automatica, non una misura di completezza. |
| D4 | L'N32L403 è riportato nella [discussione hardware IronOS](https://github.com/Ralim/IronOS/issues/2195). La [PR del port T90B](https://github.com/Ralim/IronOS/pull/2219) fornisce riscontri sulle periferiche. | Verificare sigla, pin e revisione prima di attribuire un comportamento al proprio esemplare. Il port può servire da riferimento hardware. |
| D5 | GhidraScript annota i registri con il CMSIS-SVD della revisione verificata. GNU Arm Embedded compila il candidato. Renode esegue scenari ripetibili. | Versioni e digest delle dipendenze vanno registrati prima della prima build del candidato. |
| D6 | Lo schema da riprodurre è il comportamento osservato. | Implementare codice originale da una specifica funzionale tracciata. Usare un nome e una grafica propri. |

Tutte le attività di implementazione sono di competenza dell'esecutore indicato. Aggiornare il checkbox di un'attività soltanto al passaggio del suo criterio. Ogni fallimento conserva i dati raccolti e blocca la fase dipendente. Durata indicativa: alcune settimane, sensibile alla revisione e al grado di copertura delle periferiche.

## Fase 1 — Baseline e mappa

### - [x] T1.1 — Congelare gli input

**Owner:** @developer · **Priorità:** P0 · **Stima:** S · **Update Plan:** ✅

1. Eseguire `shasum -a 256 t90.atk analysis/t90-app.bin`. Il primo digest deve essere `29afcaca439177bf68cc1bbe3f91aeebfe8159db9916bd999dfa539b1e2c6c8b`.
2. Eseguire `wc -l analysis/functions.tsv analysis/t90-disassembly.txt`. Attesi 416 e 17.824, rispettivamente.
3. Creare `docs/reconstruction/baseline.md` con i due digest, le lunghezze, i risultati e il link al [pacchetto ALIENTEK Russia](https://alientek.ru/proshivki-dlja-alientek/). Registrare versione e revisione del dispositivo solo se osservate sull'esemplare.
4. Verificare che `test -s docs/reconstruction/baseline.md` esca con codice 0. Su digest o conteggio inattesi, interrompere e registrare la divergenza prima di usare gli export.

### - [x] T1.2 — Mappare registri, funzioni e aree irrisolte

**Owner:** @developer · **Priorità:** P0 · **Stima:** XL · **Dipendenza:** T1.1 · **Update Plan:** ✅

1. Creare un progetto Ghidra di lavoro separato `analysis/T90-work.gpr`. Importare `analysis/t90-app.bin` con `BinaryLoader`, base `0x08005000` e linguaggio `ARM:LE:32:Cortex`. Rieseguire `analysis/ghidra/SeedT90.java`.
2. Confrontare gli indirizzi base del CMSIS-SVD con il reference manual N32L403. Importare in Ghidra soltanto riferimenti confermati. Registrare indirizzo, nome, periferica, evidenza e livello di certezza in `docs/reconstruction/registers.tsv`.
3. Creare `docs/reconstruction/functions.tsv` con colonne `address`, `symbol`, `subsystem`, `evidence`, `status`. Usare un record per funzione, con uno stato tra `confirmed`, `candidate`, `unknown`. In `docs/reconstruction/unresolved.md` registrare per indirizzo i salti indiretti, i puntatori a funzione e i confini codice/dati ancora incerti.
4. Confrontare gli indirizzi dell'indice originale con quelli del nuovo indice. Accettazione: 415 indirizzi originali presenti e nessun duplicato. Ogni simbolo confermato ha una catena di chiamate e un riscontro indipendente nei registri, nelle stringhe o nelle tracce osservate. Senza SVD verificato usare il reference manual per annotare solo indirizzi documentati. Conservare `unknown` per ogni corrispondenza non dimostrata.

**Chiusura fase:** ✅ · **Compact Context:** ✅ · **Context Refill:** `docs/plans/t90b-firmware-reconstruction.md`, `docs/reconstruction/baseline.md`, `docs/reconstruction/registers.tsv`, `docs/reconstruction/functions.tsv`, `docs/reconstruction/unresolved.md`.

## Fase 2 — Specifica e ricostruzione

### - [x] T2.1 — Congelare scenari di riferimento

**Owner:** @developer · **Priorità:** P0 · **Stima:** L · **Dipendenza:** T1.2 · **Update Plan:** ✅

1. Creare `docs/reconstruction/behavior.tsv` con colonne `id`, `initial_state`, `stimulus`, `oracle`, `tolerance`, `evidence`. Definire gli ID `boot`, `menu_navigation`, `setpoint_change`, `settings_persistence`, `sleep`, `wake`, `tip_missing`, `sensor_fault`, `power_loss`, `watchdog_reset`, `thermal_response`.
2. Per ogni scenario registrare lo stato iniziale, la sequenza temporizzata d'ingresso e l'uscita osservabile. Eseguire tre ripetizioni sul riferimento per ogni osservazione autorizzata. Per stati, selezioni e ordine degli eventi richiedere uguaglianza. Per tempi e temperature documentare intervallo osservato, risoluzione dello strumento e limiti hardware prima di osservare il candidato.
3. Accettazione: ogni riga ha evidenza ripetibile e unità esplicite. Quando un comportamento non è osservabile in sicurezza, marcare `unverified` e tenerlo aperto nella matrice. Non iniettare guasti su una punta alimentata.

### - [x] T2.2 — Creare il firmware compilabile con uscita termica disabilitata

**Owner:** @developer · **Priorità:** P0 · **Stima:** XL · **Dipendenza:** T2.1 · **Update Plan:** ✅

1. Creare `firmware/Makefile`, `firmware/linker/t90b.ld`, `firmware/src/startup.c`, `firmware/src/main.c`, `firmware/src/board.c` e `firmware/src/ui.c`. Registrare versione esatta di compilatore, SDK e relativi digest in `firmware/toolchain.lock`.
2. Definire `Reset_Handler` per inizializzare `.data` e `.bss` e chiamare `main`. Linkare la tabella dei vettori a `0x08005000`. Dare a `board_init` la responsabilità di porre l'uscita riscaldatore in stato inattivo prima di configurare le periferiche. Fare di `ui_step` una transizione di stato testabile con eventi temporizzati.
3. Implementare nell'ordine avvio, display e tasti, menu, preferenze, sonno e risveglio. Verificare ogni blocco contro gli ID di T2.1. Per preferenze invalide, caricare solo i valori iniziali documentati e vietare scritture sulle aree di fabbrica.
4. Fissare i target `make -C firmware clean all` e `make -C firmware test`. Il primo deve produrre `firmware/build/t90b.elf` e `firmware/build/t90b.bin`, il secondo deve uscire 0 su tutti gli scenari UI implementati. Verificare la base dei vettori con `arm-none-eabi-objdump -h firmware/build/t90b.elf`. Su mismatch, bloccare l'accesso alle prove fisiche.

### - [x] T2.3 — Implementare i driver reali in `board.c` e il packer `.atk`

**Owner:** @developer · **Priorità:** P0 · **Stima:** L · **Dipendenza:** T2.2 · **Update Plan:** ✅

1. Estrarre dal disassemblato in `analysis/` il pinout esatto di display (`SPI1` + `DMA2` + DC/RST/BL), tasti A/B (`GPIO` + debounce), sensore di movimento, `ADC` + `DMA1` (canali temperatura punta, NTC, `Vin`, presenza punta) e `SysTick` (1 ms).
2. Implementare i driver reali in `firmware/src/board.c` mantenendo `T90B_HEATER_ENABLED=0` e aggiungendo la lettura/scrittura sicura delle preferenze a `0x0801F000` (con divieto di scrittura su bootloader e byte di fabbrica).
3. Aggiungere uno script di impacchettamento `.atk` (header 13 byte + payload XOR `0xFF`) compatibile con la procedura di flash/ripristino del dispositivo.
4. Verificare `make -C firmware clean all`, `make -C firmware test` e `verify_differential.py` con `TIM1_CCDAT1=0` e `TIM1_BKDT.MOE=0`.

**Chiusura fase:** ✅ · **Compact Context:** ✅ · **Context Refill:** `docs/plans/t90b-firmware-reconstruction.md`, `docs/reconstruction/behavior.tsv`, `docs/reconstruction/baseline.md`, `firmware/Makefile`, `firmware/toolchain.lock`.

## Fase 3 — Verifica differenziale e prove termiche

### - [x] T3.1 — Confrontare firmware originale e candidato

**Owner:** @developer · **Priorità:** P0 · **Stima:** XL · **Dipendenza:** T2.2 · **Update Plan:** ✅

1. Creare `firmware/sim/t90b.repl` e `firmware/sim/t90b.robot`. Definire Cortex-M4, RAM, flash e i modelli delle periferiche effettivamente usate dagli scenari. Applicare gli stessi stimoli a originale e candidato. Il [manuale Renode](https://renode.readthedocs.io/en/latest/advanced/writing-peripherals.html) descrive la modellazione delle periferiche.
2. Eseguire `renode-test firmware/sim/t90b.robot`. Atteso: exit 0 sugli scenari modellati. Registrare in `docs/reconstruction/validation.tsv` per ogni ID stato `pass`, `fail` o `unverified`, backend, esito e percorso delle tracce. Un accesso non modellato che influenza l'oracolo rende lo scenario `unverified`.
3. Ripetere due volte `make -C firmware clean all` e `shasum -a 256 firmware/build/t90b.bin`. Accettazione: digest identici e assenza di `fail`. La simulazione non autorizza l'erogazione di potenza.

### - [ ] T3.2 — Verifica a freddo sul T90B, prove pratiche con stagno e chiusura release

**Owner:** @developer · **Priorità:** P0 · **Stima:** XL · **Dipendenza:** T3.1, T2.3 · **Update Plan:** ✅

1. **Artefatti di sicurezza (fatto)**: `firmware/src/heater.c` (`heater_init`, `heater_step`, `heater_trip`, `heater_rearm`), `docs/reconstruction/thermal-gates.md` e `docs/reconstruction/release.md` creati e verificati su host/Unicorn.
2. **Verifica ripristino e test a freddo (`T90B_HEATER_ENABLED=0`)**:
   - **Ripristino `t90.atk` verificato**: su T90B (`v 1.1.4`), `firmware/tools/flash_atk.py --flash t90.atk --yes` (`0x19F5:0x3245`) flasha e riavvia normalmente il dispositivo (`Vol low` su USB 5 V).
   - **Sblocco bootloader (`0x08005800`)**: disassemblando il dump del bootloader (`0x080031c0` / `0x08002fb0`) ottenuto via `t90_msdmem`, è emerso che `SET_BOOT` scrive e valida 8 byte di metadati a `0x08005800`. Riservata `.boot_meta 0x08005800` in `firmware/linker/t90b.ld` per avviare `t90b.atk` sul T90B fisico.
   - **Test LCD separato**: dopo la comparsa di due linee orizzontali sul candidato, preparata la build `make -C firmware lcd-test` con pattern RGB e riscaldatore disabilitato. Pattern RGB e riquadro bianco confermati su hardware con la seconda build, che usa frame SPI da 16 bit per i pixel. Sul dispositivo sono stati confermati anche il testo leggibile, l’apertura del menu con A+B, lo scorrimento e l’uscita.
3. **Prove termiche graduate con tetto PWM (`T90B_HEATER_ENABLED=1`)**: in assenza di carico fittizio, alimentatore limitato e oscilloscopio, applicare un tetto massimo conservativo al duty PWM (es. 15–20%) e monitorare in tempo reale il **cavo USB-C con wattmetro** (potenza media, aggiornamento ~0,5–1 s) su punta T245 reale:
   - **150 °C**: verificare che la punta intiepidisca con potenza contenuta e **non** fondi lo stagno (né Sn63/Pb37 né SAC305).
   - **200 °C (Sn63/Pb37) / 235 °C (SAC305)**: verificare l'inizio della fusione dello stagno alla soglia attesa.
   - **Guasti / Standby**: verificare `No tip` alla rimozione della punta e il ritorno immediato della potenza sul cavo USB-C al valore base (< 1 W).
4. **Chiusura `docs/reconstruction/validation.tsv` e `docs/reconstruction/release.md`**: aggiornare gli esiti osservati sul T90B fisico, dichiarando esplicitamente eventuali limiti/funzionalità non dimostrate (es. assenza di banco con carico fittizio).

**Chiusura fase:** ✅ · **Compact Context:** ❌ (la chiusura richiede la revisione degli stessi risultati).

## Dipendenze, rischi e consegna

Percorso critico: T1.1 → T1.2 → T2.1 → T2.2 → T3.1 → T2.3 → T3.2. Il confine tra codice, dati e flussi indiretti si dimostra per sottosistema. I rischi maggiori sono l'attribuzione di driver alla revisione sbagliata, i modelli di simulazione incompleti e la perdita di controllo termico. Li gestiscono rispettivamente la verifica della scheda, il test a freddo (`T90B_HEATER_ENABLED=0`) prima di ogni potenza, e il tetto PWM conservativo nelle prove con stagno.

**Dati raccolti utente:** `Ver Info` originale `v 1.1.4`, flash/ripristino via USB HID macOS (`firmware/tools/flash_atk.py`), stagno `Sn63/Pb37`.

| Versione | Data | Modifica |
|---|---|---|
| 1.0 | 2026-11-27 | Piano iniziale |
| 1.1 | 2026-11-27 | Allineato stato a 5/7 attività; aggiunta T2.3 (driver `board.c` + packer `.atk`) e aggiornata T3.2 con verifica a freddo, cavo USB-C wattmetro e soglie pratiche con stagno (150 °C / 200–235 °C) |
| 1.2 | 2026-11-27 | Completata T2.3; verificato flash/ripristino `t90.atk` su macOS (`v 1.1.4`); documentato blocco bootloader stock su payload terzi in T3.2 |

## Piano pronto

Iniziare da T1.1. La scrittura di questo piano non esegue le attività né autorizza il flash del dispositivo.
