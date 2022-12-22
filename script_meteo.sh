#!/bin/bash
#Initialisation des variables
tout_arguments=$#
opt=":t:p:wmhFGSAOQ"
if [ -e $fichier_temp]; then
    echo "Le dossier 'fichier_temp' existe déjà."
else
    mkdir fichier_temp
fi
#Initialisation des fonctions tests pour chaques arguments et options
test_option_mode() {
    MODE=$OPTARG
    if [[ $MODE -ne 1 && $MODE -ne 2 && $MODE -ne 3 ]]; then
        echo "Les arguments sont compris entre 1 et 3 tout inclus ou Vous n'avez pas mis d'argument" >&2
        exit 1
    fi
}
test_argument() {
    if [ -z "$MODE" ]; then
        echo "Il faut au moins mettre 1 option parmis -t[OPTION] -p[OPTION] -w -m -h" >&2
        exit 1
    fi
}
execution_mode_t() {
    if [ $OPTARG -eq 1 ]; then
        cut -d ';' -f 11 meteo_filtered_data_v1.csv >fichier_temp/donnee_filtree_temperature.txt
    elif [ $OPTARG -eq 2 ]; then
        cut -d ';' -f 11 meteo_filtered_data_v1.csv >fichier_temp/donnee_filtree_temperature.txt
        cut -d ';' -f 2 meteo_filtered_data_v1.csv >fichier_temp/donnee_filtree_date.txt
    elif [ $OPTARG -eq 3 ]; then
        cut -d ';' -f 11 meteo_filtered_data_v1.csv >fichier_temp/donnee_filtree_temperature.txt
        cut -d ';' -f 2 meteo_filtered_data_v1.csv >fichier_temp/donnee_filtree_date.txt
        cut -d ';' -f 1 meteo_filtered_data_v1.csv >fichier_temp/donnee_filtree_id.txt
    fi
}
# Traitement des options de la ligne de commande avec getops
while getopts $opt option; do
    case "$option" in
    #traitement de la temperature accompagné d'une option 1 ou 2 ou 3
    t)
        test_option_mode
        execution_mode_t
        ;;
    p) #traitement de la pression accompagné d'une option 1 ou 2 ou 3
        test_option_mode
        echo "$MODE"
        ;;
    w) #traitement de l'option vent
        echo "vent"
        ;;
    m)
        echo "humidite"
        ;; #traitement de l'option humidite
    h)
        echo "altitude"
        ;; #traitement de l'option altitude

    #Options lié à la géographie
    F)
        echo "France"
        ;;
    G)
        echo "Guyane française"
        ;;
    S)
        echo "Saint-Pierre et Miquelon"
        ;;
    A)
        echo "Antilles"
        ;;
    O)
        echo "Océan indien"
        ;;
    Q)
        echo "Antarctique"
        ;;
    \?)
        echo "$OPTARG: option invalide" >&2
        exit 1
        ;;
    esac
done
test_argument
