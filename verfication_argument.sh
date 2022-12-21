#!/bin/bash
# Traitement des options de la ligne de commande avec getops
while getopts ":t:p:wmh" option
do
    case "$option" in
        #traitement de la temperature accompagné d'une option 1 ou 2 ou 3
        t)
        MODE=$OPTARG
        if [[ $MODE -ne 1 && $MODE -ne 2 && $MODE -ne 3 ]]; then
            echo "Les arguments sont compris entre 1 et 3 tout inclus."
            exit 1
        fi
        echo "$MODE" 
        ;;

        p) #traitement de la pression accompagné d'une option 1 ou 2 ou 3
        MODE=$OPTARG
        if [[ $MODE -ne 1 && $MODE -ne 2 && $MODE -ne 3 ]]; then
            echo "Les arguments sont compris entre 1 et 3 tout inclus."
            exit 1
        fi
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
        *)
        echo "Utilisation: -t[-option] -p[-option]"
        echo "rien"
        ;;
    esac
done