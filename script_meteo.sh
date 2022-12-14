#!/bin/bash
#Initialisation des variables
tout_arguments=$*
mode_tri="avl"
option_geographique=""
i=0
nom_fichier=""
option_t="non"
option_p="non"
vent="non"
humidite="non"
altitude="non"
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
    awk -F';' '{print $1 ";" $10 ";" $11 ";" $12 ";" $13 }' meteo.csv >donnee_filtree_temperature_et_num_t.csv
}
filtrage_2() {
    awk -F';' '{print $1 ";" $10 ";" $2 ";" $11 ";" 0}' meteo.csv >donnee_filtree_temperature_et_date_t.csv
}
filtrage_3() {
    awk -F':' '{print $1 ";" $10 ";" $2 ";" $11 }' meteo.csv >donnee_filtree_temperature_et_id_t.csv
    #cut -d ';' -f 1,11,10 meteo_filtered_data_v1.csv >donnee_filtree_temperature_et_id_t.csv
}
#filtrage pour l'option -p
filtrage_1_bis() {
    awk -F';' '{print $1 ";" $10 ";" $3 ";" $7 ";" 0}' meteo.csv >donnee_filtree_temperature_et_num_p.csv
}
filtrage_2_bis() {
    awk -F';' '{print $1 ";" $10 ";" $2 ";" $7 ";" 0}' meteo.csv >donnee_filtree_temperature_et_date_p.csv
}
filtrage_3_bis() {
    awk -F';' '{print $1 ";" $10 ";" $2 ";" $7 ";" 0}' meteo.csv >donnee_filtree_temperature_et_id_p.csv
}
#filtrage pour l'option -w
filtrage_w() {
    awk -F';' '{print $1 ";" $10 ";" $3 ";" 0}' meteo.csv >donnee_filtree_id_vent_moyenne.csv
}
filtrage_m() {
    awk -F';' '{print $1 ";" $10 ";" $6 ";" 0}' meteo.csv >donnee_filtree_temperature_et_num_p.csv
}
filtrage_h() {
    awk -F';' '{print $1 ";" $10 ";" $4 ";" 0}' meteo.csv >donnee_filtree_humidite.csv
}
#execution des arguments et options
execution_mode_t() {
    if [ $OPTARG -eq 1 ]; then
        option_t="1"
        echo $option_t
    elif [ $OPTARG -eq 2 ]; then
        option_t="2"
    elif [ $OPTARG -eq 3 ]; then
        option_t="3"
    fi
}

execution_mode_p() {
    if [ $OPTARG -eq 1 ]; then
        option_p="1"
    elif [ $OPTARG -eq 2 ]; then
        option_p="2"
    elif [ $OPTARG -eq 3 ]; then
        option_p="3"
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
    if [ "$option_p" == '1' ]; then
        filtrage_1_bis
    elif [ "$option_p" == '2' ]; then
        filtrage_2_bis
    elif [ "$option_p" == '3' ]; then
        filtrage_3_bis
    fi
}
execution_argument_restant() {
    if [ "$vent" == "ok" ]; then
        filtrage_w
    fi
    if [ "$humidite" == "ok" ]; then
        filtrage_m
    fi
    if [ "$altitude" == "ok" ]; then
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

        #traitement de la temperature accompagn?? d'une option 1 ou 2 ou 3
        t)
            test_argument_mode
            test_options
            execution_mode_t
            ;;
        f) nom_fichier=$OPTARG ;;
        p) #traitement de la pression accompagn?? d'une option 1 ou 2 ou 3
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
if [ -z "$nom_fichier" ]; then
    echo "Le nom du fichier d'entr??e doit ??tre renseign??." >&2
    exit 1
fi
#remplace les cellules vides par des 0, 2 filtrages sont n??c??ssaires pour avoir toute les cellules vides ?? 0
sed 's/;;/;0;/g; s/;$/;0/g' $nom_fichier >meteo_temp.csv
sed 's/;;/;0;/g; s/;$/;0/g' meteo_temp.csv >meteo.csv
rm meteo_temp.csv
execution_mode_p_final
execution_mode_t_final
execution_argument_restant
#filtrage par zone
fichier_csv=$(ls | grep ^donnee)
for fic in $fichier_csv; do
    i=$(($i + 1))
    case $option_geographique in
    F) #la commande awk va selectionner la premi??re colonne qui correspond aux coordon??es et s??pare en 2 ?? l'aide
        #d'une virgule en latitude puis longitude et stocke les valeurs de la colonne dans une variable coords ?? l'aide de l'option split.
        #coords[1] correspond aux latitude et coords[2] aux longitude.
        awk -F";" '{
  split($2, coords, ",")
  if (coords[1] + 0 >= 40 && coords[1] + 0<= 51 && coords[2] + 0>= -5 && coords[2] + 0 <= 8) {
    print $0
} }' $fic >donnee_filtree_metropole_$1.csv
        rm $fic
        ;;
    G)
        awk -F";" '{
  split($2, coords, ",")
  if (coords[1] + 0 >= 0 && coords[1] + 0 <= 6  && coords[2]+0 >=-54 && coords[2] + 0<= -50) {
    print $0
} }' $fic >donnee_filtree_Guyane_$i.csv
        rm $fic
        ;;
    S)
        awk -F";" '{
  split($2, coords, ",")
  if (coords[1] + 0>= 45 && coords[1] + 0 <=50  && coords[2]+0 >= -60 && coords[2] + 0 <= -53) {
    print $0
} }' "$fic" >donnee_filtree_Saint_Miq_$i.csv
        rm $fic
        ;;
    A)
        awk -F";" '{
  split($2, coords, ",")
  if (coords[1] +0>= 11 j&& coords[1] + 0 <=16  && coords[2]+0 >= -65 && coords[2] + 0 <= -57) {
    print $0
} }' "$fic" >donnee_filtree_Antille_$i.csv
        rm $fic
        ;;
    O)
        awk -F";" '{
  split($2, coords, ",")
  if (coords[1] +0>= -26 && coords[1] + 0 <=-10  && coords[2]+0 >= 35 && coords[2] + 0 <= 61) {
    print $0
} }' "$fic" >donnee_filtree_Ocean_$i.csv
        rm $fic
        ;;
    Q)
        awk -F";" '{
  split($2, coords, ",")
  if (coords[1] +0>= -75 && coords[1] + 0 <=-41  && coords[2]+0 >= 36 && coords[2] + 0 <= 131) {
    print $0
} }' "$fic" >donnee_filtree_antarctique_$i.csv
        rm $fic
        ;;
    esac
done
shift $((OPTIND - 1))
#execution des tris
make
fichier_csv_a_trier=$(ls | grep ^donnee)
for f in $fichier_csv_a_trier; do
    ./abr $f $mode_tri $option_t $option_p $humidite $vent $altitude
done
