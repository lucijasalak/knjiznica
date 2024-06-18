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
		do{
			printf("Godina izdanja: ");
			if (scanf("%d", &novaknjiga->godina_izdanja) != 1) {
				printf("Molimo unesite valjanu godinu.");
				while (getchar() != '\n');
			}
			else {
				break;
			}
		} while (1);
		int unesen;
		do {
			printf("Dostupnost (1 - dostupna, 0 - nije dostupna): ");
			unesen = scanf("%d", &novaknjiga->dostupnost);

			if (unesen != 1 || (novaknjiga->dostupnost != 0 && novaknjiga->dostupnost != 1)) {
				printf("Molimo unesite iskljucivo 1 ili 0.\n");

				while (getchar() != '\n');
			}
			else {
				break;
			}
		} while (1);

		if (novaknjiga->dostupnost == 1) {
			printf("Odabrana je dostupna.\n");
		}
		else {
			printf("Odabrana nije dostupna.\n");
		}
		if (getchar() == EOF) {
			perror("Greska pri citanju.");
			exit(EXIT_FAILURE);
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

			while (p != pp && p->next != NULL) {
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
	printf("Pretrazite po:\n1. Naslovu\n2. Autoru\n3. Vrsti\n");
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
void brisanje(KNJIGA** knjiga, int id) {
	if (*knjiga == NULL) {
		printf("Lista je prazna.\n");
		return;
	}

	KNJIGA* temp = *knjiga;
	KNJIGA* prethodna = NULL;

	
	if (temp != NULL && temp->ID == id) {
		*knjiga = temp->next;
		memorija(temp);
		zapis(*knjiga);
		printf("Knjiga s ID %d je obrisana.\n", id);
		return;
	}


	while (temp != NULL && temp->ID != id) {
		prethodna = temp;
		temp = temp->next;
	}

	
	if (temp == NULL) {
		printf("Knjiga s ID %d nije pronadena.\n", id);
		return;
	}

	
	prethodna->next = temp->next;

	
	memorija(temp);

	
	zapis(*knjiga);
	printf("Knjiga s ID %d je obrisana.\n", id);
}

void obrisisve (KNJIGA** knjiga) {
	// Funkcija za brisanje svih knjiga iz datoteke
	KNJIGA* temp = *knjiga;
	KNJIGA* sljedeci;

	while (temp != NULL) {
		sljedeci = temp->next;
		free(temp);
		temp = sljedeci;
	}

	*knjiga = NULL;
	printf("Sve knjige su uspjesno obrisane.\n");
	zapis(*knjiga);  // Ovdje pozovite funkciju za spremanje prazne liste u datoteku
}

void azuriranje(KNJIGA* knjiga) {
	if (knjiga == NULL) {
		printf("Nema unesenih knjiga.\n");
		return;
	}

	int id;
	printf("Unesite ID knjige koju zelite azurirati: ");
	if (scanf("%d", &id) != 1) {
		printf("Pogresan unos.\n");
		return;
	}
	if (getchar() == EOF) {
		perror("Greska pri citanju.");
		exit(EXIT_FAILURE);
	}

	KNJIGA* temp = knjiga;
	while (temp != NULL) {
		if (temp->ID == id) {
			int duljina = 100;
			printf("Azurirajte podatke za knjigu ID %d:\n", id);

			printf("Naslov (trenutni: %s): ", temp->naslov);
			fgets(temp->naslov, duljina, stdin);
			temp->naslov[strcspn(temp->naslov, "\n")] = '\0';

			printf("Autor (trenutni: %s): ", temp->autor);
			fgets(temp->autor, duljina, stdin);
			temp->autor[strcspn(temp->autor, "\n")] = '\0';

			printf("Vrsta (trenutna: %s): ", temp->vrsta);
			fgets(temp->vrsta, duljina, stdin);
			temp->vrsta[strcspn(temp->vrsta, "\n")] = '\0';

			printf("Godina izdanja (trenutna: %d): ", temp->godina_izdanja);
			if (scanf("%d", &temp->godina_izdanja) != 1) {
				printf("Pogrešan unos.\n");
				return;
			}
			if (getchar() == EOF) {
				perror("Greska pri citanju.");
				exit(EXIT_FAILURE);
			}

			printf("Dostupnost (1 - dostupna, 0 - nije dostupna) (trenutna: %d): ", temp->dostupnost);
			if (scanf("%d", &temp->dostupnost) != 1) {
				printf("Pogrešan unos.\n");
				return;
			}
			if (getchar() == EOF) {
				perror("Greska pri citanju.");
				exit(EXIT_FAILURE);
			}

			printf("Podaci su azurirani.\n");
			zapis(knjiga);
			return;
		}
		temp = temp->next;
	}

	printf("Knjiga s ID %d nije pronadena.\n", id);
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