# Gate di sicurezza termica (T3.2)

**Stato:** aperto — nessuna prova di potenza su punta reale eseguita.  
**Build corrente:** `T90B_HEATER_ENABLED=0` (riscaldatore disabilitato a compilazione e a runtime).

## 1. Limiti richiesti prima di abilitare `T90B_HEATER_ENABLED=1`

| Grandezza | Limite di progetto | Unità | Fonte / Riferimento | Stato |
|---|---:|---|---|---|
| Tensione di ingresso valida (`Work Vol`) | da rilevare su banco (tipico 9–20) | V | Manuale ALIENTEK T90B §§5, 8 | unverified (banco) |
| Potenza massima su carico fittizio | da dimensionare su cartuccia T245 | W | Manuale ALIENTEK T90B §§1–2 | unverified (banco) |
| Latenza massima di arresto su guasto (`heater_trip`) | ≤ 50 (1 ciclo superloop) | ms | `firmware/src/heater.c` + `main.c` | pass (host/sim); unverified (banco) |
| Timeout sensore scaduto (`SENSOR_STALE_TIMEOUT_MS`) | 500 | ms | `firmware/src/heater.c` | pass (host) |
| Temperatura massima setpoint (`T90B_TEMP_MAX_C`) | 450 | °C | Manuale ALIENTEK T90B §6 | pass (host) |
| Overshoot massimo consentito al regime | da fissare con 3 prove | °C | Piano T3.2 punto 4 | unverified (banco) |

## 2. Criterio di stato sicuro (`firmware/src/heater.c`)

- **Avvio / Reset**: `board_init()` azzera `TIM1_CCDAT1` e disabilita `TIM1_BKDT.MOE` prima di configurare le periferiche; `heater_init()` imposta `armed = false`, `duty_pct = 0`.
- **Guasti bloccanti**: punta assente (`FAULT_TIP_MISSING`), sensore guasto/scaduto (`FAULT_SENSOR`), NTC (`FAULT_NTC`), tensione bassa (`FAULT_VOL_LOW`) invocano `heater_trip()`, azzerando immediatamente il PWM e richiedendo `heater_rearm()` esplicito solo con `faults == FAULT_NONE` e `sensor_valid == true`.
- **Carico fittizio e ripristino**: prima di collegare una punta reale, eseguire prove su carico resistivo fittizio con alimentatore limitato in corrente e misura indipendente del segnale di gate, verificando la procedura di ripristino con `t90.atk` ufficiale (senza alterare il bootloader).

## Arresto PWM in caso di stallo del ciclo principale

In Unicorn, una build separata con uscita abilitata ha impostato CCR1 a 51 e MOE a 1 per una richiesta del 20%. Senza aggiornamenti dal ciclo principale, il gestore SysTick ha azzerato entrambi al tick 501. Un comando positivo tardivo è stato ignorato fino a un comando a zero. La prova simula un ciclo principale fermo con interrupt SysTick funzionante. Non misura i tempi reali sul dispositivo. La build destinata al T90B mantiene l’uscita disabilitata.

## Confronto del comando fisico con il firmware originale

La routine originale `0x08013310` comanda il canale 1 del timer a `0x40000000`. La routine `0x080133d0` configura il pin 0 della porta GPIO a `0x40010800` in AF2 e inizializza lo stesso timer. La build ricostruita usa invece PA7 AF5 e TIM1 a `0x40012c00`. Il test precedente in Unicorn verificava quindi l'arresto dei registri del timer candidato. La corrispondenza con il percorso del riscaldatore originale richiede di portare e verificare la configurazione PA0 AF2 e le operazioni di accensione e spegnimento del timer originale prima di una prova di potenza.

Il percorso candidato ora usa PA0 AF2 e il timer a `0x40000000`. Come nel riferimento, lo spegnimento seleziona l’uscita forzata alta (`0x50`) e l’accensione usa PWM1 (`0x60`). Il candidato usa una portante nominale di circa 60 kHz con tratto alto del 90%, modulata in finestre di 100 tick. Il 20% comanda 20 tick di portante e 80 tick di riposo. In Unicorn sono stati verificati lo stato di avvio, la finestra 20/80, lo spegnimento immediato a comando zero e il blocco al tick 501 senza aggiornamenti. La frequenza fisica e la lettura ADC durante l’erogazione restano da verificare. La build abilitata è stata usata soltanto nel simulatore.

## Acquisizione ADC durante la pausa di riscaldamento

