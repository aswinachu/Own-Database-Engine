#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "btree_mgr.h"
#include "tables.h"
#include "record_mgr.h"
#include "buffer_mgr.h"
#include "storage_mgr.h"

typedef struct BtreeHandle                      
{
	int temp_count;									
	int numCount;
	RID *index;
	int val;
        int tempval;
	int cond;
	int *pointer;
	int maxNodes;
	int totalNumOfNodes;
	int totalNumOfEntries;
	int flag;
        int temp;
        int pages;
        int slots;
        int exchange;
	struct BtreeHandle **adjNode;
}BtreeHandle;

typedef struct BtreeBufferHandle
{
BM_BufferPool *bufferPool;
BM_PageHandle *handlePages;
}BtreeBufferHandle;

BtreeHandle *parent;
BtreeHandle bth;
SM_FileHandle fileHandle;
SM_PageHandle pageHandle;
BtreeHandle *dummy;
BtreeBufferHandle *btbh;
int bo = sizeof(bool);
int in = sizeof(int);
int ch = sizeof(char);
int isOpen =0;

#define NODE_MEMORY()                                            \
BtreeHandle *ptr = (BtreeHandle*)malloc(sizeof(BtreeHandle));    \
(*ptr).pointer = malloc(sizeof(int) + sizeof(char));             \
(*ptr).index = malloc(sizeof(int) + sizeof(char));               \
(*ptr).adjNode = malloc(sizeof(int) + (sizeof(int)));            \


RC initIndexManager (void *mgmtData)			   			     //initializing index Manager
{
	pageHandle = malloc(4096 * in);								//Allocating memory for pageHandle with the size of page multiples of int size
	parent = (BtreeHandle*)malloc(sizeof(BtreeHandle));  		// Allocating memory for tree handle 
	if(parent==NULL)											//checks if the value is initialized or not
	{
		return RC_FILE_NOT_FOUND;								//returns if memory allocation is failed
	}
	return RC_OK;												//returns OK on success

}

RC shutdownIndexManager ()			   				    		//shutdown index manager
{
	free(pageHandle);											//freeing memory allocated for pageHandle
	free(parent);												//freeing memory allocated for parent
	return RC_OK;												//returns OK on success
}

RC createBtree (char *idxId, DataType keyType, int num)			//creating Btree with filename, datatype and number of nodes
{
	if (parent!=NULL)											//checks if the memory already allocated or not
	{
		RC rc;													//declaration for checking RC value for conditions
		(*parent).pointer = malloc(in + ch);					//Allocating memory for pointer with the maximum size of int & char           
		(*parent).index = malloc(in + ch);						//Allocating memory for index with the maximum size of int and char           
		(*parent).adjNode = malloc(in + in); 					//Allocating memory for adjNode with the maximum size of int            
		bth.val=0;												//initializing BTreeHandle value to zero
		while(bth.val < num + ch)			
		{
			(*parent).adjNode[bth.val] = '\0';	
			bth.maxNodes = bo;									//setting maximum nodes to the size of boolean
			bth.val += bo;										//incrementing BTreeHandle value to size of boolean
		}                                               
		if(keyType== DT_INT)									//Checkin if the datatype is integer
		{
			rc = createPageFile (idxId);						//on Success, pagefile is created with the name passed as idxId
			if(rc !=RC_OK)										//if creation of page fails, returns rc error
			{
				return rc;										//returns type of rc error
			}
			rc=openPageFile (idxId, &fileHandle);				//checks and opens the pagefile created
			if(rc !=RC_OK)										// if it fails returns the error
			{
				return rc;										//returns the failed rc value
			}
		}
		isOpen++;			            			   		    //incremented when the pageifle is created,it can be checked in the openpagefile
	}
	return RC_OK;												//returns RC_OK on success.
}

