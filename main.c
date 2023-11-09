/*
Name : Adil Aman Mohammed
Course : Formal language theory
Assignment no: 3
CWID : A20395630
Description: The following code is logic for implementing the Minimization of DFSM and finding the equivalence classes then grouping the given strings.
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 1000
char buffer[MAX][MAX][MAX],string[MAX],statenum,sbuff[MAX][MAX],newclasses[MAX][MAX],KA[1000],A[1000],noreach[1000],appendednum[MAX],notreachable[MAX];
int buffindex=0,DFSM=1,position=-1,found,sindex=0,scount=0,subcount=0,alphalength,marked[MAX] = {0},    fileIndex = 0,charIndex;

/*
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

//used to flag the states which are reachable
void mark_state_which_are_reachable(int currentState, int* marked, int numStates,int symbol) {
    marked[currentState] = 1;

    for (int i = 0; i < symbol; i++) {
        int nextState = buffer[currentState][i] - '0'; 
        if (nextState >= 1 && nextState <= numStates && !marked[nextState]) {
            mark_state_which_are_reachable(nextState, marked, numStates,symbol);
        }
    }
}

//check if the string belongs to which equivalence_state
int belongs_to_which_equivalence_state(const char *string)
{
    int DFSM=1;

    int length=strlen(string);
    for(int i=0;i<length;i++)
    {
        int position =Verify_and_store_alphabet_position(buffer[0],string[i]);
        statenum=buffer[DFSM][position];
        //coverting character to integer and intialize to DFSM
        DFSM=statenum-'0';

    }
    return DFSM;

}

void savegroup(const char *string, char groupnum)
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

void append_character(char newclasses[], char ch) {
    // Find the null-terminator in the newclasses array
    int len = strlen(newclasses);

    // Append the character to the end of the array
    newclasses[len] = ch;
    
    // Null-terminate the new string
    newclasses[len + 1] = '\0';
}


// Checking if x is present in buffer[buffindex-1]
void appendToAorKA(int x) {

    // Convert integer x to character
    char x_char = x + '0'; 
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



int find_character_present_in_array(const char *array, char target) {
    while (*array != '\0') {
        if (*array == target) {
            // Character found in the array
            return 1; 
        }
        array++;
    }
    
    return 0; // Character not found in the array
}



int checkgroup(int character) {
    int foundRow = -1; // Initialize to -1 to indicate not found
    char A=character+'0';

    for(int i=0;i<scount;i++)
    {
        if(find_character_present_in_array(newclasses[i],A)==1)
        {
            return i;
            break;
        }
    }
    
}


*/


int stringcount(int A)
{
    int x=0;
    for (int j = 0; j < MAX && buffer[A][j][0] != '\0'; j++) 
    {
    x++;
    }
    return x;
}