Con il riscaldatore abilitato, il firmware forza il livello di riposo prima di acquisire VIN, NTC e punta. Se c’è una richiesta di calore attende due tick di SysTick. La portante resta sospesa fino al comando successivo del regolatore. Se i tick non avanzano, la lettura viene scartata e il ciclo riceve `FAULT_SENSOR`. Due tick sono la scelta del candidato e il comportamento analogico della pausa resta da verificare su hardware. Unicorn ha verificato il modo del timer durante le tre conversioni, la ripresa su comando e il percorso di errore senza tick.

## Incidente durante la prima prova di potenza

L’utente ha riportato `NO TIP` e punta calda sia con il Mac sia con l’alimentatore da 60 W dopo il flash della build `heat-probe`. Senza misure temporali, il contributo del calore residuo tra i due collegamenti resta indeterminato. La prova è fallita e la build è sospesa. Le prove in Unicorn non convalidano l’effettivo livello di arresto sullo stadio di potenza. Per il ripristino usare il firmware originale, a dispositivo freddo, con punta rimossa e bootloader confermato.

## Diagnosi della polarità di arresto

Sul T90B, la nuova diagnostica passiva ha rilevato ADC punta 4095 senza punta e ADC 10–20 con punta fredda inserita, NTC 28 °C, punta 29 °C e gruppo 1. Il disassemblato originale corregge l’interpretazione precedente: a `0x0801332c` il ramo per richiesta zero passa esplicitamente `0x40` a `0x0800a804` (uscita forzata bassa). A `0x08013344` il ramo per richiesta massima passa `0x50` (uscita forzata alta). La build di prova aveva usato erroneamente `0x50` per lo spegnimento. Questo spiega il rischio di erogazione anche in presenza di un guasto. La correzione `0x40` è stata compilata e verificata all’avvio in Unicorn. La build di potenza resta sospesa e sul T90B rimane la diagnostica passiva.

La build hardware `heater-off-test` configura PA0 AF2 in modalità forzata bassa `0x40`, con il comando di riscaldamento disabilitato a compilazione. Sul Mac l’utente ha osservato `VOL LOW`. Con alimentatore da 60 W, a punta inserita, ha osservato 30 °C, `HEATER OFF / TEST` e punta fredda. La prova conferma il comportamento a riposo nelle condizioni osservate. La transizione da erogazione a riposo resta da verificare sul dispositivo.

Con la build `heater-pulse` la richiesta è limitata al 10%, con arresto a 100 °C indicati o dopo 1000 tick. In Unicorn il limite di durata è intervenuto anche con comandi positivi periodici. Sul T90B l’utente ha riportato 30 °C prima del comando, `HEAT PROBE` e poi 31 °C. Il ritorno della schermata a `HEATER OFF` e l’andamento successivo della temperatura sono da confermare.

Con la build `heater-100-test`, dopo una pressione di A la lettura della punta è salita da 30 a 38 °C nell’arco dei 15 secondi della prova e poi è scesa gradualmente a 30 °C. Il risultato mostra una risposta termica rilevabile con il comando limitato al 10%. Il setpoint di 100 °C non è stato raggiunto. Il caso di arresto tramite seconda pressione di A resta da osservare su hardware.

Con la build ricompilata al 35%, una pressione di A ha mostrato `REQ 35`. La punta ha raggiunto 51 °C indicati. Dopo 15 secondi il riscaldamento si è interrotto automaticamente, il display è tornato a `REQ 0` e la punta si è raffreddata. Il target di 100 °C resta da raggiungere.

Con la build al 35% e limite di riserva a 90 s, la punta è salita da 30 a 97 °C indicati. La richiesta visualizzata è passata da `REQ 35` all’avvio a circa `REQ 5` vicino al picco. Lo stagno non è fuso. A 90 s è intervenuto l’arresto automatico e la punta si è raffreddata. Il risultato conferma la riduzione della richiesta vicino al target e il raffreddamento dopo lo stop. Il target di 100 °C esatti e il mantenimento a regime restano da verificare.

## Regolatore originale e correzione del superamento a 103 °C

Nel disassemblato dell’originale, la routine a `0x080124bc` calcola un termine proporzionale, integra l’errore con un limite e può sottrarre un termine derivativo calcolato sulla variazione della misura. L’inizializzazione a `0x0800ce8c` carica due profili con guadagni iniziali (Kp, Ki, Kd) pari a (1, 0,2, 0) e (0,1, 0,02, 0) nei rispettivi percorsi. La routine a `0x080127e4` riscalibra i termini I e D al cambio di intervallo. Il percorso principale commuta tra valori di intervallo 100 e 20 in prossimità di 30 °C di errore (`0x0801314c`). I guadagni nominali hanno Kd pari a zero in entrambi i profili inizializzati.

