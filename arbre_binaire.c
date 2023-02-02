#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arbre_binaire.h"
pArbre creerArbre(int a, int cols1, char *cols2, float cols3, char *cols4, float cols5, float cols6, float somme, char *mode)
{
    pArbre new = malloc(sizeof(Arbre));
    if (new == NULL)
        exit(1);
    new->nombre = a;
    new->fg = NULL;
    new->fd = NULL;
    new->equilibre = 0;
    if (strcmp(mode, "1") == 0)
    {
        new->cols1 = cols1;        // numéro de station
        strcpy(new->cols2, cols2); // coordonées
        new->cols3 = cols3;        // temperature ou pression
        strcpy(new->cols4, cols4); // date
        new->cols5 = cols5;        // temperature min à traiter/direction moyenne ou autre
        new->cols6 = cols6;        // temperature max à traiter/orientation moyenne ou autre
        new->somme = new->cols3;
        new->nb_noeuds = 1;
        new->temperature_max = cols3;
        new->temperature_min = cols3;
        new->nombre = cols1;
    }
    else if (strcmp(mode, "2") == 0)
    {
        new->cols1 = cols1;        // numéro de station
        strcpy(new->cols2, cols2); // coordonées
        strcpy(new->cols4, cols4); // date
        new->somme = somme;        // temperature/pression
        new->nb_noeuds = 1;
    }
    else if (strcmp(mode, "h") == 0) // humidite
    {
        new->cols1 = cols1;
        new->nb_noeuds = 1;
        strcpy(new->cols2, cols2); // coordonées
        new->cols3 = cols3;
        new->temperature_max = cols3;
        new->nombre = cols3;
    }
    else if (strcmp(mode, "v") == 0) // vent
    {
        new->cols1 = cols1;
        new->nb_noeuds = 1;
        strcpy(new->cols2, cols2); // coordonées
        new->cols5 = cols5;        // temperature min à traiter/direction moyenne ou autre
        new->cols6 = cols6;        // temperature max à traiter/orientation moyenne ou autre
    }
    else if (strcmp(mode, "a") == 0) // altitude
    {
        new->cols1 = cols1;
        new->nb_noeuds = 1;
        strcpy(new->cols2, cols2); // coordonées
        new->cols3 = cols3;
    }
    return new;
}
pArbre creerArbre_t3(int a, int cols1, char *cols2, float cols3, char *cols4, float cols5, float cols6, float somme, char *mode)
{
    pArbre new = malloc(sizeof(Arbre));
    if (new == NULL)
        exit(1);
    new->nombre = a;
    new->fg = NULL;
    new->fd = NULL;
    if (strcmp(mode, "1") == 0)
    {
        new->cols1 = cols1;        // numéro de station
        strcpy(new->cols2, cols2); // coordonées
        new->cols3 = cols3;        // temperature ou pression
        strcpy(new->cols4, cols4); // date
        new->somme = somme;
        new->nb_noeuds = 1;
    }
    else if (strcmp(mode, "2") == 0)
    {
        new->cols1 = cols1;        // numéro de station
        strcpy(new->cols2, cols2); // coordonées
        strcpy(new->cols4, cols4); // date
        new->cols3 = cols3;
        new->somme = somme; // temperature/pression
        new->nb_noeuds = 1;
    }
    return new;
}
int estVide(pArbre a) // J'ai modifié tout ton bloc ici
{
    if (a == NULL)
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
    return (a ? ((!a->fg) && (!a->fd) ? 1 : 0) : 0);
}

int element(pArbre a) // Moi j'aurai proposé un truc de ce genre:
{
    int r;
    r = a->nombre;
    return r;
}

int existeFilsGauche(pArbre a) // je suis d'accord avec toi
{
    return (a->fg ? 1 : 0);
}

int existeFilsDroit(pArbre a)
{
    return (a->fd ? 1 : 0);
}
pArbre ajouterFilsDroit(pArbre a, int e)
{
    pArbre b;
    if (estVide(a) == 1)
    {
        return a;
    }
    else
    {
        float somme = 0;
        char mode[1024] = "azefgazf";
        float cols6 = 0.0000;
        b = creerArbre(e, a->cols1, a->cols2, a->cols3, a->cols4, a->cols5, cols6, somme, mode);
        a->fd = b;
        return a;
    }
    return a;
}

