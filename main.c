/*
  Utilizzo dell'ADT parking sfruttando
  le funzionalità presenti nel file prova_esame1.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parking.h"


int main() {
    // 1. ALL'AVVIO: Creazione del parcheggio (max 5 in coda per il test)
    parking my_park = parking_create(5);

    if (my_park == NULL) {
        printf("ERRORE: Impossibile allocare il parcheggio.\n");
        return -1;
    }

    int scelta, id_auto, posizione, auto_da_coda;
    short status;
    bool sistema_attivo = true;

    printf("=== SISTEMA DI GESTIONE PARCHEGGIO SERPENTE ===\n");

    while (sistema_attivo) {
        printf("\n--- MENU PRINCIPALE ---\n");
        printf("1. Inserisci Auto\n");
        printf("2. Rimuovi Auto\n");
        printf("0. Esci dal programma\n");
        printf("Scelta: ");

        // Leggiamo la scelta dell'utente
        scanf("%d", &scelta);

        switch (scelta) {
        case 1: // --- LOGICA INSERIMENTO ---
            printf("Inserire ID auto: ");
            scanf("%d", &id_auto);
            status = parking_push(my_park, id_auto, &posizione);

            switch (status) {
            case PARKING_GO_IN_PARK:
                printf("OK: Auto %d parcheggiata. Distanza cima: %d\n", id_auto, posizione);
                break;
            case PARKING_GO_IN_QUEUE:
                printf("CODA: Auto %d in attesa. Distanza testa: %d\n", id_auto, posizione);
                break;
            case PARKING_ERROR_ALREADY_COUNTED:
                printf("AVVISO: Auto %d gia' presente nel sistema.\n", id_auto);
                break;
            case PARKING_ERROR_FULL:
                printf("AVVISO: Sistema pieno. Impossibile inserire.\n");
                break;
            case PARKING_CRITICAL_ERROR:
                printf("!!! CRITICAL ERROR !!!: Integrita' compromessa. Chiusura forzata.\n");
                parking_destroy(&my_park);
                return -1;
            default:
                printf("ERRORE: Risposta del sistema non riconosciuta.\n");
                break;
            }
            break;

        case 2: // --- LOGICA RIMOZIONE ---
            printf("Inserire ID auto da rimuovere: ");
            scanf("%d", &id_auto);
            status = parking_pop(my_park, id_auto, &auto_da_coda);

            switch (status) {
            case PARKING_SUCCESS:
                printf("OK: Auto %d uscita.\n", id_auto);
                if (auto_da_coda != -1)
                    printf("INFO: Auto %d entrata dalla coda nel parcheggio.\n", auto_da_coda);
                break;
            case PARKING_ERROR_NOT_FOUND:
                printf("AVVISO: Auto %d mai registrata.\n", id_auto);
                break;
            case PARKING_ERROR_NOT_PARKED:
                printf("AVVISO: Auto %d ancora in coda. Non puo' uscire.\n", id_auto);
                break;
            case PARKING_ERROR_MANEUVER_SPACE:
                printf("AVVISO: Impossibile uscire (Troppe auto sopra).\n");
                break;
            case PARKING_CRITICAL_ERROR:
                printf("!!! CRITICAL ERROR !!!: Integrita' compromessa. Chiusura forzata.\n");
                parking_destroy(&my_park);
                return -1;
            default:
                printf("ERRORE: Risposta del sistema non riconosciuta.\n");
                break;
            }
            break;

        case 0: // --- LOGICA USCITA ---
            sistema_attivo = false;
            break;

        default: // --- INPUT ERRATO O CARATTERI ---
            printf("Scelta non valida. Reinserire correttamente.\n");
            // Pulisce il buffer se l'utente inserisce lettere per sbaglio
            while (getchar() != '\n');
            break;
        }
    }

    // 2. ALLA CHIUSURA: Distruzione e rilascio memoria
    parking_destroy(&my_park);
    printf("\nSistema chiuso correttamente.\n");

    printf("Premi ovunque per uscire...");
    getchar();  //pulizia buffer
    getchar();  //fine programma

    return 0;
}
