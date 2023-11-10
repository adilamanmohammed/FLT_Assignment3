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
#include <stdbool.h>
#define MAX 1000
char buffer[MAX][MAX][MAX],string[MAX],statenum,sbuff[MAX][MAX],newclasses[MAX][MAX],notreachable[MAX];
int buffindex=0,DFSM=1,position=-1,found,sindex=0,scount=0,subcount=0,appended_count=0,alphalength,marked[MAX] = {0},appendednum[MAX],size=0,    fileIndex = 0,charIndex,noreach[1000],KA[1000],A[1000],A_count = 0,KA_count = 0;


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


bool visited[MAX] = {false}; // Keep track of visited states

void dfs(int state, char buffer[][MAX][MAX], int numStates, int alphalength) {
    visited[state] = true;
    for (int i = 0; i < alphalength; i++) {
        int nextState = atoi(buffer[state + 1][i]); // Already 1-based indexing from buffer
        if (nextState > 0 && nextState <= numStates && !visited[nextState - 1]) { // Convert to 0-based index for visited
            dfs(nextState - 1, buffer, numStates, alphalength);
        }
    }
}


int findNonReachableStates(char buffer[][MAX][MAX], int numStates, int alphalength, int noreach[]) {
    // Fill the visited array by running dfs starting from state 1 (which is the first state in buffer[1])
    dfs(0, buffer, numStates, alphalength);

    int count = 0;
    for (int i = 0; i < numStates; i++) {
        if (!visited[i]) {
            noreach[count++] = i + 1; // Store non-reachable states as 1-based index
        }
    }
    return count; // Return the count of non-reachable states
}

void printNonReachableStates(int noreach[], int count) {
    printf("Non-reachable States: ");
    if (count == 0) {
        printf("None\n");
    } else {
        for (int i = 0; i < count; i++) {
            printf("%d ", noreach[i]);
        }
        printf("\n");
    }
}



bool isInNoReach(int state, int noreach[], int count) {
    for (int i = 0; i < count; i++) {
        if (noreach[i] == state) {
            return true;
        }
    }
    return false;
}

bool isFinalState(int state, int A[], int A_count) {
    for (int i = 0; i < A_count; i++) {
        if (A[i] == state) {
            return true;
        }
    }
    return false;
}

int findNonFinalReachableStates(int numStates, int noreach[], int nonReachableCount, int A[], int A_count, int KA[]) {
    int KA_count = 0;
    for (int state = 1; state <= numStates; state++) {
        if (!isInNoReach(state, noreach, nonReachableCount) && !isFinalState(state, A, A_count)) {
            KA[KA_count++] = state;
        }
    }
    return KA_count;
}



// Function to find if an integer is present in an array
int find_integer_present_in_array(const int A[], int size, int target) {
    for (int j = 0; j < size; j++) {
        if (A[j] == target) {
            return 1; // Integer found in the array
        }
    }
    return 0; // Integer not found in the array
}

void append_character(char newclasses[], char ch) {
    // Find the null-terminator in the newclasses array
    int len = strlen(newclasses);

    // Append the character to the end of the array
    newclasses[len] = ch;
    
    // Null-terminate the new string
    newclasses[len + 1] = '\0';
}





