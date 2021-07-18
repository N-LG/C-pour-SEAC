#efface le dernier fichier
rm $1.FE


# option de GCC utillisé ici 
#-std=gnu90  //norme du language (au choix)
#-march=i386 //famille du processeur cible
#-m32        //processeur en 32bits (indispensable)
#-nostdlib   //pas besoin de stdlib (indispensable)
#-e _start   //spécfie le point d'entrée (indispensable)
#-o $1.FE    //nom du fichier de sortie(doit être en majuscule avec l'extension FE)          
#-s          //enlève les table de symbole et de relocation (gagne de l'espace)
#-fno-asynchronous-unwind-tables //enlève  (gagne de l'espace)
#-Wl         //option du linkage séparé par des virgules
#-c          //pas de linkage (inutilisé ici)

# option de LD utillisé ici
#--nmagic         //désactive l'alignement par page (gagne de l'espace)
#--strip-all      //ne met pas les infos pour le débuggeure (gagne de l'espace)
#--script=seac.ld //script de linkage a employer (indispensable)


#compilation et linkage
gcc -std=gnu90 -m32 -march=i386  -nostdlib -e _start -fno-asynchronous-unwind-tables -s -o $1.FE -Wl,--nmagic,--strip-all,--script=seac.ld $1.C base_seac.s

#affiche des infos sur le fichier compilé
readelf -S -l $1.FE

#envoyer le résultat de la compilation a un pc qui a démarré SEAC 
tftp -4 192.168.1.200 -m binary -c put $1.FE

