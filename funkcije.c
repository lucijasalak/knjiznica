#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

const char* imeDatoteke = "Knjiznica.txt";

KNJIGA* novaknjiga(KNJIGA* knjiga) {
	int (*pokazivacNaMaxID)(KNJIGA*);
	pokazivacNaMaxID = maxID;
	int duljina = 100;
	KNJIGA* novaknjiga = (KNJIGA*)calloc(1, sizeof(KNJIGA));
	if (novaknjiga == NULL) {
		perror("Pogreska.");
		return knjiga;
	}
	else {
		novaknjiga->naslov = (char*)calloc(duljina, sizeof(char));
		novaknjiga->autor = (char*)calloc(duljina, sizeof(char));
		novaknjiga->vrsta = (char*)calloc(duljina, sizeof(char));
		if (novaknjiga->naslov == NULL || novaknjiga->autor == NULL || novaknjiga->vrsta == NULL) {
			perror("Pogreska pri zauzimanju memorije.");
			memorija(novaknjiga);
			return knjiga;
		}
		if (knjiga == NULL) {
			novaknjiga->ID = 1;
		}
		else {
			novaknjiga->ID = maxID(knjiga) + 1;
		}
		printf("Unesite podatke o knjizi:\n");
		printf("Naslov: ");
		fgets(novaknjiga->naslov, duljina, stdin);
		novaknjiga->naslov[strcspn(novaknjiga->naslov, "\n")] = '\0';
		printf("Autor: ");
		fgets(novaknjiga->autor, duljina, stdin);
		novaknjiga->autor[strcspn(novaknjiga->autor, "\n")] = '\0';
		printf("Vrsta: ");
		fgets(novaknjiga->vrsta, duljina, stdin);
		novaknjiga->vrsta[strcspn(novaknjiga->vrsta, "\n")] = '\0';
		printf("Godina izdanja: ");
		if (scanf("%d", &novaknjiga->godina_izdanja) != 1) {
			printf("Greska.");
			exit(EXIT_FAILURE);
		}
		printf("Dostupnost (1 - dostupna, 0 - nije dostupna): ");
		if (scanf("%d", &novaknjiga->dostupnost) != 1) {
			printf("Greska.");
			exit(EXIT_FAILURE);
		}
		if (getchar() == EOF) {
			perror("Greska pri citanju.");
			exit (EXIT_FAILURE);
		}
		novaknjiga->next = knjiga;
		ispisknjigadat(novaknjiga);
	}
	return novaknjiga;
}
	


void ispisknjigadat(KNJIGA* trenutnoKnjiga) {
	FILE* fp = fopen(imeDatoteke, "a+");
	if (fp == NULL) {
		perror("Pogreska pri zapisivanju u datoteku.");
		return;
	}

	fprintf(fp, "Knjiga %d\n\tNaslov: %s\n\tAutor: %s\n\tVrsta: %s\n\tGodina izdanja: %d\n\tDostupnost: %d\n",
		trenutnoKnjiga->ID, trenutnoKnjiga->naslov, trenutnoKnjiga->autor, trenutnoKnjiga->vrsta,
		trenutnoKnjiga->godina_izdanja, trenutnoKnjiga->dostupnost);
	rewind(fp);
	fclose(fp);
}

void ispis() {
	FILE* fp = fopen(imeDatoteke, "r");
	if (fp == NULL) {
		perror("Pogreska pri citanju datoteke.");
		return;
	}
	char c;
	while ((c = fgetc(fp)) != EOF) {
		putchar(c);
	}
	fclose(fp);
}




void sortiranje(KNJIGA* knjiga) {
	if (knjiga == NULL) return;

	OpcijeSortiranja opcijeSortiranja;
	int novi;
	KNJIGA* p;
	KNJIGA* pp = NULL;

	printf("1: Sortiranje po naslovu\n2: Sortiranje po autoru\n3: Sortiranje po vrsti\n");
	char unos[10];
	fgets(unos, sizeof(unos), stdin);

	int opcija;
	if (sscanf(unos, "%d", &opcija) != 1) {
		printf("Krivi unos.\n");
		return;
	}

	opcijeSortiranja = (OpcijeSortiranja)opcija;

	switch (opcijeSortiranja) {
	case sortiranje_po_naslovu:
		do {
			novi = 0;
			p = knjiga;

			while (p->next != p) {
				if (strcmp(p->naslov, p->next->naslov) > 0) {
					zamjena(p, p->next);
					novi = 1;
				}
				p = p->next;
			}
			pp = p;
		} while (novi);
		break;

	case sortiranje_po_autoru:
		do {
			novi = 0;
			p = knjiga;

			while (p->next != pp) {
				if (strcmp(p->autor, p->next->autor) > 0) {
					zamjena(p, p->next);
					novi = 1;
				}
				p = p->next;
			}
			pp = p;
		} while (novi);
		break;

	case sortiranje_po_vrsti:
		do {
			novi = 0;
			p = knjiga;

			while (p->next != pp) {
				if (strcmp(p->vrsta, p->next->vrsta) > 0) {
					zamjena(p, p->next);
					novi = 1;
				}
				p = p->next;
			}
			pp = p;
		} while (novi);
		break;

	default:
		printf("Krivi unos.\n");
		return;
	}

	zapis(knjiga);
}


