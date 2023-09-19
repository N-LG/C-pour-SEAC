struct dateheure {
    unsigned long annee;
    unsigned char mois;
    unsigned char jour;
    unsigned char heure;
    unsigned char minute;
    unsigned long milliseconde;
};



//******************************************************************************
//fonctions g�n�rales

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


//r�cup�re l'ID de la tache
int id_tache(){
    int id = 0;
    asm volatile ("mov $0x02, %%al\n"
                  "int   $0x61\n"
    	          :"=bx"(id)
                  : 
                  :"eax");
   return id;
}


//recup�re la commande
int commande(char *string){
    asm volatile ("mov $0x00, %%al\n"
                  "int   $0x61\n"
    	          : 
                  :"edx"(string)
                  :"eax");
}

// r�cup�re argument par son num�ros
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

// r�cup�re argument par sa lettre
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

//change la taille de la m�moire
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

//r�cup�re la date et l'heure
struct dateheure lireDH(){
    struct dateheure structure;
    asm volatile ("mov   $0x09, %%al\n"
                  "int   $0x61\n"
                  :"=bh"(structure.heure),"=bl"(structure.minute),"=eS"(structure.milliseconde),"=dl"(structure.jour),"=dh"(structure.mois),"=ecx"(structure.annee)
                  :/*aucunes entr�es*/
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

//lit le compteur de temps
long compteur(){
    long lsb;
    long msb;
    asm volatile ("mov   $0x0C, %%al\n"
                  "int   $0x61\n"
                  :"=eax"(lsb),"=ebx"(msb)
                  :/*aucunes entr�es*/
                  :);
    return lsb;
}

//lire un message systeme
void message_systeme(int num,char* chaine){
    asm volatile ("mov   $0x000D, %%ax\n"
                  "mov   $0, %%ch\n"
                  "int   $0x61\n"
                  :"=edx"(chaine),"=cl"(num)
                  :/*aucunes entr�es*/
                  :);   
}

//lire un message d'erreur
void message_erreur(int num,char* chaine){
    asm volatile ("mov   $0x010D, %%ax\n"
                  "mov   $0, %%ch\n"
                  "int   $0x61\n"
                  :"=edx"(chaine),"=cl"(num)
                  :/*aucunes entr�es*/
                  :);   
}

//lire journal systeme
void lire_journal(char* chaine,long taille){
    asm volatile ("mov   $0x0E, %%al\n"
                  "int   $0x61\n"
                  :/*pas de sortie*/
                  :"edx"(chaine),"ecx"(taille)
                  :);   
}

//copier des donn�es dans le presse papier
void ecrire_pp(char* chaine,long taille){
    asm volatile ("mov   $0x0F, %%al\n"
                  "int   $0x61\n"
                  :/*pas de sortie*/
                  :"edx"(chaine),"ecx"(taille)
                  :);   
}


//lire les donn�s dans le presse papier
void lire_pp(char* chaine,long taille){
    asm volatile ("mov   $0x10, %%al\n"
                  "int   $0x61\n"
                  :/*pas de sortie*/
                  :"edx"(chaine),"ecx"(taille)
                  :);   
}

//effacer le contenu du presse papier
void effacer_pp(){
     asm volatile ("mov   $0x11, %%al\n"
    		  "int   $0x61\n"
    	          :/*pas de sortie*/
                  :/*pas d'entr�e*/
                  :);

}

//lire l'adresse du dossier de travail
void lire_dossier_travail(char* chaine){
    asm volatile ("mov   $0x12, %%al\n"
                  "int   $0x61\n"
                  :/*pas de sortie*/
                  :"edx"(chaine)
                  :);   
}

//lire l'adresse du dossier de travail
void lire_dossier_travail(char* chaine,char nb){
    asm volatile ("mov   $0x13, %%al\n"
                  "int   $0x61\n"
                  :/*pas de sortie*/
                  :"edx"(chaine),"cl"(nb)
                  :);   
}
