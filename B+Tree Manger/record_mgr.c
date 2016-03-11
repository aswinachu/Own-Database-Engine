#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "record_mgr.h"
#include "buffer_mgr.h"
#include "storage_mgr.h"
#include "record_mgr_data_structures.h"

                                                              /* TABLE AND MANAGER */

int dataTypeINT = DT_INT;
char dataTypeSTRING = DT_STRING;
float dataTypeFLOAT = DT_FLOAT;
bool dataTypeBOOL = DT_BOOL;

RC initRecordManager (void *mgmtData)
{
return RC_OK;
}

RC shutdownRecordManager ()
{
return RC_OK;
}

RC createTable (char *name, Schema *schema)
{
TABLE_MEMORY();                                                             // Memory Allocation for the TableSchema dataStructure
initBufferPool(&tSchema->poolHandle, name, 50, RS_FIFO, NULL);              // Initializing the BufferPool
char size[4096];                                                            // Initializing a character variable with the PAGE_SIZE
char *handlePages = size;                                                   // Assigning the character size[] to BM_PageHandle DataStructure
memset(handlePages, 0, 4096);                                               // Setting the PAGE_SIZE to BM_PageHandle
temp.val=0;
while(temp.val<=sizeof(char))                                               // Condition check - (temp.val<=sizeof(char))
{                                                                           // If temp.val is less than number of attributes i.e., sizeof(char)
*(int*)handlePages = temp.val;                                              // SET NUMBER OF TUPLES - Initializing the BM_PageHandle
handlePages = handlePages + 4;                                              // Increment the pointer variable of BM_PageHandle
temp.val++;                                                                 // Increment temp.val
}                                                                           // end of 'while' loop
*(int*)handlePages = 3;                                                     // SET NUMBER OF ATTRIBUTES - Initializing the BM_PageHandle    
handlePages = handlePages + 4;                                              // Increment the pointer variable of BM_PageHandle
while(temp.val<=sizeof(char))                                               // Condition check - (temp.val<=sizeof(char))
{                                                                           // If temp.val is less than number of attributes i.e., sizeof(char)
*(int*)handlePages = (int)schema->dataTypes[temp.val];                      // SET THE DATATYPES
handlePages = handlePages + sizeof(char);                                   // Increment the pointer variable of BM_PageHandle
*(int*)handlePages = (int) schema->typeLength[temp.val];                    // SET THE TYPELENGTH - for the String datatype
handlePages = handlePages + sizeof(char);                                   // Increment the pointer variable of BM_PageHandle
temp.val++;                                                                 // Increment temp.val 
}                                                                           // end of 'while' loop
createPageFile(name);                                                       // After initializing, call createPageFile function 
if(name == NULL)                                                            // Check if the pagefile name is NULL
{                                                                         
return RC_FILE_NOT_FOUND;                                                   // if 'yes' return RC_FILE_NOT_FOUND
}
else                                                                        //'else' block
{
openPageFile(name, &handleFile);                                            // else call openPageFile function
writeBlock(0, &handleFile, size);                                           // Write the entries to the 0th page(begining of the pageFile)
}
return RC_OK;
}

