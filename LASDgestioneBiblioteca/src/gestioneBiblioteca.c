/*
 * listaLibro.c
 *
 *  Created on: 2 mag 2020
 *      Author: antov
 */
#include "gestioneBiblioteca.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct elementoLibro *listaLibri;
struct elementoStudente *listaStudenti;
struct elementoPrestito *listaPrenotazioni;
struct elementoPrestito *listaPrestiti;

void menuBiblioteca(){
	int scelta=0;
	int esco=0;
	char* matricola=malloc(sizeof(char));

	while(esco!=1){
		//system("clear");

		printf("\nBenvenuto in BIBLIOTECA\n");
		printf("Di cosa hai bisogno?\n");
		printf("1-Richiedi libro in prestito.\n"
			   "2-Restituisci libro.\n"
			   "3-Esci.\n");
		printf("scelta >");
		scanf("%d",&scelta);

		switch(scelta){
			case 1:
				matricola=login();
				if(matricola!=NULL){
					if( (controlloPrenotazioni(matricola))>0 ){
						gestisciPrenotazioni(matricola);
					}else{
						printf("Nessuna prenotazione in sospeso.\n");
						richiestaPrestito(matricola);
					}

				}else{
					printf("è null nnt prestito!\n");
				}
				break;

			case 2:
				matricola=login();
				if(matricola!=NULL){
					if(controlloPrestiti(matricola)>0){
						restituisciLibro(matricola);
						printf("\nLibro restituito.");
					}else{
						printf("Non hai libri da restituire.\n");
					}
				}

				break;

			case 3:
				printf("Chiusura programma...\n");
				esco=1;
				break;

			case 4:
				visualizzaListaLibri();
				visualizzaListaStudenti();
				visualizzaListaPrestiti();
				break;

			default:
				printf("Comando errato, ritenta.\n");
				scelta=0;
				break;

			}//fine switch
		}
	printf("Chiusura programma...");
}

void rimuoviPrestito(char *matricola,int libro){
	struct elementoPrestito *s;
	struct elementoPrestito *daEliminare;
	if(listaPrestiti==NULL)	printf("Nulla da eliminare.\n");
	if(listaPrestiti->next!=NULL){
		s=listaPrestiti;
		while(s->next!=NULL){
			if(s->next->p.codiceLibro==libro && strcmp(s->next->p.matricolaStudente,matricola)==0 ){
				daEliminare=s->next;
				s->next=s->next->next;
				free(daEliminare);
			}else{
				s=s->next;
			}
		}
	}

	if(listaPrestiti->p.codiceLibro==libro && strcmp(listaPrestiti->p.matricolaStudente,matricola)==0){
		daEliminare=listaPrestiti;
		listaPrestiti=listaPrestiti->next;
		free(daEliminare);
	}
}

void restituisciLibro(char *matricola){
	int scelta;
	printf("Quale libro vuoi restituire?\n");
	stampaPrestati(matricola);
	printf("Inserisci il codice corrispondente.\n");
	printf("codice >");
	scanf("%d",&scelta);
	rimuoviPrestito(matricola,scelta);
}

void stampaLibro(int libro){
	struct elementoLibro *testa;
		testa=listaLibri;
		while(listaLibri!=NULL){
			if( listaLibri->l.id==libro ){
				printf("%d	",listaLibri->l.id);
				printf("%s	",listaLibri->l.titolo);
				printf("%s\n",listaLibri->l.autore);
				listaLibri=listaLibri->next;
			}else{
				listaLibri=listaLibri->next;
			}
		}
		listaLibri=testa;
}

void stampaPrestati(char *matricola){
	struct elementoPrestito *testa;
	testa=listaPrestiti;

	if(listaPrestiti==NULL){
		printf("Al momento non ci sono prestiti.\n");
	}else{
		while(listaPrestiti!=NULL){
			if( strcmp(listaPrestiti->p.matricolaStudente,matricola)==0 ){
				stampaLibro(listaPrestiti->p.codiceLibro);
			}
			listaPrestiti=listaPrestiti->next;

		}
	}
	listaPrestiti=testa;
}

//controllo se la matricola è presente nella lista prestiti effettuati
int controlloPrestiti(char *matricola){
	struct elementoPrestito *testa;

	testa=listaPrestiti;
	while(listaPrestiti!=NULL){
		if( strcmp(listaPrestiti->p.matricolaStudente,matricola)==0 ){
			listaPrestiti=testa;
			return 1;
		}else{
			listaPrestiti=listaPrestiti->next;
		}
	}
	listaPrestiti=testa;
	return 0;
}

