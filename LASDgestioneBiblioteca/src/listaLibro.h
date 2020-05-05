/*
 * listaLibro.h
 *
 *  Created on: 2 mag 2020
 *      Author: antov
 */

#ifndef LISTALIBRO_H_
#define LISTALIBRO_H_

typedef struct{
	int id;
	char titolo[50];
	char autore[50];
}Libro;

struct elemento{
	Libro l;
	struct elemento *next;
};



void creaListaLibri();
void visualizzaListaLibri();
void aggiungiLibro(Libro l);
void menu();
//struct elemento *modificaLibro(struct elemento *l);
//struct elemento *rimuoviLibro(struct elemento *l);


#endif /* LISTALIBRO_H_ */