RC openTable (RM_TableData *rel, char *name)
{
temp.val=0;
rel->mgmtData = tSchema;                                                    // Initializing the rel->mgmtData variable to TABLESCHEMA DataStr.
pinPage(&tSchema->poolHandle, &tSchema->handlePages, -1);                   // Start pinning the page for reading the in bufferPool
handlePage = (char*) tSchema->handlePages.data;	                             
tSchema->numTuples= *(int*)handlePage; 	                                    // Get the number of tuples from BM_PageHandle
handlePage = handlePage + 4;                                                // Increment the value of handlePage
tSchema->emptySlots= *(int*)handlePage;	                                    // Get the empty slots available from BM_PageHandle
handlePage = handlePage + 4;                                                // Increment the value of handlePage                            
temp.numOfAttr = *(int*)handlePage;		                           			// Get the number of attributes
handlePage = handlePage + 4;                                                // Increment the value of handlePage
SCHEMA_MEMORY();                                                            // Memory allocation for Schema
while(temp.val <= sizeof(char))                                             // Condition check - (temp.val<=sizeof(char))
{                                                                           // If temp.val is less than number of attributes i.e., sizeof(char)
schemaMemory->attrNames[temp.val]=(char*)malloc(sizeof(char)+sizeof(int));  // Memory allocation for the Name of Attributes
temp.val++;                                                                 // Increment temp.val
}                                                                           // end of while loop
while(temp.val <= (sizeof(char) + sizeof(int)))                             // Condition check - (temp.val<=sizeof(char)+sizeof(int))
{                                                                           
schemaMemory->dataTypes[temp.val]= *(int*)handlePage;                       // Initializing the datatypes in the schema for BM_PageHandle 
rel->schema = schemaMemory;                                                 // Assigning back SchemaMemory back to rel->schema
temp.val++;                                                                 // Increment temp.val
}                                                                           // end of 'while' loop
unpinPage(&tSchema->poolHandle, &tSchema->handlePages);                     // UnPin the pages after finish reading
return RC_OK;    
}
   
RC closeTable (RM_TableData *rel)
{
BM_BufferPool *poolHandle=(BM_BufferPool *)rel->mgmtData;
tableSchema *tSchema = rel->mgmtData;                                       // assigning rel->mgmtData to tSchema before closing the table
shutdownBufferPool(&tSchema->poolHandle);	                            // BufferPool is shutted down
return RC_OK;
}

RC deleteTable (char *name)
{
destroyPageFile(name);	                                                    // calling 'destroyPageFile' function
return RC_OK;
}

int getNumTuples (RM_TableData *rel)					    //get number of tuples from management data
{
return(((tableSchema*)rel->mgmtData)->numTuples);
}
                        
/* HANDLING RECORDS IN A TABLE */

RC insertRecord (RM_TableData *rel, Record *record)			    
{
tSchema = rel->mgmtData;						    // assigns page information to tSchema
key = &record->id;		                  			    // assigns id value of record to key
temp.sizeOfRecord = getRecordSize(rel->schema);				    // assigns sizeOfRecord to size from getRecordSize function
key->page = tSchema->emptySlots;					    // assigns emptySlots from tSchema to page value from key	 
pinPage(&tSchema->poolHandle, &tSchema->handlePages, key->page);	    // pins page with the value to buffermgr 
value = tSchema->handlePages.data;					    // assigns tSchema value to value
key->slot = freeSpace(value, temp.sizeOfRecord);			    // gets freeSpace value to slot of key
while((key->slot)<0)							    // checks if the slot value is less than 0
{                                                                           
key->page++;								    // increaments page
pinPage(&tSchema->poolHandle, &tSchema->handlePages, key->page);	    // pins page with the value to buffermgr function
value = tSchema->handlePages.data;					    // assigns handlePages.data to value schema
key->slot = freeSpace(value, temp.sizeOfRecord);			    // adds freeSpace to slot
}
markDirty(&tSchema->poolHandle,&tSchema->handlePages);			    // calls markDirty function
value = value + (key->slot * temp.sizeOfRecord);			    // increment value to accomdate data (slot X sizeofrecord)
*value = '$';								    // adds value to empty slot
value++;	                                		            // increments pointer to 1;
memmove(value, record->data+1, temp.sizeOfRecord); 			    // moves (record->data+1) to value with sizeOfRecord
unpinPage(&tSchema->poolHandle, &tSchema->handlePages);			    // calls unPinPage function
pinPage(&tSchema->poolHandle, &tSchema->handlePages, 1);		    // calls pinPage function
return RC_OK;								    
}