void zamjena(KNJIGA* a, KNJIGA* b) {
	char tempNaslov[100];
	char tempAutor[100];
	char tempVrsta[100];
	int tempGodinaIzdanja = a->godina_izdanja;
	int tempDostupnost = a->dostupnost;
	int tempID = a->ID;

	strcpy(tempNaslov, a->naslov);
	strcpy(tempAutor, a->autor);
	strcpy(tempVrsta, a->vrsta);

	strcpy(a->naslov, b->naslov);
	strcpy(a->autor, b->autor);
	strcpy(a->vrsta, b->vrsta);
	a->godina_izdanja = b->godina_izdanja;
	a->dostupnost = b->dostupnost;
	a->ID = b->ID;

	strcpy(b->naslov, tempNaslov);
	strcpy(b->autor, tempAutor);
	strcpy(b->vrsta, tempVrsta);
	b->godina_izdanja = tempGodinaIzdanja;
	b->dostupnost = tempDostupnost;
	b->ID = tempID;


}

void zapis(KNJIGA* knjiga) {
	FILE* fp = fopen(imeDatoteke, "w");
	if (fp == NULL) {
		perror("Pogreska pri zapisivanju u datoteku.");
		return;
	}
	while (knjiga != NULL) {
		fprintf(fp, "Knjiga %d\n\tNaslov: %s\n\tAutor: %s\n\tVrsta: %s\n\tGodina izdanja: %d\n\tDostupnost: %d\n",
			knjiga->ID, knjiga->naslov, knjiga->autor, knjiga->vrsta,
			knjiga->godina_izdanja, knjiga->dostupnost);
		knjiga = knjiga->next;
	}
	fclose(fp);
}


void dostupnost(KNJIGA* knjiga) {
	if (knjiga == NULL) {
		printf("Nema unesenih knjiga.\n");
		return;
	}

	char naslov[100];
	printf("Unesite naslov knjige za provjeru dostupnosti: ");
	fgets(naslov, 100, stdin);
	naslov[strcspn(naslov, "\n")] = '\0';

	KNJIGA* temp = knjiga;
	while (temp != NULL) {
		if (strcmp(temp->naslov, naslov) == 0) {
			if (temp->dostupnost) {
				printf("Knjiga '%s' je dostupna.\n", naslov);
			}
			else {
				printf("Knjiga '%s' nije dostupna.\n", naslov);
			}
			return;
		}
		temp = temp->next;
	}
	printf("Knjiga '%s' nije pronadena.\n", naslov);
}

void pretrazivanje(KNJIGA* knjiga) {
	if (knjiga == NULL) {
		printf("Nema unesenih knjiga.\n");
		return;
	}

	int opcija;
	printf("Pretra�ite po:\n1. Naslovu\n2. Autoru\n3. Vrsti\n");
	if (scanf("%d", &opcija) != 1) {
		printf("Greska.");
	}
	if (getchar() == EOF) {
		perror("Greska pri citanju.");
		return;
	}

	char unos[100];
	switch (opcija) {
	case unos_naslova:
		printf("Unesite naslov: ");
		fgets(unos, 100, stdin);
		unos[strcspn(unos, "\n")] = '\0';
		break;
	case unos_autora:
		printf("Unesite autora: ");
		fgets(unos, 100, stdin);
		unos[strcspn(unos, "\n")] = '\0';
		break;
	case unos_vrste:
		printf("Unesite vrstu: ");
		fgets(unos, 100, stdin);
		unos[strcspn(unos, "\n")] = '\0';
		break;
	default:
		printf("Krivi unos.\n");
		return;
	}

	KNJIGA* temp = knjiga;
	int found = 0;
	while (temp != NULL) {
		if ((opcija == 1 && strcmp(temp->naslov, unos) == 0) ||
			(opcija == 2 && strcmp(temp->autor, unos) == 0) ||
			(opcija == 3 && strcmp(temp->vrsta, unos) == 0)) {
			printf("Knjiga %d\n\tNaslov: %s\n\tAutor: %s\n\tVrsta: %s\n\tGodina izdanja: %d\n\tDostupnost: %d\n",
				temp->ID, temp->naslov, temp->autor, temp->vrsta,
				temp->godina_izdanja, temp->dostupnost);
			found = 1;
		}
		temp = temp->next;
	}

	if (!found) {
		printf("Knjiga nije pronadena.\n");
	}
}

