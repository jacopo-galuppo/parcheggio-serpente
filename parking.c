/*
  Implementazione dell'ADT parking sfruttando stack e queue
  Implementazioni di funzioni private per funzioni specifiche (car_is_present, get_car_distance, get_queue_distance)
  Implementazioni di funzioni pubbliche (create, destroy, push e pop)
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "parking.h"


struct _parking {
	stack stack_park;
	stack stack_maneuver;
	queue queue_waiting;
	int waiting_capacity;
};

//-----------------FUNZIONI AUSILIARIE E INTERNE----------------------------------

/*
  Verifica se un auto è già presente nel parcheggio con stack e code di appoggio
  Parametro _park è il parcheggio
			_car è la macchina che devo verificare
			*_found è la variabile in cui inserire se ho già trovato
  Ritorna PARKING_CRITICAL_ERROR se perdo le macchine quando le ripristino
		  PARKING_ERROR_NULL se puntatori nulli
		  PARKING_SUCCESS se non ho errori
*/
static short parking_car_is_present(parking _park, int _car, bool* _found) {
	if (_park == NULL || _found == NULL)
		return PARKING_ERROR_NULL;

	stack temp_stack = stack_create(10);
	if (temp_stack == NULL)
		return PARKING_ERROR_NULL;

	int car_to_found;
	*_found = false;

	//sposto le macchine dallo stack originale ad uno di appoggio
	while (stack_pop(_park->stack_park, &car_to_found) == STACK_SUCCESS) {
		if (car_to_found == _car)
			*_found = true;

		if (stack_push(temp_stack, car_to_found) != STACK_SUCCESS) {
			if (stack_push(_park->stack_park, car_to_found) != STACK_SUCCESS) {
				stack_destroy(&temp_stack);
				return PARKING_CRITICAL_ERROR;  //errore critico, se non riesco a metterla nel temporaneo e non riesco a portarla nell'originale, l'ho persa
			}
			stack_destroy(&temp_stack);
			return PARKING_CRITICAL_ERROR;  //non sono riuscito comunque a metterla nel temporaneo, l'ho salvata ma mi fermo lo stesso
		}

		if (*_found == true)
			break;
	}

	//rimetto le macchine nello stack originale
	while (stack_pop(temp_stack, &car_to_found) == STACK_SUCCESS) {
		if (stack_push(_park->stack_park, car_to_found) != STACK_SUCCESS) {
			stack_destroy(&temp_stack);
			return PARKING_CRITICAL_ERROR; //errore critico perché si perde l'auto dato che non riesco più a metterla nello stack originale
		}
			
	}

	stack_destroy(&temp_stack);  //non controllo perché non rischio danni alle altre strutture fondamentali

	if (*_found == true)
		return PARKING_SUCCESS;

	queue temp_queue = queue_create(_park->waiting_capacity);
	if (temp_queue == NULL)
		return PARKING_ERROR_NULL;

	//sposto le macchine dalla coda originale a quella di appoggio
	while (queue_dequeue(_park->queue_waiting, &car_to_found) == QUEUE_SUCCESS) {
		if (car_to_found == _car)
			*_found = true;

		if (queue_enqueue(temp_queue, car_to_found) != QUEUE_SUCCESS) {
			if (queue_enqueue(_park->queue_waiting, car_to_found) != QUEUE_SUCCESS) {
				queue_destroy(&temp_queue);
				return PARKING_CRITICAL_ERROR;  //errore critico, se non riesco a metterla nel temporaneo e non riesco a portarla nell'originale, l'ho persa
			}
			queue_destroy(&temp_queue);
			return PARKING_CRITICAL_ERROR;  //non sono riuscito comunque a metterla nel temporaneo, l'ho salvata ma mi fermo lo stesso
		}
	}

	//rimetto le macchine nella coda originale
	while (queue_dequeue(temp_queue, &car_to_found) == QUEUE_SUCCESS) {
		if (queue_enqueue(_park->queue_waiting, car_to_found) != QUEUE_SUCCESS) {
			queue_destroy(&temp_queue);
			return PARKING_CRITICAL_ERROR; //errore critico perché si perde l'auto dato che non riesco più a metterla nella coda originale
		}
			
	}

	queue_destroy(&temp_queue);  //non controllo perché non rischio danni alle altre strutture fondamentali

	if (*_found == true)
		return PARKING_SUCCESS;

	return PARKING_SUCCESS;  //0 errori ma non l'ho trovata
}

