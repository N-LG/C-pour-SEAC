//******************************************************************************
//fonctions d'acces aux fichier

//ouvre le fichier
int open_file(char *nom){
    int erreur = 0;
    int numero = 0;
    asm volatile ("mov   $0x00, %%al\n"
                   "int   $0x64\n"
    	           : "=eax"(erreur),"=ebx"(numero)
                   : "edx"(nom)
                   : );
    if (erreur==0){
        return numero;
    }else{
        return -1;
    }
}


//ferme le fichier
int close_file(int numero){
    int erreur = 0;
     asm volatile ("mov   $0x01, %%al\n"
                   "int   $0x64\n"
    	           : "=eax"(erreur)
                   : "ebx"(numero)
                   : );
    return erreur;
}


//créer fichier
int create_file(char *nom){
    int erreur = 0;
    int numero = 0;
    asm volatile ("mov   $0x02, %%al\n"
                  "int   $0x64\n"
    	          : "=eax"(erreur),"=ebx"(numero)
                  : "edx"(nom)
                  : );
    if (erreur==0){
        return numero;
    }else{
        return -1;
    }
}

//supprime le fichier
int delete_file(int numero){
    int erreur = 0;
    asm volatile ("mov $0x03, %%al\n"
                  "int $0x64\n"
    	          : "=eax"(erreur)
                  : "ebx"(numero)
                  : );
    return erreur;
}


int read_file(int numero,int offset,int count,char *destination){
    int erreur = 0;
    asm volatile("mov $0x04, %%al\n"
                 "int $0x64\n"
    	         : "=eax"(erreur)
                 : "ebx"(numero),"ecx"(count),"edx"(offset),"eD"(destination)
                 : );
    return erreur;
}


int write_file(int numero,int offset,int count,char *source){
    int erreur = 0;
    asm volatile("mov $0x05, %%al\n"
                 "int $0x64\n"
    	         : "=eax"(erreur)
                 : "ebx"(numero),"ecx"(count),"edx"(offset),"eS"(source)
                 : );
    return erreur;
}



//******************************************************************************
//fonctions d'affichage

//affiche du texte dans le journal
static void printJ(char *string){
	asm volatile ("mov   $0x06, %%al\n"
    		      "int   $0x61\n"
    	             : /* no output */
                     : "edx"(string)
                     : "al");
}









//******************************************************************************
//fonctions autres

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
    	          : /* no output */
                  : "ecx"(millis)
                  : "eax","edx" );

}