inline void memorija(KNJIGA* knjiga) {
	free(knjiga->naslov);
	free(knjiga->autor);
	free(knjiga->vrsta);
	free(knjiga);
}

void Memorija(KNJIGA* knjiga) {
	KNJIGA* temp;
	while (knjiga != NULL) {
		temp = knjiga;
		knjiga = knjiga->next;
		memorija(temp);
	}
}

KNJIGA* pretragaID(KNJIGA* knjiga, int ID) {
	while (knjiga != NULL && knjiga->ID != ID) {
		knjiga = knjiga->next;
	}
	return knjiga;
}

inline int maxID(KNJIGA* knjiga) {
	int max = 0;
	while (knjiga != NULL) {
		if (knjiga->ID > max) {
			max = knjiga->ID;
		}
		knjiga = knjiga->next;
	}
	return max;
}



void rekzapis(FILE* fp, KNJIGA* knjiga) {
	if (knjiga == NULL) return;
	fprintf(fp, "Knjiga %d\n\tNaslov: %s\n\tAutor: %s\n\tVrsta: %s\n\tGodina izdanja: %d\n\tDostupnost: %d\n",
		knjiga->ID, knjiga->naslov, knjiga->autor, knjiga->vrsta,
		knjiga->godina_izdanja, knjiga->dostupnost);
	rekzapis(fp, knjiga->next);
}

KNJIGA* ucitaj() {
	FILE* fp = fopen(imeDatoteke, "r");
	if (fp == NULL) {
		perror("Pogreska pri citanju datoteke.");
		return NULL;
	}
	KNJIGA* knjiga = NULL;
	KNJIGA* tempKnjiga = NULL;
	KNJIGA* trenutnaKnjiga = NULL;
	int id, dostupnost, godina_izdanja;
	char naslov[100] = { 0 };
	char autor[100] = { 0 };
	char vrsta[100] = { 0 };

	while (fscanf(fp, "Knjiga %d\n", &id) == 1) {
		if (fscanf(fp, "\tNaslov: %[^\n]\n", naslov) != 1) {
			printf("Greska.");
			exit(EXIT_FAILURE);
		}
		if (fscanf(fp, "\tAutor: %[^\n]\n", autor) != 1) {
			printf("Greska.");
			exit(EXIT_FAILURE);
		}
		if (fscanf(fp, "\tVrsta: %[^\n]\n", vrsta) != 1) {
			printf("Greska.");
			exit(EXIT_FAILURE);
		}
		if (fscanf(fp, "\tGodina izdanja: %d\n", &godina_izdanja) != 1) {
			printf("Greska.");
			exit(EXIT_FAILURE);
		}
		if (fscanf(fp, "\tDostupnost: %d\n", &dostupnost) != 1) {
			printf("Greska.");
			exit(EXIT_FAILURE);
		}

		tempKnjiga = (KNJIGA*)calloc(1, sizeof(KNJIGA));
		if (tempKnjiga == NULL) {
			perror("Greska pri ucitavanju knjige.");
			fclose(fp);
			Memorija(knjiga);
			return NULL;
		}

		tempKnjiga->naslov = _strdup(naslov);
		tempKnjiga->autor = _strdup(autor);
		tempKnjiga->vrsta = _strdup(vrsta);
		tempKnjiga->godina_izdanja = godina_izdanja;
		tempKnjiga->dostupnost = dostupnost;
		tempKnjiga->ID = id;
		tempKnjiga->next = NULL;

		if (knjiga == NULL) {
			knjiga = tempKnjiga;
			trenutnaKnjiga = knjiga;
		}
		else {
			trenutnaKnjiga->next = tempKnjiga;
			trenutnaKnjiga = trenutnaKnjiga->next;
		}
	}

	fclose(fp);
	return knjiga;
}