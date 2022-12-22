# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "liste_chainées.h"
# include <string.h>

pListe creerChainon()
{
    pListe c = malloc(sizeof(Chainon));
    if(c==NULL)
    {
        exit(1);
    }
    printf("Entrer la valeur: \n");
    if(scanf("%d", &(c->elmt)) != 1)
    {
        exit(2);
    }
    c->suivant=NULL;
    return c;
}

int element(pListe p1)
{
    int r;
    r=p1->nombre;
    return r;
}

void traiter(pListe p1)
{
    printf("%d ", p1->nombre);
}

pListe insertFin(pListe p1)
{
    pListe nouveau;
    pListe a;
    nouveau = creerChainon();
    a=p1;
    while(p1->suivant != NULL)
    {
        p1 = p1->suivant;
    }
    p1->suivant = nouveau;
    return p1;
}

pListe insertDebut(pListe p1)
{
    pListe nouveau;
    nouveau = creerChainon();
    nouveau->suivant = p1;
    p1 = nouveau;
    return p1;
}

pListe insertMilieu(pListe p1, int e)
{
    int i;
    pListe nouveau;
    pListe a;
    if(e==0 || p1==NULL)
    {
        p1 = insertDebut(p1);
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
        nouveau = creerChainon();
        nouveau->suivant = a->suivant;
        a->suivant = nouveau;
    }
    return p1;
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

int partition(int A[n],int debut,int fin)
{
    int inf;
    int sup;
    int tmp;
    inf = debut+1;
    sup = fin;
    while(inf<=sup)
    {
        while(A[sup]>A[debut])
        {
            sup = sup-1;
        }
        while(A[inf]<A[debut])
        {
            inf = inf+1;
        }
        if(inf<sup)
        {
            tmp = A[sup];
            A[sup] = A[inf];
            A[inf] = tmp;
        }
    }
    tmp = A[debut];
    A[debut] = A[sup];
    A[sup] = tmp;
    return sup;
}

void triRapideRec(int A[n],int debut,int fin)
{
    int pivot;
    if(debut<fin)
    {
        pivot = partition(A,debut,fin);
        triRapideRec(A,debut,pivot-1);
        triRapideRec(A,pivot+1,fin);
    }
}

void triRapide(int A[n])
{
    triRapideRec(A,0,n-1);
}