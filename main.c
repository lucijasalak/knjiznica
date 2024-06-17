
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "header.h"

int main() {

	izbornik();

	return 0;
}

void izbornik() {
	static int izlaz = 1;
    int izbornikOpcija;
	KNJIGA* prvaKnjiga = ucitajKnjigeIzDatoteke();
	printf("-----------------------------\n");
	printf("     K NJ I Z N I C A \n");
	printf("-----------------------------\n");
	while (izlaz) {
		printf("1. Unesite novu knjigu\n");
		printf("2. Pregledajte knjige\n");
		printf("3. Sortirajte knjige\n");
		printf("4. Provjerite dostupnost knjige\n");
		printf("5. Pretrazite knjige\n");
		printf("6. Izadjite iz izbornika\n");

		char unos[10];
		fgets(unos, sizeof(unos), stdin);
		int opcija;
		if (sscanf(unos, "%d", &opcija) == 1) {
			izbornikOpcija = (IzbornikOpcija)opcija;
			switch (izbornikOpcija) {
			case UNOS_NOVE_KNJIGE:
				prvaKnjiga = dodavanjeNoveKnjige(prvaKnjiga);
				break;
			case PREGLED_KNJIGA:
				ispisKnjigaUKonzolu();
				break;
			case SORTIRANJE_KNJIGA:
				sortiranjeKnjiga(prvaKnjiga);
				break;
			case PROVJERA_DOSTUPNOSTI:
				provjeraDostupnosti(prvaKnjiga);
				break;
			case PRETRAZIVANJE_KNJIGA:
				pretrazivanjeKnjiga(prvaKnjiga);
				break;
			case IZLAZ:
				izlaz = 0;
				break;
			default:
				printf("Krivi unos.\n");
				break;
			}
		}
		else {
			printf("Krivi unos.\n");
		}
	}
	oslobadjanjeMemorijeSvega(prvaKnjiga);
}