RC openBtree (BTreeHandle **tree, char *idxId)										//opens Btree file which was created using createBTree functions
{
	if (isOpen==1)																	//checks if the pagefile is created using counter in createBTree func.	
	{
		RC rc;																		//declaration for RC type	
		btbh = (BtreeBufferHandle*)malloc(sizeof(BtreeBufferHandle));				//allocating memory for the BtreeBufferHandle pointer
		if(btbh!=NULL)                          									//checks if the pointer memory is allocated
		{
		(*btbh).bufferPool = ((BM_BufferPool *) malloc (sizeof(BM_BufferPool)));	//allocating memory for bufferPool
		(*btbh).handlePages = ((BM_PageHandle *) malloc (sizeof(BM_PageHandle)));	//similarly,allocating memory for handlePages
		rc =initBufferPool((*btbh).bufferPool, idxId, 3, RS_FIFO, NULL);			//initializing buffer pool using function in buffer_mgr.c
		}
		if(rc!=RC_OK)                                   							//if initializing buffer pool is failure, it returns failure rc
			{
				return rc;
			}
	        rc =pinPage((*btbh).bufferPool, (*btbh).handlePages,1);					//executes pinPage function from buffer_mgr.c
		if(rc !=RC_OK)																//pinPage function execution is checked for success or failure
			{
				return rc;															//returns rc value on failure
			}																		//on Success, it proceeds to execute unpinPage function
		rc =unpinPage((*btbh).bufferPool, (*btbh).handlePages);
		if(rc !=RC_OK)				        										//checks if function execution is success or failure
			{
				return rc;															//returns rc value on failure
			}
																					//on success it passes the function openBtree
	}
	return RC_OK;
}

RC closeBtree (BTreeHandle *tree)								// closing Btree
{
		if(tree!=NULL)											//checks if the tree is used/has values
		{
			RC rc;
			free(parent);										//deallocates memory location allocated for pointer
                        free(tree);                             //deallocates memory location allocated for tree
			rc = closePageFile(&fileHandle);					//closing the created page file
			if(rc!=RC_OK)										//checks the condition of closing page file function 
			{
				return rc;										//if function fails to execute returns rc value;
			}
		}
	return RC_OK;												//returns RC_OK on success
}

RC deleteBtree (char *idxId)                                    //deletes Btree with the filename
{
    if(remove(idxId)!=0)                                        //checks if the deletion is successful
    {
    return RC_FILE_NOT_FOUND;                                   //if it fails, file not found is printed
    }
    else
    {
        return RC_OK;                                           //if the file is deleted retuns RC_OK
    }
}

RC getNumNodes (BTreeHandle *tree, int *result)                 //returns number of nodes in the Btree
{
    getDataValue(tree, result, 1);                              //calls function which returns tree details
    return RC_OK;
}

RC getNumEntries (BTreeHandle *tree, int *result)               // returns number of entries from the Btree
{

    getDataValue(tree, result, 2);                              //calls functions which return tree details
    return RC_OK;
}

int getDataValue(BTreeHandle *tree, int *result, int no)        //retuns BTree entires and node values
{
    bth.totalNumOfEntries = 0;                                  //initialize values
    bth.val=0;
    if (no==1)                                                  //checks if the condition is for number of entries
    {
        while(bth.val < bth.maxNodes + bo)                      //checks condition for each values from 0 to max value
        {
            bth.totalNumOfNodes = bth.totalNumOfNodes + 1;      //increments number of nodes value on each turn
            bth.val++;                                          //increments val 
        }
        *result = bth.totalNumOfNodes;                          //retuns total number of nodes calculated
    }
    else if(no==2)                                              //checks if the condition is for number of entries
    {
    while(bth.val < bth.maxNodes + in)                          //checks condition for each values from 0 to max value
        {
            bth.totalNumOfEntries = bth.totalNumOfEntries + 1;  //increments number of entries value on each turn
            bth.val++;                                          //increments val
        }
        *result = bth.totalNumOfEntries;                        //returns number of entries 
    }
    return *result;                                             //retuns result based on the condition called
}

RC getKeyType (BTreeHandle *tree, DataType *result)				
{
    return RC_OK;
}

RC findKey (BTreeHandle *tree, Value *key, RID *result)			//search for key
{
	RC rc;
	dummy = (BtreeHandle*)malloc(sizeof(BtreeHandle));			//memory allocation for BtreeHandle structure as dummy
	bth.flag = 0;												//initializing flag value to 0
	rc =searchForKey(dummy, key, result);						//calls function to search throught the contents
	checkCond(bth);											 	//checks final result for success or failure
	
}

