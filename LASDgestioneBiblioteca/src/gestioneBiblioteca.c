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
#include <unistd.h>


struct elementoLibro *listaLibri;
struct elementoStudente *listaStudenti;
struct elementoPrestito *listaPrenotazioni;
struct elementoPrestito *listaPrestiti;

void menuBiblioteca(){
	int scelta=0;
	int esco=0;
	char comando[1];
	char* matricola=malloc(sizeof(char));

	while(esco!=1){
		system("clear");
		printf("\n----BENVENUTO in BIBLIOTECA----\n");
		printf("\nDi cosa hai bisogno?\n");
		printf("1-Richiedi libro in prestito.\n"
			   "2-Restituisci libro.\n"
			   "3-Esci.\n"
			   "4-Amministrazione.\n");
		printf("scelta >");
		scanf("%s",comando);
		scelta=comando[0];
		switch(scelta){
			case '1':
				matricola=login();
				if(matricola!=NULL){
					if( (controlloPrenotazioniStudente(matricola))>0 ){
						gestisciPrenotazioni(matricola);
					}else{
						richiestaPrestito(matricola);
					}
				}
				pausa();
				break;

			case '2':
				matricola=login();
				if(matricola!=NULL){
					if(controlloPrestitiStudente(matricola)>0){
						restituisciLibro(matricola);
						printf("\nLibro restituito.\n");
					}else{
						printf("\nNon hai libri da restituire.\n");
					}
				}
				pausa();
				break;

			case '3':
				if(controllaUscita()>0){
					esco=1;
					printf("Uscita in corso...");
				}else{
					printf("\nATTENZIONE!!!\n"
							"Ci sono ancora richieste di prestito o prenotazioni non risolte!\n"
							"Impossibile chiudere il sistema.\n");
					//scelta=0;
				}
				pausa();
				break;

			case '4':
				visualizzaListaLibri();
				visualizzaListaStudenti();
				visualizzaListaPrestiti();
				visualizzaListaPrenotazioni();
				pausa();
				break;

			default:
				printf("Comando errato, ritenta.\n");
				//scelta=0;
				pausa();
				break;

			}//fine switch
		}
	printf("Chiusura programma...");
}
int controllaUscita(){
	if(listaPrestiti==NULL && listaPrenotazioni==NULL){
		return 1;
	}else{
		return 0;
	}
}
void pausa(){
	printf("\nPremi il tasto INVIO per continuare...");
	getchar();
	getchar();
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

//se trovo una prenotazione setto il prossimo prenotato
int controlloPrenotazioniLibro(int libro){
	struct elementoPrestito *testa;
	testa=listaPrenotazioni;
	char *matricola;
	while(listaPrenotazioni!=NULL){
		if( (listaPrenotazioni->p.codiceLibro==libro) ){
			matricola=listaPrenotazioni->p.matricolaStudente;
			impostaPrenotato(libro,matricola);

			return 1;
		}else{
			listaPrenotazioni=listaPrenotazioni->next;
		}
	}
	listaPrenotazioni=testa;
	return 0;
}

void impostaPrenotato(int libro,char *matricola){
	struct elementoLibro *testa;
	testa=listaLibri;

	while(listaLibri!=NULL){
		if( listaLibri->l.id!=libro ){
			listaLibri=listaLibri->next;
		}else{
			strcpy(listaLibri->l.prossimoPrenotato,matricola);
			listaLibri=testa;
			return;
		}
	}
	listaLibri=testa;
}

void restituisciLibro(char *matricola){
	int scelta;

	system("clear");
	printf("\n----RESTITUZIONE LIBRO----\n\n");
	printf("Quale libro vuoi restituire?\n\n");
	printf("I tuoi prestiti:\n");
	printf("CODICE	Titolo		Autore		\n");
	stampaPrestati(matricola);
	printf("\nInserisci il codice corrispondente.\n");
	printf("codice libro >");
	scanf("%d",&scelta);
	rimuoviPrestito(matricola,scelta);

	if(controlloPrenotazioniLibro(scelta)==0){
		if(impostaDisponibilitaLibro(scelta)==0){
			printf("!!!Errore. Non ho trovato il libro.\n");
		}

	}

}

int impostaDisponibilitaLibro(int libro){
	struct elementoLibro*testa;
	testa=listaLibri;
	while(listaLibri!=NULL){
		if( listaLibri->l.id==libro ){
			listaLibri->l.disponibile=1;
			listaLibri=testa;
			return 1;
		}else{
			listaLibri=listaLibri->next;
		}
	}
	listaLibri=testa;
	return 0;
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
		printf("\nAl momento non ci sono prestiti.\n");
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
int controlloPrestitiStudente(char *matricola){
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
		printf("\nATTENZIONE!!!\n");
		printf("Hai prenotazioni in sospeso. Cosa vuoi fare?\n\n"
				"1-Controlla le tue richieste in sospeso.\n"
				"2-Richiedi un altro libro.\n"
				"scelta >");
		scanf("%d",&scelta);
		switch(scelta){
			case 1:
				risolviRichiesteStudente(matricola);
				esco=1;
				break;

			case 2:
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

void risolviRichiesteStudente(char *matricola){
	int scelta;
	printf("\nLe tue prenotazioni:\n");
	printf("CODICE	Titolo		Autore		\n");
	stampaPrenotazioniStudente(matricola);
	printf("\nInserisci un codice di un libro per controllare se è tornato disponibile.\n");
	printf("codice >");
	scanf("%d",&scelta);
	controlloPrenotazioneLibroStudente(scelta,matricola);

}

void rimuoviPrenotazione(Prestito pr){
	struct elementoPrestito *s;
	struct elementoPrestito *daEliminare;
	if(listaPrenotazioni==NULL)	printf("\nNulla da eliminare.\n");
	if(listaPrenotazioni->next!=NULL){
			s=listaPrenotazioni;
			while(s->next!=NULL){
				/*()*/
				if(s->next->p.codiceLibro==pr.codiceLibro && strcmp(s->next->p.matricolaStudente,pr.matricolaStudente)==0 ){
					daEliminare=s->next;
					s->next=s->next->next;
					free(daEliminare);
				}else{
					s=s->next;
				}
			}
		}

		if(listaPrenotazioni->p.codiceLibro==pr.codiceLibro && strcmp(listaPrenotazioni->p.matricolaStudente,pr.matricolaStudente)==0){
			daEliminare=listaPrenotazioni;
			listaPrenotazioni=listaPrenotazioni->next;
			free(daEliminare);
		}

}

void controlloPrenotazioneLibroStudente(int libro,char *matricola){
	Prestito p;
	struct elementoLibro *testa;
	testa=listaLibri;
	int scelta=0;

	if(listaLibri==NULL){
		printf("\nAl momento non ci sono libri.\n");
	}else{
		while(listaLibri!=NULL){
			if( listaLibri->l.id==libro ){
				if( strcmp(listaLibri->l.prossimoPrenotato,matricola)==0 ){
					p.codiceLibro=libro;
					strcpy(p.matricolaStudente,matricola);
					printf("\nLibro disponibile!\n\nVuoi procedere col prestito?\n");
					printf("1-Si.\n"
						   "2-Indietro.\n");
					printf("scelta >");
					scanf("%d",&scelta);
					if(scelta==1){
						rimuoviPrenotazione(p);
						aggiungiPrestito(p);
						printf("\nPrestito effettuato!\n");
						return;
					}else{
						return;
					}
				}else{
					printf("\nLibro non ancora disponibile.\n");
					listaLibri=testa;
					return;
				}
			}else{
				listaLibri=listaLibri->next;
			}
		}
	}
	listaLibri=testa;


}

void stampaPrenotazioniStudente(char *matricola){
	struct elementoPrestito *testa;
	testa=listaPrenotazioni;

		if(listaPrenotazioni==NULL){
			printf("\nAl momento non ci sono prenotazioni.\n");
		}else{
			while(listaPrenotazioni!=NULL){
				if( strcmp(listaPrenotazioni->p.matricolaStudente,matricola)==0 ){
					stampaLibro(listaPrenotazioni->p.codiceLibro);
				}
				listaPrenotazioni=listaPrenotazioni->next;

			}
		}
		listaPrenotazioni=testa;
}

//cerco se nella lista delle prenotazioni è presente
//la matricola in modo da capire se ha prenotato qlk libro in precedenza
int controlloPrenotazioniStudente(char *matricola){
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

//se il libro è disponibile al prestito setto a zero il flag disponibilità e ritorno 1
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
	int scelta=0;

	system("clear");
	printf("----CONFERMA PRESTITO----\n");
	printf("Matricola studente: %s\n",matricola);
	printf("Libro selezionato > ");
	stampaLibro(libro);
	printf("\n");
	p.codiceLibro=libro;
	strcpy(p.matricolaStudente,matricola);
	if( controlloDisponibilitaLibro(libro)>0 ){
		printf("Libro disponibile..\n");
		aggiungiPrestito(p);
		printf("\nPrestito effettutato correttamente!\n");
	}else{
		printf("ATTENZIONE!!!\nIl libro non è disponibile al momento.\n\n"
						"E' possibile richiedere una prenotazione oppure "
						"tornare indietro e scegliere un altro libro selezionando una delle seguenti opzioni:\n\n"
						"1-Prenota libro.\n"
						"2-Torna al menù principale.\n"
						"scelta >");
		scanf("%d",&scelta);
		printf("\n");
		if(scelta==1){
			aggiungiPrenotazione(p);
			printf("\nLibro prenotato correttamente!\n");
		}

	}
}

void visualizzaListaPrenotazioni(){
	struct elementoPrestito *testa;
	testa=listaPrenotazioni;
	printf("\n\nPrenotazioni effettuate in questo momento:\n");
	if(listaPrenotazioni==NULL){
		printf("-Al momento non ci sono prenotazioni.\n");
	}else{
		while(listaPrenotazioni!=NULL){
			printf("%d	",listaPrenotazioni->p.codiceLibro);
			printf("%s\n",listaPrenotazioni->p.matricolaStudente);
			listaPrenotazioni=listaPrenotazioni->next;

		}
	}
	listaPrenotazioni=testa;
}

void aggiungiPrenotazione(Prestito pr){
	struct elementoPrestito *testa;
	testa=listaPrenotazioni;

	if(listaPrenotazioni==NULL){
		listaPrenotazioni=(struct elementoPrestito *)malloc(sizeof(struct elementoPrestito));
		listaPrenotazioni->p=pr ;
		listaPrenotazioni->next=NULL;
	}else{
		while(testa->next!=NULL){
			testa=testa->next;
		}
		testa->next=(struct elementoPrestito *)malloc(sizeof(struct elementoPrestito));
		testa=testa->next;
		testa->p=pr;
		testa->next=NULL;
	}
}

void richiestaPrestito(char *matricola){
	int esco=0;
	int scelta=0;
	int codiceLibro;
	system("clear");
	printf("\n----RICHIESTA PRESTITO----\n");
	printf("1-Visualizza libri.\n");
	printf("2-Annulla richiesta.\n");
	printf("Scelta >");
	scanf("%d",&scelta);
	while(esco!=1){
		switch(scelta){
			case 1:
				visualizzaListaLibri();
				printf("\nInserisci il codice del libro scelto >");
				scanf("%d",&codiceLibro);
				approvaPrestito(codiceLibro,matricola);
				esco=1;
				break;

			case 2:
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
	printf("\n\nPrestiti effettuati in questo momento:\n");
	if(listaPrestiti==NULL){
		printf("-Al momento non ci sono prestiti.\n");
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

	system("clear");
	printf("\n----REGISTRAZIONE NUOVO STUDENTE----\n"
			"Inserisci i dati indicati.\n\n");
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
	if(cercaStudente(matricolaUpper)>0){
		printf("ATTENZIONE!!!\n"
				"La matricola inserita risulta gia registrata.");
		return NULL;
	}else{
		aggiungiStudente(s);
		printf("\nRegistrazione avvenuta con successo!\n");
		return matricolaUpper;
	}



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
	char comando[1];

	printf("\nInserire  matricola >");
	scanf("%s",matricola);
	for(int i=0;i<sizeof(matricola);i++){
			matricola[i]=toupper(matricola[i]);
		}
	if(cercaStudente(matricola) >0 ){
		return matricola;
	}else{
		printf("\nATTENZIONE!!!\nAttualmente non risulti registrato come studente, vuoi procedere alla registrazione?\n");
		printf("1-Si.\n"
				"2-No.\n"
				"scelta >");
		scanf("%s",comando);
		scelta=comando[0];
		if(scelta=='1'){
			matricola=registrazione();
			if(matricola!=NULL){
				return matricola;
			}else{
				return NULL;
			}

		}else{
			printf("\nNon potrai usufruire dei servizi di BIBLIOTECA se non sei registrato.\n");
			return NULL;
		}

	}

}

void visualizzaListaLibri(){
	struct elementoLibro *testa;
	testa=listaLibri;

	printf("\nLISTA LIBRI:\n");
	printf("CODICE	Titolo		Autore		Disopnibilità\n");
	if(listaLibri==NULL){
		printf("-Al momento non sono presenti libri disponibili al prestito.\n");
	}else{
		while(listaLibri!=NULL){
			printf("%d	",listaLibri->l.id);
			printf("%s	",listaLibri->l.titolo);
			printf("%s	",listaLibri->l.autore);
			printf("%d\n",listaLibri->l.disponibile);
			listaLibri=listaLibri->next;

		}
	}
	listaLibri=testa;
	printf("\nATTENZIONE!!!\nAlcuni libri potrebbero non essere disponibili perchè in prestito ad altri studenti.\n");
	printf("Tuttavia è possibile prenotarsi per avere il libro in esclusiva non appena risulta disponibile!\n");

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
	printf("\n\nStudenti registrati in questo momento:\n");
	if(listaStudenti==NULL){
		printf("-Al momento non sono presenti studenti registrati.\n");
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
	Libro libro7={7,"Harry Potter 7","J. K. Rowling",1,"NULL"};
	Libro libro8={8,"Biancaneve e i 7 nani","Disney",1,"NULL"};
	Libro libro9={9,"Il processo","Kafka",1,"NULL"};
	Libro libro10={10,"Guerra e Pace","Lev Nikolaevic",1,"NULL"};
	Libro libro11={11,"Moby Dick","Herman Melville",1,"NULL"};
	Libro libro12={12,"Il barone rampante","Italo Calvino",1,"NULL"};
	Libro libro13={13,"La montagna incantata","Thomas Mann",1,"NULL"};
	Libro libro14={14,"Il deserto dei tartari","Dino Buzzati",1,"NULL"};
	Libro libro15={15,"Harry Potter il ritorno","J. K. Rowling",1,"NULL"};

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




