#ifndef ARBRE1
#define ARBRE1

typedef struct arbre
{
    int elmt;
    struct arbre* fd;
    struct arbre* fg;
    int equilibre;
    int hauteur;
} Arbre;

typedef Arbre * pArbre;

Arbre* creationArbre(int a);
int estVide(pArbre a);
int estFeuille(pArbre a);
int element(pArbre a);
int existeFd(pArbre a);
int existeFg(pArbre a);
pArbre ajouterFilsGauche(pArbre a, int e);
pArbre ajouterFilsDroit(pArbre a, int e);
int recherche(pArbre a,int e);
void traiter(pArbre a);
pArbre insertionABR(pArbre a,int e);
pArbre insertionAVL(pArbre a,int e,int *h);
pArbre suppMax(pArbre a,int *pe);
pArbre suppression(pArbre a,int e);
int min(int a, int b);
int min_of_three(int a, int b, int c);
int max(int a, int b);
int max_of_three(int a, int b, int c);
pArbre rotationDroite(pArbre a);
pArbre rotationGauche(pArbre a);
pArbre doubleRotationDroite(pArbre a);
pArbre doubleRotationGauche(pArbre a);
pArbre equilibrerAVL(pArbre a);
#endif