checkCond(BtreeHandle bth)										//checks flas value and returns result
{
	if(bth.flag == 1) 										
		return RC_OK;											//on successful key find returns RC_OK
	else
		return RC_IM_KEY_NOT_FOUND;								//on Failure, returns KEY NOT FOUND
}

searchForKey(BTreeHandle *tree, Value *key, RID *result)			//function used to find keys
{
for (dummy = parent; dummy != NULL; dummy = (*dummy).adjNode[bo])	//checks using current BTreeHandle pointer with the next node
	{
		bth.val=0;													//initializes bth value	
		while(bth.val<in)											//checks and executes function for all contents
		{
			
			if ((*dummy).pointer[bth.val] == (*key).v.intV) 		//checks if bth value is equal to value from "Value" structure 
			{
				
				(*result).page =(*dummy).index[bth.val].page;		//assigns page value to the index
				(*result).slot = (*dummy).index[bth.val].slot;		//assign slot value to the index
				bth.flag = 1;										//sets flag value as 1 to state it is executed
				bth.val=1;											//set val to 1 similarly as above
				break;						
			}
			bth.val++;												//increments val to check for all entries
		}
		if(bth.flag == 1)											//checks flag value if it is executed
		break;
	}
}

RC insertKey (BTreeHandle *tree, Value *key, RID rid)				//Inserts key function
{
	RC rc;
	int treeSize =sizeof(BtreeHandle);								//allocates  BtreeHandle size to new value
	bth.numCount = 0;												//initializes count value
	rc = recursiveinsert(rid, key, tree);							//executes and checks if the function is successful
	if(rc!=RC_OK)
	{
		return rc;													//returns error rc value on failure
	}
    return rc;														//returns rc on success
}

RC recursiveinsert(RID rid, Value *key, BTreeHandle *tree)				//recursive insert function
{
	dummy = (BtreeHandle*)malloc(sizeof(BtreeHandle));					//allocates BtreeHandle memory
	for (dummy = parent; dummy != NULL; dummy = (*dummy).adjNode[bo])	//checks condition with the next node
		{
	            keyinsert(rid, key, tree);								//executes function each iteration		

		}
}

RC keyinsert(RID rid, Value *key, BTreeHandle *tree)					//inserting key
{
	NODE_MEMORY();														//initializing memory
	bth.val=0;															//initializing bth val
	while(bth.val<bo)													//checks for each value of val with the total size
	{

		if ((*dummy).pointer[bth.val] == 0)								//performs checking operation if the val is 0
		{
			(*dummy).index[bth.val].page = rid.page;					//assigns page,slot, intV and numCount value to the structure
			(*dummy).index[bth.val].slot = rid.slot;
			(*dummy).pointer[bth.val] = (*key).v.intV;
			bth.numCount = bth.numCount + bo;
			break;
		}
	    bth.val++;														//increments to check next value
	}
	if (bth.numCount == 0)												//Checks if the above cond is not executed 
	{
		if((*dummy).adjNode[bth.maxNodes] == NULL)						//checks if the adjacent node is empty
		{
			(*dummy).adjNode[bth.maxNodes] = ptr;						//assigns pointer
		}
	}
}

RC deleteKey (BTreeHandle *tree, Value *key)					//Deleting key checking
{
	int handleSize = sizeof(BtreeHandle);						//allocates memory with the size of BtreeHandle
	if(handleSize>0)											//checks if the size of BtreeHandle is already initialized
	{
		bth.flag = 0;											//decrements flag value to 0 markiing it is deleted
		recursivedelete(key,tree);								//calls recursivedelete function to perform delete operation
	}
	return RC_OK;												//returns RC_OK on success
}

