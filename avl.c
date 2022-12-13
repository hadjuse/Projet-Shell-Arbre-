# include <stdio.h>
# include <stdlib.h>

# include "arbre.h"

pArbre insertionAVL(pArbre a, int e, int *h)
{
    if(a==NULL)
    {
        *h=1;
        return creationArbre(e);
    }
    else if(e<a->elmt)
    {
        a->fg=insertionAVL(a->fg,e,h);
        *h=-*h;
    }
    else if(e>a->elmt)
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