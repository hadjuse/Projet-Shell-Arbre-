#include "arbre_binaire.h"
# include "liste_chainées.h"
#include <stdio.h>
#include <stdlib.h>
int main(){ 
    //racine
    pArbre a = creerArbre(1);
    pArbre pA = a;
    a = ajouterFilsGauche(a,2);
    a = ajouterFilsDroit(a, 8);
    //noeud 2
    pA = a->fg;
    pA = ajouterFilsGauche(pA, 3);
    pA = ajouterFilsDroit(pA, 6);
    //noeud 3
    pA = a->fg->fg;
    pA = ajouterFilsGauche(pA, 4);
    pA = ajouterFilsDroit(pA, 5);

    //noeud 6
    pA = a->fg->fd;
    pA = ajouterFilsDroit(pA,7);
    
    //noeud 8
    pA = a->fd;
    pA = ajouterFilsDroit(pA, 10);
    pA = ajouterFilsGauche(pA, 9);
    parcoursPostFixe(a);
    //parcoursLargeurs(a);
    printf("\n");
    //test suppression
    pA = a;
    //modifierRacine(pA, 15);
    //supprimerFilsGauche(pA);
    //parcoursLargeurs(a);
    printf("Nombre de feuille: %d\n", nbmFeuille(pA));
    printf("Taille: %d\n", taille(pA));
    printf("Hauteur: %d\n", hauteur(pA));
    printf("%d\n", recherche(a,10));
    pArbre ABR = NULL;
    /*
    ABR = insertionABRIter(ABR, 2);
    ABR = insertionABRIter(ABR, 3); 
    ABR = insertionABRIter(ABR, 1);
    ABR = insertionABRIter2(ABR, 0);
    parcoursLargeurs(ABR);*/
    pArbre pAb = ABR;
    pAb = insertionABRIter(pAb, 10);
    pAb = insertionABRIter(pAb, 3);
    pAb = insertionABRIter(pAb, 5);
    pAb = insertionABRIter(pAb, 15);
    pAb = insertionABRIter(pAb, 20);
    pAb = insertionABRIter(pAb, 12);
    pAb = insertionABRIter(pAb, 7);
    pAb = insertionABRIter(pAb, 45);
    pAb = insertionABRIter(pAb, 9);
    parcoursLargeurs(pA);
    printf("moyenne du sous arbre gauche = %f", moyennefg(pAb));
    //int min,max;
    //MinMaxABR(pAb, &min,&max);
    //affArbreGraphique(ABR,5);
    //free(min);
    //free(max);
    pArbre AVL = creerArbre(1);
    pArbre pAVL = AVL;
    pAVL = insertionAVL(pAVL, 10, &pAVL->hauteur);
    pAVL = insertionAVL(pAVL, 30, &pAVL->hauteur);
    pAVL = insertionAVL(pAVL, 7, &pAVL->hauteur);
    parcoursInfixe(AVL);
    return 0;
}