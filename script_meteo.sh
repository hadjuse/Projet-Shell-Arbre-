#!/bin/bash
#Initialisation des variables
tout_arguments=$*
mode_tri="avl"
option_geographique=""
i=0
nom_fichier=""
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
    cut -d ';' -f 1,11,15 meteo_filtered_data_v1.csv >donnee_filtree_temperature_et_num_t.csv
}
filtrage_2() {
    cut -d ';' -f 1,11,2,15 meteo_filtered_data_v1.csv >donnee_filtree_temperature_et_date_t.csv
}
filtrage_3() {
    cut -d ';' -f 1,11,15 meteo_filtered_data_v1.csv >donnee_filtree_temperature_et_id_t.csv
}
#filtrage pour l'option -p
filtrage_1_bis() {
    cut -d ';' -f 11,15 meteo_filtered_data_v1.csv >donnee_filtree_temperature_et_num_p.csv

}
filtrage_2_bis() {
    cut -d ';' -f 11,2,15 meteo_filtered_data_v1.csv >donnee_filtree_temperature_et_date_p.csv
}
filtrage_3_bis() {
    cut -d ';' -f 1,11,15 meteo_filtered_data_v1.csv >donnee_filtree_temperature_et_id_p.csv
}
#filtrage pour l'option -w
filtrage_w() {
    cut -d ';' -f 1,3,4,15 meteo_filtered_data_v1.csv >donnee_filtree_id_vent_moyenne.csv
}
filtrage_m() {
    cut -d ';' -f 1,6,15 meteo_filtered_data_v1.csv >donnee_filtree_altitude.csv
}
filtrage_h() {
    cut -d ';' -f 1,4,15 meteo_filtered_data_v1.csv >donnee_filtree_humidite.csv
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

#while true; do
# Traitement des options de la ligne de commande avec getopt
while getopts ":t:p:wmhFGSAOQ-:" option; do
    if [ $option = "-" ]; then
        case $OPTARG in
        abr) mode_tri="abr" ;;
        #tab) mode_tri="tab" ;;
        avl) mode_tri="avl" ;;
        help) cat help.txt ;;
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
            filtrage_m
            ;; #traitement de l'option humidite
        h)
            filtrage h
            ;; #traitement de l'option altitude
        f)  nom_fichier=$OPTARG  ;;
        #option geographique
        F)
            option_geographique="F"
            ;;
        G)
            option_geographique="G"
            shift
            ;;
        S)
            option_geographique="S"
            shift
            ;;
        A)
            option_geographique="A"
            shift
            ;;
        O)
            option_geographique="O"
            shift
            ;;
        Q)
            option_geographique="Q"
            shift
            ;;
        *)
            echo "option invalide"
            ;;
        --) break ;;
        esac
    fi
done
fichier_csv=$(ls | grep ^donnee)
for f in $fichier_csv; do
    i=$(($i + 1))
    case $option_geographique in
    F)
        cut -d ';' -f 1- "$f" | grep -E '1[001-976][1-7]' >donnee_filtree_metropole_$i.csv
        rm $f
        ;;
    G)
        cut -d ';' -f 1- "$f" | grep -E '973[01-62]' >donnee_filtree_Guyane_$i.csv
        rm $f
        ;;
    S)
        cut -d ';' -f 1- "$f" | grep -E '97500' >donnee_filtree_Saint_Miq_$i.csv
        rm $f
        ;;
    A)
        cut -d ';' -f 1- "$f" | grep -E '971[00-90]' >donnee_filtree_Antille_$i.csv
        rm $f
        ;;
    O)
        cut -d ';' -f 1- "$f" | grep -E '974[30-40]' >donnee_filtree_Ocean_$i.csv
        rm $f
        ;;
    Q)
        cut -d ';' -f 1- "$f" | grep -E '984[11-15]' >donnee_filtree_antarctique_$i.csv
        rm $f
        ;;
    esac
done
shift $((OPTIND - 1))
make
./abr $nom_fichier $mode_tri