Con il primo PID custom la punta ha raggiunto 103 °C indicati e si è raffreddata dopo lo spegnimento automatico a 90 s. La nuova build usa un setpoint interno di 98 °C, dimezza Ki, limita l’integrale a otto punti percentuali e riduce la richiesta in base alla salita proiettata sui prossimi due secondi. Il limite di richiesta scende a zero a 99 °C indicati, mentre 100 °C disarma il riscaldatore. Il test Unicorn verifica i comandi su letture simulate, il riarmo dopo il cutoff e la durata massima. Il picco termico sul dispositivo resta da misurare.

La prova sul T90B del PID con margine a 98 °C ha dato un picco indicato di 98 °C. La build successiva consente `REQ 45` a freddo e riduce il limite gradualmente tra 75 e 80 °C, dove torna al 35%. Restano il setpoint interno di 98 °C, la frenata predittiva, il disarmo a 100 °C e il limite di 90 s.

L’originale limita la richiesta del regolatore a 0–100 (costanti a `0x080126d4` e `0x080126d8`). A `0x080131a8` moltiplica la richiesta per il numero di tick dell’intervallo di controllo, divide per 100 e arrotonda al tick più vicino. Il limite 100 è una percentuale di richiesta e non una misura di potenza in watt. Il firmware originale calcola separatamente la modulazione della portante in base alle condizioni di alimentazione.

La prova custom con limite del 60% ha raggiunto 99 °C indicati. La revisione successiva porta la richiesta iniziale a 100%. La richiesta si riduce prima se la salita proiettata si avvicina a 80 °C e il tetto scende al 60% dopo i primi 15 s. Nel tratto finale il tetto scende più rapidamente in funzione della distanza proiettata dal limite. Il regolatore aggiunge un contributo di 5 punti percentuali, soggetto allo stesso tetto, per compensare le perdite verso il target. Lo stop a 100 °C indicati e il limite di 90 s restano attivi. Unicorn verifica il primo ciclo al 100%, la riduzione a 60% anche con aggiornamenti della richiesta al 100%, la frenata durante una salita rapida e il disarmo a 100 °C. Restano da osservare sul T90B il tempo di salita e il picco dopo lo spegnimento.

La revisione successiva elimina la riduzione temporizzata da 100% a 60% dopo 15 s. Il limite di riscaldamento dipende dalla temperatura proiettata, con riduzione al tetto del 35% entro 90 °C indicati e una frenata finale che annulla la richiesta quando la proiezione raggiunge 100 °C. Interpolazione NTC, conversione punta, PID e display della prova usano decimi di grado. Il regolatore può continuare a scaldare a richiesta ridotta quando la lettura è a 99,9 °C e la salita è lenta. Alla prima lettura di almeno 100,0 °C disarma l’uscita. Il limite complessivo di 90 s resta attivo. I test Unicorn coprono il 100% oltre i 15 s, la frenata predittiva e la transizione da 99,9 a 100,0 °C. Il picco dopo lo spegnimento resta da osservare su hardware.

## PID continuo a 100 °C

Sul T90B la revisione precedente ha raggiunto 100 °C indicati. L’utente riferisce una salita ancora lenta rispetto al firmware originale. Il tempo di salita e il picco successivo non sono stati misurati.

Nella nuova build `heater-100-test`, A avvia la regolazione e una seconda pressione la termina. A partire da 100,0 °C misurati, il comando vale zero e il PID resta attivo per compensare il successivo raffreddamento. La modalità continua esclude sia il limite di sessione di 90 s sia lo standby per inattività. Oltre 2 °C di errore aumenta il contributo proporzionale. Il tetto dipende dal margine previsto a tre secondi, così una punta che sta già salendo rapidamente può proseguire per inerzia. Su una rampa imposta di 2 °C/s Unicorn verifica REQ 100 a 85 °C, una richiesta intermedia a 90 °C e zero a 99 °C.

Restano attivi i controlli su punta, ADC, tensione e freschezza del campione. La modalità continua segnala anche `HEAT ERROR` a 105 °C indicati durante la regolazione o il tentativo di avvio, oppure se, con REQ di almeno 60%, la lettura non guadagna 2 °C in 12 s. A punta sotto 100 °C e con i sensori validi, una pressione di A riconosce il guasto e una successiva riavvia. Unicorn verifica questi casi e oltre sette minuti di regolazione su ingressi sintetici. Tempo di salita reale, escursione attorno al target e confronto cronometrato con l’originale restano da misurare.

## Riduzione più tardiva della richiesta durante la salita

