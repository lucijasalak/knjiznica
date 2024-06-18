
#ifndef HEADER_H
#define HEADER_H

extern const char* imeDatoteke;

typedef enum {
	nova_knjiga = 1,
	pregled_knjiga,
	sortiranje_knjiga,
	provjera_dostupnosti,
	pretrazivanje_knjiga,
	IZLAZ
} IzbornikOpcija;

typedef enum {
	UNOS_NASLOVA = 1,
	UNOS_AUTORA,
	UNOS_VRSTE
} UnosPodataka;

typedef enum {
	sortiranje_po_naslovu = 1,
	sortiranje_po_autoru,
	sortiranje_po_vrsti,
} OpcijeSortiranja;

typedef struct knjiznica {
	char* naslov;
	char* autor;
	char* vrsta;
	int godina_izdanja;
	int dostupnost;
	int ID;
	struct knjiznica* next;
} KNJIGA;


KNJIGA* novaknjiga(KNJIGA*);
void ispisknjigadat(KNJIGA*);
void ispis();
void izbornik();
void sortiranje(KNJIGA*);
void zamjena(KNJIGA*, KNJIGA*);
void dostupnost(KNJIGA*);
void pretrazivanje(KNJIGA*);
inline void memorija(KNJIGA*);
void Memorija(KNJIGA*);
KNJIGA* pretragaID(KNJIGA*, int);
inline int maxID(KNJIGA*);
void zapis(KNJIGA*);
void rekzapis(FILE*, KNJIGA*);
KNJIGA* ucitaj();

#endif

