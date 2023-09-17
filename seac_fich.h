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

//lit dans fichier
int read_file(int numero,int offset,int count,char *destination){
    int erreur = 0;
    asm volatile("mov $0x04, %%al\n"
                 "int $0x64\n"
    	         : "=eax"(erreur)
                 : "ebx"(numero),"ecx"(count),"edx"(offset),"eD"(destination)
                 : );
    return erreur;
}

//ecrire dans fichier
int write_file(int numero,int offset,int count,char *source){
    int erreur = 0;
    asm volatile("mov $0x05, %%al\n"
                 "int $0x64\n"
    	         : "=eax"(erreur)
                 : "ebx"(numero),"ecx"(count),"edx"(offset),"eS"(source)
                 : );
    return erreur;
}

//lire taille du fichier
long taille_file(int numero){
    int erreur = 0;
    long taille= 0;
    asm volatile("mov $0x05, %%ax\n"
                 "int $0x64\n"
    	         :"=eax"(erreur)
                 :"ebx"(numero),"edx"(&taille)
                 : );
    return erreur;
}