L’utente segnala che la build PID continua riduce REQ troppo presto rispetto al firmware originale. Nella revisione successiva il PID usa il target fisso di 100 °C, aumenta il guadagno di avvicinamento e prevede da 1,5 a 3 s di salita secondo la velocità misurata. Negli ultimi decimi l’integrale conserva anche le frazioni accumulate tra due campioni e la richiesta scende gradualmente con il margine previsto. A 100 °C misurati l’uscita va a zero.

Nel replay dello stesso ingresso a 2 °C/s, campionato ogni 50 ms, l’ultima lettura a REQ 100 passa da 86,7 a 94,1 °C. A 95 °C la richiesta passa da 0 a 75%. A 5 °C/s la nuova build rilascia il pieno comando dopo 82,2 °C e a 90 °C è già a zero. Queste temperature descrivono le rampe di prova. In tre modelli termici sintetici con inerzia da 0,5 a 3 s si osserva anche il raggiungimento di 100 °C indicati. Il confronto cronometrato fra custom e originale sulla stessa punta resta da eseguire.

## Preset selezionabili prima dell’avvio

La build `heater-presets` parte in standby con `SET 100`. Una pressione breve di B seleziona ciclicamente 100, 200 o 300 °C. A avvia il PID direttamente sul valore visualizzato e lo spegne alla pressione successiva. Il preset resta selezionato fino al riavvio. Durante il riscaldamento il tasto B da solo conserva il target in uso.

Il margine predittivo usa il target scelto. La compensazione iniziale delle perdite scala i 9 punti percentuali della regolazione a 100 °C con la differenza tra il target e un ambiente nominale a 25 °C. A partire dal target misurato la richiesta vale zero. La protezione termica interviene a 5 °C sopra il target. Per un avvio con calore residuo da un preset più alto, il comando resta a zero durante il raffreddamento. In questa fase il limite segue la temperatura minima osservata più 5 °C, fino a un massimo assoluto di 305 °C.

In Unicorn i tre preset hanno raggiunto e mantenuto il rispettivo target su un modello termico sintetico per una prova di 240 s ciascuno. Verificati selezione con uscita spenta, avvio diretto, blocco della selezione a caldo durante la regolazione, stop con A, protezione relativa al preset e ripartenza con calore residuo. Il comportamento termico reale a 200 e 300 °C resta da misurare.

## Estensione a 350 e 400 °C

In standby B scorre 100, 200, 300, 350, 400 °C e torna a 100 °C. Il display arrotonda al grado più vicino, mentre il PID usa i decimi. Il limite di sovratemperatura durante la regolazione resta 5 °C sopra il preset, con limite assoluto di 405 °C anche al riavvio con calore residuo. Il modello termico ha raggiunto tutti e cinque i target nella prova di 240 s per preset. Il bootloader ha confermato il flash della build. Le prestazioni reali a 350 e 400 °C restano da misurare.

Sul T90B con la precedente build l’utente riferisce che attorno a 299 °C con SET 300 il display alterna REQ 0 e circa 40. A 300 °C la stima iniziale di compensazione delle perdite è 33 punti percentuali. Il PID corregge questo valore sotto target e può azzerare il comando quando prevede di raggiungere il target per inerzia. Mancano i tempi trascorsi a ciascun valore per ricavare una media.

### Come leggere il display durante il mantenimento

Con SET 300, una lettura interna di 299,6 °C appare come 300. Il controllo usa ancora 299,6 °C e tiene conto anche della velocità di salita. REQ indica il comando percentuale istantaneo del regolatore, da 0 a 100. Per esempio, cinque secondi a REQ 40 e cinque a REQ 0 danno una richiesta media del 20% sui dieci secondi. Per esprimere in watt la potenza realmente erogata occorre una misura elettrica.

### Identificazione della build installata

- Build riproducibile con `make -C firmware heater-presets`. Pacchetto di aggiornamento in `firmware/build/heater-presets/t90b.atk`.
- SHA-256 del binario applicativo installato (`t90b.bin`): `d94650e246567c5018541a4118cbdf1e20a2a60cd8df43e14fd45cf087c1e3e3`.
- Verifiche eseguite prima del flash: test host UI e protezioni, simulazione dei cinque preset, uscita del riscaldatore forzata bassa al boot e confronto del pacchetto ATK con il binario testato.
- Il bootloader ha restituito `00` per SET_FW_INFO, START_DATA, END_DATA e SET_BOOT. Al riavvio il preset iniziale è 100 °C e il riscaldatore attende A. A avvia o arresta la regolazione. B seleziona il preset in standby. La regolazione continua fino allo stop manuale o all’intervento di una protezione.