void append_integer(int array[], int *size, int value) {
    // Add the integer to the end of the array
    array[*size] = value;
    (*size)++; // Increase the size of the array
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

    // Read the file line by line
    while (fgets(line, sizeof(line), file1)) {
        // Ignore empty lines
        if (strcmp(line, "\n") != 0) {
            int col = 0;
            // Split the line by spaces and store each part in the buffer
            char *token = strtok(line, " ");
            while (token) {
                if (strlen(token) > 0) {
                    // Remove new line characters if present
                    token[strcspn(token, "\n")] = 0;
                    strcpy(buffer[buffindex][col], token);
                    col++;
                }
                token = strtok(NULL, " ");
            }
            buffindex++;
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

    int nonReachableCount = findNonReachableStates(buffer, buffindex - 2, alphalength, noreach); // Use buffindex - 2 because last line is final states
    printNonReachableStates(noreach, nonReachableCount);


    A_count = 0; // Initialize the counter for number of final states
    for (int i = 0; buffer[buffindex - 1][i][0] != '\0'; i++) {
        A[A_count++] = atoi(buffer[buffindex - 1][i]); // Convert string to int and store in A
    }

    // Print the final states stored in A
    printf("A: ");
    for (int i = 0; i < A_count; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");


    /*for(int i=0;i<buffindex;i++)
    {
        for(int j=0;j<alphalength;j++)
        {
           printf("\nbuffer[%d][%d]:%s",i,j,buffer[i][j]); 
        }
    }*/
    
    //printf("\n\n%s\n",buffer[12][0]);

    // Find non-final, reachable states
    KA_count = findNonFinalReachableStates(buffindex - 2, noreach, nonReachableCount, A, A_count, KA);

    // Print the non-final, reachable states
    printf("KA: ");
    for (int i = 0; i < KA_count; i++) {
        printf("%d ", KA[i]);
    }
    printf("\n");


    printf("For non final :\n");
    //check and make eqivalence states for non final logic
    for(int i=1;i<buffindex-1;i++)
    {   subcount=0;
        printf("entered logic A@%d\n",i);
        int infinal=find_integer_present_in_array(A,A_count,i);
        int flag = find_integer_present_in_array(appendednum, size, i );
        printf("flag=%d\n",flag);
        int noreachflag=find_integer_present_in_array(noreach,nonReachableCount,i);
        if(flag==1 || infinal==1 || noreachflag==1)
        {
            printf("skip@%d\n",i);
        }
        else if(i==buffindex-2)
        {
            newclasses[scount][subcount]=i+'0';
            append_integer(appendednum,&size,i);
            appended_count++;
            printf("appended %d@i=%d\n",i,i);
            printf("newclass[%d][%d]=%c\n",scount,subcount,i+'0');
            scount++;
        }
        else
        {
            int tflag=0;
            int len=strlen(newclasses[scount]);
            if(len==0)
            {
                newclasses[scount][subcount]=i+'0';
                append_integer(appendednum,&size,i);
                appended_count++;
                printf("appended %d@i=%d\n",i,i);
                tflag++;
                subcount++;
            }
            
            for(int j=i+1;j<buffindex-1;j++)
            {
                
                int finalflag=find_integer_present_in_array(A,A_count,j);
                if(finalflag!=1)
                {
                    int compare=strcmp(buffer[i][0],buffer[j][0]);
                    if(compare==0)
                    {
                        newclasses[scount][subcount]=j+'0';
                        append_integer(appendednum,&size,j);
                        appended_count++;
                        printf("appended %d@i=%d\n",j,i);
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

printf("\n\n");


printf("For final :\n");
//check and make eqivalence states for final logic
    for(int i=1;i<buffindex-1;i++)
    {   subcount=0;
        printf("entered logic A@%d\n",i);
        int in_non_final=find_integer_present_in_array(KA,KA_count,i);
        int flag = find_integer_present_in_array(appendednum, size, i );
        printf("flag=%d\n",flag);
        int noreachflag=find_integer_present_in_array(noreach,nonReachableCount,i);
        if(flag==1 || in_non_final==1 || noreachflag==1)
        {
            printf("skip@%d\n",i);
        }
        else if(i==buffindex-2)
        {
            newclasses[scount][subcount]=i+'0';
            append_integer(appendednum,&size,i);
            appended_count++;
            printf("appended %d@i=%d\n",i,i);
            printf("newclass[%d][%d]=%c\n",scount,subcount,i+'0');
            scount++;
        }
        else
        {
            int tflag=0;
            int len=strlen(newclasses[scount]);
            if(len==0)
            {
                newclasses[scount][subcount]=i+'0';
                append_integer(appendednum,&size,i);
                appended_count++;
                printf("appended %d@i=%d\n",i,i);
                tflag++;
                subcount++;
            }
            
            for(int j=i+1;j<buffindex-1;j++)
            {
                
                int finalflag=find_integer_present_in_array(KA,KA_count,j);;
                if(finalflag!=1)
                {
                    int compare=strcmp(buffer[i][0],buffer[j][0]);
                    if(compare==0)
                    {
                        newclasses[scount][subcount]=j+'0';
                        append_integer(appendednum,&size,j);
                        appended_count++;
                        printf("appended %d@i=%d\n",j,i);
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



















printf("\n");
    for (int i = 0; i < size; i++) {
       printf("appendednum[%d]: %d\n", i, appendednum[i]);
    }
    




//check debug loop
    printf("These are the new equivalence states:\n");
    for (int i = 0; i < scount; i++) {
       printf("newclasses[%d]: %s\n", i+1, newclasses[i]);
    }
    printf("Note: With respect to above state-numbers group numbers are given\n");




    




    
    }


    }


return 0;
}
