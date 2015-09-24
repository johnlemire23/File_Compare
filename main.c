/***********************
John Lemire
Main.c
Program 1, File Comparison 

Main file for program, contains calls to hashmethod.c and processfiles.c

************************/


#include "headers.h"
#include "processfiles.h"

int main (int argc, char* argv[]){
	
	// int for phraselength
	// numfiles counter and buffer and few loop variabls

	int phraseLength;
	int numFiles = 0;
	char buffer[50][30];
	int i,n;

	if(argc !=2){
		fprintf(stdout, "Not enough args, please enter the phrase length \n");
		exit(1);
	}

	phraseLength = atoi(argv[1]);

	if(phraseLength <2 || phraseLength> 10){
		fprintf(stdout, "Phrase length to long or short, please enter a number between 2-10 inclusive\n");
		exit(1);
	}

	fileList(buffer,&numFiles);

	if(numFiles > 30){
		fprintf(stdout, "Too many files! \n");
		exit (1);
	}

	// formatting file for output output is saved in output.txt
	
		system ("echo "" > output.txt");
		FILE * output;
		output=fopen("output.txt","w");
		fprintf(output,"\t");
	
		for (i=0; i< numFiles;i++){
			fprintf(output,"File%i \t",i+1);
		}
		
		fprintf(output,"\n");
	
	//fprintf(stderr,"Numfiles = %i Phrase Lenght = %i\n",numFiles,pCounter);

	//Main For Loop which goes through files for hashing and comparing

	for(i=0;i<numFiles-1;i++){

		// first line for output file structure
		// create a new hash table pointer
		// create buffer based on (size) of file.. no limited to 20k bytes, but could easily implement that
		// copy file contents into new buffer

		fprintf(output,"File%i",i+1);		
		table_e * newHtable;
		char currentBuffer[getSize(buffer[i])+1];
		strcpy(currentBuffer,fileContents(buffer[i]));

		// point newHtable at newly created and allocated table
		// processes file (hash and store each phrase)
		// output file structure loop

		newHtable=createTable(5000);
		processFile(newHtable,currentBuffer, phraseLength,1,1);

		for(n=0;n<=i;n++){
			fprintf(output,"\t");
		}

		// for loop goes through each file on file buffer and compares the value
				
		for(n=i+1;n<=numFiles-1;n++){

			// create and allocate new buffer to hold file to compare	
			// copy new file contents into newbuffer
			// compare contents
			
			char newBuffer[getSize(buffer[n])+1];
			strcpy(newBuffer,(char *)fileContents(buffer[n]));
			fprintf(output, "\t %i",processFile(newHtable,newBuffer,phraseLength,1,-1));
		}

	// output file structure

	fprintf(output,"\n");		
	}

	//close output file
	//print output file
	//close program
	
	fclose(output);
	system("cat ./output.txt");
	return 0;
}
