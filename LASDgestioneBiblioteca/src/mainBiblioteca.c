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

#include "gestioneBiblioteca.h"


int main(void) {
	creaListaLibri();
	menuBiblioteca();
	return EXIT_SUCCESS;
}
