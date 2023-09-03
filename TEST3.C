#include "base_seac.h"

char nom_fichier[256];
char buffer[2048];

int main(void){
    int numero = create_file("fichier test3.txt");
    write_file(numero,0,25,"ecriture dans fichier ok!");
    printJ("ecriture dans fichier ok!");
}

