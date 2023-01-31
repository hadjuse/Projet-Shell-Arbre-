#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arbre_binaire.h"

pListe creerChainon(int a, int cols1, char *cols2, float cols3, char *cols4, float cols5, float cols6, float somme, char *mode)
{
    pListe c = malloc(sizeof(Chainon));
    if (c == NULL)
    {
        exit(1);
    }
    c->suivant = NULL;
    c->nombre = a;
    if (strcmp(mode, "1") == 0)
    {
        c->arbre=creerArbre(a, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
    }
    
    return c;
}

pListe insertDebut(pListe liste, int e, int cols1, char *cols2, float cols3, char *cols4, float cols5, float cols6, float somme, char *mode)
{
    pListe nouveau = creerChainon(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode), p1 = liste;
    nouveau->suivant = p1;
    p1 = nouveau;
    return liste;
}

pListe ajouterCroissant(pListe liste, int e, int cols1, char *cols2, float cols3, char *cols4, float cols5, float cols6, float somme, char *mode)
{

    pListe nouveau = creerChainon(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
    pListe p1 = liste;
    if (strcmp(mode, "1") == 0)
    {
        if (p1 == NULL)
        { // si la liste est vide
            p1 = nouveau;
        }
        else if (p1->nombre > e)
        {
            p1 = insertDebut(liste, e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        }
        else
        {
            while (p1->suivant != NULL && p1->suivant->nombre < e)
            {
                p1 = p1->suivant;
            }
            if (p1->suivant == NULL)
            {
                p1->suivant = nouveau;
            }
            else
            {
                nouveau->suivant = p1->suivant;
                p1->suivant = nouveau;
            }
        }
    }

    return p1;
}