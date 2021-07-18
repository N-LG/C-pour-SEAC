static void print(char *string)
	{
	asm volatile ("mov   $0x06, %%al\n"
    		      "int   $0x61\n"
    	             : /* no output */
                     : "edx"(string)
                     : "al");
	}

extern int asm_printc();

static void printc(char *string,char couleur)
	{
	asm volatile ("call asm_printc"
    	             : /* no output */
                     : "edx"(string),"al"(couleur)
                     : );
	}