RC deleteRecord (RM_TableData *rel, RID id)			            
{
openPageFile(tSchema->name, &handleFile);				    // opens a page to access it
if(pinPage(&tSchema->poolHandle, &tSchema->handlePages,id.page)==RC_OK);    // checks if pinPage functions returns OK
value = tSchema->handlePages.data; 					    // assigns data from tSchema to value
temp.val = tSchema->numTuples; 						    // assign number of Tuples value from tSchema to temp value
temp.sizeOfRecord = getRecordSize(rel->schema);  			    // assign size of record by getting value from getRecordSize()
temp.val = temp.val + (id.slot * temp.sizeOfRecord); 			    // increments val to accomdate all values (slot X size of record)
markDirty(&tSchema->poolHandle, &tSchema->handlePages); 	 	    // calls markdirty function in buffer manager
unpinPage(&tSchema->poolHandle, &tSchema->handlePages);			    // calls unpinPage function in buffer manager
return RC_OK;								   
}

RC updateRecord (RM_TableData *rel, Record *record)							
{
key = &record->id;							    // assigns key value from id of record
pinPage(&tSchema->poolHandle, &tSchema->handlePages, record->id.page); 	    // pins page (from buffer manager)
value = tSchema->handlePages.data;					    // assigns data value from tschema to value
temp.sizeOfRecord = getRecordSize(rel->schema);				    // gets size of record from getRecordSize() 	
value = value + (key->slot * temp.sizeOfRecord); 			    // increments value to accomdate size of record
value++;							            // increments to write in next
memmove(value,record->data + 1, temp.sizeOfRecord);  			    // moves (record->data+1) to value with size of record declared 
markDirty(&tSchema->poolHandle, &tSchema->handlePages); 		    // marks dirty before it is written, calls markDirty in buffermgr
unpinPage(&tSchema->poolHandle, &tSchema->handlePages); 		    // unpins record using function in buffer manager
return RC_OK;								    
}

RC getRecord (RM_TableData *rel, RID id, Record *record)			
{
pinPage(&tSchema->poolHandle, &tSchema->handlePages, id.page); 	            // pins page to get record
temp.sizeOfRecord = getRecordSize(rel->schema);				    //assigns sizeOfRecord by getting value from getRecordSize function
pointer = tSchema->handlePages.data;					    // assigns data from tSchema to pointer value
pointer = pointer + ((id.slot)*temp.sizeOfRecord);			    //increments pointer to accomdate all contents(slot X sizeofrecord)
value = record->data;							    // assigns data value from record schema to temp value 
value++;								    // increments to use next location
memmove(value,pointer + 1,temp.sizeOfRecord - 1);			    // copies value(pointer+1) to value with (sizeOfRecord-1) 
record->id = id; 			                        	    // assigns id value to id of record schema
unpinPage(&tSchema->poolHandle, &tSchema->handlePages); 		    // unpins page using function from buffer manager 
return RC_OK;									
}

                                                              /* SCANS */

RC startScan (RM_TableData *rel, RM_ScanHandle *scan, Expr *cond)			
{
char *name;           							    // declaring local variable pointer
openTable(rel, name);							    // opens table
SCAN_MEMORY(); 								    // Memory allocation
scan->mgmtData = s;							    // assigns 's' to management data 
s->key.page= 1;      							    // assigns page value to 1 
s->key.slot= 0;      							    // assigns slot value to 0
s->scanCondition = cond;                                                    // set the condition for scan
tableSchema *tSchema; 							    // taking pointer for schema
tSchema = rel->mgmtData; 						    // adding management data to the schema
tSchema->numTuples = 25;					            // assigning number of tuples value to 25
scan->rel= rel;	
return RC_OK;	
}