/*
  Controlla quante macchine devo spostare per farne uscire una
  Parametro _s è lo stack (parcheggio) da cui devono uscire le macchine
			_car è la macchina che devo trovare prima di uscire
			*_distance è la distanza dalla prima a quella che deve uscire
  Ritorna PARKING_CRITICAL_ERROR se perdo un auto
		  PARKING_ERROR_NULL se ho puntatori nulli
		  PARKING_SUCCESS se non ho trovato errori
*/
static short parking_get_car_distance(stack _s, int _car, int* _distance) {
	if (_s == NULL || _distance == NULL)
		return PARKING_ERROR_NULL;

	stack temp_stack = stack_create(10);
	if (temp_stack == NULL)
		return PARKING_ERROR_NULL;

	int current_car;
	int count = 0;
	bool found = false;
	*_distance = -1;

	while (stack_pop(_s, &current_car) == STACK_SUCCESS) {
		if (current_car == _car)
			found = true;

		if (stack_push(temp_stack, current_car) != STACK_SUCCESS) {
			if (stack_push(_s, current_car) != STACK_SUCCESS) {
				stack_destroy(&temp_stack);
				return PARKING_CRITICAL_ERROR;  //la perdo se non riesco a metterla né nell'originale né nel temporaneo
			}
			stack_destroy(&temp_stack);
			return PARKING_CRITICAL_ERROR;  //mi fermo perché non sono riuscito a metterla nel temporaneo
		}

		if (found == true)
			break;

		count++;
	}

	while (stack_pop(temp_stack, &current_car) == STACK_SUCCESS) {
		if (stack_push(_s, current_car) != STACK_SUCCESS) {
			stack_destroy(&temp_stack);
			return PARKING_CRITICAL_ERROR; //non sono riuscito a riprisitinare il parcheggio iniziale
		}
	}

	stack_destroy(&temp_stack);

	if (found == true)
		*_distance = count;
	else
		*_distance = -1;

	return PARKING_SUCCESS;
}

/*
  Conta quanti elementi ho in coda per avere la posizione quando inserisco
  Parametro _q è la queue (attesa) da valutare
			_capacity per la dimensione della coda di travaso
			*_count sono le macchine presenti
  Ritorna PARKING_CRITICAL_ERROR se perdo un auto
		  PARKING_ERROR_NULL se ho puntatori nulli
		  PARKING_SUCCESS se non ho errori
*/
static short parking_get_queue_distance(queue _q, int _capacity, int* _count) {
	if (_q == NULL || _count == NULL)
		return PARKING_ERROR_NULL;

	queue temp_queue = queue_create(_capacity);
	if (temp_queue == NULL)
		return PARKING_ERROR_NULL;

	int car_to_remove;
	int local_count = 0;

	while (queue_dequeue(_q, &car_to_remove) == QUEUE_SUCCESS) {
		local_count++;
		
		if (queue_enqueue(temp_queue, car_to_remove) != QUEUE_SUCCESS) {
			if (queue_enqueue(_q, car_to_remove) != QUEUE_SUCCESS) {
				queue_destroy(&temp_queue);
				return PARKING_CRITICAL_ERROR;
			}
			queue_destroy(&temp_queue);
			return PARKING_CRITICAL_ERROR;
		}
	}

	while (queue_dequeue(temp_queue, &car_to_remove) == QUEUE_SUCCESS) {
		if (queue_enqueue(_q, car_to_remove) != QUEUE_SUCCESS) {
			queue_destroy(&temp_queue);
			return PARKING_CRITICAL_ERROR;
		}
	}

	queue_destroy(&temp_queue);

	*_count = local_count;

	return PARKING_SUCCESS;
}


//---------------------FUNZIONI PUBBLICHE-------------------------------------
parking parking_create(int _max_wait) {
	if (_max_wait <= 0)
		return NULL;

	parking p = (parking)malloc(sizeof(struct _parking));
	if (p == NULL)
		return NULL;

	stack park = stack_create(10);
	if (park == NULL) {
		free(p);
		return NULL;
	}

	stack maneuver = stack_create(4);
	if (maneuver == NULL) {
		stack_destroy(&park);
		free(p);
		return NULL;
	}

	queue wait = queue_create(_max_wait);
	if (wait == NULL) {
		stack_destroy(&maneuver);
		stack_destroy(&park);
		free(p);
		return NULL;
	}
	
	p->stack_park = park;
	p->stack_maneuver = maneuver;
	p->queue_waiting = wait;
	p->waiting_capacity = _max_wait;

	return p;
}

short parking_destroy(parking* _park) {
	if (_park == NULL || *_park == NULL)
		return PARKING_ERROR_NULL;

	stack_destroy(&(*_park)->stack_park);
	stack_destroy(&(*_park)->stack_maneuver);
	queue_destroy(&(*_park)->queue_waiting);
	free(*_park);
	*_park = NULL;

	return PARKING_SUCCESS;
}

