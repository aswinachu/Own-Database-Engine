#include <stdio.h>
#include <stdlib.h>
#include "record_mgr.h"
#include "buffer_mgr.h"
#include "dt.h"
#include "storage_mgr.h"
#include <math.h>

//DataStructures for the table
typedef struct tableSchema
{
    int numTuples;	          // To track the total number of tuples in a table
    int tid;                      // To update and delete particular slot
    int emptySlots;	          // To track the empty slots in first free page of a table
    char *name;                   // To track the length of the records
    BM_PageHandle handlePages;	  // Buffer Manager PageHandle 
    BM_BufferPool poolHandle;	  // Buffer Manager Buffer Pool
}tableSchema;

//DataStructures for Scanning the tuples in a Table
typedef struct scanRecord
{
    Expr *scanCondition;         // expression to be checked
    int tuplesScanned;           // To track the no. of tuples scanned
    RID key;                     // To track the current row that is scanned
    BM_PageHandle handlePages;   // Buffer Manager PageHandle
} scanRecord;

typedef struct tempVariables
{
int numOfSlots;
int numOfAttr;
int sizeOfRecord;
int attributeOffset;
int position;
int val;
int numPages;
int stringLength;
int lengthOfPage;
}tempVariables;

SM_FileHandle handleFile;
SM_PageHandle handlePage;
tableSchema *tSchema;
RID *key;
tempVariables temp;
char *pointer;
char *value;
char *newValue;

#define POINTER_MEMORY()                                                      \
scanRecord *s;                                                                \
s = (scanRecord*)scan->mgmtData;                                              \
tableSchema *t;                                                               \
t = (tableSchema*)scan->rel->mgmtData;                                        \

#define TABLE_MEMORY()					                      \
tSchema = ((tableSchema *) malloc (sizeof(tableSchema)));

#define SCHEMA_MEMORY()                                                       \
Schema *schemaMemory;                                                         \
schemaMemory= (Schema*) malloc(sizeof(Schema));                               \
schemaMemory->numAttr= temp.numOfAttr;                                        \
schemaMemory->attrNames= (char**) malloc(sizeof(char*)*3);                    \
schemaMemory->dataTypes= (DataType*) malloc(sizeof(int)*3);                   \
schemaMemory->typeLength= (int*) malloc(sizeof(int)*3);                       \

#define SCAN_MEMORY()                                                         \
scanRecord *s;                                                                \
s = (scanRecord*) malloc(sizeof(scanRecord)); 

#define VALUE_MEMORY()                                                        \
Value *v;                                                                     \
v = (Value *) malloc(sizeof(Value));
