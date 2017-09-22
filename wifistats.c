/*
   CITS2002 Project 1 2017
   Name(s):             Mohamed Abdinasir ( Harrison Carter-Turner )
   Student number(s):   22046631 (, student-number2)
   Date:                Friday 22 Sept 2017
*/

#include <stdio.h>

#include <stdlib.h>

#include <string.h>



#include <ctype.h>
#define Macs	500     // Maximum number of Mac Addrresses

#define OUIs	25000   // Max number of OUIs
#define vname   90      // Max length of vendor name

#define LINESIZE 128    //Maximum linesize of file


//  READ THE SCENARIO FILE 
int read_scenario_file1 (char condition[], char filename[]){

    char transmitter[Macs][48]; //Mac addresses require exactly 48 bytes;

    char receiver[Macs][48];

    char tHold[48]; // i.e. transmitterHold
    char rHold[48]; // i.e. receivererHold
    char bHold[16]; // i.e. bytesHold
    int noOfMacs = 0;   
    char *value;    //pointer, each value will be passed to and stored in either rHold,tHold or bHold
    int bytes[Macs];
    char line[LINESIZE];

    int i = 0;

    //  ATTEMPT TO OPEN NAMED FILE
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        perror(filename);
        exit(EXIT_FAILURE);
    }
    //  READ Macs UNTIL END-OF-FILE REACHED
    while(fgets(line, sizeof(line), fp)){ 
        value = strtok(line, "\t");
        value = strtok(NULL, "\t");
        strcpy(tHold, value);
  

        
        value = strtok(NULL, "\t");
    //store the value pointed to by "value" in rHold
        strcpy(rHold, value); 

        value = strtok(NULL, "\n");
        //store the value pointed to by "value" in rHold
        strcpy(bHold, value); 
     
//Detect the conditions, t for transmiter and r for receiver
     
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
        //go to the next line   
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

//  READ THE SCENARIO FILE
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
    //  READ EVENTS UNTIL END-OF-FILE REACHED    
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

        value = strtok(line, "\t");         // Read untill we encounter a tab character
        value = strtok(NULL, "\t");
        strcpy(tHold, value);               //Copy that value into tHold     
        tHold[8] = '\0';

        value = strtok(NULL, "\t");         // Read untill we encounter a tab character

        strcpy(rHold, value);               //Copy that value into rHold
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
    //go to the next line
    i++;

    }
    i = 0;

    //  READ EVENTS UNTIL END-OF-FILE REACHED
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

//  END OF SCENARIO FILE, CLOSE FILE,     
fclose(mfp);

    
fclose(vfp);
    return 0;

}

int main(int argc, char *argv[])
{

//ENSURE THAT WE HAVE THE REQUIRED NUMBER OF COMMAND-LINE ARGUMENTS


    if (argc == 3){                     //if 3 args, call first function
        read_scenario_file1(argv[1],argv[2]);

    }
    else if (argc == 4){
        readfileOUI(argv[1], argv[2], argv[3]);     //if 4 args, call second function and execute
    }
    else{
        printf("Usage: %s file1 condition (file2)\n", argv[0]);    //otheriwse give an error

        exit(EXIT_FAILURE);

    }
}



