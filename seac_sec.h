


//******************************************************************************
//fonctions secondaires

//convertit chaine decimale
long deci(char *chaine){
    long nombre = 0;
    asm volatile ("mov   $100, %%eax\n"
    		  "int   $0x61\n"
    	          :"=ecx"(nombre)
                  :"edx"(chaine)
                  :"eax");
    return nombre;
}

//convertit chaine hexadecimale
long hexa(char *chaine){
    long nombre = 0;
    asm volatile ("mov   $101, %%eax\n"
    		  "int   $0x61\n"
    	          :"=ecx"(nombre)
                  :"edx"(chaine)
                  :"eax");
    return nombre;
}


//convertit nombre decimal en chaine
void long2deci(long nombre,char *chaine){
    asm volatile ("mov   $102, %%eax\n"
    		  "int   $0x61\n"
    	          : /* no output */
                  :"ecx"(nombre),"edx"(chaine)
                  :"eax");
}

//convertit nombre hexadecimal en chaine
void long2hexa(long nombre,char *chaine){
    asm volatile ("mov   $103, %%eax\n"
    		  "int   $0x61\n"
    	          : /* no output */
                  :"ecx"(nombre),"edx"(chaine)
                  :"eax");
}


//convertit adresse ethernet chaine vers binaire
void etherS2B(char *entree,char *sortie){
    asm volatile ("mov   $108, %%eax\n"
    		  "int   $0x61\n"
    	          : /* no output */
                  :"ecx"(entree),"edx"(sortie)
                  :"eax");
}

//convertit adresse ipv4 chaine vers binaire
void ipv4S2B(char *entree,char *sortie){
    asm volatile ("mov   $109, %%eax\n"
    		  "int   $0x61\n"
    	          : /* no output */
                  :"ecx"(entree),"edx"(sortie)
                  :"eax");
}

//convertit adresse ipv6 chaine vers binaire
void ipv6S2B(char *entree,char *sortie){
    asm volatile ("mov   $110, %%eax\n"
    		  "int   $0x61\n"
    	          : /* no output */
                  :"ecx"(entree),"edx"(sortie)
                  :"eax");
}

//convertit adresse ethernet chaine vers binaire
void etherB2S(char *entree,char *sortie){
    asm volatile ("mov   $108, %%eax\n"
    		  "int   $0x61\n"
    	          : /* no output */
                  :"edx"(entree),"ecx"(sortie)
                  :"eax");
}

//convertit adresse ipv4 chaine vers binaire
void ipv4B2S(char *entree,char *sortie){
    asm volatile ("mov   $109, %%eax\n"
    		  "int   $0x61\n"
    	          : /* no output */
                  :"edx"(entree),"ecx"(sortie)
                  :"eax");
}

//convertit adresse ipv6 chaine vers binaire
void ipv6B2S(char *entree,char *sortie){
    asm volatile ("mov   $110, %%eax\n"
    		  "int   $0x61\n"
    	          : /* no output */
                  :"edx"(entree),"ecx"(sortie)
                  :"eax");
}
