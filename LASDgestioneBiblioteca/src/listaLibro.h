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

struct elementoLibro{
	Libro l;
	struct elementoLibro *next;
};


typedef struct{
	char matricola[50];
	char nome[50];
	char cognome[50];
}Studente;

struct elementoStudente{
	Studente s;
	struct elementoStudente *next;
};



void creaListaLibri();
void visualizzaListaLibri();
void aggiungiLibro(Libro l);
void menu();
void visualizzaListaStudenti();
void aggiungiStudente(Studente s);
int login();
int cercaStudente();
int registrazione();
void richiediPrestitoLibro();
int eliminaNewLine(char *s);
//struct elemento *modificaLibro(struct elemento *l);
//struct elemento *rimuoviLibro(struct elemento *l);


#endif /* LISTALIBRO_H_ */
