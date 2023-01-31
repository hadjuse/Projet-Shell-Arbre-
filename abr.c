#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arbre_binaire.h"

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
pArbre insertionABR(pArbre a, int e, int cols1, char *cols2, float cols3, char *cols4, float cols5, float cols6, float somme, char *mode)
{
    if (strcmp(mode, "1") == 0) // le mode vaut t1/p1
    {
        if (a == NULL)
            return creerArbre(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        else if (e < a->nombre)
            a->fg = insertionABR(filsGauche(a), e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        else if (e > a->nombre)
            a->fd = insertionABR(filsDroit(a), e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        else
        {
            a->somme += somme;
            a->nb_noeuds++;
            if (somme > a->cols3)
                a->temperature_max = somme;
            if (somme < a->cols3)
                a->temperature_min = somme;
            return a;
        }
    }
    else if (strcmp(mode, "2") == 0)
    {
        if (a == NULL)
            return creerArbre(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        else if (strcmp(cols4, a->cols4) > 0)
            a->fd = insertionABR(filsDroit(a), e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        else
        {
            a->nb_noeuds++;
            a->somme += somme;
            return a;
        }
    }
    else if (strcmp(mode, "h") == 0)
    {
        if (a == NULL)
            return creerArbre(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        else if (e < a->nombre)
            a->fg = insertionABR(filsGauche(a), e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        else if (e > a->nombre)
            a->fd = insertionABR(filsDroit(a), e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        else
        {
            a->nb_noeuds++;
            if (cols3 > a->cols3)
                a->temperature_max = cols3;
            return a;
        }
    }
    else if (strcmp(mode, "v") == 0)
    {
        if (a == NULL)
            return creerArbre(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        else if (e < a->nombre)
            a->fg = insertionABR(filsGauche(a), e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        else if (e > a->nombre)
            a->fd = insertionABR(filsDroit(a), e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        else
        {
            a->nb_noeuds++;
            a->cols5 += cols5;
            a->cols6 += cols6;
            return a;
        }
    }
    else if (strcmp(mode,"a") == 0)
    {
        if (a == NULL)
            return creerArbre(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        else if (e < a->nombre)
            a->fg = insertionABR(filsGauche(a), e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        else if (e > a->nombre)
            a->fd = insertionABR(filsDroit(a), e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        else
        {
            return a;
        }
    }
    
    return a;
} 
pArbre insertionABR_t3(pArbre a, int e, int cols1, char *cols2, float cols3, char *cols4, float cols5, float colonne6, float somme, char *mode)
{
    if (strcmp(mode, "1") == 0)
    {
        if (a == NULL)
            return creerArbre_t3(e, cols1, cols2, cols3, cols4, cols5, colonne6, somme, mode);
        else if (e < a->nombre)
            a->fg = insertionABR_t3(filsGauche(a), e, cols1, cols2, cols3, cols4, cols5, colonne6, somme, mode);
        else if (e > a->nombre)
            a->fd = insertionABR_t3(filsDroit(a), e, cols1, cols2, cols3, cols4, cols5, colonne6, somme, mode);
        else
        {
            return a;
        }
    }
    else if (strcmp(mode, "2") == 0)
    {
        if (a == NULL)
            return creerArbre_t3(e, cols1, cols2, cols3, cols4, cols5, colonne6, somme, mode);
        else if (strcmp(cols4, a->cols4) > 0)
            a->fd = insertionABR_t3(filsDroit(a), e, cols1, cols2, cols3, cols4, cols5, colonne6, somme, mode);
        else
        {
            return a;
        }
    }
    return a;
} 

/*
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
