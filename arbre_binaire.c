#include <stdio.h>
#include <stdlib.h>
#include "arbre_binaire.h"
#include <string.h>
pArbre creerArbre(int a)
{
    pArbre new= malloc(sizeof(Arbre));
    if(new == NULL)
    {
        exit(1);//Je l'ai modifié car lors de la création par convention il faut quitter le prog si le noeud vide
    }
    new->nombre=a;//Je l'ai simplifié un peu
    new->fg=NULL;//idem
    new->fd=NULL;//idem
    return new;
}

int estVide(pArbre a) //J'ai modifié tout ton bloc ici
{
    if(a==NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int estFeuille(pArbre a)
{
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

int element(pArbre a)//Moi j'aurai proposé un truc de ce genre:
{
    /*int r;
    r=a->nombre;
    return r;*/

    if (estVide(a) == 1)
    {
        return 0;
    }
    else{
        return a->nombre;
    }
    if (a) return a->nombre;
}

int existeFilsGauche(pArbre a) //je suis d'accord avec toi
{
    return (a->fg ? 1 : 0);
}

int existeFilsDroit(pArbre a) //je suis d'accord avec toi
{
    return (a->fd ? 1 : 0);
}
pArbre ajouterFilsDroit(pArbre a, int e)// je dirai plutôt ça:
{
    /*if(a==NULL)
    {
        a=creerArbre(e);
        return a;
    }
    else if(!existeFilsDroit(a))
    {
        a=creerArbre(e);
        return a;
    }*/
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

pArbre ajouterFilsGauche(pArbre a, int e) // je dirai plutôt ça:
{
     /*if(a==NULL)
    {
        a=creerArbre(e);
        return a;
    }
    else if(!existeFilsGauche(a))
    {
        a=creerArbre(e);
        return a;
    }*/
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
        parcoursPostFixe(a->fg);
        parcoursPostFixe(a->fd);
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

int nbmFeuille(pArbre a) // je dirai plus:
{
    /*if(estVide(a))
    {
        return 0;
    }
    if(estFeuille(a))
    {
        return 1;
    }
    return nbmFeuille(a->fg)+nbmFeuille(a->fd);*/


    if (a == NULL) return 0 ;
    if (estFeuille(a)) return 1;
    else return nbmFeuille(filsGauche(a)) + nbmFeuille(filsDroit(a));
}

int taille(pArbre a) // je dirai plus:
{
    /*if(estVide(a)||estFeuille(a))
    {
        return 0;
    }
    return 1+taille(a->fg)+taille(a->fd);*/


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

pArbre suppMinAVL(pArbre a, int *h, int *pe)
{
    pArbre tmp;
    if(a->fg == NULL)
    {
        *pe = a->nombre;
        *h = -1;
        tmp = a;
        a = a->fd;
        free(tmp);
        return a ;
    }
    else
    {
        a->fg = suppMinAVL(a->fg,h,pe);
        *h=-*h;
    }
    if(*h!=0)
    {
        a->equilibre = a->equilibre + *h;
        if(a->equilibre == 0)
        {
            *h = -1;
        }
        else
        {
            *h = 0;
        }
    }
    return a;
}

pArbre suppressionAVL(pArbre a,int e, int *h)
{
    pArbre tmp;
    if(a==NULL)
    {
        *h = 1;
        return a;
    }
    else if(e>a->nombre)
    {
        a->fd = suppressionAVL(a->fd,e,h);
    }
    else if(e<a->nombre)
    {
        a->fg = suppressionAVL(a->fg,e,h);
        *h = -*h;
    }
    else if(existeFilsDroit(a))
    {
        a->fd = suppMinAVL(a->fd,h,&a->nombre);
    }
    else
    {
        tmp = a;
        a = a->fg;
        free(tmp);
        *h = -1;
    }
    if(a==NULL)
    {
        *h=0;
    }
    if(*h!=0)
    {
        a->equilibre = a->equilibre + *h;
        if(a->equilibre == 0)
        {
            *h = 0;
        }
        else
        {
            *h = 1;
        }
    }
    return a;
}

int min(int a, int b)
{
    return (a<b ? a : b);
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

//partie liste_chainee

pListe creerChainon(int n)
{
    pListe c = malloc(sizeof(Chainon));
    if(c==NULL)
    {
        exit(1);
    }
    c->suivant=NULL;
    c->nombre = n;
    return c;
}

int element_liste_chainee(pListe p1)
{
    return p1->nombre;
}

void traiter_liste_chainee(pListe p1)
{
    printf("%d ", p1->nombre);
}

pListe insertFin(pListe liste, int n)
{
    pListe nouveau = creerChainon(n), p1= liste;
    while(p1->suivant != NULL)
    {
        p1 = p1->suivant;
    }
    p1->suivant = nouveau;
    return liste;
}

pListe insertDebut(pListe liste, int n)
{
    pListe nouveau = creerChainon(n), p1= liste;
    nouveau->suivant = p1;
    p1 = nouveau;
    return liste;
}

pListe insertMilieu(pListe liste, int e)
{
    int i;
    pListe nouveau, p1=liste;
    pListe a;
    if(e==0 || p1==NULL)
    {
        p1 = insertDebut(p1, e);
    }
    else
    {
        a=p1;
        for(i=0;i<e;i++)
        {
            if(a==NULL)
            {
                return NULL;
            }
            else
            {
                a = a->suivant;
            }
        }
        nouveau = creerChainon(e);
        nouveau->suivant = a->suivant;
        a->suivant = nouveau;
    }
    return liste;
}

pListe suppDebut(pListe p1)
{
    pListe a;
    if(p1==NULL)
    {
        return NULL;
    }
    a=p1;
    p1=a->suivant;
    free(a);
    return p1;
}
int taille_liste_chainee(pListe p1)
{
    int t=0;
    while (p1 != NULL)
    {
        t++;
        printf("->");
        traiter_liste_chainee(p1);
        p1=p1->suivant;
        
    }
    return t;
}

pListe ajouterCroissant(pListe liste, int e) 
{
	nouveau=creerChainon(e);
	pListe p1;
	if(p1==NULL){// si la liste est vide
		p1=nouveau;
	}
	else if (p1->nombre > e) 
    {
		p1=insertDebut(liste,e);
	}
	else
    {
		while(p1->suivant!= NULL && p1->suivant->nombre < e)
        { 
			p1=p1->suivant;
		}
		if(p1->suivant==NULL)
        { 
			p1->suivant=nouveau;
		}
		else
        {
			nouveau->suivant=p1->suivant;
			p1->suivant = nouveau;
		}
	}
	return p1;
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

