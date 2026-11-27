# Aree irrisolte

L'indice di lavoro conserva i 415 indirizzi originali. I puntatori Thumb a `0x08016100`–`0x0801613f` includono sette destinazioni aggiuntive; lo slot a `0x08016108` è nullo. Il dispatcher a `0x08014ce0` carica la base da `0x08014cf8` e chiama la destinazione indicizzata a `0x08014cee`. Il ruolo delle singole routine e i vincoli sull’indice restano da verificare.

Le corrispondenze dei registri indicano indirizzi caricati come costanti. L'operazione successiva e il ruolo sulla scheda richiedono riscontro.

## Trasferimenti indiretti e tabelle

| Indirizzo | Istruzione | Evidenza |
|---|---|---|
| `0x08005152` | `bx r0` | target statico `0x080115f4`, letterale Thumb `0x080115f5` |
| `0x080052ce` | `blx r0` | target statico `0x0800a648`, letterale Thumb `0x0800a649` |
| `0x080052d2` | `bx r0` | target statico `0x08005148`, letterale Thumb `0x08005149` |
| `0x08005384` | `blx r2` | origine del puntatore e target da verificare |
| `0x08005c3c` | `blx r3` | origine del puntatore e target da verificare |
| `0x0800a7dc` | `blx r0` | origine del puntatore e target da verificare |
| `0x0800acfa` | `ldr.w pc,[sp],#0x14` | ritorno probabile tramite stack |
| `0x0800ad30` | `ldr.w pc,[sp],#0x14` | ritorno probabile tramite stack |
| `0x0800ad56` | `ldr.w pc,[sp],#0x14` | ritorno probabile tramite stack |
| `0x0800d6fc` | `blx r2` | origine del puntatore e target da verificare |
| `0x0800d7ae` | `blx r2` | origine del puntatore e target da verificare |
| `0x0800d968` | `blx r2` | origine del puntatore e target da verificare |
| `0x0800d98c` | `blx r2` | origine del puntatore e target da verificare |
| `0x0800d9aa` | `blx r2` | origine del puntatore e target da verificare |
| `0x0800dc12` | `blx r2` | origine del puntatore e target da verificare |
| `0x0800dc46` | `blx r2` | origine del puntatore e target da verificare |
| `0x0800dc60` | `blx r2` | origine del puntatore e target da verificare |
| `0x0800dc78` | `blx r2` | origine del puntatore e target da verificare |
| `0x0800dcb2` | `blx r6` | origine del puntatore e target da verificare |
| `0x0800dce0` | `blx r6` | origine del puntatore e target da verificare |
| `0x0800dcf6` | `tbb [pc,r4]` | `0x0800dcfa`–`0x0800dd00`; 7 voci in ordine di indice: `0x0800dd26`, `0x0800dd1c`, `0x0800dd10`, `0x0800dd12`, `0x0800dd02`, `0x0800dd04`, `0x0800dd06` |
| `0x0800e88a` | `tbb [pc,r0]` | `0x0800e88e`–`0x0800e8a1`; 20 voci in ordine di indice: `0x0800e8a2`, `0x0800e8b8`, `0x0800e8ce`, `0x0800ea44`, `0x0800e8e4`, `0x0800e8fa`, `0x0800e910`, `0x0800e926`, `0x0800e93c`, `0x0800e956`, `0x0800e96e`, `0x0800e984`, `0x0800e99c`, `0x0800e9b4`, `0x0800e9cc`, `0x0800e9e4`, `0x0800e9fc`, `0x0800ea44`, `0x0800ea14`, `0x0800ea2c` |
| `0x0800f55a` | `blx r3` | origine del puntatore e target da verificare |
| `0x0800f86e` | `blx r3` | origine del puntatore e target da verificare |
| `0x0800fd0a` | `blx r3` | origine del puntatore e target da verificare |
| `0x0800fe08` | `blx r3` | origine del puntatore e target da verificare |
| `0x0800feca` | `blx r3` | origine del puntatore e target da verificare |
| `0x08010026` | `blx r3` | origine del puntatore e target da verificare |
| `0x0801005e` | `blx r3` | origine del puntatore e target da verificare |
| `0x0801045c` | `blx r3` | origine del puntatore e target da verificare |
| `0x08010d48` | `tbb [pc,r2]` | `0x08010d4c`–`0x08010d50`; 5 voci in ordine di indice: `0x08010d52`, `0x08010d94`, `0x08010db0`, `0x08010e2e`, `0x08010e36` |
| `0x08011ce8` | `blx r2` | origine del puntatore e target da verificare |
| `0x08011eaa` | `blx r2` | origine del puntatore e target da verificare |
| `0x0801248e` | `tbb [pc,r1]` | `0x08012492`–`0x08012499`; 8 voci in ordine di indice: `0x080124b0`, `0x0801249a`, `0x0801249e`, `0x080124a0`, `0x080124a4`, `0x080124a6`, `0x080124aa`, `0x080124ac` |
| `0x08012904` | `tbb [pc,r0]` | `0x08012908`–`0x0801290d`; 6 voci in ordine di indice: `0x0801290e`, `0x08012920`, `0x08012948`, `0x080129c6`, `0x08012a2c`, `0x08012a78` |
| `0x08012f6c` | `tbb [pc,r0]` | `0x08012f70`–`0x08012f75`; 6 voci in ordine di indice: `0x08012f76`, `0x08012f90`, `0x08012fb6`, `0x080130c0`, `0x08013168`, `0x08013166` |
| `0x08014cee` | `blx r0` | dispatch attraverso la tabella `0x08016100`; 15 target Thumb e uno slot nullo; vincoli sull’indice da verificare |

## Confine codice e dati

Le sei tabelle TBB delimitate sopra sono dati. Le tabelle dei puntatori UI a `0x08016050`–`0x080160ff` e `0x08016380`–`0x080163bf` sono documentate in [ui-pointer-table.tsv](ui-pointer-table.tsv). Nella prima, l’export originale aveva interpretato 88 mezze parole come istruzioni. Le tabelle sono state definite come dati nel progetto di lavoro mediante `DefineT90UiData.java`. I confini del pool dei letterali e delle aree non raggiunte dall’analisi restano aperti. Per esempio la sequenza dopo il trasferimento a `0x08005152` contiene la parola letta come destinazione a `0x08005154` e quella caricata in SP a `0x08005158`. Il ruolo dell’intervallo `0x08005000`–`0x08005147` oltre alle voci del vettore riconosciute da SeedT90 va verificato.

## Basi SVD escluse dal confronto automatico

- `0xe0042000` DBG: base senza riscontro nella mappa estratta.
- `0x40003400` TSC: base senza riscontro nella mappa estratta.
