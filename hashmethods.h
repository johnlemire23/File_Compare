/*******************************************

Student Name: John Lemire
File Name: GetFiles.h
Project 1, Comparing Files

********************************************/
//5000 entries, each allocated 200 byte char array.. 1M bytes!

struct StringEntry{
	char hashedString[200];
	struct StringEntry * next;	
};

typedef struct StringEntry string_e;

struct Htable{ 
	struct StringEntry **entry;
};

typedef struct Htable table_e;

int hash (char []);

table_e * createTable(int);

string_e * createEntry(char []);

void putEntry(char [], string_e *);

int compare(char [], string_e *);