short parking_push(parking _park, int _car, int* _position) {
	if (_park == NULL || _position == NULL)
		return PARKING_ERROR_NULL;

	bool found = false; //da inserire nelle ausiliarie
	short status;
	*_position = -1;

	status = parking_car_is_present(_park, _car, &found);
	if (status != PARKING_SUCCESS)
		return status; //ritorno il codice di errore specifico 
	if (found == true)
		return PARKING_ERROR_ALREADY_COUNTED;  //la macchina è già presente

	if (stack_is_full(_park->stack_park) == false) {
		if (stack_push(_park->stack_park, _car) == STACK_SUCCESS) {
			*_position = 0;  //inserisco sempre in cima
			return PARKING_GO_IN_PARK;
		}
		return PARKING_CRITICAL_ERROR; //se lo stack non è pieno ma non posso inserire auto, ho un errore critico
	}

	if (queue_is_full(_park->queue_waiting) == false) {
		int num_cars;

		//vedo se ho ottenuto la distanza e la salvo passandola per riferimento
		status = parking_get_queue_distance(_park->queue_waiting, _park->waiting_capacity, &num_cars);
		if (status != PARKING_SUCCESS)
			return status;

		if (queue_enqueue(_park->queue_waiting, _car) == QUEUE_SUCCESS) {
			*_position = num_cars;
			return PARKING_GO_IN_QUEUE;  //se riesco ad inserirla in coda
		}

		return PARKING_CRITICAL_ERROR;  //se non sono riuscito perché ad inserirla
	}

	return PARKING_ERROR_FULL;  //non ho inserito né nel parcheggio né in coda
}

short parking_pop(parking _park, int _car, int* _queue_car) {
	if (_park == NULL || _queue_car == NULL)
		return PARKING_ERROR_NULL;

	*_queue_car = -1;  //se non ne inserisco nessuna

	int dist, status;

	//verifico che sia nel parcheggio, ottenendo una distanza consona
	status = parking_get_car_distance(_park->stack_park, _car, &dist);  
	if (status != PARKING_SUCCESS)
		return status;

	if (dist == -1) {  //non è nel parcheggio, vedo se è in coda
		bool found = false;
		status = parking_car_is_present(_park, _car, &found);
		if (status != PARKING_SUCCESS)
			return status;

		if (found == true)
			return PARKING_ERROR_NOT_PARKED;  //era in coda e non va bene

		return PARKING_ERROR_NOT_FOUND;  //non era né in coda né nel parcheggio
	}

	if (dist > 4)
		return PARKING_ERROR_MANEUVER_SPACE;

	int car_to_move; //sposto le macchine
	for (int i = 0; i < dist; i++) {
		if (stack_pop(_park->stack_park, &car_to_move) != STACK_SUCCESS)
			return PARKING_CRITICAL_ERROR;  //perché se ho la possibilità di rimuovere e non me lo fa fare, si è corrotto lo stack

		if (stack_push(_park->stack_maneuver, car_to_move) != STACK_SUCCESS) {
			if (stack_push(_park->stack_park, car_to_move) != STACK_SUCCESS)
				return PARKING_CRITICAL_ERROR; //se non riesco a metterla nella manovra e nemmeno a riportal indietro, l'ho persa

			return PARKING_CRITICAL_ERROR; //magari ripristino ma non riesco comunque a usare lo stack di manovra
		}
	}

	int target_car;
	if (stack_pop(_park->stack_park, &target_car) != STACK_SUCCESS)
		return PARKING_CRITICAL_ERROR; //perché se poteva uscire e non lo ha fatto si è corrotto lo stack

	while (stack_pop(_park->stack_maneuver, &car_to_move) == STACK_SUCCESS) {
		if (stack_push(_park->stack_park, car_to_move) != STACK_SUCCESS)
			return PARKING_CRITICAL_ERROR; //errore durante il ripristino, ho perso le macchine
	}
	 
	if (queue_is_empty(_park->queue_waiting) == false) {
		int car_from_queue; //creo una macchina che andrà nel parcheggio
		if (queue_dequeue(_park->queue_waiting, &car_from_queue) == QUEUE_SUCCESS) {
			if (stack_push(_park->stack_park, car_from_queue) == STACK_SUCCESS) {
				*_queue_car = car_from_queue;
			}
			else {
				if (queue_enqueue(_park->queue_waiting, car_from_queue) != QUEUE_SUCCESS)
					return PARKING_CRITICAL_ERROR; //l'ho tolta dalla coda, non è andata nello stack e non è tornata nella coda

				return PARKING_CRITICAL_ERROR; //l'ho salvata ma non l'ho messa nel parcheggio
			}
		}
		else {
			return PARKING_CRITICAL_ERROR; //non sono riuscito a toglierla dalla coda nonostante questa non fosse vuota
		}
	}

	return PARKING_SUCCESS;
}