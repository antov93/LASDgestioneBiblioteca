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
#include <string.h>

struct elementoLibro *listaLibri;
struct elementoStudente *listaStudenti;


void menu(){
	int scelta=0;
	int esco=0;


while(esco!=1){
	//system("clear");
	printf("\nBenvenuto in BIBLIOTECA\n");
	printf("Di cosa hai bisogno?\n");
	printf("1-Richiedi libro in prestito.\n"
		   "2-Restituisci libro.\n"
		   "3-Esci.\n");
	printf("Inserisci comando: ");
	scanf("%d",&scelta);
	switch(scelta){
				case 1:	//richiesta di un pfflush(stdin);restito
					if(login()>0)richiediPrestitoLibro();
					break;

				case 2:
					printf("cliccato 2\n");
					visualizzaListaLibri();
					visualizzaListaStudenti();
					break;

				case 3:
					printf("cliccato 3\n");
					esco=1;
					break;


				default:
					printf("Comando errato, ritenta.\n");
					scelta=0;
					break;
		}//fine switch
	}
printf("Ok ciao");
}

void richiediPrestitoLibro(){
	printf("Richiesta prestito.\n");
}

int registrazione(){
	Studente s;
	char nome[50];
	char cognome[50];
	char matricola[50];
	char svuotaBuffer[100];
	printf("REGISTRAZIONE NUOVO STUDENTE\n"
			"Inserisci i dati indicati.\n");


	fgets(svuotaBuffer,45,stdin);

	printf("NOME >");
	//fflush(stdin);
	fgets(nome,45,stdin);
	eliminaNewLine(nome);
	strcpy(s.nome,nome);
	//fflush(stdin);

	printf("COGNOME >");

	//fflush(stdin);
	fgets(cognome,45,stdin);
	eliminaNewLine(cognome);
	strcpy(s.cognome,cognome);


	//fflush(stdin);
	printf("MATRICOLA >");
	//fflush(stdin);
	fgets(matricola,45,stdin);

	eliminaNewLine(matricola);
	strcpy(s.matricola,matricola);

	aggiungiStudente(s);

	printf("Registrazione avvenuta con successo.\n");
	//visualizzaListaStudenti();
	return 1;
}

int eliminaNewLine(char *stringa){
	int lunghezza=-1;
	if(NULL!=stringa){
		lunghezza=strlen(stringa);
		if(0!=lunghezza && '\n'==stringa[lunghezza-1]){
			stringa[--lunghezza]='\0';
		}
	}
	return 1;
}

int cercaStudente(){
	return 0;
}

int login(){

	char matricola[9];
	int scelta=0;
	printf("RICHIESTA PRESTITO\n");
	printf("Inserire i dati richiesti:\n");
	printf("Matricola >");
	scanf("%s",matricola);

	if(cercaStudente() >0 ){
		return 1;
	}else{
		printf("Attualmente non sei registrato come studente, vuoi procedere alla registrazione?\n");
		printf("1-Si.\n"
				"2-No.\n"
				"Risposta >");
		scanf("%d",&scelta);
		if(scelta==1){
			if(registrazione()>0)return 1;
		}else{
			printf("Non potrai richiedere libri in perestito se non sei registrato.\n");
			return 0;
		}

	}

}

void visualizzaListaLibri(){
	struct elementoLibro *testa;
	testa=listaLibri;
	printf("Libri disponibili in questo momento:\n");
	if(listaLibri==NULL){
		printf("Al momento non sono presenti libri disponibili al prestito.\n");
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

	struct elementoLibro *puntatore;
	puntatore=listaLibri;
	if(listaLibri==NULL){
		listaLibri=(struct elementoLibro *)malloc(sizeof(struct elementoLibro));
		listaLibri->l= libro;
		listaLibri->next=NULL;
	}else{
		while(puntatore->next!=NULL){
			puntatore=puntatore->next;
		}
		puntatore->next=(struct elementoLibro *)malloc(sizeof(struct elementoLibro));
		puntatore=puntatore->next;
		puntatore->l=libro;
		puntatore->next=NULL;
	}


}

void aggiungiStudente(Studente studente){

	struct elementoStudente *puntatore;
	puntatore=listaStudenti;
	if(listaStudenti==NULL){
		listaStudenti=(struct elementoStudente *)malloc(sizeof(struct elementoStudente));
		listaStudenti->s=studente;
		listaStudenti->next=NULL;
	}else{
		while(puntatore->next!=NULL){
			puntatore=puntatore->next;
		}
		puntatore->next=(struct elementoStudente *)malloc(sizeof(struct elementoStudente));
		puntatore=puntatore->next;
		puntatore->s=studente;
		puntatore->next=NULL;
	}


}

void visualizzaListaStudenti(){
	struct elementoStudente *testa;
	testa=listaStudenti;
	printf("Studenti registrati in questo momento:\n");
	if(listaStudenti==NULL){
		printf("Al momento non sono presenti studenti registrati.\n");
	}else{
		while(listaStudenti!=NULL){
			printf("%s ",listaStudenti->s.matricola);
			printf("%s ",listaStudenti->s.cognome);
			printf("%s \n",listaStudenti->s.nome);
			listaStudenti=listaStudenti->next;

		}
	}
	listaStudenti=testa;
}

void creaListaLibri(){

	Libro libro1={1,"Harry Potter 1","J. K. Rowling"};
	Libro libro2={2,"Harry Potter 2","J. K. Rowling"};
	Libro libro3={3,"Harry Potter 3","J. K. Rowling"};
	Libro libro4={4,"Harry Potter 4","J. K. Rowling"};
	Libro libro5={5,"Harry Potter 5","J. K. Rowling"};
	Libro libro6={6,"Harry Potter 6","J. K. Rowling"};
	Libro libro7={7,"Harry Potter 7","J. K. Rowling"};
	Libro libro8={8,"Harry il","J. K. Rowling"};
	Libro libro9={9,"Harry","J. K. Rowling"};
	Libro libro10={10,"Harry Potter 10","J. K. Rowling"};
	Libro libro11={11,"Harry Potter 11","J. K. Rowling"};
	Libro libro12={12,"Harry Potter 12","J. K. Rowling"};
	Libro libro13={13,"Harry Potter 13","J. K. Rowling"};
	Libro libro14={14,"Harry Potter","J. K. Rowling"};
	Libro libro15={15,"Harry Potteriiiii","J. K. Rowling"};

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




