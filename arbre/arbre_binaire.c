#include <stdio.h>
#include <stdlib.h>
#include "arbre_binaire.h"
#include <string.h>
pArbre creerArbre(int a){
    pArbre new= malloc(sizeof(Arbre));
    if(new == NULL){
        return new;
    }
    *new = (Arbre) {a, NULL, NULL, 0, 0};
    return new;
}

int estVide(pArbre a){
    return a == NULL;
}

int estFeuille(pArbre a){
    /*
    if(a == NULL){
        return 0;
    }
    else if(a->fg == NULL && a->fd == NULL){
        return 1;
    }
    else{
        return 0;
    }*/
    return (a ? ((!a->fg) && (!a->fd) ? 1:0) : 0);
}

int element(pArbre a){
    
    if (estVide(a) == 1)
    {
        return 0;
    }
    else{
        return a->nombre;
    }
    if (a) return a->nombre;
}

int existeFilsGauche(pArbre a){
    return (a->fg ? 1 : 0);
}

int existeFilsDroit(pArbre a){
    return (a->fd ? 1 : 0);
}
pArbre ajouterFilsDroit(pArbre a, int e)
{
    pArbre b;
    if (estVide(a) == 1){
        return a;
    }
    else
    {
        b  = creerArbre(e);
        a->fd = b;
        return a;
    }
    return a;   
}

pArbre ajouterFilsGauche(pArbre a, int e)
{
    pArbre b;
    if (estVide(a) == 1){
        return a;
    }
    else
    {
        b = creerArbre(e);
        a->fg = b;
        return a;
    }
    
}


void parcoursPrefixe(pArbre a)
{   
    if (estVide(a) != 1)
    {
        traiter(a);
        parcoursPrefixe(a->fg);
        parcoursPrefixe(a->fd);
    }
}

void parcoursPostFixe(pArbre a)
{
    if (estVide(a) != 1)
    {
        parcoursPrefixe(a->fg);
        parcoursPrefixe(a->fd);
        traiter(a);
    }
}

void parcoursInfixe(pArbre a)
{
    if (estVide(a) !=1)
    {
        parcoursInfixe(a->fg);
        traiter(a);
        parcoursInfixe(a->fd);
    }
}
void traiter(pArbre a)
{
    printf("%d ", a->nombre);
}
pArbre modifierRacine(pArbre a, int e)
{
    if (a != NULL) a->nombre = e;
    return a;   
}
void supprimerFilsDroit(pArbre a)
{
    if (a == NULL){exit(1);}
    else if (existeFilsDroit(a) == 1)
    {
        if (existeFilsGauche(a->fd)) supprimerFilsGauche(a->fd);
        if (existeFilsDroit(a->fd)) supprimerFilsDroit(a->fd);
        a->fd = NULL;
        free(a->fd);
    }
}
void supprimerFilsGauche(pArbre a)
{
    
    if (a == NULL){exit(1);}
    else if (existeFilsGauche(a))
    {
        if (existeFilsGauche(a->fg)) supprimerFilsGauche(a->fg);
        if (existeFilsDroit(a->fg)) supprimerFilsDroit(a->fg);
        a->fg = NULL;
        free(a->fg);
    }
}
pArbre filsDroit(pArbre a)
{
    if (a == NULL) exit(1);
    return (existeFilsDroit(a)) ?  a->fd : NULL;
}

pArbre filsGauche(pArbre a)
{
    if (a == NULL) exit(1);
    return (existeFilsGauche(a)) ?  a->fg : NULL;
}

int nbmFeuille(pArbre a)
{
    if (a == NULL) return 0 ;
    if (estFeuille(a)) return 1;
    else return nbmFeuille(filsGauche(a)) + nbmFeuille(filsDroit(a));
}

int taille(pArbre a)
{
    if (a == NULL) return 0; else if (estFeuille(a)) return 0 ;
    else return 1 + taille(filsGauche(a)) + taille(filsDroit(a));
}
int hauteur(pArbre a)
{
    return (a == NULL) ? -1 : 1 + max(hauteur(filsGauche(a)), hauteur(filsDroit(a)));
}
//partie file
Chainon* creationChainon(pArbre a)
{
    Chainon* p = malloc(sizeof(Chainon));
    if (p == NULL)
    {
        exit(1);
    }
    p->arbre = a;
    p->suivant = NULL;
    return p;   
}
int verif(File * file) {
    int res = 0;
    if (file == NULL) {
        res = -1;
    } else if ((file->tete == NULL && file->queue!= NULL) || (file->queue == NULL && file->tete!= NULL)) {
//(file->tete==NULL)!=(file->queue==NULL)
        res = -2;
    } else if (file->queue != NULL && file->queue->suivant != NULL) {
        res = -3;
    }
    return (res);
}
int enfiler(File *f, pArbre a) {
    Chainon * c;
    int result = 0;
    result = verif(f);
    if (result > -2) //test de la file si elle est corompue
    {
        c = creationChainon(a);
        if (f->queue == NULL) //si la file est vide
        {
            f->tete = c; //affecter la tete au 1er chainon   
            f->queue = c; //affecter la queue au 1er chainon
        } else {
            f->queue -> suivant = c; //affecter le queue au dernier chainoN
            f->queue = c; //decaler la queue
        }
    }
    return result;
}

