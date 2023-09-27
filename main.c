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
char buffer[MAX][MAX],string[MAX],statenum;
int buffindex=0,DFSM=1,position=-1,found,stringlength=0;

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
    printf("alphalength:%d\n",alphalength);


    //accessing the buffer
    //printf("\nseparate :%c\n",buffer[2][0]);

 
    int finalstatelength= strlen(buffer[buffindex-1]);

    //printf("final state: %s\t FSlength :%d FSarrayIndex:%d\n ",buffer[buffindex-1],finalstatelength,buffindex-1);


	
    // Open the second text file string.txt for reading
    FILE *file2 = fopen(argv[2], "r");
    if (file2 == NULL) 
    {
        perror("Check with string.txt Error opening the file");
        return 1;
    }

    // Read the string from the second text file
    fgets(string, sizeof(string), file2);
    string[strcspn(string, "\n")] = '\0'; // Remove newline character
    stringlength=strlen(string);

    // Close the first text file
    fclose(file2);
    
    //accessing character
    printf("string :%s  stringlength=%d\n\n", string,stringlength);

	
    //check that the given transition is valid DFSM or Not
    int V=0;
    for(int j=1;j<=alphalength;j++)
    {
        if(strlen(buffer[j])==alphalength)
        {
            //printf("buffer[%d]:%ld=alphalength:%d\n",j,strlen(buffer[j]),alphalength);
            V=0;
        }
        else{
            printf("transition is not valid state:%d length:%ld\n",j,strlen(buffer[j]));
	    printf("NO\n\n");
            V=1;
            exit(0); //can use exit(1);
        }
    }
	
    //printf("V=%d\n",V); //V is a flag to indicate that the given transition is invalid	



    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<DFSM Logic>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	if(stringlength==0)
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






        //check if the given string alphabets are in DFSM alphabets
	for(int i=0;i<stringlength;i++)
	{
		if(strchr(buffer[0],string[i]))
		{
			int temp=1;
		}
		else
		{
			printf("\n %c is not present in given DFSM specifications, the given String is NOT accepted by DFSM \n",string[i]);
			exit(0);
		}
	}


		//printf("\n all okay\n"); // debuging
		//DFSM Logic
        	for(int i=0;i<stringlength;i++)
        		{

            			char target = string[i];

            			int position = Verify_and_store_alphabet_position(buffer[0], target);

            			if (position != -1) {

                			//accessing the postion of alphabet
                			//printf("%c is present in Buffer[0] at position %d\n", target, position);

                			//DFSM
                			statenum=buffer[DFSM][position];
                			//covert character to integer and intialize to DFSM
                			DFSM=statenum-'0';
                			//printf("DFSM=%d\n",DFSM);


            			} 
            			else 
            			{
                			printf("\nNO \n");
            			}

        	}
		
		//Debugging and checking the values of finalstates, Present state, last state of DFSM after taking string as input
        	//printf("\n finatstates=%s  statenum=%c DFSM=%d\n",buffer[buffindex-1],statenum,DFSM);

        	if(strchr(buffer[buffindex-1],statenum))
        	{
            	printf("\nYES \n");
        	}
        	else
		{
            	printf("\nNO \n");
        	}

    	}
    	else
	{
        	printf("\n NO \n ");
    	}


//end of first else 
	}
	return 0;
}