RC recursivedelete(Value *key, BTreeHandle *tree)					//recursive delete function for allocating and calling delete function
{
	dummy = (BtreeHandle*)malloc(sizeof(BtreeHandle));					//mem allocation for Btreehandle using temp variable dummy
	for (dummy = parent; dummy != NULL; dummy = (*dummy).adjNode[bo]) 	//checks for all contents
	{
		bth.val = 0;													//initializing val to 0
		keydeletion(key, tree);											//calls delete on checking
		if (bth.flag == 1)												//checks if executed and breaks from the loop
        {
			break;
        }
	}
}

RC keydeletion(Value *key, BTreeHandle *tree)						//delete key value function
{
	while(bth.val < in)												//conditions are checked in prev functions, it iterates on all values
	{
		if ((*dummy).pointer[bth.val] == (*key).v.intV) 			//searchs for vale which has struct value
		{
			(*dummy).pointer[bth.val] = 0;							//initialize pointer val to 0 as key is deleted
			(*dummy).index[bth.val].page = 0;						//initialize index page value to 0 as key is deleted
			(*dummy).index[bth.val].slot = 0;						//initialize index slot value to 0 as key is deleted
			bth.flag = 1;											//increments flag on deletion
			break;
		}
		bth.val ++;													//completes deletion for one occurence 
	}
}

RC openTreeScan (BTreeHandle *tree, BT_ScanHandle **handle)					//Scanning the tree function
{
    dummy = (BtreeHandle*)malloc(sizeof(BtreeHandle));						//mem allocation for the BtreeHandle with the temp variable dummy
    dummy = parent;															//passing value from parent to temp value
    bth.temp = 0;
    BtreeHandle *node = (BtreeHandle*)malloc(sizeof(BtreeHandle));			//creates and allocates memory for BtreeHandle variable
    bth.totalNumOfEntries = 0;												//initializing number of entries to 0
    for (node = parent; node != NULL; node = (*node).adjNode[bth.maxNodes])	//checks for not null value and incrementing node value to next max node value
      {
        for (bth.val = 0; bth.val < sizeof(int); bth.val ++)				//checks for entire contents 
         {
            if ((*node).pointer[bth.val] != 0)								//checks if the value is not initialized
             {	
                bth.totalNumOfEntries ++;									//incrementing number of entries on success
             }
         }
      }
    scanTree(tree, handle);													//calls scanTree function to lookup values
    return RC_OK;
}

RC scanTree(BTreeHandle *tree, BT_ScanHandle **handle)						//Scanning tree value
{	
BtreeHandle *node = (BtreeHandle*)malloc(sizeof(BtreeHandle));				//allocates memory for node with the size to accomdate BtreeHandle
int pointer[bth.totalNumOfEntries];											
    int elements[bth.maxNodes][bth.totalNumOfEntries];	
    bth.temp_count = 0;														//initializinf count value to scan from first
    for (node = parent; node != NULL; node = (*node).adjNode[bth.maxNodes]) //checks if the node is not null throught all values
    {
        for (bth.val = 0; bth.val < sizeof(int); bth.val ++) 				//initialize val to 0 and executes from first to all values
        {
            pointer[bth.temp_count] = (*node).pointer[bth.val];				//assigns value to count value in pointer
            elements[0][bth.temp_count] = (*node).index[bth.val].page;		//assigns page value 
            elements[1][bth.temp_count] = (*node).index[bth.val].slot;		//assigns slot value
            bth.temp_count ++;												//increments count to scan next value
        }
    }
}

RC nextEntry (BT_ScanHandle *handle, RID *result)							//function for next Entry 
{	 
    dummy = (BtreeHandle*)malloc(sizeof(BtreeHandle));						//memory allocates for BtreeHandle
    if((bth.maxNodes == 0))													//checks if the entry is available
    {
      dummy = (*dummy).adjNode[bth.maxNodes];								//assigns value to the dummy struct
      (*result).page = (*dummy).index[bth.temp].page;						//assigns page value to *result page
      (*result).slot = (*dummy).index[bth.temp].slot;						//assigns page slot to *result slot
      bth.temp+sizeof(bool);												
    }	
    return RC_OK;															//returns RC_OK on success

}

RC closeTreeScan (BT_ScanHandle *handle)									//closing Tree Scan
{
    return RC_OK;
}

char *printTree (BTreeHandle *tree)											//test function
{
    return RC_OK;
}
