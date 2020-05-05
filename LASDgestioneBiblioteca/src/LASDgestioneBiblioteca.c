/*
 ============================================================================
 Name        : LASDgestioneBiblioteca.c
 Author      : Antonio Vanacore
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stddef.h>
#include "listaLibro.h"


int main(void) {
	creaListaLibri();
	menu();
	return EXIT_SUCCESS;
}
