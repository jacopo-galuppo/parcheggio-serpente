/*
  Implementazione dell'ADT queue e definizione delle sue funzioni dichiarate in queue.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

struct _queue {
	int* elements;  //array di elementi
	int head;  //indice dell'elemento da rimuovere
	int tail;  //indice della posizione in cui aggiungere 
	int current_capacity;  //dim logica
	int max_capacity;  //dim fissa
};

queue queue_create(int _capacity) {
	if (_capacity <= 0)
		return NULL;

	queue q = malloc(sizeof(struct _queue));
	if (q == NULL)
		return NULL;

	q->elements = calloc(_capacity, sizeof(int));
	if (q->elements == NULL) {
		free(q);
		q = NULL;
		return NULL;
	}

	q->head = q->tail = q->current_capacity = 0;
	q->max_capacity = _capacity;

	return q;
}

short queue_destroy(queue* _q) {
	if (_q == NULL || *_q == NULL)
		return QUEUE_ERROR_NULL;

	free((*_q)->elements);
	free(*_q);
	*_q = NULL;

	return QUEUE_SUCCESS;
}

short queue_enqueue(queue _q, int _new_element) {
	if (_q == NULL)
		return QUEUE_ERROR_NULL;

	if (_q->current_capacity == _q->max_capacity)
		return QUEUE_ERROR_FULL;

	_q->elements[_q->tail] = _new_element;  //aggiungo alla coda
	_q->tail = (_q->tail + 1) % _q->max_capacity;  //aggiorno la coda che, dopo aver raggiungo max_capacity-1, tornerà a 0, coda circolare
	_q->current_capacity++;  //aggiorno la dimensione logica

	return QUEUE_SUCCESS;
}

short queue_dequeue(queue _q, int* _extracted_element) {
	if (_q == NULL || _extracted_element == NULL)
		return QUEUE_ERROR_NULL;

	if (!_q->current_capacity)
		return QUEUE_ERROR_EMPTY;

	*_extracted_element = _q->elements[_q->head];
	_q->head = (_q->head + 1) % _q->max_capacity;
	_q->current_capacity--;

	return QUEUE_SUCCESS;
}

short queue_peek(const queue _q, int* _oldest_element) {
	if (_q == NULL || _oldest_element == NULL)
		return QUEUE_ERROR_NULL;

	if (!_q->current_capacity)
		return QUEUE_ERROR_EMPTY;

	*_oldest_element = _q->elements[_q->head];

	return QUEUE_SUCCESS;
}

bool queue_is_empty(const queue _q) {
	if (_q == NULL) return false;
	return (_q->current_capacity == 0); //mi assicuro sempre un return
}

bool queue_is_full(const queue _q) {
	if (_q == NULL) return false;
	return (_q->current_capacity == _q->max_capacity);  //mi assicuro sempre un return 
}

short queue_print(const queue _q) {
	if (_q == NULL)
		return QUEUE_ERROR_NULL;

	for (int i = 0; i < _q->current_capacity; i++) {
		printf("%d\n", _q->elements[(_q->head + i) % _q->max_capacity]);
	}

	return QUEUE_SUCCESS;
}