void printcontent(char buffer[][MAX][MAX],int buffindex,int A)
{
    for (int i = A; i < buffindex; i++) {
        printf("buffer[%d]:",i);
        for (int j = 0; j < MAX && buffer[i][j][0] != '\0'; j++) {
            printf("%s ", buffer[i][j]);
        }
        printf("\n");
    }
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
        perror("Check with DFSM.txt Error opening the file");
        return 1;
    }

    

    
    char line[MAX * MAX]; // Buffer to hold each line of text, assuming each token can be up to MAX characters

    // Read lines and store each token as a string in the buffer
    while (fgets(line, sizeof(line), file1)) {
        // Check if the line is not just a newline or space
        if (strspn(line, " \t\r\n") != strlen(line)) {
            char *token = strtok(line, " \t\n");
            int tokenIndex = 0;
            while (token != NULL && tokenIndex < MAX) {
                strncpy(buffer[buffindex][tokenIndex], token, MAX);
                buffer[buffindex][tokenIndex][MAX - 1] = '\0'; // Ensure null-termination
                tokenIndex++;
                token = strtok(NULL, " \t\n");
            }
            if (tokenIndex > 0) { // If at least one token was found
                buffindex++;
            }
        }

        if (buffindex >= MAX) {
            // Handle the case where the maximum number of lines has been reached
            break;
        }
    }

    //Closing file 1
    fclose(file1);

    //printing the buffer index
    printf("bufferindex:%d\n\n",buffindex);

    //Print the contents of the buffer
    printcontent(buffer,buffindex,0);
    
    //aphalet Length defining
    alphalength=stringcount(0);
    printf("\nalphalength:%d\n",stringcount(0));


    //accessing the buffer
    printf("\nAccess buffer[12][0] :%s\n",buffer[12][0]);

    
    int finalstatelength= stringcount(buffindex-1);
    //debug
    printf("\nFSlength :%d FSarrayIndex:%d\nfinal states: \n",finalstatelength,buffindex-1);
    printcontent(buffer,buffindex,buffindex-1);



    //Opening the second text file string.txt for reading
    FILE *file2 = fopen(argv[2], "r");
    if (file2 == NULL) 
    {
        perror("Check with string.txt Error opening the file");
        return 1;
    }

    //storing list of strings in sbuff
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

    printf("\n");
    for(int i = 0; i < sindex; i++) {
       printf("sbuff[%d]: %s\n", i, sbuff[i]);
    }
    printf("\nSindex=%d \n\n",sindex);


    // Close the first text file
    fclose(file2);
    
	
    //check that the given transition is valid DFSM or Not
    int V=0;
    for(int j=1;j<buffindex-1;j++)
    {
        if(stringcount(j)==alphalength)
        {
            //printf("buffer[%d]:%d=alphalength:%d\n",j,stringcount(j),alphalength);
            V=0;
        }
        else{
            printf("transition is not valid \n");
             printf("buffer length of buffer[%d]:%d!=alphalength:%d\n",j,stringcount(j),alphalength);
	    printf("NO\n\n");
            V=1;
            exit(0); //can use exit(1);
        }
    }


	
    printf("V=%d\n",V); //V is a flag to indicate that the given transition is invalid	



    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<Logic to check DFSM is valid>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

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
    // Check if all the transitions are valid transitions
    for (int i = 1; i < buffindex - 1; i++) {
        for (int j = 0; j < alphalength; j++) {
            // Convert the string at buffer[i][j] to an integer
            int state = atoi(buffer[i][j]);
            // Check if the state is within the valid range
            if (state >= buffindex - 1) {
                printf("error %s is not a valid state transition; DFSM is invalid\n", buffer[i][j]);
                exit(0);
            }
        }
    }



    // Check if all the characters of strings in sbuff are in the given alphabet list
    char alphabetList[MAX] = {0};
    for (int i = 0; buffer[0][i][0] != '\0' && i < MAX; i++) {
        strcat(alphabetList, buffer[0][i]);
    }
    
    // Check if all the characters of strings in sbuff are in the given alphabet list
    for (int i = 0; i < sindex; i++) {
        for (int j = 0; j < strlen(sbuff[i]); j++) {
            if (strchr(alphabetList, sbuff[i][j]) == NULL) {
                // If the character is not found in the alphabet list
                printf("\nstring[%d][%d]:%c is not in alphabet list\n", i, j, sbuff[i][j]);
                exit(0);
            }
        }
    }





    //check if given final states are valid for given DFSM
    for(int i=0;i<stringcount(buffindex-1);i++)
    {
        if(atoi(buffer[buffindex-1][i]) > buffindex-2)
        {
            printf("DFSM invalid\n");
            exit(0);
        }

    }