void gestisciPrenotazioni(char *matricola){
	int esco=0;
	int scelta=0;
	while(esco!=1){
		printf("\nHai prenotazioni in sospeso. Cosa vuoi fare?\n"
				"1-Controlla le tue richieste in sospeso.\n"
				"2-Richiedi un altro libro.\n"
				"scelta >");
		scanf("%d",&scelta);
		switch(scelta){
			case 1:
				printf("caso1\n");
				//risolviRichieste(matricola);
				esco=1;
				break;

			case 2:
				printf("caso2\n");
				richiestaPrestito(matricola);
				esco=1;
				break;

			default:
				printf("Comando errato, risprova...");
				scelta=0;
				break;
		}
	}

}

int controlloPrenotazioni(char *matricola){
	struct elementoPrestito *testa;
	testa=listaPrenotazioni;
	while(listaPrenotazioni!=NULL){
		if( strcmp(listaPrenotazioni->p.matricolaStudente,matricola)==0 ){
			listaPrenotazioni=testa;
			return 1;
		}else{
			listaPrenotazioni=listaPrenotazioni->next;
		}
	}
	listaPrenotazioni=testa;
	return 0;
}

int controlloDisponibilitaLibro(int libro){
	struct elementoLibro *testa;
	testa=listaLibri;
	while(listaLibri!=NULL){
		if( (listaLibri->l.id==libro) ){
			if(listaLibri->l.disponibile==1){
				listaLibri->l.disponibile=0;
				listaLibri=testa;
				return 1;
			}else{
				listaLibri=listaLibri->next;
			}
		}else{
			listaLibri=listaLibri->next;
		}
	}
	listaLibri=testa;
	return 0;
}

void aggiungiPrestito(Prestito prestito){
	struct elementoPrestito *testa;
	testa=listaPrestiti;
	if(listaPrestiti==NULL){
		listaPrestiti=(struct elementoPrestito *)malloc(sizeof(struct elementoPrestito));
		listaPrestiti->p= prestito;
		listaPrestiti->next=NULL;
	}else{
		while(testa->next!=NULL){
			testa=testa->next;
		}
		testa->next=(struct elementoPrestito *)malloc(sizeof(struct elementoPrestito));
		testa=testa->next;
		testa->p=prestito;
		testa->next=NULL;
	}


}

void approvaPrestito(int libro,char *matricola){
	Prestito p;
	printf("Matricola utente: %s\n",matricola);
	printf("Hai selezionato il libro: %d\n",libro);

	if( controlloDisponibilitaLibro(libro)>0 ){
		printf("libro disponibile\n"
				"prendilo in culo\n");
		p.codiceLibro=libro;
		strcpy(p.matricolaStudente,matricola);

		aggiungiPrestito(p);
		printf("Hai il libro!!! riportamelo xo è!\n");
		visualizzaListaPrestiti();
	}else{
		printf("libro nn disponibile al momento."
				"vuoi prenotarti?\n");
	}
}

void richiestaPrestito(char *matricola){
	int esco=0;
	int scelta=0;
	int codiceLibro;

	printf("\n----RICHIESTA PRESTITO----\n");
	printf("1-Cerca libro tramite parola chiave.\n");
	printf("2-Visualizza tutti i libri in ordine alfabetico.\n");
	printf("3-Annulla richiesta.\n");
	printf("Scelta >");
	scanf("%d",&scelta);
	while(esco!=1){
		switch(scelta){
			case 1:
				printf("Inserisci parola chiave >");
				esco=1;
				break;

			case 2:
				visualizzaListaLibri();
				printf("Inserisci il codice del libro scelto >");
				scanf("%d",&codiceLibro);
				approvaPrestito(codiceLibro,matricola);
				esco=1;
				break;

			case 3:
				esco=1;
				break;

			default:
				printf("Comando errato, ritenta.\n");
				scelta=0;
				break;
		}//fine switch
	}

}

void visualizzaListaPrestiti(){
	struct elementoPrestito *testa;
	testa=listaPrestiti;
	printf("Prestiti effettuati in questo momento:\n");
	if(listaPrestiti==NULL){
		printf("Al momento non ci sono prestiti.\n");
	}else{
		while(listaPrestiti!=NULL){
			printf("%d	",listaPrestiti->p.codiceLibro);
			printf("%s\n",listaPrestiti->p.matricolaStudente);
			listaPrestiti=listaPrestiti->next;

		}
	}
	listaPrestiti=testa;
}

