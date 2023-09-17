//arret de la tache
void stop(){
    asm volatile ("int   $0x60\n"
                  : 
                  : 
                  : );
}

#include "seac_gen.h"    //fonctions générales
//#include "seac_sec.h"    //fonctions secondaires

//rien a faire (passe le controle a la tache suivante)
void raf(){
    asm volatile ("int   $0x62\n"
                  : 
                  : 
                  : );
}

#include "seac_vid.h"    //fonctions d'interfaces homme machine
#include "seac_fich.h"   //fonctions de manipulation de fichier et de disques 
//#include "seac_com.h"    //fonctions de communication inter taches
//#include "seac_port.h"   //fonctions de manipulation de port série et parallèle
//#include "seac_usb.h"    //fonctions de manipulation de périphériques usb





//convertit nombre en chaine
void nbstring(long nombre,char *chaine){
    asm volatile ("mov   $102, %%eax\n"
    		  "int   $0x61\n"
    	          : /* no output */
                  :"ecx"(nombre),"edx"(chaine)
                  :"eax");

}

//******************************************************************************
//fonctions d'affichage












