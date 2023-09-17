
#define ECRAN_TEXTE  1
#define ECRAN_VIDEO  2
#define ECRAN_SOURIS 4

struct retourclavier {
    unsigned char touche;
    unsigned char spec;
    unsigned long carac;
    unsigned long x;
    unsigned long y;
};

//******************************************************************************
//fonctions video

long cree_ecran(unsigned char mode_ecran){
    long erreur = 0;
     asm volatile ("mov   $0, %%al\n"
    		  "int   $0x63\n"
    	          :"=eax"(erreur)
                  :"ah"(mode_ecran)
                  :);
    return erreur;

}

void supprime_ecran(){
     asm volatile ("mov   $1, %%al\n"
    		  "int   $0x63\n"
    	          :/*pas de sortie*/
                  :/*pas d'entrée*/
                  :);

}

void afficher_ecran(int id){
    asm volatile ("mov $3,%%al\n"
                  "int $0x63\n"
                  :/*pas de sortie*/ 
                  :"dx"(id)
                  : );
}

struct retourclavier clavier(){
     struct retourclavier structure;
     asm volatile ("mov   $5, %%al\n"
    		  "int   $0x63\n"
                  :"=ah"(structure.touche),"=al"(structure.spec),"=ecx"(structure.carac),"=ebx"(structure.x)
                  :/*aucunes entrées*/
                  :);
    if (structure.touche<0xF0){
        structure.y = 0;
    }else{
        structure.y = structure.carac;
        structure.carac = 0;
    }
    return structure ;
}


char saisie_clavier(char* chaine,char couleur,long taille){
    char retour = 0;
    asm volatile ("mov $6,%%al\n"
                  "int $0x63\n"
                  :"=al"(retour) 
                  :"edx"(chaine),"ah"(couleur),"ecx"(taille)
                  : );
    return retour;
}

void maj_ecran(){
     asm volatile ("mov   $7, %%al\n"
    		  "int   $0x63\n"
    	          :/*pas de sortie*/
                  :/*pas d'entrée*/
                  :);

}

void maj_ecran_partiel(long x1,long y1,long x2,long y2){
     asm volatile ("mov   $8, %%al\n"
    		  "int   $0x63\n"
    	          :/*pas de sortie*/
                  :"ebx"(x1),"ecx"(y1),"eS"(x2),"eD"(y2)
                  :);

}

