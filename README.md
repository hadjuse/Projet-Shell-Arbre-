# Cy-meteo Hadj Rabearimanana ET Elyes Dachraoui

Bienvenue sur le projet Cy-meteo. 
Ce projet consiste à traiter une base de donnée météorologique qui affiche en résultat final des graphiques portant sur différent types de filtre et de tris.

# Utilisation Shell-C
Assurez d'avoir mis chmod +rwx * dans le dossier courant et d'avoir la base de donnée nécéssaire à l'exécution du script.
Pour exécuter le script, il faut d'abord écrire ./script_meteo.sh puis les arguments et option qui vont avec.
Exemple: ./script.sh -t1 -p3 -m --abr
tapez ./script --help  -f nom_du_fichier pour obtenir de l'aide sur l'exécution du script
# Utilisation indépendante du Shell

Si vous voulez recommencer tout le processus mais en utilisant le le tri en c (Attention, il faut avoir des données déjà filtrées de base qui soient présents dans le dossier).
il faut taper: 
  1) make mrproper (si déjà compilé)
  2) make
  3) (Executable ./abr argument)./abr $nom_fichier_a_trier $mode_tri $option_t $option_p $humidite $vent $altitude $fichier_sortie
      exemple:
      ./abr nom_fichier.csv avl 1 non non w non trie.csv  

# Erreur d'exécution ou de syntaxe

Les Erreurs apparaîtront sur le terminal.