pArbre ajouterFilsGauche(pArbre a, int e)
{
    pArbre b;
    if (estVide(a) == 1)
    {
        return a;
    }
    else
    {
        float somme = 0;
        char mode[1024] = "azefgazf";
        float cols6 = 0.0000;
        b = creerArbre(e, a->cols1, a->cols2, a->cols3, a->cols4, a->cols5, cols6, somme, mode);
        a->fd = b;
        return a;
    }
}

void parcoursPrefixe(pArbre a)
{
    if (estVide(a) != 1)
    {
        traiter(a);
        parcoursPrefixe(a->fg);
        parcoursPrefixe(a->fd);
    }
}

void parcoursPostFixe(pArbre a)
{
    if (estVide(a) != 1)
    {
        parcoursPostFixe(a->fg);
        parcoursPostFixe(a->fd);
        free(a);
    }
}
void parcoursInfixe_decroissant(pArbre a, int *c, int nb_ligne, char *mode, FILE *fichier)
{
    if (estVide(a) != 1)
    {
        parcoursInfixe_decroissant(a->fd, c, nb_ligne, mode, fichier);
        if (strcmp(mode, "1") == 0) // t1/p1
        {

            fprintf(fichier, "%d;%f;%f;%f;%s\n", a->cols1, a->somme / a->nb_noeuds, a->temperature_max, a->temperature_min, a->cols4);
        }
        else if (strcmp(mode, "2") == 0) // t2/p2
        {
            fprintf(fichier, "%d;%f;%s\n", a->cols1, a->somme / a->nb_noeuds, a->cols4);
        }
        else if (strcmp(mode, "v") == 0)
        {
            fprintf(fichier, "%d;%f;%f;%s\n", a->cols1, a->cols5 / nb_ligne, a->cols6 / nb_ligne, a->cols2);
        }
        else if (strcmp(mode, "a") == 0) // altitude
        {
            fprintf(fichier, "%d;%s;%d\n", a->cols1, a->cols2, (int)a->cols3);
        }
        else if (strcmp(mode, "h") == 0) // humidite
        {
            fprintf(fichier, "%d;%s;%d\n", a->cols1, a->cols2, (int)a->temperature_max);
        }
        parcoursInfixe_decroissant(a->fg, c, nb_ligne, mode, fichier);
    }
}
void parcoursInfixe_t3_decroissant(pArbre a, int *c, int nb_ligne, char *mode, FILE *fichier)
{
    if (estVide(a) != 1)
    {
        parcoursInfixe_t3_decroissant(a->fd, c, nb_ligne, mode, fichier);
        if (strcmp(mode, "1") == 0)
        {

            fprintf(fichier, "%d %f %s\n", a->cols1, a->somme, a->cols4);
            *c = *c + 1;
        }
        else if (strcmp(mode, "2") == 0)
        {
            fprintf(fichier, "%d %s %f %s\n", a->cols1, a->cols2, a->somme, a->cols4);
            *c = *c + 1;
        }
        parcoursInfixe_t3_decroissant(a->fg, c, nb_ligne, mode, fichier);
    }
}

