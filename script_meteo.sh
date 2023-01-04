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
        echo "Il faut au moins mettre 1 option parmis -t[option] -p[option] -w -m -h" >&2
        exit 1
    fi
}
#filtrage pour l'option -t
filtrage_1() {
    awk -F';' '{print $10 ";" $11 ";" $1}' $nom_fichier>donnee_filtree_temperature_et_num_t.csv
}
filtrage_2() {
    awk -F';' '{print $10 ";" $1 ";" $11 ";" $2}' $nom_fichier>donnee_filtree_temperature_et_date_t.csv
}
filtrage_3() {
    awk -F';' '{print $10 ";" $1 ";" $11 ";" $2}' $nom_fichier>donnee_filtree_temperature_et_id_t.csv
    #cut -d ';' -f 1,11,10 meteo_filtered_data_v1.csv >donnee_filtree_temperature_et_id_t.csv
}
#filtrage pour l'option -p
filtrage_1_bis() {
    awk -F';' '{print $10 ";" $7 ";" $1}' $nom_fichier>donnee_filtree_temperature_et_num_p.csv
}
filtrage_2_bis() {
    awk -F';' '{print $10 ";" $2 ";" $7}' $nom_fichier>donnee_filtree_temperature_et_date_p
}
filtrage_3_bis() {
    awk -F';' '{print $10 ";" $1 ";" $7 ";" 2}' $nom_fichier>donnee_filtree_temperature_et_id_p.csv
}
#filtrage pour l'option -w
filtrage_w() {
    awk -F';' '{print $10 ";" $1 ";" $3 ";" $4 ";" $10}' $nom_fichier>donnee_filtree_id_vent_moyenne.csv
}
filtrage_m() {
    awk -F';' '{print $10 ";" $1 ";" $6}' $nom_fichier>donnee_filtree_temperature_et_num_p.csv
}
filtrage_h() {
    awk -F';' '{print $10 ";" $1 ";" $4}' $nom_fichier>donnee_filtree_humidite.csv
}
#execution des arguments et options
execution_mode_t() {
    if [ $OPTARG -eq 1 ]; then
        option_t=1
    elif [ $OPTARG -eq 2 ]; then
        option_t=2
    elif [ $OPTARG -eq 3 ]; then
        option_t=3
    fi
}

execution_mode_p() {
    if [ $OPTARG -eq 1 ]; then
        option_w=1
    elif [ $OPTARG -eq 2 ]; then
        option_w=2
    elif [ $OPTARG -eq 3 ]; then
        option_w=3
    fi
}
execution_mode_t_final() {
    if [ "$option_t" == '1' ]; then
        filtrage_1
    elif [ "$option_t" == '2' ]; then
        filtrage_2
    elif [ "$option_t" == '3' ]; then
        filtrage_3
    fi
}
execution_mode_p_final() {
    if [ "$option_w" == '1' ]; then
        filtrage_1_bis
    elif [ "$option_w" == '2' ]; then
        filtrage_2_bis
    elif [ "$option_w" == '3' ]; then
        filtrage_3_bis
    fi
}
execution_argument_restant() {
    if [ "$vent" == "ok" ];then
        filtrage_w
    fi
    if [ "$humidite" == "ok" ];then
        filtrage_m
    fi
    if [ "$altitude" == "ok" ];then
        filtrage_h
    fi
}
#while true; do
# Traitement des options de la ligne de commande avec getopt
while getopts ":t:p:wmhFGSAOQ-:f:d:" option; do
    if [ $option = "-" ]; then
        case $OPTARG in
        abr) mode_tri="abr" ;;
        tab) mode_tri="tab" ;;
        avl) mode_tri="avl" ;;
        help) cat help.txt ;;
        esac
    else
        case "$option" in
        
        #traitement de la temperature accompagné d'une option 1 ou 2 ou 3
        t)
            test_argument_mode
            test_options
            execution_mode_t
        ;;
        f) nom_fichier=$OPTARG;;
        p) #traitement de la pression accompagné d'une option 1 ou 2 ou 3
            test_argument_mode
            test_options
            execution_mode_p
            ;;
        w) #traitement de l'option vent
            vent="ok"
            ;;
        m)
            humidite="ok"
            ;; #traitement de l'option humidite
        h)
            altitude="ok"
            ;; #traitement de l'option altitude
        
        #option geographique
        F)
            option_geographique="F"
            ;;
        G)
            option_geographique="G"
            ;;
        S)
            option_geographique="S"
            ;;
        A)
            option_geographique="A"
            ;;
        O)
            option_geographique="O"
            ;;
        Q)
            option_geographique="Q"
            ;;
        *)
            echo "option invalide"
            ;;
        --) break ;;
        esac
    fi
done
echo "$min" "$max"
if [ -z "$nom_fichier" ]; then
  echo "Le nom du fichier d'entrée doit être renseigné." >&2
  exit 1
fi
execution_mode_p_final
execution_mode_t_final
execution_argument_restant
#filtrage par zone
fichier_csv=$(ls | grep ^donnee)
for fic in $fichier_csv; do
    i=$(($i + 1))
    case $option_geographique in
    F) #la commande awk va selectionner la première colonne qui correspond aux coordonées et sépare en 2 à l'aide
        #d'une virgule en latitude puis longitude et stocke les valeurs de la colonne dans une variable coords à l'aide de l'option split.
        #coords[1] correspond aux latitude et coords[2] aux longitude.
        awk -F";" '{
  split($1, coords, ",")
  if (coords[1] + 0 >= 41 && coords[1] + 0<= 51 && coords[2] + 0>= -5 && coords[2] + 0 <= 2) {
    print $0
} }' $fic >donnee_filtree_metropole_$1.csv
        rm $f
        ;;
    G)
        awk -F";" '{
  split($1, coords, ",")
  if (coords[1] + 0 >= -4 && coords[1] + 0 <= 8  && coords[2]+0 >=-58 && coords[2] + 0<= -48) {
    print $0
} }' $fic >donnee_filtree_Guyane_$i.csv
        rm $f
        ;;
    S)
        awk -F";" '{
  split($0, coords, ",")
  if (coords[1] + 0>= 45 && coords[1] + 0 <=50  && coords[2]+0 >= -60 && coords[2] + 0 <= -53) {
    print $0
} }' "$fic" >donnee_filtree_Saint_Miq_$i.csv
        rm $f
        ;;
    A)
        awk -F";" '{
  split($0, coords, ",")
  if (coords[1] +0>= 11 && coords[1] + 0 <=16  && coords[2]+0 >= -65 && coords[2] + 0 <= -57) {
    print $0
} }' "$fic" >donnee_filtree_Antille_$i.csv
        rm $f
        ;;
    O)
        awk -F";" '{
  split($0, coords, ",")
  if (coords[1] +0>= -26 && coords[1] + 0 <=-10  && coords[2]+0 >= 35 && coords[2] + 0 <= 61) {
    print $0
} }' "$fic" >donnee_filtree_Ocean_$i.csv
        rm $f
        ;;
    Q)
        awk -F";" '{
  split($0, coords, ",")
  if (coords[1] +0>= -75 && coords[1] + 0 <=-41  && coords[2]+0 >= 36 && coords[2] + 0 <= 131) {
    print $0
} }' "$fic" >donnee_filtree_antarctique_$i.csv
        rm $f
        ;;
    esac
done
shift $((OPTIND - 1))
#execution des tris
make
fichier_csv_a_trier=$(ls | grep ^donnee)
echo $fichier_csv_a_trier

