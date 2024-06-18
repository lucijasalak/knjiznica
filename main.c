
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
	KNJIGA* knjiga = ucitaj();
	printf("-----------------------------\n");
	printf("     K NJ I Z N I C A \n");
	printf("-----------------------------\n");
	while (izlaz) {
		printf("1. Unesite novu knjigu\n");
		printf("2. Pregledajte knjige\n");
		printf("3. Sortirajte knjige\n");
		printf("4. Provjerite dostupnost knjige\n");
		printf("5. Pretrazite knjige\n");
		printf("6. Obrisi knjigu\n");
		printf("7. Obrisi sve knjige\n");
		printf("8. Azuriraj knjigu\n");
		printf("9. Izadjite iz izbornika\n");

		char unos[10];
		fgets(unos, sizeof(unos), stdin);
		int opcija;
		if (sscanf(unos, "%d", &opcija) == 1) {
			izbornikOpcija = (IzbornikOpcija)opcija;
			switch (izbornikOpcija) {
			case nova_knjiga:
				knjiga = novaknjiga(knjiga);
				break;
			case pregled_knjiga:
				ispis();
				break;
			case sortiranje_knjiga:
				sortiranje(knjiga);
				break;
			case provjera_dostupnosti:
				dostupnost(knjiga);
				break;
			case pretrazivanje_knjiga:
				pretrazivanje(knjiga);
				break;
			case brisanje_knjiga:
			{
				int idZaBrisanje;
				printf("Unesite ID knjige za brisanje: ");
				if (scanf("%d", &idZaBrisanje) == 1) {
					brisanje(&knjiga, idZaBrisanje);
				}
				else {
					printf("Pogresan unos.\n");
				}
				while (getchar() != '\n');
				break;
			}
			case brisanje_svih_knjiga:
				obrisisve(&knjiga);
				break;
			case azuriranje_knjiga:
				azuriranje(knjiga);
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
	Memorija(knjiga);
}

