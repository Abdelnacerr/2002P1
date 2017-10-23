/*
 CITS2002 Project 1 2017
 Names: Harrison Carter-Turner, Mohamed Abdinasir
 Student Numbers: 21973737, 22046631
 Date: 22/09/2017
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define Macs	1000
#define OUIs	25000
#define vname   90
#define LINESIZE 128

int status = 0;

//The sorter method is a helper because the project is in 2 parts. Both parts call this method.
int sortfile(int condition){
    int pid = fork();    
    if(pid == 0 && condition == 1){
        printf("hi");              
	char *param[] = {
		"",
		"-t\t",
		"-k 2, 2nr",
		"-k 1, 1d",
                "f.txt",
                NULL
	};
        execv("/usr/bin/sort", param);
    }
    else if(pid == 0 && condition == 2){	
	printf("IMOVERHERELOOKATME");	
        char *param[] = {
                "",
		"-t\t",
		"-k 3,3nr",
		"-k 2,2d",
                "f.txt",
                NULL
	};
        execv("/usr/bin/sort", param);
    }

    else {
       wait(&status);
    }
    return 0;
}

//Reads and sorts the sample file with only MAC addresses and packet sizes
int readfile (char condition[], char filename[]){

    char transmitter[Macs][48]; //Mac addresses require exactly 48 bytes;

    char receiver[Macs][48];

    char tHold[48]; // i.e. transmitterHold
    char rHold[48]; // i.e. receiverHold
    char bHold[16]; //Allowing 16 bytes for the 'packet size'
    int noOfMacs = 0;
    char *value; //Values are stored and passed to tHold, rHold and bHold appropriately
    int bytes[Macs];
    char line[LINESIZE];
    char bigstring[BUFSIZ];

    int i = 0;
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        perror(filename);
        exit(EXIT_FAILURE);
    }
    while(fgets(line, sizeof(line), fp)){ 
        value = strtok(line, "\t"); //Splits on the tab characters
        value = strtok(NULL, "\t");
        strcpy(tHold, value);
        
        value = strtok(NULL, "\t");
        strcpy(rHold, value);
        value = strtok(NULL, "\n");
        strcpy(bHold, value);
     
        
    if (strcmp(condition, "t")==0){ //detect conditions, t for transmitter and r for receiver
       
        for(int j = 0; j <= i; j++){
            if(!transmitter[j][0]){
                strcpy(transmitter[j], tHold);
                bytes[j] += atoi(bHold);
                noOfMacs++;
                break;
            }
            else if(strcmp(tHold, transmitter[j])==0){
                bytes[j] += atoi(bHold);
                break;
            }
        }
    }
    else if (strcmp(condition, "r")==0){
       
        for(int j = 0; j <= i; j++){
            if(!receiver[j][0]){
                strcpy(receiver[j], rHold);
                bytes[j] += atoi(bHold);
                noOfMacs++;
                break;
            }
            else if(strcmp(rHold, receiver[j])==0){
                bytes[j] += atoi(bHold);
                break;
            }
        }
    }
    i++;

    }
    FILE *wfile = fopen("f.txt","w");
    if (strcmp(condition, "t")==0){
        for(int j = 0; j < noOfMacs; j++){
            sprintf(bigstring, "%s\t %i\n", transmitter[j], bytes[j]);
            fputs(bigstring, wfile);
        }
    }
    else 
    if (strcmp(condition, "r")==0){
        for(int j = 0; j < noOfMacs; j++){
            sprintf(bigstring, "%s\t %i\n", receiver[j], bytes[j]);
            fputs(bigstring, wfile);
        }
    }
fclose(wfile); 
sortfile(1);  
fclose(fp);

return 0;

}

//Reads and sorts the MAC address file and the OUI file
int readfileOUI (char condition[], char macFile[], char vendorFile[]){
    char transmitter[Macs][48]; //Mac addresses require exactly 48 bytes;

    char receiver[Macs][48];

    char vendor[OUIs][vname];
    char OUI[OUIs][48];
    char tHold[48];
    char rHold[48];
    char bHold[16];
    int noOfMacs = 0;
    int totalBytes = 0;
    char *value;
    int bytes[Macs];
    char line[LINESIZE];
    char bigstring[BUFSIZ];

    int i = 0;
    FILE *mfp = fopen(macFile, "r");
    if(mfp == NULL){
        perror(macFile);
        exit(EXIT_FAILURE);
    }
    FILE *vfp = fopen(vendorFile, "r");
    if(vfp == NULL){
        perror(vendorFile);
        exit(EXIT_FAILURE);
    }
    while(fgets(line, sizeof(line), mfp)){ 
        value = strtok(line, "\t");
        value = strtok(NULL, "\t");
        strcpy(tHold, value);
        tHold[8] = '\0';

        value = strtok(NULL, "\t");

        strcpy(rHold, value);
        rHold[8] = '\0';

        value = strtok(NULL, "\n");

        strcpy(bHold, value);
        totalBytes += atoi(bHold);
        
        if (strcmp(condition, "t")==0){
       
            for(int j = 0; j <= i; j++){
                if(!transmitter[j][0]){
                    strcpy(transmitter[j], tHold);
                    bytes[j] += atoi(bHold);
                    noOfMacs++;
                    break;
                }
                else if(strcmp(tHold, transmitter[j])==0){
                    bytes[j] += atoi(bHold);
                    break;
                }
            }
        }

        else if (strcmp(condition, "r")==0){
       
            for(int j = 0; j <= i; j++){
                if(!receiver[j][0]){
                    strcpy(receiver[j], rHold);
                    bytes[j] += atoi(bHold);
                    noOfMacs++;
                    break;
                }
                else if(strcmp(rHold, receiver[j])==0){
                    bytes[j] += atoi(bHold);
                    break;
                }
           }
       }
    i++;

    }
    i = 0;
    while(fgets(line, sizeof(line), vfp)){ 
        value = strtok(line, "\t");
        strcpy(OUI[i], value);
        int a = 0;
        while(OUI[i][a]){
            OUI[i][a] = tolower(OUI[i][a]);
            a++;
        }
        OUI[i][2] = ':';
        OUI[i][5] = ':';
        value = strtok(NULL, "\n");
        
        strcpy(vendor[i], value);
        i++;
    }
    FILE *wfile = fopen("f.txt","w");

    if (strcmp(condition, "t")==0){
   
        for(int j = 0; j < noOfMacs; j++){
            for(int k = 0; k < i; k++){
                if(strcmp(OUI[k], transmitter[j])==0){
                    sprintf(bigstring, "%s\t%s\t%i\n", OUI[k], vendor[k], bytes[j]);
                    fputs(bigstring, wfile);
                    totalBytes -= bytes[j];
                }
            }
        }
    }
    else if (strcmp(condition, "r")==0){
   
        for(int j = 0; j < noOfMacs; j++){
            for(int k = 0; k < i; k++){
                if(strcmp(OUI[k], receiver[j])==0){
                    sprintf(bigstring, "%s\t%s\t%i\n", OUI[k], vendor[k], bytes[j]);
                    fputs(bigstring, wfile);
                    totalBytes -= bytes[j];
                }
            }
        }
    }
    if (totalBytes > 0){
        sprintf(bigstring, "??:??:??\tUNKNOWN-VENDOR\t%i\n",totalBytes);
        fputs(bigstring, wfile);
    }
	fclose(wfile);    
	fclose(mfp);
	sortfile(2);  
    
	fclose(vfp);
	return 0;

}

int main(int argc, char *argv[])
{
    if (argc == 3){                     //if 3 args, call first function
        readfile(argv[1],argv[2]);

    }
    else if (argc == 4){
        readfileOUI(argv[1], argv[2], argv[3]);     //if 4 args, call second function
    }
    else{
        printf("Usage: %s file1 condition (file2)\n", argv[0]);    //otheriwse give an error

        exit(EXIT_FAILURE);

    }
return 0;
}
