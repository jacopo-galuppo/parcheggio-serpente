/*
  Dichiarazione dell'ADT stack tramite array statico di interi

  Dichiarazione di funzioni utili alla creazione (create),
  distruzione (destroy), aggiunta in cima (push), eliminazione e lettura in cima (pop),
  lettura in cima (top), verifica se lo stack è vuoto (is_empty), pieno (is_full), stampa stack (print)
*/

#include <stdbool.h>    

#ifndef STACK_H
#define STACK_H

#define STACK_SUCCESS 0
#define STACK_ERROR_ALLOC -1
#define STACK_ERROR_NULL -2
#define STACK_ERROR_FULL -3
#define STACK_ERROR_EMPTY -4


/*
  Creazione tipo di dato stack con puntatore opaco
*/
typedef struct _stack* stack;

/*
  Funzione che crea lo stack
  Parametro size per la dimensione massima dello stack
  Ritorna il puntatore allo stack creato, NULL se fallisce la creazione
*/
stack stack_create(int _size);

/*
  Funzione che libera tutta la memoria allocata per lo stack
  Parametro *_s è il puntatore alla zona di memoria da liberare
  Ritorna STACK_SUCCESS, STACK_ERROR_NULL a seconda dei casi
*/
short stack_destroy(stack* _s);

/*
  Funzione che aggiunge un elemento in cima allo stack
  Parametro _s è lo stack su cui lavoro
  Parametro _new_element è l'elemento da aggiungere passato per valore
  Ritorna STACK_SUCCESS, STACK_ERROR_NULL, STACK_ERROR_FULL a seconda dei casi
*/
short stack_push(stack _s, int _new_element);

/*
  Funzione che visualizza ed elimina l'elemento in cima allo stack
  Parametro _s è lo stack su cui lavoro
  Parametro *_extracted_element è l'elemento da leggere e rimuovere
            passato per riferimento per salvarlo in una variabile del main
  Ritorna STACK_SUCCESS, STACK_ERROR_NULL, STACK_ERROR_EMPTY a seconda dei casi
*/
short stack_pop(stack _s, int* _extracted_element);

/*
  Funzione che visualizza l'elemento in cima senza modificare lo stack (il const rende la struct costante, proteggendola)
  Parametro const stack const _s è lo stack su cui lavoro
  Parametro *_top_element è l'elemento da leggere passato
            per riferimento per salvarlo in una variabile del main
  Ritorna STACK_SUCCESS, STACK_ERROR_NULL, STACK_ERROR_EMPTY a seconda dei casi
*/
short stack_top(const stack _s, int* _top_element);

/*
  Funzione che verifica se lo stack è vuoto senza modificarlo (il const rende la struct costante, proteggendola)
  Parametro const stack const _s è lo stack da valutare
  Ritorna true se vuoto, false altrimenti o se _s è NULL
*/
bool stack_is_empty(const stack _s);

/*
  Funzione che verifica se lo stack è pieno senza modificarlo (il const rende la struct costante, proteggendola)
  Parametro const stack const _s è lo stack da valutare
  Ritorna true se pieno, false altrimenti o se _s è NULL
*/
bool stack_is_full(const stack _s);

/*
  Funzione che stampa gli elementi dello stack senza modificarlo (il const rende la struct costante, proteggendola)
  Parametro const stack const _s è lo stack da stampare
  Ritorna STACK_SUCCESS, STACK_ERROR_NULL, STACK_ERROR_EMPTY a seconda dei casi
*/
short stack_print(const stack _s);

#endif
