/*
 * listaLibro.c
 *
 *  Created on: 2 mag 2020
 *      Author: antov
 */
#include "listaLibro.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct elemento *listaLibri;

void menu(){
	int scelta=0;
	int esco=0;
	printf("Benvenuto in BIBLIOTECA\n");
	printf("Di cosa hai bisogno?\n");
	printf("1-Richiedi libro in prestito.\n"
					"2-Restituisci libro.\n"
					"3-Esci.\n");

while(esco!=1){
	printf("Inserisci comando: ");
	scanf("%d",&scelta);
	switch(scelta){ //switch di antov //assumo che nn possono esserci 2 pacchi contemporaneamente nella matrice
				case 1:
					printf("cliccato 1");
					visualizzaListaLibri();
					break;

				case 2:
					printf("cliccato 2");
					break;

				case 3:
					printf("cliccato 3");
					esco=1;
					break;


				default:
					printf("Comando errato, ritenta.");
					scelta=0;
					break;
		}//fine switch
	}
printf("Ok ciao");
}

void visualizzaListaLibri(){
	struct elemento *testa;
	testa=listaLibri;
	printf("Libri disponibili in questo momento:\n");
	if(listaLibri==NULL){
		printf("Al momento non sono presenti libri disponibili al prestito.");
	}else{
		while(listaLibri!=NULL){
			printf("%d  ",listaLibri->l.id);
			printf("%s ",listaLibri->l.titolo);
			printf("%s\n",listaLibri->l.autore);
			listaLibri=listaLibri->next;

		}
	}
	listaLibri=testa;
}

void aggiungiLibro(Libro libro){

	struct elemento *puntatore;
	puntatore=listaLibri;
	if(listaLibri==NULL){
		listaLibri=(struct elemento *)malloc(sizeof(struct elemento));
		listaLibri->l= libro;
		listaLibri->next=NULL;
	}else{
		while(puntatore->next!=NULL){
			puntatore=puntatore->next;
		}
		puntatore->next=(struct elemento *)malloc(sizeof(struct elemento));
		puntatore=puntatore->next;
		puntatore->l=libro;
		puntatore->next=NULL;
	}


}

void creaListaLibri(){

	Libro libro1={1,"Harry Potter 1","J. K. Rowling"};
	Libro libro2={2,"Harry Potter 2","J. K. Rowling"};
	Libro libro3={3,"Harry Potter 3","J. K. Rowling"};
	Libro libro4={4,"Harry Potter 4","J. K. Rowling"};
	Libro libro5={5,"Harry Potter 5","J. K. Rowling"};
	Libro libro6={6,"Harry Potter 6","J. K. Rowling"};
	Libro libro7={7,"Harry Potter 7","J. K. Rowling"};
	Libro libro8={8,"Harry Potter 8","J. K. Rowling"};
	Libro libro9={9,"Harry Potter 9","J. K. Rowling"};
	Libro libro10={10,"Harry Potter 10","J. K. Rowling"};
	Libro libro11={11,"Harry Potter 11","J. K. Rowling"};
	Libro libro12={12,"Harry Potter 12","J. K. Rowling"};
	Libro libro13={13,"Harry Potter 13","J. K. Rowling"};
	Libro libro14={14,"Harry Potter 14","J. K. Rowling"};
	Libro libro15={15,"Harry Potter 15","J. K. Rowling"};

	aggiungiLibro(libro1);
	aggiungiLibro(libro2);
	aggiungiLibro(libro3);
	aggiungiLibro(libro4);
	aggiungiLibro(libro5);
	aggiungiLibro(libro6);
	aggiungiLibro(libro7);
	aggiungiLibro(libro8);
	aggiungiLibro(libro9);
	aggiungiLibro(libro10);
	aggiungiLibro(libro11);
	aggiungiLibro(libro12);
	aggiungiLibro(libro13);
	aggiungiLibro(libro14);
	aggiungiLibro(libro15);

}




