# include <stdio.h>
# include <stdlib.h>

# include "arbre.h"

int recherche(pArbre a,int e)
{
    if(a==NULL)
    {
        return 0;
    }
    else if(a->elmt==e)
    {
        return 1;
    }
    else if(e<a->elmt)
    {
        return recherche(a->fg,e);
    }
    else
    {
        return recherche(a->fd,e);
    }
}

pArbre insertionABR(pArbre a, int e)
{
    if(a==NULL)
    {
        return creationArbre(e);
    }
    else if(e<a->elmt)
    {
        a->fg=insertionABR(a->fg,e);
    }
    else if(e>a->elmt)
    {
        a->fd=insertionABR(a->fd,e);
    }
    return a;
}

pArbre suppMax(pArbre a,int *pe)
{
    pArbre tmp;
    if(existeFd(a))
    {
        a->fd=suppMax(a->fd,pe);
    }
    else 
    {
        *pe=a->elmt;
        tmp=a;
        a=a->fg;
        free(tmp);
    }
    return a;
}

pArbre suppression(pArbre a,int e)
{
    pArbre tmp;
    if(a==NULL)
    {
        return a;
    }
    else if(e>a->elmt)
    {
        a->fd=suppression(a->fd,e);
    }
    else if(e<a->elmt)
    {
        a->fg=suppression(a->fg,e);
    }
    else if(!existeFg(a))
    {
        tmp=a;
        a=a->fd;
        free(tmp);
    }
    else 
    {
        a->fg=suppMax(a->fg, &a->elmt);
    }
    return a;
}
