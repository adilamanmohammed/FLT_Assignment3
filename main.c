/*
Name : Adil Aman Mohammed
Course : Formal language theory
Assignment no: 3
CWID : A20395630
Description:
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 1000
char buffer[MAX][MAX],string[MAX],statenum,sbuff[MAX][MAX],newclasses[MAX][MAX],KA[1000],A[1000],noreach[1000],appendednum[MAX];
int buffindex=0,DFSM=1,position=-1,found,stringlength=0,sindex=0,scount=0,subcount=0;


//function to verify the alphabet is present and return the position for use of logic
int Verify_and_store_alphabet_position(const char *buffer, char target)
{
	//int position=-1;

	for(int i=0;i<strlen(buffer);i++)
	{
		if(buffer[i]==target)
		{
			position=i;
			break; //Searching Stopped once the position is found
		}
	}
	return position;

}


int belongs_to_which_equivalence_state(const char *string)
{
    int DFSM=1;

    int length=strlen(string);
    for(int i=0;i<length;i++)
    {
        int position =Verify_and_store_alphabet_position(buffer[0],string[i]);
        statenum=buffer[DFSM][position];
        //covert character to integer and intialize to DFSM
        DFSM=statenum-'0';

    }
    return DFSM;

}

void save_into_group(const char *string, char groupnum)
{
    char filename[1000];  // Adjust the size according to your needs
    sprintf(filename, "group_%d.txt", groupnum);

    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    fprintf(file, "%s\n", string);
    fclose(file);
}

void appendChar(char newclasses[], char ch) {
    // Find the null-terminator in the newclasses array
    int len = strlen(newclasses);

    // Append the character to the end of the array
    newclasses[len] = ch;
    
    // Null-terminate the new string
    newclasses[len + 1] = '\0';
}

int isValueInArray(const char *array, char value) {
    int len = strlen(array);

    for (int i = 0; i < len; i++) {
        if (array[i] == value) {
            return 1; // Value found in the array, return 1 as a flag
        }
    }

    return 0; // Value not found in the array, return 0 as a flag
}



void appendToAorKA(int x) {
    // Check if x is present in buffer[buffindex-1]
    char x_char = x + '0'; // Convert integer x to character
    int found = 0;

    for (int i = 0; buffer[buffindex - 1][i] != '\0'; i++) {
        if (buffer[buffindex - 1][i] == x_char) {
            found = 1;
            break;
        }
    }

    // Append x_char to KA or A based on the condition
    if (found) {
        strcat(A, &x_char);
    } else {
        strcat(KA, &x_char);
    }

    
}


void checkfornotreachablestate(char x)
{
    int f=0;
    for(int i=1;i<buffindex-1;i++)
    {
       
            if (strchr(buffer[i],x))
            {
                f=1;
                //printf(" f=%d for i=%d\n",f,i);
            }
            else{
                //printf(" f=%d for i=%d\n",f,i);
            }
    
    }

    if(f==0)
    {
        appendChar(noreach,x);
    }
}





int isCharacterPresent(const char *array, char target) {
    while (*array != '\0') {
        if (*array == target) {
            return 1; // Character found in the array
        }
        array++;
    }
    
    return 0; // Character not found in the array
}



int findStringLength(char array[MAX][MAX][MAX], int i, int j) {
    return strlen(array[i][j]);
}














//main function
int main(int argc, char *argv[])
{
	//verifying the command line argument
    if(argc!=3)
    {
        printf("The given no.of arguments are incorrect please check your arguments in command line:\n");
    }
    else
    {

    //printf("%s\t%s\n",argv[1],argv[2]); //printing the input files names


    //open the 1nd file DFSM.txt
    FILE *file1 = fopen(argv[1], "r");
    if (file1 == NULL) 
    {
        perror("Check with string.txt Error opening the file");
        return 1;
    }

    

    //Read lines and store non-empty lines (excluding lines with only spaces)
    while (fgets(buffer[buffindex], MAX, file1)) {
        int length = strlen(buffer[buffindex]);

        // Remove spaces from the line and store only non-space characters
        int newLength = 0;
        for (int i = 0; i < length; i++) {
            if (buffer[buffindex][i] != ' ' && buffer[buffindex][i] != '\n') {
                buffer[buffindex][newLength] = buffer[buffindex][i];
                newLength++;
            }
        }
        buffer[buffindex][newLength] = '\0'; // Null-terminate the modified line

        if (newLength > 0) {
            buffindex++;
        }
    }
    
    //Closing file 1
    fclose(file1);

    //printing the buffer index
    printf("bufferindex:%d\n\n",buffindex);


    //printing the stored non-empty lines
    for (int i = 0; i < buffindex; i++) {
       printf("buffer[%d]: %s\n", i, buffer[i]);
    }

    //aphalet Length defining
    int alphalength=strlen(buffer[0]);
    printf("alphalength:%d\n\n",alphalength);


    //accessing the buffer
    //printf("\nseparate :%c\n",buffer[2][0]);

 
    int finalstatelength= strlen(buffer[buffindex-1]);

    printf("final state: %s\t FSlength :%d FSarrayIndex:%d\n ",buffer[buffindex-1],finalstatelength,buffindex-1);


	
    // Open the second text file string.txt for reading
    FILE *file2 = fopen(argv[2], "r");
    if (file2 == NULL) 
    {
        perror("Check with string.txt Error opening the file");
        return 1;
    }

    //store list of strings
    while (fgets(sbuff[sindex], MAX, file2)) {
        int length = strlen(sbuff[sindex]);

        // Remove spaces from the line and store only non-space characters
        int newLength = 0;
        for (int i = 0; i < length; i++) {
            if (sbuff[sindex][i] != ' ' && sbuff[sindex][i] != '\n') {
                sbuff[sindex][newLength] = sbuff[sindex][i];
                newLength++;
            }
        }
        sbuff[sindex][newLength] = '\0'; // Null-terminate the modified line

        if (newLength > 0) {
            sindex++;
        }
    }

    for (int i = 0; i < sindex; i++) {
       printf("sbuff[%d]: %s\n", i, sbuff[i]);
    }
    //printf("\nSindex=%d \n",sindex);


    // Close the first text file
    fclose(file2);
    
	
    //check that the given transition is valid DFSM or Not
    int V=0;
    for(int j=1;j<buffindex-1;j++)
    {
        if(strlen(buffer[j])==alphalength)
        {
            //printf("buffer[%d]:%ld=alphalength:%d\n",j,strlen(buffer[j]),alphalength);
            V=0;
        }
        else{
            printf("transition is not valid \n");
	    printf("NO\n\n");
            V=1;
            exit(0); //can use exit(1);
        }
    }
	
    printf("V=%d\n",V); //V is a flag to indicate that the given transition is invalid	



    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<DFSM Logic>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	if(sindex==0)
	{
		printf("\nstring.txt is empty\n");
	}
	else if(buffindex==0)
	{
		printf("\nDFSM.txt is empty\n");
	}
	else if(V!=1)
	{

        //check if all the transitions are valid transition
    for(int i=1;i<buffindex-1;i++)
    {
        for(int j=0;j<alphalength;j++)
        {
            if (buffer[i][j] >= '0' + buffindex-1)
            {
                printf("error %c is not a valid state transition DFSM is invalid",buffer[i][j]);
                exit(0);
            }
        }
    }

    //check if all the list of string alphabets in given alphabet list 
    for(int i=0;i<sindex;i++)
    {
        for(int j=0;j<strlen(sbuff[i]);j++)
        {
            if(strchr(buffer[0],sbuff[i][j]))
            {
                
            }
            else
            {
                printf("\nstring[%d][%d]:%c is not in alphabet list\n",i,j,sbuff[i][j]);
                exit(0);
            }
        }

    }

    //check if given final states are valid for given DFSM
    for(int i=0;i<strlen(buffer[buffindex-1]);i++)
    {
        if(buffer[buffindex-1][i] > '0'+buffindex-2 && buffer[buffindex-1][i]!='0')
        {
            printf("DFSM invalid\n");
            exit(0);
        }

    }

    // Create text files
    /*for (int fileNumber = 1; fileNumber <= buffindex-2; fileNumber++) {
        char filename[50];
        sprintf(filename, "group_%d.txt", fileNumber); 
        
        
        FILE *file = fopen(filename, "w");

        if (file == NULL) {
            printf("Failed to create %s\n", filename);
        } else {
            //printf("%s created successfully\n", filename);
            fclose(file); 
        }
    }*/


    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<Actual logic >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    //removing not reachable states from sate 2 to last state
    for(int i=2;i<buffindex-1;i++)
    {
        char char_i = i + '0';
        checkfornotreachablestate(char_i);
        //printf(" %c\n",char_i);
    }
    

    //append to A or KA
    for(int i=1;i<buffindex-1;i++)
    {
        char char_i = i + '0';

        if(strchr(noreach,i+'0'))
        {

        }
        else
        appendToAorKA(i);
    }
    // Print A and KA
    printf("A: %s\n", A);
    printf("KA: %s\n", KA);
    printf("no reach: %s\n\n", noreach);

    printf("for non final:\n");
    //check and make eqivalence states for non final logic
    for(int i=1;i<buffindex-1;i++)
    {   subcount=0;
        int infinal=isCharacterPresent(A,i+'0');
        int flag=isCharacterPresent(appendednum,i+'0');
        if(flag==1 || infinal==1)
        {
            printf("skip@%d\n",i);
        }
        else if(i==buffindex-2)
        {
            newclasses[scount][subcount]=i+'0';
            appendChar(appendednum,i+'0');
            //printf("newclass[%d][%d]=%c\n",scount,subcount,i+'0');
            scount++;
        }
        else
        {
            int tflag=0;
            int len=strlen(newclasses[scount]);
            if(len==0)
            {
                newclasses[scount][subcount]=i+'0';
                appendChar(appendednum,i+'0');
                tflag++;
                subcount++;
            }
            
            for(int j=i+1;j<buffindex-1;j++)
            {
                /*if(j==buffindex-1)
                {
                    newclasses[scount][subcount]=i+'0';
                    appendChar(appendednum,i+'0');
                    tflag++;
                    subcount++; 
                }
                else
                {*/
                int finalflag=isCharacterPresent(A,j+'0');
                if(finalflag!=1)
                {
                    int compare=strcmp(buffer[i],buffer[j]);
                    if(compare==0)
                    {
                        newclasses[scount][subcount]=j+'0';
                        appendChar(appendednum,j+'0');
                        tflag++;
                        subcount++;
                    }
                }
                    
                //}
            }

            if(tflag!=0)
            {
                scount++;
            }
        }
        
        
    }



    printf("for final states:\n");
    //check and make eqivalence states for non final logic
    for(int i=1;i<buffindex-1;i++)
    {   subcount=0;
        int innonfinal=isCharacterPresent(KA,i+'0');
        int flag=isCharacterPresent(appendednum,i+'0');
        if(flag==1 || innonfinal==1)
        {
            printf("skip@%d\n",i);
        }
        else if(i==buffindex-2)
        {
            newclasses[scount][subcount]=i+'0';
            appendChar(appendednum,i+'0');
            //printf("newclass[%d][%d]=%c\n",scount,subcount,i+'0');
        }
        else
        {
            int tflag=0;
            int len=strlen(newclasses[scount]);
            if(len==0)
            {
                newclasses[scount][subcount]=i+'0';
                appendChar(appendednum,i+'0');
                tflag++;
                subcount++;
            }
            
            for(int j=i+1;j<buffindex-1;j++)
            {
                /*if(j==buffindex-1)
                {
                    newclasses[scount][subcount]=i+'0';
                    appendChar(appendednum,i+'0');
                    tflag++;
                    subcount++; 
                }
                else
                {*/
                int nonfinalflag=isCharacterPresent(KA,j+'0');
                if(nonfinalflag!=1)
                {
                    int compare=strcmp(buffer[i],buffer[j]);
                    if(compare==0)
                    {
                        newclasses[scount][subcount]=j+'0';
                        appendChar(appendednum,j+'0');
                        tflag++;
                        subcount++;
                    }
                }
                    
                //}
            }

            if(tflag!=0)
            {
                scount++;
            }
        }
        
        
    }


    printf("\n");
   //check debug loop
    for (int i = 0; i < scount; i++) {
       printf("newclasses[%d]: %s\n", i, newclasses[i]);
    }

   
    printf("append: %s\n",appendednum);
    printf("scount: %d\n",scount);


    //check strings.txt and check each string belongs to which group




















    for(int i=0;i<sindex;i++)
    {
        int class_state=belongs_to_which_equivalence_state(sbuff[i]);
        //printf("%d \n", class_state);
        //save_into_group(sbuff[i],class_state);

    }














    }
    	

//end of first else 
	}
	return 0;
}


