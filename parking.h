/*
  Dichiarazione dell'ADT parking

  Dichiarazione di 4 funzioni, creazione (create),
  distruzione (destroy), inserisci auto (push), rimuovi auto (pop)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"  //per il parcheggio e per lo spazio di manovra, LIFO
#include "queue.h"  //per la coda di attesa, FIFO

#ifndef PARKING_H
#define PARKING_H

#define PARKING_GO_IN_PARK (-1)
#define PARKING_GO_IN_QUEUE (-2)
#define PARKING_ERROR_FULL (-3)
#define PARKING_ERROR_ALREADY_COUNTED (-4)
#define PARKING_ERROR_NOT_PARKED (-5)
#define PARKING_ERROR_NOT_FOUND (-6)
#define PARKING_ERROR_MANEUVER_SPACE (-7)
#define PARKING_SUCCESS (-8)
#define PARKING_ERROR_NULL (-9)
#define PARKING_CRITICAL_ERROR (-10)

/*
  Creazione tipo di dato parking tramite puntatore opaco
*/
typedef struct _parking* parking;

/*
  Crea il parcheggio
  Parametro _max_wait è la lunghezza massima della coda di attesa
  Ritorna il puntatore a parking	
		  NULL se non riesce a creare il parcheggio
*/
parking parking_create(int _max_wait);

/*
  Distrugge il parcheggio
  Parametro *_park è il puntatore al parcheggio, evito dangling pointers nel main
  Ritorna PARKING_SUCCESS se dealloca correttamente
		  PARKING_ERROR_NULL se puntatori nulli
*/
short parking_destroy(parking* _park);

/*
  Aggiunge un auto, verificando se va in coda o nel parcheggio
  Parametro _park è il parcheggio
            _car è la macchina inserita, rappresentata dall'intero
			*_position la posizione dove è stata inserita, NULL se non può entrare
  Ritorna PARKING_GO_IN_QUEUE se va in coda
		  PARKING_GO_IN_PARK se va nel parcheggio
		  PARKING_ERROR_FULL se non va da nessuna delle due parti
		  PARKING_ERROR_ALREADY_COUNTED se l'auto è gia presente
		  PARKING_CRITICAL_ERROR se perdo le macchine
*/
short parking_push(parking _park, int _car, int* _position);

/*
  La macchina esce dal parcheggio se possibile
  Parametro _park è il parcheggio
			_car per la macchina che deve uscire
			*_queue_car è la macchina che va dalla coda al parcheggio
			            la metto a -1 se fallisco
  Ritorna PARKING_GO_OUT se l'auto è uscita correttamente
		  PARKING_ERROR_ALREADY_COUNTED se l'auto c'era già ma in coda
		  PARKING_ERROR_NOT_FOUND se non l'ho trovata
		  PARKING_ERROR_NOT_PARKED se non ho parcheggiato dalla coda
		  PARKING_ERROR_MANEUVER_SPACE se non ho abbastanza spazio di manovra
		  PARKING_CRITICAL_ERROR se perdo le macchine
*/
short parking_pop(parking _park, int _car, int* _queue_car);

#endif