/*
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<Actual logic >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    //removing not reachable states from state 2 to last state


    //Doing DFS from state 1 and removing not reachable states from state 2 to last state
    mark_state_which_are_reachable(1, marked, buffindex-2,alphalength);  // Since you mentioned transition[1] is initial state and your indexing is 1-based.

    // Printing the unreachable states
    for (int i = 1; i <= buffindex-2; i++) 
    {   // Using 1-based indexing loop
        if (!marked[i]) {
            append_character(noreach,i+'0');
        }
    }

    //debug norech
    //printf("Unreachable states: ");
    for(int i=0;i<strlen(noreach);i++)
    {
        printf(" %c",noreach[i]);
    }
    printf("\n");

    

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
    //Print A and KA
    //printf("A: %s\n", A);
    //printf("KA: %s\n", KA);
    //printf("no reach: %s\n\n", noreach);

    //printf("for non final:\n");
    //check and make eqivalence states for non final logic
    for(int i=1;i<buffindex-1;i++)
    {   subcount=0;
        int infinal=find_character_present_in_array(A,i+'0');
        int flag=find_character_present_in_array(appendednum,i+'0');
        int noreachflag=find_character_present_in_array(noreach,i+'0');
        if(flag==1 || infinal==1 || noreachflag==1)
        {
            //printf("skip@%d\n",i);
        }
        else if(i==buffindex-2)
        {
            newclasses[scount][subcount]=i+'0';
            append_character(appendednum,i+'0');
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
                append_character(appendednum,i+'0');
                tflag++;
                subcount++;
            }
            
            for(int j=i+1;j<buffindex-1;j++)
            {
                
                int finalflag=find_character_present_in_array(A,j+'0');
                if(finalflag!=1)
                {
                    int compare=strcmp(buffer[i],buffer[j]);
                    if(compare==0)
                    {
                        newclasses[scount][subcount]=j+'0';
                        append_character(appendednum,j+'0');
                        tflag++;
                        subcount++;
                    }
                }
                    
                
            }

            if(tflag!=0)
            {
                scount++;
            }
        }
        
        
    }



    //printf("for final states:\n");
    //check and make eqivalence states for non final logic
    for(int i=1;i<buffindex-1;i++)
    {   subcount=0;
        int in_non_final=find_character_present_in_array(KA,i+'0');
        int flag=find_character_present_in_array(appendednum,i+'0');
        int noreachflag=find_character_present_in_array(noreach,i+'0');
        if(flag==1 || in_non_final==1 || noreachflag==1)
        {
            //skip if not in appended or in in final or if in no reach
            //printf("skip@%d\n",i);
        }
        else if(i==buffindex-2)
        {
            newclasses[scount][subcount]=i+'0';
            append_character(appendednum,i+'0');
            //printf("newclass[%d][%d]=%c\n",scount,subcount,i+'0');
        }
        else
        {
            int tflag=0;
            int len=strlen(newclasses[scount]);
            if(len==0)
            {
                newclasses[scount][subcount]=i+'0';
                append_character(appendednum,i+'0');
                tflag++;
                subcount++;
            }
            
            for(int j=i+1;j<buffindex-1;j++)
            {
                int nonfinalflag=find_character_present_in_array(KA,j+'0');
                if(nonfinalflag!=1)
                {
                    int compare=strcmp(buffer[i],buffer[j]);
                    if(compare==0)
                    {
                        newclasses[scount][subcount]=j+'0';
                        append_character(appendednum,j+'0');
                        tflag++;
                        subcount++;
                    }
                }
                    
                
            }

            if(tflag!=0)
            {
                scount++;
            }
        }
        
        
    }


    //printf("\n");
   //check debug loop
    printf("These are the new equivalence states:\n");
    for (int i = 0; i < scount; i++) {
       printf("newclasses[%d]: %s\n", i+1, newclasses[i]);
    }
    printf("Note: With respect to above state-numbers group numbers are given\n");
    //debug
    //printf("append: %s\n",appendednum);
    //printf("scount: %d\n\n",scount);


    //check strings.txt and check each string belongs to which group
    for(int i=0;i<sindex;i++)
    {
        int class_state=belongs_to_which_equivalence_state(sbuff[i]);
        int check=checkgroup(class_state);
        //printf("%s belongs : %d , and final is %d\n",sbuff[i], class_state,check);
        savegroup(sbuff[i],check+1);

    }

    }

    //end of first else 
	} 
*/
	return 0;

    }
}
}
