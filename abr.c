#include <stdio.h>
#include <stdlib.h>
#include "arbre_binaire.h"
/*
int recherche(pArbre a, int e)
{
    if (a == NULL)
        return 0;
    else if (e == a->nombre)
        return 1;
    else if (e < a->nombre)
        return recherche(filsGauche(a), e);
    else
        return recherche(filsDroit(a), e);
}
pArbre insertionABR(pArbre a, int e, int cols1, char *cols2, float cols3, char *cols4, float cols5, float somme, char *mode)
{
    if (a == NULL)
        return creerArbre(e, cols1, cols2, cols3, cols4, cols5, somme, mode);
    else if (e < a->nombre)
        a->fg = insertionABR(filsGauche(a), e, cols1, cols2, cols3, cols4, cols5, somme, mode);
    else if (e > a->nombre)
        a->fd = insertionABR(filsDroit(a), e, cols1, cols2, cols3, cols4, cols5, somme, mode);
    else
    {
        a->somme += somme;
        a->nb_noeuds++;
        if (a->temperature_max < somme)
            a->temperature_max = somme;
        if (a->temperature_min > somme)
            a->temperature_min = somme;
        return a;
    }
    return a;
}
pArbre suppMax(pArbre a, int *pe)
{
    pArbre tmp;
    if (existeFilsDroit(a))
        a->fd = suppMax(filsDroit(a), pe);
    else
    {
        *pe = a->nombre;
        tmp = a;
        a = filsGauche(a);
        free(tmp);
    }
    return a;
}
pArbre suppressionABR(pArbre a, int e)
{
    pArbre tmp;
    if (a == NULL)
        return a;
    else if (e > a->nombre)
        return suppressionABR(filsDroit(a), e);
    else if (e < a->nombre)
        return suppressionABR(filsGauche(a), e);
    else if (!existeFilsGauche(a))
    {
        tmp = a;
        a = filsDroit(a);
        free(tmp);
    }
    else
        a->fg = suppMax(filsGauche(a), &a->nombre);
    return a;
}*/
