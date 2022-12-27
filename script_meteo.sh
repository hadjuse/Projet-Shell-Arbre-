#!/bin/bash
#Initialisation des variables
tout_arguments=$*
mode_tri="avl"
#teste pour savoir si les fichiers temporaires existent
if [ -d fichier_temp_t ]; then
    echo "Le dossier 'fichier_temp_t' existe déjà."
else
    mkdir fichier_temp_t
fi
if [ -d fichier_temp_p ]; then
    echo "Le dossier 'fichier_temp_p' existe déjà."
else
    mkdir fichier_temp_p
fi
if [ -d fichier_temp_w ]; then
    echo "Le dossier 'fichier_temp_w' existe déjà."
else
    mkdir fichier_temp_w
fi
#Initialisation des fonctions tests pour chaques arguments et options
test_argument_mode() {
    MODE=$OPTARG
    if [[ $MODE -ne 1 && $MODE -ne 2 && $MODE -ne 3 ]]; then
        echo "Les arguments sont compris entre 1 et 3 tout inclus/ Vous n'avez pas mis d'argument/ Arguments invalide" >&2
        exit 1
    fi
}
test_options() {
    if [ -z "$MODE" ]; then
        echo "Il faut au moins mettre 1 option parmis -t[ARGUMENTS] -p[ARGUMENTS] -w -m -h" >&2
        exit 1
    fi
}
#filtrage pour l'option -t
filtrage_1() {
    cut -d ';' -f 11,15 meteo_filtered_data_v1.csv >fichier_temp_t/donnee_filtree_temperature_et_num.txt
}
filtrage_2() {
    cut -d ';' -f 11,2 meteo_filtered_data_v1.csv >fichier_temp_t/donnee_filtree_temperature_et_date.txt
}
filtrage_3() {
    cut -d ';' -f 11,1 meteo_filtered_data_v1.csv >fichier_temp_t/donnee_filtree_temperature_et_id.txt
}
#filtrage pour l'option -p
filtrage_1_bis() {
    cut -d ';' -f 11,15 meteo_filtered_data_v1.csv >fichier_temp_p/donnee_filtree_temperature_et_num.txt

}
filtrage_2_bis() {
    cut -d ';' -f 11,2 meteo_filtered_data_v1.csv >fichier_temp_p/donnee_filtree_temperature_et_date.txt
}
filtrage_3_bis() {
    cut -d ';' -f 11, 1 meteo_filtered_data_v1.csv >fichier_temp_p/donnee_filtree_temperature_et_id.txt
}
#filtrage pour l'option -w
filtrage_w() {
    cut -d ';' -f 1,3,4 meteo_filtered_data_v1.csv >fichier_temp_w/donnee_filtree_id_vent_moyenne.txt
}
#execution des arguments et options
execution_mode_t() {
    if [ $OPTARG -eq 1 ]; then
        filtrage_1
    elif [ $OPTARG -eq 2 ]; then
        filtrage_2
    elif [ $OPTARG -eq 3 ]; then
        filtrage_3
    fi
}

execution_mode_p() {
    if [ $OPTARG -eq 1 ]; then
        filtrage_1_bis
    elif [ $OPTARG -eq 2 ]; then
        filtrage_2_bis
    elif [ $OPTARG -eq 3 ]; then
        filtrage_3_bis
    fi
}
verification_tri() {
    for mode in tout_arguments; do
        if [ $mode == "tab" ]; then
            mode_tri = "tab"
            break
        elif [ $mode == "abr" ]; then
            mode_tri = "abr"
            break
        elif [ $mode == "avl" ]; then
            mode_tri == "avl"
            break
        fi
    done
}

#while true; do
# Traitement des options de la ligne de commande avec getopt
while getopts ":t:p:wmhFGSAOQ-:" option; do
    if [ $option = "-" ]; then
        case $OPTARG in
            abr) mode_tri="abr" ;;
            tab) mode_tri="tab" ;;
            avl) mode_tri="avl" ;;
            help) cat help.txt;;
        esac
    else
        case "$option" in
        #traitement de la temperature accompagné d'une option 1 ou 2 ou 3

        t)
            test_argument_mode
            execution_mode_t
            test_options
            ;;
        p) #traitement de la pression accompagné d'une option 1 ou 2 ou 3
            test_argument_mode
            execution_mode_p
            test_options
            ;;
        w) #traitement de l'option vent
            filtrage_w
            ;;
        m)
            echo "humidite"
            ;; #traitement de l'option humidite
        h)
            echo "altitude"
            ;; #traitement de l'option altitude
        F)
            echo "France"
            shift
            ;;
        G)
            echo "Guyane française"
            shift
            ;;
        S)
            echo "Saint-Pierre et Miquelon"
            shift
            ;;
        A)
            echo "Antilles"
            shift
            ;;
        O)
            echo "Océan indien"
            shift
            ;;
        Q)
            echo "Antarctique"
            shift
            ;;
        *)
            echo "option invalide"
            ;;
        --) break;;
        esac
    
    fi
done
shift $((OPTIND - 1))
#verification_tri
echo $mode_tri
