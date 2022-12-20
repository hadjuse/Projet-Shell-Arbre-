#ifndef __ARBRE__
#define __ARBRE__

typedef struct arbre {
    int nombre;
    struct arbre *fg;
    struct arbre *fd;
    int equilibre;
    int hauteur;
} Arbre;
typedef Arbre * pArbre;
typedef struct chainon
{
    pArbre arbre;
    struct chainon * suivant;
}Chainon;



typedef struct file
{
    Chainon* queue;
    Chainon* tete;
}File;

//ds------------------------------
void parcoursmoy(pArbre a, int*c, int* somme);
float moyennefg(pArbre a);
float moyennefd(pArbre a);
void MinMaxABR(pArbre a, int min, int max);
//partie arbre----------------------
pArbre creerArbre(int a);
int estVide(pArbre a);
int estFeuille(pArbre a);
int element(pArbre a);
int existeFilsGauche(pArbre a);
int existeFilsDroit(pArbre a);
pArbre ajouterFilsGauche(pArbre a, int e);
pArbre ajouterFilsDroit(pArbre a, int e);
void traiter(pArbre a);
void parcoursPrefixe(pArbre a);
void parcoursPostFixe(pArbre a);
void parcoursInfixe(pArbre a);
void parcoursLargeurs(pArbre a);
pArbre modifierRacine(pArbre a, int e);
void supprimerFilsDroit(pArbre a);
void supprimerFilsGauche(pArbre a);
pArbre filsGauche(pArbre a);
pArbre filsDroit(pArbre a);
int max(int a, int b);
int taille(pArbre a);
int nbmFeuille(pArbre a);
int hauteur(pArbre a);
//partie file
Chainon* creationChainon(pArbre a);
int verif(File* file);
int enfiler(File* f, pArbre a);
pArbre defiler(File *f);
void creerfile(File *f);

//void affArbreGraphique(pArbre a,int info);
//partie Arbre binaire de recherche
int recherche(pArbre a, int e);
pArbre insertionABR(pArbre a, int e);
pArbre insertionABRIter(pArbre a, int e);
pArbre insertionABRIter2(pArbre a, int e);
pArbre suppMax(pArbre a, int *e);
pArbre suppressionABR(pArbre a, int e);

//partie AVL
int min(int a, int b);
int min_of_three(int a, int b, int c);
int max(int a, int b);
int max_of_three(int a, int b, int c);
pArbre rotationDroite(pArbre a);
pArbre rotationGauche(pArbre a);
pArbre doubleRotationDroite(pArbre a);
pArbre doubleRotationGauche(pArbre a);
pArbre equilibrerAVL(pArbre a);
pArbre insertionAVL(pArbre a, int n, int *hauteur);
//void MinMaxABR(pArbre a, int *min, int *max);
#endif