void parcoursInfixe_croissant(pArbre a, int *c, int nb_ligne, char *mode, FILE *fichier)
{
    if (estVide(a) != 1)
    {
        parcoursInfixe_croissant(a->fg, c, nb_ligne, mode, fichier);
        if (strcmp(mode, "1") == 0) // t1
        {

            fprintf(fichier, "%d;%f;%f;%f;%s\n", a->cols1, a->somme / a->nb_noeuds, a->temperature_max, a->temperature_min, a->cols4);
            *c = *c + 1;
        }
        else if (strcmp(mode, "2") == 0) // t2
        {
            fprintf(fichier, "%d;%f;%s\n", a->cols1, a->somme / a->nb_noeuds, a->cols4);
            *c = *c + 1;
        }
        else if (strcmp(mode, "v") == 0) // vent
        {
            fprintf(fichier, "%d;%f;%f;%s\n", a->cols1, a->cols5 / nb_ligne, a->cols6 / nb_ligne, a->cols2);
        }
        else if (strcmp(mode, "a") == 0) // altitude
        {
            fprintf(fichier, "%d;%s;%d\n", a->cols1, a->cols2, (int)a->cols3);
        }
        else if (strcmp(mode, "h") == 0) // humidite
        {
            fprintf(fichier, "%d;%s;%d\n", a->cols1, a->cols2, (int)a->temperature_max);
        }
        parcoursInfixe_croissant(a->fd, c, nb_ligne, mode, fichier);
    }
}
void parcoursInfixe_croissant_temp(pArbre a, int *c, int nb_ligne, char *mode, FILE *fichier)
{
    if (estVide(a) != 1)
    {
        parcoursInfixe_croissant_temp(a->fg, c, nb_ligne, mode, fichier);
        if (strcmp(mode, "h") == 0) // humidite
            fprintf(fichier, "%d %s %d\n", a->cols1, a->cols2, (int)a->temperature_max);
        else if (strcmp(mode, "1") == 0)
        {
            fprintf(fichier, "%d %f %s\n", a->cols1, a->somme, a->cols4);
            *c = *c + 1;
        }
        else if (strcmp(mode, "2") == 0)
        {
            fprintf(fichier, "%d %s %d %s\n", a->cols1, a->cols2, (int)a->somme, a->cols4);
            *c = *c + 1;
        }
        parcoursInfixe_croissant_temp(a->fd, c, nb_ligne, mode, fichier);
    }
}
void parcoursInfixe_t3(pArbre a, int *c, int nb_ligne, char *mode, FILE *fichier)
{
    if (estVide(a) != 1)
    {
        parcoursInfixe_t3(a->fg, c, nb_ligne, mode, fichier);
        if (strcmp(mode, "1") == 0)
        {

            fprintf(fichier, "%d;%f;%s\n", a->cols1, a->somme, a->cols4);
            *c = *c + 1;
        }
        else if (strcmp(mode, "2") == 0)
        {
            fprintf(fichier, "%d;%s;%f;%s\n", a->cols1, a->cols2, a->somme, a->cols4);
            *c = *c + 1;
        }
        parcoursInfixe_t3(a->fd, c, nb_ligne, mode, fichier);
    }
}

void traiter(pArbre a)
{
    printf("%d ", a->nombre);
}
pArbre modifierRacine(pArbre a, int e)
{
    if (a != NULL)
        a->nombre = e;
    return a;
}
void supprimerFilsDroit(pArbre a)
{
    if (a == NULL)
    {
        exit(1);
    }
    else if (existeFilsDroit(a) == 1)
    {
        if (existeFilsGauche(a->fd))
            supprimerFilsGauche(a->fd);
        if (existeFilsDroit(a->fd))
            supprimerFilsDroit(a->fd);
        a->fd = NULL;
        free(a->fd);
    }
}
void supprimerFilsGauche(pArbre a)
{

    if (a == NULL)
    {
        exit(1);
    }
    else if (existeFilsGauche(a))
    {
        if (existeFilsGauche(a->fg))
            supprimerFilsGauche(a->fg);
        if (existeFilsDroit(a->fg))
            supprimerFilsDroit(a->fg);
        a->fg = NULL;
        free(a->fg);
    }
}
pArbre filsDroit(pArbre a)
{
    if (a == NULL)
        exit(1);
    return (existeFilsDroit(a)) ? a->fd : NULL;
}

pArbre filsGauche(pArbre a)
{
    if (a == NULL)
        exit(1);
    return (existeFilsGauche(a)) ? a->fg : NULL;
}

int nbmFeuille(pArbre a) // je dirai plus:
{
    if (a == NULL)
        return 0;
    if (estFeuille(a))
        return 1;
    else
        return nbmFeuille(filsGauche(a)) + nbmFeuille(filsDroit(a));
}

