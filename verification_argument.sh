#!/bin/bash
#echo "$*"
#if [ $# != 5 ] || [ $# != 6 ]; then
#    echo "Il faut avoir 6 à 5 arguments"
#    exit 1
#fi 

while getopts "t:p:wmh" option
do
    case "$option" in
        t);; #traitement de la temperature accompagné d'une option 1 ou 2 ou 3
        p);; #traitement de la pression accompagné d'une option 1 ou 2 ou 3
        w);; #traitement de l'option vent
        m);; #traitement de l'option humidite
        h);; #traitement de l'option altitude
        *);;
    esac
done


