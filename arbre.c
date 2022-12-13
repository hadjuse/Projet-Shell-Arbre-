# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# include "arbre.h"
Arbre* creationArbre(int a)
{
    Arbre* noeud=malloc(sizeof(Arbre));
    if(noeud==NULL)
    {
        exit(1);
    }
    noeud->elmt=a;
    noeud->fg=NULL;
    noeud->fd=NULL;
    noeud->equilibre = 0;
    return noeud;
}

int estVide(pArbre a)
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
    if(a==NULL)
    {
        exit(1);
    }
    if(a->fd==NULL && a->fg==NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int element(pArbre a)
{
    int r;
    r=a->elmt;
    return r;
}

int existeFd(pArbre a)
{
    if(a==NULL)
    {
        exit(1);
    }
    else if(a->fd==NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int existeFg(pArbre a)
{
    if(a==NULL)
    {
        exit(1);
    }
    else if(a->fg==NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

pArbre ajouterFilsGauche(pArbre a, int e)
{
    if(a==NULL)
    {
        a=creationArbre(e);
        return a;
    }
    else if(!existeFg(a))
    {
        a->fg=creationArbre(e);
        return a;
    }
    return a;
}

pArbre ajouterFilsDroit(pArbre a, int e)
{
    if(a==NULL)
    {
        a=creationArbre(e);
        return a;
    }
    else if(!existeFd(a))
    {
        a->fd=creationArbre(e);
        return a;
    }
    return a;
}

void Traiter(pArbre a)
{
    printf("%d",a->elmt);
}

void parcoursInfixe(pArbre a)
{
    if(!estVide(a))
    {
        parcoursInfixe(a->fg);
        Traiter(a);
        parcoursInfixe(a->fd);
    }
}