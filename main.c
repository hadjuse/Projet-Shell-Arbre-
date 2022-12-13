# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <stdbool.h>

# include "arbre.h"

int main()
{
    int a=1;
    pArbre arbre = NULL;
    pArbre parc = arbre;
    pArbre abr=NULL;
    pArbre avl=NULL;
    printf("la\n");
    arbre = creationArbre(a);
    abr=insertionABR(abr,a);
    avl=insertionAVL(avl,a,&avl->hauteur);
    arbre = ajouterFilsGauche(arbre,2);
    arbre = ajouterFilsDroit(arbre,8);
    parc = arbre->fg;
    parc = ajouterFilsDroit(parc,6);
    parc = ajouterFilsGauche(parc,3);
    parc = parc->fg;
    parc = ajouterFilsDroit(parc,5);
    parc = ajouterFilsGauche(parc,4);
    parc = arbre->fg;
    parc = parc->fd;
    parc = ajouterFilsDroit(parc,7);
    parc = arbre->fd;
    parc = ajouterFilsGauche(parc,9);
    parc = ajouterFilsDroit(parc,10);
    printf("Voila votre arbre est créé\n");   
    insertionABR(abr,10);
    insertionABR(abr,3);
    insertionABR(abr,5);
    insertionABR(abr,15);
    insertionABR(abr,20);
    insertionABR(abr,12);
    insertionABR(abr,7);
    insertionABR(abr,45);
    insertionABR(abr,9);
    printf("%d",recherche(abr,12));
    printf("%d",recherche(abr,13));
    printf("%d",recherche(abr,15));
    suppression(abr,15);
    printf("%d",recherche(abr,15));
    insertionAVL(avl,10,&avl->hauteur);
    insertionAVL(avl,3,&avl->hauteur);
    insertionAVL(avl,5,&avl->hauteur);
    insertionAVL(avl,15,&avl->hauteur);
    insertionAVL(avl,20,&avl->hauteur);
    insertionAVL(avl,12,&avl->hauteur);
    insertionAVL(avl,7,&avl->hauteur);
    insertionAVL(avl,45,&avl->hauteur);
    insertionAVL(avl,9,&avl->hauteur);
    return 0;
}