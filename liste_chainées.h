#ifndef __LISTE__
#define __LISTE__

typedef struct chainon
{
    int nombre;
    struct chainon* suivant;
} Chainon;

typedef Chainon * pListe;
pListe creerChainon();
int element(pListe p1);
void traiter(pListe p1);
pListe insertFin(pListe p1);
pListe insertDebut(pListe p1);
pListe insertMilieu(pListe p1, int e);
pListe suppDebut(pListe p1);
pListe triselection(pListe p1,int n);