int taille(pArbre a) // je dirai plus:
{
    if (a == NULL)
        return 0;
    else if (estFeuille(a))
        return 0;
    else
        return 1 + taille(filsGauche(a)) + taille(filsDroit(a));
}
int hauteur(pArbre a)
{
    return (a == NULL) ? -1 : 1 + max(hauteur(filsGauche(a)), hauteur(filsDroit(a)));
}
// partie file
Chainon *creationChainon(pArbre a)
{
    Chainon *p = malloc(sizeof(Chainon));
    if (p == NULL)
    {
        exit(1);
    }
    p->arbre = a;
    p->suivant = NULL;
    return p;
}
int verif(File *file)
{
    int res = 0;
    if (file == NULL)
    {
        res = -1;
    }
    else if ((file->tete == NULL && file->queue != NULL) || (file->queue == NULL && file->tete != NULL))
    {
        //(file->tete==NULL)!=(file->queue==NULL)
        res = -2;
    }
    else if (file->queue != NULL && file->queue->suivant != NULL)
    {
        res = -3;
    }
    return (res);
}
int enfiler(File *f, pArbre a)
{
    Chainon *c;
    int result = 0;
    result = verif(f);
    if (result > -2) // test de la file si elle est corompue
    {
        c = creationChainon(a);
        if (f->queue == NULL) // si la file est vide
        {
            f->tete = c;  // affecter la tete au 1er chainon
            f->queue = c; // affecter la queue au 1er chainon
        }
        else
        {
            f->queue->suivant = c; // affecter le queue au dernier chainoN
            f->queue = c;          // decaler la queue
        }
    }
    return result;
}

pArbre defiler(File *f)
{
    Chainon *p1 = f->tete;
    pArbre a = f->tete->arbre;
    if (f->tete->suivant == NULL)
        f->queue = NULL;
    f->tete = f->tete->suivant;
    free(p1);
    return a;
}
void creerfile(File *f)
{
    f->tete = NULL;
    f->queue = NULL;
}

void parcoursLargeurs(pArbre a)
{
    File f;
    if (!estVide(a))
    {
        creerfile(&f);
        enfiler(&f, a);
        while ((f.tete != NULL))
        {
            a = defiler(&f);
            traiter(a);
            if (existeFilsGauche(a))
                enfiler(&f, a->fg);
            if (existeFilsDroit(a))
                enfiler(&f, a->fd);
        }
    }
}

void parcoursmoy(pArbre a, int *c, int *somme)
// l'idée de base est de pointé sur c et somme afin de modifier directement les valeurs dedans.
{
    if (a != NULL)
    {
        parcoursmoy(a->fg, c, somme);
        *c += 1;
        *somme += a->nombre;
        parcoursmoy(a->fd, c, somme);
    }
}

// partie AVL