RC next (RM_ScanHandle *scan, Record *record)								
{
POINTER_MEMORY();					// allocates memory for pointer
VALUE_MEMORY();						// allocate memory for value schema
temp.sizeOfRecord = getRecordSize(scan->rel->schema);	// gets record size from getRecordSize()
temp.numOfSlots = ceil(4096/temp.sizeOfRecord);	       //assigns no. of slots as smallest integer equal to or grater than (4096/size of record)
s->tuplesScanned=0;					// initializing tuplesScanned value to 0
while(s->tuplesScanned <= t->numTuples)			// checks if all the tuples are scanned using tuplesScanned value  
{                                                                           
s->key.slot = s->key.slot + 1;				// moves next slot as slot+1 
pinPage(&t->poolHandle, &s->handlePages, s->key.page);	// pins page using function declared in buffer manager 
newValue = s->handlePages.data;				// assigns data value from page handle to newValue
newValue = newValue + (s->key.slot * temp.sizeOfRecord);// incrememtns newValue to accomdate all contents by (slot X size of record)
record->id.page = s->key.page; 				// assigns page from key to record page id
record->id.slot = s->key.slot;				// assigns slot from key to record slot id
value = record->data;					// assigns data from record to value schema
value = value + 1;					// increments value to 1
memmove(value,newValue+1,temp.sizeOfRecord-1); 		// copies newValue+1 to the value with (sizeOfRecord-1)
evalExpr(record,(scan->rel)->schema, s->scanCondition, &v);
s->tuplesScanned++;                                     // Increment the value of tuples Scanned
if((v->v.floatV == TRUE)||(v->v.boolV == TRUE))		// checks if the value is float or bool
{
unpinPage(&t->poolHandle, &s->handlePages);		// unpins page using function from buffer manager
return RC_OK;						
}
}
unpinPage(&t->poolHandle, &s->handlePages); 		// unpin page using function in buffer manager 
s->key.page = 1;				        // assigns page value to 1
s->key.slot = 0;					// assigns slot value to 0
s->tuplesScanned = 0;					// assigns tuplesScanned(local variable) to 0
return RC_RM_NO_MORE_TUPLES;				
}

RC closeScan (RM_ScanHandle *scan)
{
POINTER_MEMORY();                                                           // Memory Allocatiofor TableSchema and ScanRecord DataStructures
if((s->tuplesScanned < 0)&&(s->tuplesScanned == 0))                         // Check if there is any tuples are scanned or not
{                                                                            
scan->mgmtData= '\0';                                                       // if 'yes' make scan->mgmtData as NULL
free(scan->mgmtData);                                                       // free scan->mgmtData
return RC_OK;               
}                                                                           // end of 'if' block
else                                                                        // else if there are any tuples scanned
{
unpinPage(&tSchema->poolHandle, &s->handlePages);                           // unpin the pages that are pinned
s->key.page= 1;                                                             // assign back the page number as 1
s->key.slot= 0;                                                             // assign the slot number as 0
s->tuplesScanned = 0;                                                       // make the tuplesscanned pointer as 0
return RC_OK;
}                                                                           // end of 'else' block 
}

                                                    /* DEALING WITH SCHEMA*/
int getRecordSize (Schema *schema)
{
temp.attributeOffset = 0;                                                   // Setting the value of offset as '0'
temp.val = 0;                                                               
while(temp.val<schema->numAttr)                                             // Conditional 'while' loop for total number of attributes
{                                                                           // if the condition is satisfied, check for the type of dataType
if (schema->dataTypes[temp.val] == dataTypeINT)                             // if data type is an INT
{                                          
temp.attributeOffset = temp.attributeOffset + 4;                            // increment attributeOffset to size of integer
} 
else if(schema->dataTypes[temp.val] == dataTypeSTRING)                      // if data type is an STRING
{
temp.attributeOffset = temp.attributeOffset + schema->typeLength[temp.val]; // increment attributeOffset to typeLength
}
temp.val++;
}                                                                           // end of 'while' loop
temp.attributeOffset = temp.attributeOffset++;                              // incrementing the attributeOffset value for end of string
return temp.attributeOffset;                                                // return the value of attributeOffset
}