char* registrazione(){
	Studente s;
	char nome[50];
	char cognome[50];
	char matricola[50];
	char *matricolaUpper=malloc(sizeof(char));
	char svuotaBuffer[100];
	int i=0;

	printf("\n----REGISTRAZIONE NUOVO STUDENTE----\n"
			"Inserisci i dati indicati.\n");
	fgets(svuotaBuffer,45,stdin);
	printf("NOME >");
	fgets(nome,45,stdin);
	eliminaNewLine(nome);
	strcpy(s.nome,nome);
	printf("COGNOME >");
	fgets(cognome,45,stdin);
	eliminaNewLine(cognome);
	strcpy(s.cognome,cognome);
	printf("MATRICOLA >");
	fgets(matricola,45,stdin);
	eliminaNewLine(matricola);
	for(i=0;i<sizeof(matricola);i++){
		matricolaUpper[i]=toupper(matricola[i]);

	}
	strcpy(s.matricola,matricolaUpper);
	aggiungiStudente(s);
	printf("Registrazione avvenuta con successo.\n");
	return matricolaUpper;
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

int cercaStudente(char *matricola){
	struct elementoStudente *testa;
	testa=listaStudenti;
	while(listaStudenti!=NULL){
		if( strcmp(listaStudenti->s.matricola,matricola)==0 ){
			listaStudenti=testa;
			return 1;
		}else{
			listaStudenti=listaStudenti->next;
		}
	}
	listaStudenti=testa;
	return 0;
}

char* login(){
	char *matricola=malloc(sizeof(char));
	int scelta=0;

	printf("Inserire  matricola >");
	scanf("%s",matricola);
	for(int i=0;i<sizeof(matricola);i++){
			matricola[i]=toupper(matricola[i]);
		}
	if(cercaStudente(matricola) >0 ){
		return matricola;
	}else{
		printf("\n!ATTENZIONE!\nAttualmente non risulti registrato come studente, vuoi procedere alla registrazione?\n");
		printf("1-Si.\n"
				"2-No.\n"
				"Risposta >");
		scanf("%d",&scelta);
		if(scelta==1){
			matricola=registrazione();
			if(matricola!=NULL)return matricola;
		}else{
			printf("Non potrai usufruire dei servizi di BIBLIOTECA se non sei registrato.\n");
			return NULL;
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
			printf("%d	",listaLibri->l.id);
			printf("%s	",listaLibri->l.titolo);
			printf("%s	",listaLibri->l.autore);
			printf("%d  ",listaLibri->l.disponibile);
			printf("%s\n",listaLibri->l.prossimoPrenotato);
			listaLibri=listaLibri->next;

		}
	}
	listaLibri=testa;
}

void aggiungiLibro(Libro libro){

	struct elementoLibro *testa;
	testa=listaLibri;
	if(listaLibri==NULL){
		listaLibri=(struct elementoLibro *)malloc(sizeof(struct elementoLibro));
		listaLibri->l= libro;
		listaLibri->next=NULL;
	}else{
		while(testa->next!=NULL){
			testa=testa->next;
		}
		testa->next=(struct elementoLibro *)malloc(sizeof(struct elementoLibro));
		testa=testa->next;
		testa->l=libro;
		testa->next=NULL;
	}

}

void aggiungiStudente(Studente studente){

	struct elementoStudente *testa;
	testa=listaStudenti;
	if(listaStudenti==NULL){
		listaStudenti=(struct elementoStudente *)malloc(sizeof(struct elementoStudente));
		listaStudenti->s=studente;
		listaStudenti->next=NULL;
	}else{
		while(testa->next!=NULL){
			testa=testa->next;
		}
		testa->next=(struct elementoStudente *)malloc(sizeof(struct elementoStudente));
		testa=testa->next;
		testa->s=studente;
		testa->next=NULL;
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

	Libro libro1={1,"Harry Potter 1","J. K. Rowling",1,"NULL"};
	Libro libro2={2,"Harry Potter 2","J. K. Rowling",1,"NULL"};
	Libro libro3={3,"Harry Potter 3","J. K. Rowling",1,"NULL"};
	Libro libro4={4,"Harry Potter 4","J. K. Rowling",1,"NULL"};
	Libro libro5={5,"Harry Potter 5","J. K. Rowling",1,"NULL"};
	Libro libro6={6,"Harry Potter 6","J. K. Rowling",1,"NULL"};
	Libro libro7={7,"Harry Potter 7","J. K. Rowling",0,"NULL"};
	Libro libro8={8,"Harry il","J. K. Rowling",1,"NULL"};
	Libro libro9={9,"Harry","J. K. Rowling",1,"NULL"};
	Libro libro10={10,"Harry Potter 10","J. K. Rowling",1,"NULL"};
	Libro libro11={11,"Harry Potter 11","J. K. Rowling",1,"NULL"};
	Libro libro12={12,"Harry Potter 12","J. K. Rowling",0,"NULL"};
	Libro libro13={13,"Harry Potter 13","J. K. Rowling",1,"NULL"};
	Libro libro14={14,"Harry Potter","J. K. Rowling",1,"NULL"};
	Libro libro15={15,"Harry Potteriiiii","J. K. Rowling",1,"NULL"};

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




