
#ifndef HEADER_H
#define HEADER_H

extern const char* imeDatoteke;

typedef enum {
	UNOS_NOVE_KNJIGE = 1,
	PREGLED_KNJIGA,
	SORTIRANJE_KNJIGA,
	PROVJERA_DOSTUPNOSTI,
	PRETRAZIVANJE_KNJIGA,
	IZLAZ
} IzbornikOpcija;

typedef enum {
	UNOS_NASLOVA = 1,
	UNOS_AUTORA,
	UNOS_VRSTE
} UnosPodataka;

typedef enum {
	SORTIRANJE_PO_NASLOVU = 1,
	SORTIRANJE_PO_AUTORU,
	SORTIRANJE_PO_VRSTI,
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


KNJIGA* dodavanjeNoveKnjige(KNJIGA*);
void ispisKnjigaUDatoteku(KNJIGA*);
void ispisKnjigaUKonzolu();
void izbornik();
void sortiranjeKnjiga(KNJIGA*);
void zamjena(KNJIGA*, KNJIGA*);
void provjeraDostupnosti(KNJIGA*);
void pretrazivanjeKnjiga(KNJIGA*);
inline void oslobadjanjeMemorije(KNJIGA*);
void oslobadjanjeMemorijeSvega(KNJIGA*);
KNJIGA* trazenjeKnjigePoID(KNJIGA*, int);
inline int maxID(KNJIGA*);
void ponovnoZapisivanjeDatoteke(KNJIGA*);
void zapisiKnjiguRekurzivno(FILE*, KNJIGA*);
KNJIGA* ucitajKnjigeIzDatoteke();

#endif

