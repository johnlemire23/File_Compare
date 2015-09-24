/*******************************************

Student Name: John Lemire
File Name: hashmethods.c
Project 1, Comparing Files

Contains methods for hashing, comparing and creating hash table or nodes on list

********************************************/


#include "hashmethods.h"
#include "headers.h"
#define TABLE_SIZE 5000;

//******************
//
// createTable
// input: size of array
// returns a newly created and allocated array of pointers to struct StringEntry

table_e * createTable(int size){

	table_e * newHashTable;
	int i;
		
	if(NULL == (newHashTable = malloc(sizeof(table_e)))){
		return NULL;
	}

	if(NULL == (newHashTable->entry = malloc(sizeof(string_e)*size))){
		return NULL;
	}

	for (i=0;i<size;i++){
		newHashTable->entry[i] = NULL;
	}

	return newHashTable;
}

//*********************************
//
// create entry
// input: string phrase
// returns a newly created and allocated struct of type StringEntry (string_e)
// with phrase in it

string_e * createEntry(char s2h[]){

	string_e * newEntry;

	if(NULL == (newEntry = malloc(sizeof(string_e)))){
		return NULL;
	}

	strcpy(newEntry->hashedString,s2h);
	newEntry->next = NULL;

	return newEntry;
}

//**********************************8
//
// put entry
// takes string phrase and a pointer to an entry
// recurses to last node on list and adds string (updates pointers also)

void putEntry(char s2h[], string_e * entry){

	if(entry->next!=NULL){
		putEntry(s2h,entry->next);
	}
	else {
		entry->next=createEntry(s2h);
	}
}


//*************************************8
//
// compare
// input: phraxe and stringEntry pointer
// compares phrase with current stringEntry phrase, if match return 1, else return 0
// if next pointer != null then it navigates to it (recursivly) and does further compare 

int compare(char s2h[], string_e * entry){

	if(NULL==entry->hashedString){		
		return 0;
	}
	else if(strcmp(entry->hashedString,s2h)==0){
		return 1;
	}
	else if(entry->next != NULL){
		return compare(s2h,entry->next);}
	else
	return 0;
}


//*********************************
//
// hash 
// input word
// the hash function you provided us in class!!! thanks =]

int hash(char word[]){

	int total = 1;
	int len = strlen(word);
	int i;
	for (i=0;i<len;i++){
		total += word[i]*(i+1);
	}
	if (total <0) total *= -1;
	
	return total % TABLE_SIZE;
}