Schema *createSchema (int numAttr, char **attrNames, DataType *dataTypes, int *typeLength, int keySize, int *keys)
{
SCHEMA_MEMORY();                                                            // Memory Allocation
schemaMemory->numAttr = numAttr;                                            // Initializing the No. of Attributes
schemaMemory->attrNames = attrNames;                                        // Initializing the Attribute Names
schemaMemory->dataTypes =dataTypes;                                         // Initializing the Attribute's data types
schemaMemory->typeLength = typeLength;                                      // Initializing the Attribute's type length
schemaMemory->keySize = keySize;                                            // Initializing the Key size
schemaMemory->keyAttrs = keys;                                              // Initializing the key attribute
return schemaMemory;                                                        // Returns the value of Schema
}

RC freeSchema (Schema *schema)
{
free(schema);                                                               // free schema
return RC_OK;
}

                                               /* DEALING WITH RECORDS AND ATTRIBUTE VALUES */

RC createRecord(Record **record, Schema *schema)                       
{                
temp.numOfAttr = schema->numAttr;	                               // assigns temp number of attr value to num attr value from schema
int *size = schema->typeLength;					       // declares size from length of type
temp.val=0;							       // initialize val
DataType *dataType = schema->dataTypes;				       // assigns dataType from schema dataType
while(temp.val < sizeof(int)) 					       // checks if val<size of integer and executes based on the dataType
{
temp.position = *(dataType + temp.val);		                       // assigns position value to pointer
if (temp.position == dataTypeINT) 				       // checks if the position value is INT data type from schema
{
temp.sizeOfRecord = temp.sizeOfRecord + sizeof(int);		       // initialize sizeOfRecord to temp sizeOfRecord including size of INT
} 
else if (temp.position == dataTypeFLOAT)			       // checks if the position value is FLOAT data type from schema
{
temp.sizeOfRecord = temp.sizeOfRecord + sizeof(int);		       // initialize sizeOfRecord to temp sizeOfrecord including size of FLOAT 
}
else if (temp.position == dataTypeBOOL) 			       // checks if the position value is BOOL data type from schema
{
temp.sizeOfRecord = temp.sizeOfRecord + 1;			       // initialize sizeOfRecord to temp sizeOfrecord +1(required for BOOL)
} 
else if (temp.position == dataTypeSTRING)
{ 
temp.sizeOfRecord = temp.sizeOfRecord + (*(size + temp.val));	       //initialize sizeOfRecord to temp sizeOfrecord + size of temp value(str)
}
temp.val++;						               // increments temp val, so each instance is checked once 
}
temp.val=0;							       // once dataType is checked, value is assigned to 0
while(temp.val < sizeof(int) + sizeof(char))			       // checks entire record size with temp val as mentioned above.
{
pointer = (char *)malloc(sizeof(int) + sizeof(char));		       // allocates memory for pointer
pointer[temp.val]='\0';						       // declars temp val to zero
*record = (Record *)malloc(sizeof(int));			       // allocates memory to pointer
record[0]->data=pointer;					       // using space for pointer
temp.val++;							       // increments temp val, so that each instance is checked once
}
return RC_OK;								
}

RC freeRecord (Record *record)
{
free(record);                                      			            // free Record           
return RC_OK;								
}

