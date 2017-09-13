#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


#define MACS	500
#define OUIs	2500
#define Vname	500

int copy_word(char word[], char line[], int c)
{
    int w=0;

    while(line[c] != '\0' && !isspace(line[c])) {
	word[w] = line[c];
	++w;
	++c;
    }
    word[w]	= '\0';		// don't forget the null-byte!

    while(isspace(line[c])) {	// skip any trailing spaces
	++c;
    }
    return c;			// return where we're up to in 'line'
}


int readFile( char filename[] )
{
//  ATTEMPT TO OPEN NAMED FILE, OR USE stdin
    FILE *fp;

    if(strcmp(filename, "-") == 0)
	fp	= stdin;
    else {
	fp = fopen(filename, "r");
	if(fp == NULL) {
	    perror(filename);
	    exit(EXIT_FAILURE);
	}
}


//  READ EVENTS UNTIL END-OF-FILE REACHED
    while(fgets(line, sizeof line, fp) != NULL) {
	char	word[BUFSIZ];

    int c	= copy_word(word, line, 0);		// field-1
    printf("%s", c );
    

        fclose(fp);
    }        
}

int main(int argc, char *argv[])
{

    read_scenario_file(argv[1]);




}

