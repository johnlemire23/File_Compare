/*******************************************

Student Name: John Lemire
File Name: GetFiles.c
Project 1, Comparing Files

Contains methods to process input files, scrape data from files
Also contains main "processFile" command which parses phrases from file contents buffer

********************************************/


#include "headers.h"
#include "hashmethods.h"

// **********************
// 
// input: 2d char array, and int pointer
// opens input.txt and parses the files into the array
// updates numvalues with number of files

void fileList(char fileBuffer[][30], int *numFiles){

	//file pointer
	//loop int

	FILE * input;
	int i;
	
	//get info from ls and output it to input.txt
	//point input to file
	
	system ("ls ./datafiles/ > input.txt");
	input = fopen("input.txt","r");

	//get line of input from file store in buffer
	//store input in buffer
	//increment numFiles location one

	for(i=1;fgets(fileBuffer[i-1], 49, input);i++){
		//fprintf(stdout,"File %i %s",i,fileBuffer[i-1]);
		strtok(fileBuffer[i-1],"\n");	
		*numFiles=i;	
	}
	//null nerminate last line 

	fileBuffer[i][0]='\0';
}

//******************
// processfile
// this is the meat of the program, a lot here
// input: pointer to hash table, char array with file contents, counter with phrase length
// input (cont): first flag denotes first few words of file, 
// (cont):  compare flag denotes if it is the file to hash and store or hash and compare (1 and -1)
//

int processFile(table_e *newHtable,char currentBuffer[], int pCounter, int firstFlag, int compareFlag){

	// int for few loop variabls
	// int for match
	// token pointer
	// 2d char array 

	int m = 0;
	int k = pCounter;
	int match=0;
	char *token;
	char tokenArray[pCounter][60];

	//do initial strtok then it drops into a loop to tokenize the rest of the file
	// we store [phraseLength] tokens in a buffer, 
	// next we hash them, then either (store or compare) the hashed strings
	

	token = strtok(currentBuffer," *.,\n");

	while (token != NULL){

		// if first flag = 1, its the start of the buffer
		// fill buffer[phraseLength] with tokens
		// turn first flag to 0;
	
		if(firstFlag==1){

			while(m<pCounter && token != NULL){

				strcpy(tokenArray[m],token);
				token = strtok(NULL, " *.,\n");	
				m++;
				k=m;
			}

			firstFlag--;
		}

		// upon subsequent token calls, we simply shift each item in the buffer up one
		// then add the next token to the bottom, this forms our new phrase
		// this continues until end of file buffer
		
		else {
		
			for(m=0;m<k;m++){
				strcpy(tokenArray[m],tokenArray[m+1]);
			}

			strcpy(tokenArray[k-1],token);
			token = strtok(NULL, " *.,\n");
		}

		// create string{char array) to hold new tokenized buffer
		// strcat buffer contents into char array

		char string2hash[20*pCounter];

		for(m=0;m<k;m++){
			strcat(string2hash,tokenArray[m]);
		}

		//store hashed value in hashv

		int hashv = hash(string2hash);

		// if this is the file to be compared to subsequent files
		// we either store it in the hash table at [index = hash value]
		// or if the [index] has a string already we create a new node
		// and add the new string to it
		// 
		// otherwise its the compare file and we compare its string to the hash

		if ( compareFlag == 1 && newHtable->entry[hashv]->hashedString == NULL){
			newHtable->entry[hashv]=createEntry(string2hash);
		}

		else if (compareFlag == 1){
			putEntry(string2hash, newHtable->entry[hashv]);
		}

		else if (compare(string2hash,newHtable->entry[hashv])){			
			match++;
		}

	}

	//return the amount of matches

	return match;
}

//************************************
// 
// file contents returns a pointer to a newly created and allocated buffer
// input: file name of file to copy contents on
// 


char * fileContents(char filename[]){
	
	char path2File[50];
	int sizeOfFile;
	FILE * pCurrentFile;

	strcpy(path2File, "./datafiles/");
	strcat(path2File, filename);

	// Opens file in binary mode
	// gets size of file and creates a buffer 
	//then points back to top of file

	pCurrentFile = fopen(path2File, "rb");
	fseek(pCurrentFile,0L,SEEK_END);
	sizeOfFile=ftell(pCurrentFile);

	char currentBuffer[sizeOfFile+1];
	char * pBuffer;
	pBuffer = malloc(sizeof(currentBuffer));
	rewind(pCurrentFile);

	//	copys content from file and puts in newly allocated buffer

	if (fread(currentBuffer,sizeof(currentBuffer), 1, pCurrentFile)){
		fprintf(stderr, "Error writing data stream");
	}

	// puts null at end of buffer for cleanliness
	// copy contents of buffer to location pointed at by pBuffer

	currentBuffer[sizeof(currentBuffer)-1]='\0';
	strcpy(pBuffer,currentBuffer);

	// closes file
	// returns pointer

	fclose(pCurrentFile);
	return pBuffer;
}

//****************************
//
// opens file and scans ints length
// returns size of file as int
//

int getSize(char filename[]){

	FILE * pCurrentFile;
	char filepath[50];
	int size;

	strcpy(filepath, "./datafiles/");
	strcat(filepath, filename);

	pCurrentFile = fopen(filepath, "rb");
	fseek(pCurrentFile,0L,SEEK_END);
	size = ftell(pCurrentFile);
	fclose(pCurrentFile);
	//fprintf(stderr,"Size = %d\n", size);
	return size;

}

