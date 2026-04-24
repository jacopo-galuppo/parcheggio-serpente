/*
  Definizione e implementazione dell'ADT stack e delle funzioni
  di creazione, distruzione, aggiunta, rimozione/lettura,
  sola lettura, verifica vuoto, verifica pieno, stampa
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

struct _stack {
	int* elements;  //array di elementi
	int max_capacity;  //capacità massima
	int current_capacity;  //capacità logica
};

stack stack_create(int _size) {

	if (_size <= 0)
		return NULL;

	stack s = (stack)malloc(sizeof(struct _stack));  //creo lo stack
	if (s == NULL)
		return NULL;

	s->elements = (int*)calloc(_size, sizeof(int));  //creo l'array che contiene solo gli elementi dello stack
	if (s->elements == NULL) {
		free(s);
		s = NULL;
		return NULL;
	}

	s->current_capacity = 0;
	s->max_capacity = _size;

	return s;
}

short stack_destroy(stack* _s) {

	if (_s == NULL || *_s == NULL)
		return STACK_ERROR_NULL;

	free((*_s)->elements);  //libero l'array che compone lo stack
	free(*_s);  //libero lo stack
	*_s = NULL;  //il main punta a NULL ed evito dangling reference

	return STACK_SUCCESS;
}

short stack_push(stack _s, int _new_element) {

	if (_s == NULL)
		return STACK_ERROR_NULL;

	if (_s->current_capacity == _s->max_capacity)
		return STACK_ERROR_FULL;

	_s->elements[_s->current_capacity++] = _new_element;  //inserisco con la dimensione logica che aumento subito dopo

	return STACK_SUCCESS;
}

short stack_pop(stack _s, int* _extracted_element) {

	if (_s == NULL || _extracted_element == NULL)
		return STACK_ERROR_NULL;

	if (!_s->current_capacity)
		return STACK_ERROR_EMPTY;

	*_extracted_element = _s->elements[_s->current_capacity - 1];  //inserisco l'elemento nella viarbile puntata
	_s->current_capacity--;  //diminuisco la dimensione logica, eliminando logicamente l'elemento visualizzato

	return STACK_SUCCESS;
}

short stack_top(const stack _s, int* _top_element) {

	if (_s == NULL || _top_element == NULL)
		return STACK_ERROR_NULL;

	if (!_s->current_capacity)
		return STACK_ERROR_EMPTY;

	*_top_element = _s->elements[_s->current_capacity - 1];  //inserisco l'elemento senza eliminarlo

	return STACK_SUCCESS;

}

bool stack_is_empty(const stack _s) {

	if (_s == NULL)
		return false;

	if (!_s->current_capacity)
		return true;
	else
		return false;
}

bool stack_is_full(const stack _s) {

	if (_s == NULL)
		return false;

	if (_s->current_capacity == _s->max_capacity)
		return true;
	else
		return false;
}

short stack_print(const stack _s) {

	if (_s == NULL)
		return STACK_ERROR_NULL;

	if (!_s->current_capacity)
		return STACK_ERROR_EMPTY;

	for (int i = 0; i < _s->current_capacity; i++) {
		printf("%d\t", _s->elements[i]);
	}

	return STACK_SUCCESS;  //in questo modo se restituisce diverso da STACK_SUCCESS segnalo errore, altrimenti stampa
}