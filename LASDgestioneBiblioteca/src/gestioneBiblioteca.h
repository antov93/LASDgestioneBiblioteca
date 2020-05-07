/*
 * listaLibro.h
 *
 *  Created on: 2 mag 2020
 *      Author: antov
 */

#ifndef GESTIONEBIBLIOTECA_H_
#define GESTIONEBIBLIOTECA_H_

typedef struct{
	int id;
	char titolo[50];
	char autore[50];
	int disponibile;
	char prossimoPrenotato[50];
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


typedef struct{
	int codiceLibro;
	char matricolaStudente[50];
}Prestito;

struct elementoPrestito{
	Prestito p;
	struct elementoPrestito *next;
};

void menuBiblioteca();

char* login();
char* registrazione();

void creaListaLibri();
void visualizzaListaLibri();
void aggiungiLibro(Libro l);
void stampaPrestati(char *s);
void stampaLibro(int n);
void restituisciLibro(char *s);

void visualizzaListaStudenti();
void aggiungiStudente(Studente s);
int cercaStudente(char *s);

int controlloPrenotazioni(char *s);
void gestisciPrenotazioni(char *s);

void visualizzaListaPrestiti();
void richiestaPrestito(char *s);
void approvaPrestito(int n,char *s);
void aggiungiPrestito(Prestito p);
int controlloPrestiti(char *s);
void rimuoviPrestito(char *s,int n);

int eliminaNewLine(char *s);


//struct elemento *modificaLibro(struct elemento *l);
//struct elemento *rimuoviLibro(struct elemento *l);


#endif /* GESTIONEBIBLIOTECA_H_ */
