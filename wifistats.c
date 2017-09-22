#include <stdio.h>

#include <stdlib.h>

#include <string.h>



#include <ctype.h>
#define Macs	500 //error because cant fit 23000 entries in?

#define OUIs	25000
#define vname   90

#define LINESIZE 128



int readfile (char condition[], char filename[]){

    char transmitter[Macs][48]; //Mac addresses require exactly 48 bytes;

    char receiver[Macs][48];

    char tHold[48]; // i.e. transmitterHold
    char rHold[48];
    char bHold[16]; //maybe increase just incase
    int noOfMacs = 0;
    char *value;
    int bytes[Macs];
    char line[LINESIZE];

    int i = 0;
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        perror(filename);
        exit(EXIT_FAILURE);
    }
    while(fgets(line, sizeof(line), fp)){ 
        value = strtok(line, "\t");
        value = strtok(NULL, "\t");
        strcpy(tHold, value);
  

        
        value = strtok(NULL, "\t");

        strcpy(rHold, value);

        value = strtok(NULL, "\n");

        strcpy(bHold, value);
     
        
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
    if (strcmp(condition, "t")==0){

        for(int j = 0; j < noOfMacs; j++){
            printf("%s\t %i\n", transmitter[j], bytes[j]);
        }
    }
    else 
if (strcmp(condition, "r")==0){

        for(int j = 0; j < noOfMacs; j++){
            printf("%s\t %i\n", receiver[j], bytes[j]);
        }
    }
    
fclose(fp);

    return 0;

}

int readfileOUI (char condition[], char macFile[], char vendorFile[]){
    char transmitter[Macs][48]; //Mac addresses require exactly 48 bytes;

    char receiver[Macs][48];

    char vendor[OUIs][vname];
    char OUI[OUIs][48];
    char tHold[48]; // i.e. transmitterHold
    char rHold[48];
    char bHold[16]; //maybe increase just incase
    int noOfMacs = 0;
    int totalBytes = 0;
    char *value;
    int bytes[Macs];
    char line[LINESIZE];

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
    if (strcmp(condition, "t")==0){
   
        for(int j = 0; j < noOfMacs; j++){
            for(int k = 0; k < i; k++){
                if(strcmp(OUI[k], transmitter[j])==0){
                    printf("%s\t%s\t%i\n", OUI[k], vendor[k], bytes[j]);
                    totalBytes -= bytes[j];
                }
            }
        }
    }
    else if (strcmp(condition, "r")==0){
   
        for(int j = 0; j < noOfMacs; j++){
            for(int k = 0; k < i; k++){
                if(strcmp(OUI[k], receiver[j])==0){
                    printf("%s\t%s\t%i\n", OUI[k], vendor[k], bytes[j]);
                    totalBytes -= bytes[j];
                }
            }
        }
    }
    if (totalBytes > 0){
        printf("??:??:??\tUNKNOWN-VENDOR\t%i\n",totalBytes);
    }
    
fclose(mfp);

    
fclose(vfp);
    return 0;

}

int main(int argc, char *argv[])
{

//ENSURE THAT WE HAVE THE REQUIRED NUMBER OF COMMAND-LINE ARGUMENTS


    if (argc == 3){                     //if 3 args, call first function
        readfile(argv[1],argv[2]);

    }
    else if (argc == 4){
        readfileOUI(argv[1], argv[2], argv[3]);     //if 4 args, call second function and execute
    }
    else{
        printf("Usage: %s file1 condition (file2)\n", argv[0]);    //otheriwse give an error

        exit(EXIT_FAILURE);

    }
}



