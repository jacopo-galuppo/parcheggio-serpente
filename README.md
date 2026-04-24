# 🚗 Progetto Parcheggio Serpente

*Progetto realizzato a scopo didattico in UNIMOL*

Esercitazione in linguaggio C che simula la gestione di un parcheggio dinamico utilizzando strutture dati astratte (ADT).

## 📋 Descrizione
Il progetto implementa la logica di un "parcheggio a serpente" dove la movimentazione dei veicoli è gestita attraverso l'integrazione di pile e code. Il sistema permette di gestire l'afflusso e il deflusso delle auto ottimizzando gli spazi secondo la logica ADT.

### Funzionalità principali:
* Inserimento e gestione veicoli nel sistema.
* Gestione delle priorità di uscita tramite strutture LIFO/FIFO.
* Modulo dedicato per la gestione della logica specifica del parcheggio.

## 🧠 Dettagli di Implementazione e Metodologia
Il software è stato sviluppato adottando un approccio di **collaborazione uomo-macchina**. La logica applicativa dell'ADT parking sono state realizzate da me, mentre la stesura del codice è stata supportata dall'intelligenza artificiale per garantirne la robustezza e l'aderenza agli standard del linguaggio C. La logica applicativa e l'implementazione degli ADT stack e queue sono state viste in aula e riutilizzate come fossero asset, per valorizzarne il riuso

### Il mio processo creativo:
1. **Progettazione Logica:** Ho definito la logica che riuscisse a gestire le comunicazioni tra i tre ADT.
2. **Generazione Assistita:** Ho utilizzato l'IA per revisionare il mio codice o per generarne di nuovo, ferme restando le mie idee e la mia logica.
3. **Revisione e Refactoring:** Sono intervenuto manualmente e direttamente sui codici generati dall'IA per garantire la mia logica e le mie idee

In questo modo ho gestito meglio l'architettura piuttosto che il codice stesso, considerato che l'IA è un potente mezzo in grado di generare codice
da utilizzare. Specifico che ho dato io le direttive all'IA affinché seguisse le mie regole. Ho più volte modificato e corretto l'IA verificando ogni
riga di codice e adattandola al mio stile di programmazione (ad esempio controllando ogni valore di ritorno dalle funzioni)

## 🛠️ Architettura del Software
Il codice è modulare e suddiviso in tre diverse ADT (Abstract Data Types):

1. **Stack (Pila):** Utilizzata per la gestione LIFO (Last-In-First-Out), quando le auto entrano nel parcheggio o nello spazio di manovra, quest'ultimo
                     utile per consentire l'uscita dal parcheggio.
2. **Queue (Coda):** Utilizzata per la gestione FIFO (First-In-First-Out), quando le auto arrivano nel parcheggio e devono attendere di potersi parcheggiare.
3. **Parking:** Utilizzato per integrare tutte le strutture dati utilizzate e per consentirne l'interazione.

## 📂 Struttura dei File
* `main.c` - File che consente di testare le funzioni e i casi specifici previsti dall'ADT.
* `parking.h / .c` - Interfaccia dell'ADT parking nell'header file, implementazione delle sue funzioni nel .c.
* `stack.h / .c` - Interfaccia dell'ADT stack nell'header file, implementazione delle sue funzioni nel .c  (tutto svolto in aula).
* `queue.h / .c` - Interfaccia dell'ADT queue nell'header file, implementazione delle sue funzioni nel .c (tutto svolto in aula).

## 🚀 Compilazione ed Esecuzione

### Su Visual Studio (Windows)
1. Apri **Visual Studio**.
2. Crea un nuovo **Progetto Vuoto (C++)**.
3. Nella cartella del progetto, inserisci tutti i file `.c` e `.h`.
4. In *Esplora Soluzioni*, aggiungi i file `.c` ai **File di Origine** e i file `.h` ai **File di Intestazione**.
5. Premi **F5** per compilare ed eseguire.

### Da Terminale (GCC)
Se utilizzi un compilatore standard come GCC:
```bash
gcc *.c -o parcheggio_serpente
./parcheggio_serpente
```