pArbre defiler(File * f)
{
    Chainon *p1 = f->tete;
    pArbre a = f->tete->arbre;
    if (f->tete->suivant == NULL) f->queue = NULL;
    f->tete = f->tete->suivant;
    free(p1);
    return a;
}
void creerfile(File *f)
{
    f->tete = NULL;
    f->queue = NULL;
}

void parcoursLargeurs(pArbre a)
{
    File f;
    if (! estVide(a))
    {
        creerfile(&f);
        enfiler(&f, a);
        while ((f.tete != NULL))
        {
            a = defiler(&f);
            traiter(a);
            if (existeFilsGauche(a)) enfiler(&f, a->fg);
            if (existeFilsDroit(a)) enfiler(&f, a->fd);
        }
    }
}

void parcoursmoy(pArbre a, int*c, int* somme)
// l'idée de base est de pointé sur c et somme afin de modifier directement les valeurs dedans.
{
    if (a != NULL){
        parcoursmoy(a->fg, c, somme);
        *c += 1;
        *somme += a->nombre;
        parcoursmoy(a->fd, c, somme);
    }
}

//partie AVL


float moyennefg(pArbre a)
{
    int c = 0;
    int somme = 0;
    float moy;
    parcoursmoy(a->fg, &c, &somme);
    moy = somme/c;
    return moy;
}
float moyennefd(pArbre a)
{
    int c = 0;
    int somme = 0;
    float moy;
    parcoursmoy(a->fd, &c, &somme);
    moy = somme/c;
    return moy;
}
pArbre insertionAVL(pArbre a, int e, int *h)
{
    if(a==NULL)
    {
        *h=1;
        return creerArbre(e);
    }
    else if(e<a->nombre)
    {
        a->fg=insertionAVL(a->fg,e,h);
        *h=-*h;
    }
    else if(e>a->nombre)
    {
        a->fd=insertionAVL(a->fd,e,h);
    }
    else 
    {
        *h=0;
        return a;
    }
    if(*h!=0)
    {
        a->equilibre=a->equilibre+*h;
        if(a->equilibre==0)
        {
            *h=0;
        }
        else 
        {
            *h=1;
        }
    }
    return a;
}

int min(int a, int b)
{
    return (a<b ? a:b);
}

int min_of_three(int a, int b, int c)
{
    return min(min(a,b),c);
}

int max(int a, int b)
{
    return (a<b ? b : a);
}

int max_of_three(int a, int b, int c)
{
    return max(max(a,b),c);
}

pArbre rotationDroite(pArbre a)
{
    pArbre pivot;
    int eq_a, eq_p;
    pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - min(eq_p,0)+1;
    pivot->equilibre = max_of_three(eq_a+2, eq_a+eq_p+2, eq_p+1);
    a = pivot;
    return a;
}

pArbre rotationGauche(pArbre a)
{
    pArbre pivot;
    int eq_a, eq_p;
    pivot=a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a-max(eq_p,0)-1;
    pivot->equilibre = min_of_three(eq_a-2, eq_a+eq_p-2, eq_p-1);
    a=pivot;
    return a;
}

pArbre doubleRotationDroite(pArbre a)
{
    a->fg = rotationGauche(a->fg);
    return rotationDroite(a);
}

pArbre doubleRotationGauche(pArbre a)
{
    a->fd = rotationDroite(a->fd);
    return rotationGauche(a);
}

pArbre equilibrerAVL(pArbre a)
{
    if(a->equilibre >= 2)
    {
        if(a->fd->equilibre >= 0)
        {
            return rotationGauche(a);
        }
        else 
        {
            return doubleRotationGauche(a);
        }
    }
    else if(a->equilibre <= -2)
    {
        if(a->fg->equilibre <= 0)
        {
            return rotationDroite(a);
        }
        else 
        {
            return doubleRotationDroite(a);
        }
    }
    return a;
}
/*
void MinMaxABR(pArbre a, int *min, int* max)
{
    if (*min> a->nombre)
        *min = a->nombre;
    else if (*max < a->nombre)
        *max = a->nombre;
    MinMaxABR(a->fg, &min, &max);
    MinMaxABR(a->fd, &min, &max);
}*/
/*
void affArbreGraphique(pArbre a,int info) 
{
    TArbBin * Tarb;
    int iTarb;
    int tailleAff = 7;// noeud=" xx,xx "
    int largeur;  // largeur d'affichage maximum
    int h;
    int nbNoeuds;
    int p, i, j;
    int ecart;
    puts("");
    if(estVide(a)) 
    {
        puts("Arbre vide");
        return;
    }
    h = hauteur(a);
    largeur = tailleAff * ((int) pow(2, h)); // taille int* nbFeuillesMax;
    Tarb = ABVersTab(a, info);
    iTarb = 0;
    for(p = 0, nbNoeuds = 1; p <= h; p++, nbNoeuds *= 2)
     {  // p = profondeur, nbNoeuds par niveau
        ecart = (largeur / (nbNoeuds * 2));
        for(j = 1; j <= nbNoeuds; j++)
         {
            for(i = 0; i < ecart -3; i++)   putchar(' '); // -3 car 3 caracteres avant milieu
            if(Tarb[iTarb].elmt == 0)   printf("..... ");
            else printf(" %2d ", Tarb[iTarb].elmt);
            iTarb++;
            if(j < nbNoeuds && p < h) // entre 2 noeuds sauf au dernier niveau
                for(i = 0; i < ecart -4; i++) putchar(' '); // -4 car 4 caracteres apres milieu
         }
        puts("");
        }
        free(Tarb);
        puts("");
}*/

