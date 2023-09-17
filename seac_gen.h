struct dateheure {
    unsigned long annee;
    unsigned char mois;
    unsigned char jour;
    unsigned char heure;
    unsigned char minute;
    unsigned long milliseconde;
};



//******************************************************************************
//fonctions générales

//envoie une commande au systeme
void command(char *commande){
    asm volatile ("mov $0x00, %%al\n"
                  "int   $0x61\n"
    	          : 
                  :"edx"(commande)
                  :"eax");
}


//attend x millisecondes
static void delay(int millis){
    asm volatile ("mov $10, %%eax\n"
                  "xor %%edx, %%edx\n"
                  "mul %%ecx\n"
                  "mov $25, %%ecx\n"
                  "div %%ecx\n"
                  "mov %%eax, %%ecx\n"
                  "mov $0x01,%%al\n"
                  "int $0x61\n"
    	          :/* no output */
                  :"ecx"(millis)
                  :"eax","edx" );

}


//récupère l'ID de la tache
int id_tache(){
    int id = 0;
    asm volatile ("mov $0x02, %%al\n"
                  "int   $0x61\n"
    	          :"=bx"(id)
                  : 
                  :"eax");
   return id;
}


//recupère la commande
int commande(char *string){
    asm volatile ("mov $0x00, %%al\n"
                  "int   $0x61\n"
    	          : 
                  :"edx"(string)
                  :"eax");
}

// récupère argument par son numéros
int arg_num(char numero,char *string){
    int erreur = 0;
    asm volatile ("mov $0x04, %%al\n"
                  "mov $0x00, %%cl\n"
    		  "int   $0x61\n"
    	          :"=eax"(erreur)
                  :"ah"(numero),"edx"(string)
                  :"cl");
   return erreur;
}

// récupère argument par sa lettre
int arg_lettre(char lettre,char *string){
    int erreur = 0;
    asm volatile ("mov $0x05, %%al\n"
                  "mov $0x00, %%cl\n"
    		  "int $0x61\n"
    	          :"=eax"(erreur)
                  :"ah"(lettre),"edx"(string)
                  :"cl");
   return erreur;
}

//affiche du texte dans le journal
static void printJ(char *string){
    asm volatile ("mov   $0x06, %%al\n"
                  "int   $0x61\n"
                  :/* no output */
                  :"edx"(string)
                  :"eax");
}

//modifie le descripteur de tache
static void printD(char *string){
    asm volatile ("mov   $0x07, %%al\n"
                  "int   $0x61\n"
                  : /* no output */
                  :"edx"(string)
                  :"eax");
}

//change la taille de la mémoire
int changeT(int taille){
    long erreur = 0;
    asm volatile ("mov $0x08, %%al\n"
                  "mov $0x47,%%dx\n"
                  "int   $0x61\n"
                  :"=eax"(erreur)
                  :"ecx"(taille)
                  :"dx");
    return erreur;
}

//récupère la date et l'heure
struct dateheure lireDH(){
    struct dateheure structure;
    asm volatile ("mov   $0x09, %%al\n"
                  "int   $0x61\n"
                  :"=bh"(structure.heure),"=bl"(structure.minute),"=eS"(structure.milliseconde),"=dl"(structure.jour),"=dh"(structure.mois),"=ecx"(structure.annee)
                  :/*aucunes entrées*/
                  :);
    return structure ;
}

//change le type de service
void changeS(unsigned char service){
    asm volatile ("mov   $0x0A, %%al\n"
                  "int   $0x61\n"
                  :
                  :"ah"(service)
                  :);
}

//cherche service
int rechercheS(unsigned char service,unsigned char *table,unsigned char taille){
    int erreur = 0;
    asm volatile ("mov   $0x0B, %%al\n"
                  "int   $0x61\n"
                  :
                  :"ah"(service),"edx"(table),"cl"(taille)
                  :);
    return erreur;
}