RC getAttr (Record *record, Schema *schema, int attrNum, Value **value) 
{
temp.attributeOffset = 0; 				     // initializes temp attributeOffset value to 0
get_set_attributes(schema, attrNum, &temp.attributeOffset);  // calls function to assign value
VALUE_MEMORY();						     // allocates memory
pointer = record->data;					     // assigns pointer to data in record
pointer = pointer + temp.attributeOffset;		     // then assigns pointer value by incrementing pointer to attribureOffset from temp
if(attrNum == 1)					     // if attribureOffet value is 1 (from get_set_attributes function)
{
schema->dataTypes[attrNum] = 1;				     // assigns attrNum of dataTypes in schema to 1
}
if (schema->dataTypes[attrNum] == dataTypeINT)		     // checks if the attrNum of dataTypes from schema is INT datatype
{
memmove(&temp.val,pointer, 4);				     // copying pointer value to val from temp with size 4(size of char)
v->v.intV = temp.val;					     // assigns temp value to v.intV and INT data type to v.dt
v->dt = DT_INT;
}
else if (schema->dataTypes[attrNum] == dataTypeSTRING)	     // checks if the attrNum is of data type STRING
{
v->dt = DT_STRING;					     // assigns STRING data type to v.dt
temp.stringLength = schema->typeLength[attrNum];	     // assigns length of string from attrNum typeLength
v->v.stringV = (char *) malloc(sizeof(char));		     // allocate memory of chat for stringV
strncpy(v->v.stringV, pointer, temp.stringLength);	     // copies value from pointer to stringV with stringLenth size
v->v.stringV[temp.stringLength] = '\0';			     // terminated by null char
}
else if (schema->dataTypes[attrNum] == dataTypeFLOAT)	     // checks if the attrNum is of data type FLOAT
{
v->dt = DT_FLOAT;					     // assigns FLOAT data type to v.dt
float floatingValue;					     // declares floatingValue of float dataType
memmove(&floatingValue,pointer,4);			     // copying pointer value to floatingValue from temp with size 4(size of float)
v->v.floatV = floatingValue;				     // assigns floatingValue to floatV 
}
else if (schema->dataTypes[attrNum] == dataTypeBOOL)	     // checks if the attrNum is of data type BOOL
{
v->dt = DT_BOOL;					     // assigns BOOL data type to v.dt
bool booleanValue;					     // declares booleanValue of bool dataType
memmove(&booleanValue,pointer,1);			     // copying pointer value to booleanValue from temp with size 1(size of boolean)
v->v.boolV = booleanValue;				     // assigns booleanValue to boolV 
}
else
{
return RC_INVALID_DATATYPE;				     // else returns undeclared return type 
}
*value = v;						     // assigns values to pointer v
return RC_OK;						     
}

RC setAttr (Record *record, Schema *schema, int attrNum, Value *value)
{
temp.attributeOffset = 0;			              // assigns attribureOffset to 0
get_set_attributes(schema, attrNum, &temp.attributeOffset);   // calls function to assign value
pointer = record->data;					      // assigns data from record to pointer
pointer = pointer + temp.attributeOffset;		      // assigns value of pointer+attributeOffset(returned from get)
if (schema->dataTypes[attrNum] == dataTypeINT)		      // checks if the attrNum value of dataType from schema is of INT data Type
{
*(int *)pointer = value->v.intV;	  		      // assigns value to pointer with the value intV from value schema
}
else if(schema->dataTypes[attrNum] == dataTypeSTRING)	      // checks if the attrNum value of dataType from schema is of STRING data Type
{
temp.sizeOfRecord = schema->typeLength[attrNum]; 	      // assigns size of record to data type length
newValue = (char *) malloc(sizeof(char)+sizeof(int));	      // create temp value as newValue and allocate memory
strncpy(newValue, value->v.stringV, sizeof(char)+sizeof(int));// copies value from stringV of value schema to newvalue (char+int) combination
newValue[temp.sizeOfRecord] = '\0';			      // assigns sizeOfRecord of newValue to 0
strncpy(pointer, newValue, sizeof(char)+sizeof(int));	      // copies newvalue to pointer of size to hold char and int
}
else if(schema->dataTypes[attrNum] == dataTypeFLOAT)	      // checks if the attrNum value of dataType from schema is of FLOAT data Type
{
float floatingValue;					      // declare an local variable
floatingValue = value->v.floatV;			      // assigns floatV of value schema to floatingValue
floatingValue = floatingValue + 4;			      // increments to 4 (size of float) 
}
else if(schema->dataTypes[attrNum] == dataTypeBOOL)	      // checks if the attrNum value of dataType from schema is of BOOL data Type
{
bool booleanValue;					      // declares an local variable
booleanValue = value->v.boolV;				      // assigns boolV value from value schema to temp variable
booleanValue = booleanValue++;				      // increments to 1 because of bool
}
else
{
return RC_INVALID_DATATYPE;				      // returns invalid if anyother datatype is received
}
return RC_OK;						      
}
