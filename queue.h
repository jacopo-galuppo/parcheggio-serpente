/*
  Dichiarazione di un ADT queue (coda) di interi con array

  Dichiarazione di funzioni per creazione (create),
  distruzione (destroy), aggiunta di un elemento (enqueue),
  eliminazione e lettura di un elemento (dequeue),
  sola lettura (peek), verifica se vuota (is_empy),
  verifica se piena (is_full), stampa (print)

*/

#include <stdbool.h>

#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_SUCCESS 0
#define QUEUE_ERROR_NULL 1
#define QUEUE_ERROR_EMPTY 2
#define QUEUE_ERROR_FULL 3

typedef struct _queue* queue;

/*
  Crea una queue utilizzando un array
  Parametro _capacity è la capacità massima
  Ritorna puntatore alla queue creata
          NULL se non riesce a creare
*/
queue queue_create(int _capacity);

/*
  Distrugge la queue creata
  Parametro *_q è il doppio puntatore alla queue da eliminare
  Ritorna QUEUE_SUCCESS se dealloca correttamente
          QUEUE_ERROR_NULL se il puntatore è null
*/
short queue_destroy(queue* _q);

/*
  Aggiunge elemento alla coda
  Parametro _q è la coda
  Parametro _new_element è l'elemento da aggiungere
  Ritorna QUEUE_SUCCESS se aggiunge correttamente
          QUEUE_ERROR_NULL se puntatori nulli
          QUEUE_ERROR_FULL se la coda è piena
*/
short queue_enqueue(queue _q, int _new_element);

/*
  Legge e rimuove elemento meno recente
  Parametro _q è la coda
  Parametro *_extracted_element è il puntatore in cui inserire l'elemento
  Ritorna QUEUE_SUCCESS se rimuove correttamente
          QUEUE_ERROR_NULL se puntatori nulli
          QUEUE_ERROR_EMPTY se la coda è vuota
*/
short queue_dequeue(queue _q, int* _extracted_element);

/*
  Legge l'elemento meno recente senza toccare la coda
  Parametro const queue const _q  è la coda
  Parametro *_oldest_element è il puntatore in cui inserire l'elemento
  Ritorna QUEUE_SUCCESS se legge correttamente
          QUEUE_ERROR_NULL se puntatori nulli
          QUEUE_ERROR_EMPTY se la coda è vuota
*/
short queue_peek(const queue _q, int* _oldest_element);

/*
  Mi dice se la funzione è vuota senza toccarla
  Parametro const queue const _q è la coda
  Ritorna true se vuota
          false altrimenti
*/
bool queue_is_empty(const queue _q);

/*
  Mi dice se la funzione è piena senza toccarla
  Parametro const queue const _q è la coda
  Ritorna true se piena
          false altrimenti
*/
bool queue_is_full(const queue _q);

/*
  Stampa la coda, anche circolare, senza toccarla
  Parametro const queue const _q è la coda
  Ritorna QUEUE_SUCCESS se non ho problemi
          QUEUE_ERROR_NULL se puntatori nulli
*/
short queue_print(const queue _q);

#endif