#include <stdio.h>
#include <stdlib.h>
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

pArbre insertionABR(pArbre a, int e)
{
    if (a == NULL)
        return creerArbre(e);
    else if (e < a->nombre)
        a->fg = insertionABR(filsGauche(a), e);
    else if (e > a->nombre)
        a->fd = insertionABR(filsDroit(a), e);
    return a;
}

pArbre insertionABRIter(pArbre a, int e)
{
    pArbre pAbr = a;
    
    pArbre parc;
    pArbre nouveau = creerArbre(e);
    if (a == NULL) return nouveau;
    
    while (!estVide(pAbr))
    {
        parc = pAbr;
        if (e>pAbr->nombre)
            pAbr = pAbr->fd;
        else if (e<pAbr->nombre)
            pAbr = pAbr->fg;
    }
    if (e>parc->nombre) 
        parc->fd = nouveau;
    else if (e<parc->nombre)
        parc->fg = nouveau;
    return a;
}

pArbre suppMax(pArbre a, int *pe)
{
    pArbre tmp;
    if (existeFilsDroit(a))
        a->fd = suppMax(filsDroit(a), pe);
    else{
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
    else if (!existeFilsGauche(a)){
        tmp = a;
        a = filsDroit(a);
        free(tmp);
    }
    else
        a->fg = suppMax(filsGauche(a), &a->nombre);
    return a;
}

