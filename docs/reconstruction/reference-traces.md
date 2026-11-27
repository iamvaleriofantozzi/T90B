# Tracce del firmware di riferimento

La [matrice degli scenari](behavior.tsv) usa come ipotesi le sezioni 5–9 del manuale ALIENTEK T90A/B/C e gli indirizzi del payload applicativo. Le osservazioni vanno associate alla versione in esecuzione sullo specifico T90B. [Manuale ALIENTEK, copia Switch Science](https://doc.switch-science.com/media/files/25ac61e3-2d2f-4f24-a20f-8f8a2710cdb8.pdf)

Per ogni sessione registrare il modello, la versione visibile in `Ver Info`, l'identificativo della revisione se osservabile, la cartuccia, l'alimentatore e le risoluzioni temporali e termiche degli strumenti. Specificare se l'esemplare, il banco o la simulazione ha prodotto la traccia.

Archiviare le tre ripetizioni di ciascun caso come `traces/reference/<id>/<variante>-r1.tsv`, `-r2.tsv` e `-r3.tsv`, partendo da `docs/reconstruction/`. Le colonne sono `time_ms`, `channel`, `value`, `unit`, `artifact`. Usare il tempo relativo allo stimolo e annotare lo stato visibile al primo fotogramma utile. Per gli ingressi registrare sia la pressione sia il rilascio. Per le transizioni usare lo stesso riferimento temporale per lo stimolo e l'uscita e riportare la risoluzione della registrazione. Congelare la tolleranza con le tre tracce prima di confrontare il candidato.

Per la persistenza, rilevare prima il valore iniziale dell'unità di temperatura. Verificare separatamente l'annullamento con A lungo e il salvataggio con B lungo seguito da spegnimento e riavvio. Ripristinare il valore iniziale al termine.

Le condizioni di banco, i segnali da misurare e i limiti applicabili precedono le prove di guasto. I risultati documentali e statici della matrice restano `unverified` finché mancano le tracce.

## Dispatcher UI in emulazione

La [traccia del dispatcher](ui-dispatch-runtime.tsv) registra tre avvii isolati per ognuno dei 15 slot con puntatore. L'harness inietta l'indice in RAM, esegue il codice originale da `0x08014ce0` e rileva l'indirizzo raggiunto dopo il `BLX` a `0x08014cee`. L'indice 2 contiene un puntatore nullo e viene registrato senza eseguirlo. Per riprodurre la traccia con Unicorn 2.1.4 eseguire `python analysis/tools/trace_ui_dispatch.py analysis/t90-app.bin` dalla radice del workspace.

La traccia conferma la selezione della routine a partire da un indice dato. La provenienza dell'indice, l'esecuzione della routine e la sequenza ottenuta premendo i tasti restano da verificare.

## Reset applicativo in emulazione

Dalla baseline sono stati caricati lo SP e il vettore di reset. Su tre ripetizioni [con flash e SRAM](reset-runtime.tsv), la sequenza ha raggiunto `0x0800a64c`, prima lettura di `SCB.CPACR` a `0xe000ed88`. Con [la pagina di controllo mappata come RAM inizialmente a zero](reset-core-runtime.tsv), l'esecuzione ha superato il read-modify-write di CPACR e si è fermata a `0x0800a658`, prima lettura di `RCC_CTRLSTS` a `0x40021024`. Tale registro governa, fra l'altro, l'oscillatore MSI e ne espone il segnale di stabilità. [Manuale NSING N32L40x, capitolo RCC](https://nsing.com.sg/api/dowfilebefore?did=2816)

Riprodurre con Unicorn 2.1.4 mediante `python analysis/tools/trace_reset.py analysis/t90-app.bin` e ripetere aggiungendo `--core-page`. La pagina RAM serve a identificare la dipendenza successiva. Il comportamento dei clock, del bootloader e della prima schermata resta da verificare.

## Avvio dei clock

Il modello ridotto di RCC risponde alle abilitazioni HSI, HSE e PLL con i relativi bit di stabilità. Il caso HSE assente mantiene disattivo il suo bit. Il modello PWR restituisce prima regolazione in corso e poi completata. Flash AC e l'indirizzo non attribuito `0x40001820` sono mantenuti come valori in memoria, con inizializzazione a zero. La pagina SCB è la stessa del probe precedente.

- [HSE pronto](reset-hse-ready-runtime.tsv). Il firmware attraversa il ramo PLL, seleziona l'uscita PLL, scrive VTOR e raggiunge il secondo stadio applicativo a `0x08005148`.
- [HSE assente](reset-hse-timeout-runtime.tsv). Il polling termina, il firmware attraversa il ramo di ripiego a `0x0800a538`, scrive VTOR e raggiunge lo stesso secondo stadio.

Entrambi i casi proseguono fino alla prima lettura di `RCC_APB2PCLKEN` a `0x40021018`, eseguita dal PC `0x0800a2b8`. Ogni versione della traccia contiene tre ripetizioni e usa passi istruzione, senza attribuire una durata fisica. La schermata iniziale resta fuori dalla porzione osservata. [Manuale NSING N32L40x, capitoli PWR e RCC](https://nsing.com.sg/api/dowfilebefore?did=2816)

Per riprodurre usare `trace_reset.py` con `--clock-mode hse-ready` o `--clock-mode hse-timeout`.

## Inizializzazione delle periferiche

Con `--peripheral-clocks`, il modello permette la configurazione delle abilitazioni AHB e APB2. Il codice originale raggiunge la prima lettura di `GPIOA_AFH` a `0x40010824`. Con `--gpio` il modello aggiunge la configurazione dei porti e i latch di uscita, usando il manuale per i valori di reset dei registri di configurazione. Il dato d'ingresso è fissato a zero. In entrambi i rami HSE l'esecuzione raggiunge poi una lettura a 16 bit di `USART1_CTRL2` a `0x40013810`, dal PC `0x0800ab04`.

- [HSE pronto, clock periferiche](reset-hse-ready-peripheral-clocks-runtime.tsv) e [HSE pronto, GPIO](reset-hse-ready-gpio-runtime.tsv).
- [HSE assente, clock periferiche](reset-hse-timeout-peripheral-clocks-runtime.tsv) e [HSE assente, GPIO](reset-hse-timeout-gpio-runtime.tsv).

Il SVD 1.0.2 indica offset `0x30` per `GPIOx_SR`. Il manuale indica `0x08` e il codice originale modifica un bit per pin a tale offset nel ciclo di configurazione a `0x080097a6`–`0x080097b8`. Il probe usa l'offset del manuale. La revisione della scheda e i livelli dei pin restano da misurare. [Manuale NSING N32L40x, capitoli GPIO e USART](https://nsing.com.sg/api/dowfilebefore?did=2816)

## Prima diagnostica seriale

Con `--usart` il modello accetta letture e scritture a 16 o 32 bit sui registri di USART1, senza ingresso e con trasmissione immediata. Il codice originale scrive 66 byte su `USART1_DAT` e poi raggiunge la configurazione del primo canale DMA, fermandosi alla lettura `0x40020008` da `0x0800939c`. Il contenuto trasmesso coincide fra tutte le ripetizioni e fra i due rami HSE. I byte non dimostrano il baud rate fisico o l'instradamento dei pin.

- [Byte trasmessi](reset-usart-transmit.txt)
- [Avvio con HSE pronto](reset-hse-ready-usart-runtime.tsv)
- [Avvio con HSE assente](reset-hse-timeout-usart-runtime.tsv)

Per salvare i byte all'esecuzione usare `--usart --serial-output FILE` insieme a `--clock-mode`.

## Configurazione DMA e ingresso nella routine ADC

Con `--dma` il modello conserva i registri di configurazione dei canali, esegue la cancellazione dei flag richiesta e conserva il valore scritto in `RCC_AHBPRST`. Il firmware originale configura il canale DMA 1 per 60 trasferimenti da `0x4002084c` (`ADC_JDAT` secondo il SVD) a `0x20000fb4`. Il valore finale `0x35a3` di `DMA_CHCFG1` imposta un trasferimento periferica→memoria in modalità circolare, con incremento dell'indirizzo di memoria e ampiezza di 16 bit su entrambi i lati. Il modello registra questa configurazione, senza eseguire alcun trasferimento.

I due rami HSE producono le stesse 13 scritture DMA in tre ripetizioni ciascuno e raggiungono la lettura di `ADC_CTRL1` a `0x40020804` da `0x08005f34`. I byte USART1 precedenti coincidono con il probe senza DMA. [Manuale NSING N32L40x, capitoli RCC, DMA e ADC](https://nsing.com.sg/api/dowfilebefore?did=2816)

- [Scritture DMA](reset-dma-writes.tsv)
- [HSE pronto](reset-hse-ready-dma-runtime.tsv)
- [HSE assente](reset-hse-timeout-dma-runtime.tsv)

Per riprodurre eseguire `trace_reset.py` con `--clock-mode`, `--dma` e `--dma-output FILE`.

## Configurazione ADC

Con `--adc`, il probe conserva i registri di configurazione e simula gli indicatori di ADC pronto e calibrazione completata senza ritardo. Il firmware originale imposta una sequenza regolare di tre canali (3, 5 e 6), abilita il convertitore e richiede la calibrazione. Il modello lascia esclusi i registri dei risultati e non simula la conversione analogica.

Ogni ramo HSE produce le stesse 17 scritture ADC e le stesse scritture DMA già registrate. Il firmware arriva poi alla prima lettura a 16 bit di `SPI1`, indirizzo `0x40013000`, dal PC `0x0800a4ca`. Gli ingressi fisici associati ai canali ADC e la prima transazione del display restano da verificare. [Manuale NSING N32L40x, capitoli ADC e SPI](https://nsing.com.sg/api/dowfilebefore?did=2816)

- [Scritture ADC](reset-adc-writes.tsv)
- [HSE pronto](reset-hse-ready-adc-runtime.tsv)
- [HSE assente](reset-hse-timeout-adc-runtime.tsv)

Per riprodurre usare `trace_reset.py` con `--clock-mode`, `--adc` e `--adc-output FILE`.

## Configurazione SPI1 e attesa temporizzata

Con `--spi` il probe registra le scritture di SPI1. Entrambi i rami HSE impostano e abilitano la periferica con le stesse quattro scritture in tre ripetizioni. Nessuna scrittura raggiunge il registro dati SPI1 entro il limite di 1.500.000 istruzioni. Una lettura della traccia completa mostra chiamate ripetute da `0x0800f43c` a `0x08011edc`, che legge `SysTick.VAL` e calcola il tempo usato nel confronto di `0x0800f442`. La pagina SCB del probe simula la memoria, quindi il contatore non avanza. I comandi del display restano da osservare con SysTick modellato.

- [Scritture SPI1](reset-spi-writes.tsv)
- [HSE pronto](reset-hse-ready-spi-runtime.tsv)
- [HSE assente](reset-hse-timeout-spi-runtime.tsv)

Per riprodurre usare `trace_reset.py` con `--clock-mode`, `--spi` e `--spi-output FILE`.

## Primi byte verso il display

Con `--spi --virtual-tick`, a ogni ingresso in `0x08011edc` il probe incrementa di 1 il contatore software a `0x200000f8` se SysTick è abilitato. L'hook fa avanzare le attese secondo il contatore letto dall'applicazione. Non esegue l'interrupt SysTick e non rappresenta una misura temporale.

I due rami HSE condividono le prime 229 scritture SPI1, di cui 225 verso il registro dati. Nel ramo HSE pronto vengono osservate altre 16 scritture entro lo stesso limite di istruzioni. La sequenza inizia con `FE EF 80 FF 81 FF`. Verso la fine compaiono le sequenze compatibili con l'impostazione di una finestra da 40 × 160 pixel, seguite dall'abilitazione della richiesta DMA TX su SPI1. Questa interpretazione resta da confermare misurando il segnale comando/dati sul display.

Nel ramo HSE pronto il probe raggiunge un'attesa su un flag RAM a `0x0801140e`–`0x08011414` dopo la configurazione del trasferimento. I trasferimenti DMA e i loro interrupt non sono modellati. Nessuna schermata è stata ricostruita da queste tracce.

- [HSE pronto, scritture SPI1](reset-hse-ready-virtual-tick-spi.tsv) e [traccia CPU](reset-hse-ready-virtual-tick-runtime.tsv).
- [HSE assente, scritture SPI1](reset-hse-timeout-virtual-tick-spi.tsv) e [traccia CPU](reset-hse-timeout-virtual-tick-runtime.tsv).

Per riprodurre usare `trace_reset.py` con `--clock-mode`, `--spi --virtual-tick` e `--spi-output FILE`.

## Primo buffer a schermo intero

Nel ramo HSE pronto, il firmware imposta il canale DMA 2 con sorgente `0x20001078`, destinazione `SPI1_DAT` a `0x4001300c`, conteggio `0x1900` e ampiezza di 16 bit. La routine a `0x08011370` richiede una finestra con coordinate inclusive da (0, 0) a (39, 159). Il conteggio è quindi coerente con 6.400 pixel.

Con `--frame-output FILE` il probe legge la sorgente del DMA a `0x080113e4`, subito dopo l'abilitazione della richiesta SPI TX. I 12.800 byte sono tutti zero e coincidono in tre ripetizioni e in una seconda esecuzione completa. Il dato corrisponde a un riempimento nero se interpretato in RGB565. Il probe si ferma nell'attesa di completamento e il buffer costituisce evidenza del contenuto preparato per il DMA.

- [Scritture dei registri DMA](reset-display-dma-writes.tsv)
- [Buffer sorgente](reset-display-first-dma.bin), SHA-256 `59ec91dcb7dc65b5f928091cb0e25c26729a0a4453ebe7d8244fc1ceae7d9712`

Per riprodurre usare `trace_reset.py --clock-mode hse-ready --spi --virtual-tick --frame-output FILE analysis/t90-app.bin`.

## Completamento del primo trasferimento display

Con `--complete-display`, il probe arresta temporaneamente la CPU alla prima attesa del flag del display, imposta i flag DMA2 di completamento e invoca la routine indicata dal vettore IRQ 12 del payload. La routine originale a `0x08009328` cancella il flag DMA, disabilita la richiesta TX SPI e scrive 1 nei flag a `0x2000011e` e `0x2000011f`. Ripristinato il contesto CPU, il firmware esce dall'attesa a `0x08011416` e arriva alla prima lettura di `TIM2_CTRL1` a `0x40000000`. Il risultato si ripete in entrambi i rami HSE. Il contenuto sorgente coincide in entrambi i rami con il buffer nero già acquisito.

L'iniezione esercita la routine firmware che chiude il trasferimento. La consegna NVIC, la durata del DMA e l'aggiornamento del pannello restano fuori da questa misura.

- [HSE pronto](reset-hse-ready-display-complete-runtime.tsv)
- [HSE assente](reset-hse-timeout-display-complete-runtime.tsv)
- [Scritture DMA e riconoscimento del completamento](reset-display-dma-completion-writes.tsv)

Per riprodurre aggiungere `--complete-display` al comando del probe con `--spi --virtual-tick`.

## Timer dopo il primo trasferimento display

Con `--timers` il probe registra la configurazione dei timer, senza far avanzare il contatore o generare eventi e interrupt. Entrambi i rami HSE producono le stesse 60 scritture e avviano TIM1, TIM2, TIM4 e TIM5. I valori finali osservati sono riportati come valori dei registri, senza convertirli in frequenze misurate.

| Timer | Prescaler PSC | Auto-reload AR | Altre scritture osservate |
|---|---:|---:|---|
| TIM1 | 0 | 22222 | `CCDAT1 = 17777`, uscita principale abilitata |
| TIM2 | 0 | 1000 | `CCDAT1 = 0` |
| TIM4 | 299 | 49999 | Interrupt di aggiornamento abilitato |
| TIM5 | 29 | 999 | Interrupt di aggiornamento abilitato |

Il termine della traccia corrisponde a una scrittura a `0x42420480`, alias bit-band di `RCC_CTRLSTS` bit 0 (`LSIEN`), eseguita a `0x0800a2d6`. La relazione fra compare timer, pin e attuatori resta da dimostrare sulla revisione in esame. [Manuale NSING N32L40x, mappa bit-band e capitoli RCC/TIM](https://nsing.com.sg/api/dowfilebefore?did=2816)

- [Scritture dei timer](reset-timer-writes.tsv)
- [HSE pronto](reset-hse-ready-timers-runtime.tsv)
- [HSE assente](reset-hse-timeout-timers-runtime.tsv)

Per riprodurre aggiungere `--timers --timer-output FILE` al probe con `--spi --virtual-tick --complete-display`.

## Attivazione del watchdog indipendente

Con `--watchdog`, il modello fa corrispondere l'alias bit-band di LSIEN al registro RCC e rende LSI immediatamente pronto. Il firmware originale abilita LSI, sblocca i registri IWDG con `0x5555`, imposta il prescaler a 3 (divisione per 32) e il reload a `0x271` (625), ricarica con `0xAAAA` e avvia IWDG con `0xCCCC`. Entrambi i rami HSE eseguono le stesse sei scritture in tre ripetizioni. Il modello non fa scadere il contatore e non verifica l'esito di un reset. [Manuale NSING N32L40x, capitoli RCC e IWDG](https://nsing.com.sg/api/dowfilebefore?did=2816)

Il primo accesso successivo non modellato è una lettura da `0x0801f000` nel ciclo di copia a `0x08010108`. Quella pagina non è contenuta nel payload verificato. Il probe precedente mappava soltanto la regione applicativa.

- [Scritture LSI e IWDG](reset-watchdog-writes.tsv)
- [HSE pronto](reset-hse-ready-watchdog-runtime.tsv)
- [HSE assente](reset-hse-timeout-watchdog-runtime.tsv)

Per riprodurre aggiungere `--watchdog --watchdog-output FILE` al probe con `--spi --virtual-tick --complete-display --timers`.

## Validazione delle preferenze all'avvio

La routine originale a `0x08012e38` copia 160 byte da `0x0801f000` in RAM. Controlla due blocchi ai relativi offset `0x14` (28 byte) e `0x30` (112 byte). Per ciascun blocco confronta la parola iniziale con la somma modulo 256 dei byte successivi. Per il secondo verifica anche che il campo a offset 4 valga `0x006c`.

Il probe esegue la routine su cinque pagine sintetiche. Una pagina cancellata fa ripristinare entrambi i blocchi. Una somma errata nel primo blocco o una lunghezza errata con somma valida nel secondo fanno ripristinare soltanto il blocco interessato. Due pagine valide, inclusa una con un valore personalizzato, vengono conservate. Ciascun ingresso è stato eseguito tre volte.

Entrambe le regioni flash del probe sono in sola lettura. La prova termina prima della routine di scrittura o della lettura del record successivo. Lo scenario di persistenza dopo spegnimento e riavvio resta da verificare.

- [Decisioni e digest della RAM](settings-validation-runtime.tsv)

Per riprodurre usare `python analysis/tools/trace_settings.py analysis/t90-app.bin` con Unicorn 2.1.4.

## Avvio con preferenze sintetiche valide

Con `--preferences` il probe carica una pagina in sola lettura a `0x0801f000`. I due blocchi sono sintetizzati dai valori iniziali del payload con somme ricalcolate. A `0x0801f800` il probe aggiunge un record sintetico di 12 byte e lascia il resto della pagina cancellato per la scansione. L'origine dei dati è il firmware applicativo analizzato.

Entrambi i rami HSE eseguono la routine a `0x08012e38`, accettano i due blocchi, accettano il record e rientrano nel chiamante a `0x080116aa`. Proseguono fino al ciclo a `0x0800cd2e`–`0x0800cd38`, che attende il flag `ADC_STS.JENDC` di conversione iniettata. Il firmware resta in quel ciclo entro il limite di 3.000.000 istruzioni perché il modello non genera campioni. Le tracce sono state riprodotte byte per byte.

- [HSE pronto](reset-hse-ready-preferences-runtime.tsv)
- [HSE assente](reset-hse-timeout-preferences-runtime.tsv)

Per riprodurre aggiungere `--preferences` al probe con `--spi --virtual-tick --complete-display --timers --watchdog`.

## Secondo buffer dopo il campionamento ADC

Con `--adc-sample`, il modello fornisce un codice sintetico fisso su `ADC_JDAT1` e segnala `JENDC` quando il firmware richiede una conversione software iniettata. Con i codici 0 e 2048, entrambi i rami HSE completano due serie da 20 campioni, raggiungono la routine di inizializzazione UI a `0x08014cfc` e preparano un secondo buffer da 40 × 160 pixel.

Il secondo buffer coincide byte per byte per le quattro combinazioni e in tre ripetizioni ciascuna. In RGB565 contiene 5.699 pixel neri, 396 bianchi e 305 rossi. La decodifica mostra un bordo e una scritta. Il probe acquisisce i pixel dalla SRAM e simula il completamento del solo primo trasferimento. Il contenuto effettivamente visualizzato, la risposta a ingressi ADC realistici e i tempi restano da verificare.

- [Secondo buffer DMA](reset-display-second-dma.bin), SHA-256 `974f4c6d71a1f95006ade9a0eddf65085a7d566357bb2d8232b6475206f938ba`
- HSE pronto con [codice 0](reset-hse-ready-adc-0-runtime.tsv) e [codice 2048](reset-hse-ready-adc-2048-runtime.tsv)
- HSE assente con [codice 0](reset-hse-timeout-adc-0-runtime.tsv) e [codice 2048](reset-hse-timeout-adc-2048-runtime.tsv)

Per riprodurre aggiungere `--adc-sample 0 --frame-index 2 --frame-output FILE` al probe con `--spi --virtual-tick --complete-display --timers --watchdog --preferences`.