float moyennefg(pArbre a)
{
    int c = 0;
    int somme = 0;
    float moy;
    parcoursmoy(a->fg, &c, &somme);
    moy = somme / c;
    return moy;
}
float moyennefd(pArbre a)
{
    int c = 0;
    int somme = 0;
    float moy;
    parcoursmoy(a->fd, &c, &somme);
    moy = somme / c;
    return moy;
}
pArbre insertionAVL(pArbre a, int e, int *h, int cols1, char *cols2, float cols3, char *cols4, float cols5, float cols6, float somme, char *mode)
{
    if (strcmp(mode, "1") == 0) // le mode vaut t1/p1
    {
        if (a == NULL)
        {
            *h = 1;
            return creerArbre(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        }
        else if (e < a->nombre)
        {
            a->fg = insertionAVL(a->fg, e, h, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
            *h = -*h;
        }
        else if (e > a->nombre)
        {
            a->fd = insertionAVL(a->fd, e, h, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        }
        else
        {
            *h = 0;
            if (cols1 == a->cols1)
            {
                a->somme += somme;
                a->nb_noeuds++;
                if (somme > a->cols3)
                    a->temperature_max = somme;
                if (somme < a->cols3)
                    a->temperature_min = somme;
            }
            return a;
        }
        if (*h != 0)
        {
            a->equilibre = a->equilibre + *h;
            a = equilibrerAVL(a);
            if (a->equilibre == 0)
            {
                *h = 0;
            }
            else
            {
                *h = 1;
            }
        }
    }
    else if (strcmp(mode, "2") == 0) // mode vaut t2/p2 les dates sont déja dans l'ordre je supprime la comparaison negative afin d'économiser des lignes
    {
        if (a == NULL)
        {
            *h = 1;
            return creerArbre(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        }
        else if (strcmp(cols4, a->cols4) > 0)
            a->fd = insertionAVL(a->fd, e, h, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        else
        {
            *h = 0;
            if (cols1 == a->cols1)
            {
                a->nb_noeuds++;
                a->somme += somme;
            }

            if (!existeFilsDroit(a))
            {
                a->fd = creerArbre(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
            }
            return a;
        }
        if (*h != 0)
        {

            a->equilibre = a->equilibre + *h;
            a = equilibrerAVL(a);
            if (a->equilibre == 0)
            {
                *h = 0;
            }
            else
            {
                *h = 1;
            }
        }
    }
    else if (strcmp(mode, "h") == 0)
    {
        if (a == NULL)
        {
            *h = 1;
            return creerArbre(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        }
        else if (e < a->cols3)
        {
            a->fg = insertionAVL(a->fg, e, h, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
            *h = -*h;
        }
        else if (e > a->cols3)
        {
            a->fd = insertionAVL(a->fd, e, h, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        }
        else
        {
            *h = 1;
            a->nb_noeuds++;

            if (a->fd != NULL)
            {
                pArbre doublon = creerArbre(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
                doublon->fd = a->fd;
                a->fd = doublon;
            }
            else
            {
                pArbre doublon = creerArbre(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
                a->fd = doublon;
            }
        }
        if (*h != 0)
        {
            a->equilibre = a->equilibre + *h;
            a = equilibrerAVL(a);
            if (a->equilibre == 0)
            {
                *h = 0;
            }
            else
            {
                *h = 1;
            }
        }
    }
    else if (strcmp(mode, "v") == 0)
    {
        if (a == NULL)
        {
            *h = 1;
            return creerArbre(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        }
        else if (e < a->nombre)
        {
            a->fg = insertionAVL(a->fg, e, h, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
            *h = -*h;
        }
        else if (e > a->nombre)
        {
            a->fd = insertionAVL(a->fd, e, h, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        }
        else
        {
            *h = 0;
            a->nb_noeuds++;
            a->cols5 += cols5;
            a->cols6 += cols6;
            return a;
        }
        if (*h != 0)
        {
            a->equilibre = a->equilibre + *h;
            a = equilibrerAVL(a);
            if (a->equilibre == 0)
            {
                *h = 0;
            }
            else
            {
                *h = 1;
            }
        }
    }

    else if (strcmp(mode, "a") == 0)
    {
        if (a == NULL)
        {
            *h = 1;
            return creerArbre(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        }
        else if (e < a->nombre)
        {
            a->fg = insertionAVL(a->fg, e, h, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
            *h = -*h;
        }
        else if (e > a->nombre)
        {
            a->fd = insertionAVL(a->fd, e, h, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        }
        else
        {
            *h = 0;
            return a;
        }
        if (*h != 0)
        {
            a->equilibre = a->equilibre + *h;
            a = equilibrerAVL(a);
            if (a->equilibre == 0)
            {
                *h = 0;
            }
            else
            {
                *h = 1;
            }
        }
    }
    return a;
}
pArbre insertionAVL_t3(pArbre a, int e, int *h, int cols1, char *cols2, float cols3, char *cols4, float cols5, float cols6, float somme, char *mode)
{
    if (strcmp(mode, "1") == 0) // le mode vaut t1/p1
    {
        if (a == NULL)
        {
            *h = 1;
            return creerArbre_t3(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        }
        else if (e < a->cols1)
        {
            a->fg = insertionAVL_t3(a->fg, e, h, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
            *h = -*h;
        }
        else if (e > a->cols1)
        {
            a->fd = insertionAVL_t3(a->fd, e, h, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        }
        else
        {
            *h = 1;
            a->nb_noeuds++;
            if (a->fd != NULL)
            {
                pArbre doublon = creerArbre(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
                doublon->fd = a->fd;
                a->fd = doublon;
            }
            else
            {
                pArbre doublon = creerArbre(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
                a->fd = doublon;
            }
        }
        if (*h != 0)
        {
            a->equilibre = a->equilibre + *h;
            a = equilibrerAVL(a);
            if (a->equilibre == 0)
            {
                *h = 0;
            }
            else
            {
                *h = 1;
            }
        }
        return a;
    }
    else if (strcmp(mode, "2") == 0) // mode vaut t2/p2 les dates sont déja dans l'ordre je supprime la comparaison negative afin d'économiser des lignes
    {
        if (a == NULL)
        {
            *h = 1;
            return creerArbre_t3(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        }
        else if (strcmp(cols4, a->cols4) > 0)
            a->fd = insertionAVL_t3(a->fd, e, h, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
        else
        {
            *h = 1;
            a->nb_noeuds++;

            if (a->fd != NULL)
            {
                pArbre doublon = creerArbre(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
                doublon->fd = a->fd;
                a->fd = doublon;
            }
            else
            {
                pArbre doublon = creerArbre(e, cols1, cols2, cols3, cols4, cols5, cols6, somme, mode);
                a->fd = doublon;
            }
        }
        if (*h != 0)
        {
            a->equilibre = a->equilibre + *h;
            a = equilibrerAVL(a);
            if (a->equilibre == 0)
            {
                *h = 0;
            }
            else
            {
                *h = 1;
            }
        }
    }

    return a;
}
// cet fonction utilise le parcours en profondeur qui consiste à parcourir les sommets de l'abre et de supprimer recusivement sauf la racine
void supprimer(pArbre a)
{
    if (a == NULL)
        return;

    if (a->fg != NULL)
    {
        supprimer(a->fg);
        free(a->fg);
        a->fg = NULL;
    }

    if (a->fd != NULL)
    {
        supprimer(a->fd);
        free(a->fd);
        a->fd = NULL;
    }
}

/*
pArbre suppMinAVL(pArbre a, int *h, int *pe)
{
    pArbre tmp;
    if (a->fg == NULL)
    {
        *pe = a->nombre;
        *h = -1;
        tmp = a;
        a = a->fd;
        free(tmp);
        return a;
    }
    else
    {
        a->fg = suppMinAVL(a->fg, h, pe);
        *h = -*h;
    }
    if (*h != 0)
    {
        a->equilibre = a->equilibre + *h;
        if (a->equilibre == 0)
        {
            *h = -1;
        }
        else
        {
            *h = 0;
        }
    }
    return a;
}

pArbre suppressionAVL(pArbre a, int e, int *h)
{
    pArbre tmp;
    if (a == NULL)
    {
        *h = 1;
        return a;
    }
    else if (e > a->nombre)
    {
        a->fd = suppressionAVL(a->fd, e, h);
    }
    else if (e < a->nombre)
    {
        a->fg = suppressionAVL(a->fg, e, h);
        *h = -*h;
    }
    else if (existeFilsDroit(a))
    {
        a->fd = suppMinAVL(a->fd, h, &a->nombre);
    }
    else
    {
        tmp = a;
        a = a->fg;
        free(tmp);
        *h = -1;
    }
    if (a == NULL)
    {
        *h = 0;
    }
    if (*h != 0)
    {
        a->equilibre = a->equilibre + *h;
        a = equilibrerAVL(a);
        if (a->equilibre == 0)
        {
            *h = 0;
        }
        else
        {
            *h = 1;
        }
    }
    return a;
}*/

int min(int a, int b)
{
    return (a < b ? a : b);
}

int min_of_three(int a, int b, int c)
{
    return min(min(a, b), c);
}

int max(int a, int b)
{
    return (a < b ? b : a);
}

int max_of_three(int a, int b, int c)
{
    return max(max(a, b), c);
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
    a->equilibre = eq_a - min(eq_p, 0) + 1;
    pivot->equilibre = max_of_three(eq_a + 2, eq_a + eq_p + 2, eq_p + 1);
    a = pivot;
    return a;
}

pArbre rotationGauche(pArbre a)
{
    pArbre pivot;
    int eq_a, eq_p;
    pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - max(eq_p, 0) - 1;
    pivot->equilibre = min_of_three(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);
    a = pivot;
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
    if (a->equilibre >= 2)
    {
        if (a->fd->equilibre >= 0)
        {
            return rotationGauche(a);
        }
        else
        {
            return doubleRotationGauche(a);
        }
    }
    else if (a->equilibre <= -2)
    {
        if (a->fg->equilibre <= 0)
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

// partie liste_chainee
int element_liste_chainee(pListe p1)
{
    return p1->nombre;
}

void traiter_liste_chainee(pListe p1)
{
    printf("%d ", p1->nombre);
}
