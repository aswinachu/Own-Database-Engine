#include "dberror.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "storage_mgr.h"

//initial storage manager
void initStorageManager(void)
{

}

//Create Page
RC createPageFile (char *fileName)
{
  char *p = calloc(PAGE_SIZE, sizeof(char));
  FILE *myfile = fopen(fileName, "w+b");

    if (myfile==NULL)  //file will be created so it wont be null
        {
    return RC_FILE_NOT_FOUND;
        }
        else
        {
    fwrite(p, sizeof(char), PAGE_SIZE, myfile);
    free(p);
    fclose(myfile);
    return RC_OK;
        }
}

//Open Page
RC openPageFile (char *fileName, SM_FileHandle *fHandle)
{
FILE *myfile = NULL;

        myfile = fopen(fileName, "r");
        if (myfile == NULL)
        {
                return RC_FILE_NOT_FOUND;
        }
        else
        {
                fHandle->fileName = fileName;
                fHandle->mgmtInfo = myfile;
                fHandle->totalNumPages = 1;
                fHandle->curPagePos = 0;
                fseek(myfile, 0, SEEK_SET);
                fwrite(fileName,PAGE_SIZE,0,myfile);
                fclose(myfile);
                return RC_OK;
        }
}

//Close Page
RC closePageFile (SM_FileHandle *fHandle)
{

FILE *myfile;

myfile = fopen(fHandle->fileName,"r");

fclose(myfile);

return RC_OK;

}

//Destroy Page
RC destroyPageFile (char *fileName)
{

    if(remove("test_pagefile.bin") == -1)
    {
    perror("Error in deleting a file");
    }
    else
    {
    return RC_OK;
    }
}

//Read Block
RC readBlock (int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage)
{
    readCurrentBlock(fHandle,memPage);
}

//current block
int getBlockPos (SM_FileHandle *fHandle)
{
        fHandle->curPagePos;
}

//first block
RC readFirstBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
{
     readCurrentBlock(fHandle, memPage);
}

//previous block
RC readPreviousBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
{
 int pageNum;
  FILE *myfile;
myfile=fopen(fHandle->fileName,"r+");
 if (pageNum > fHandle->totalNumPages && pageNum < 0)
   {

  return RC_READ_NON_EXISTING_PAGE;
   }
   else
   {
 pageNum=fHandle->curPagePos-1;
 fseek(myfile,(pageNum)*PAGE_SIZE, SEEK_SET);
  fread(memPage,sizeof(char),PAGE_SIZE,myfile);
return RC_OK;
 fseek(myfile,(pageNum)*PAGE_SIZE, SEEK_SET);
 fread(memPage,sizeof(char),PAGE_SIZE,myfile);
return RC_OK;
}
}

// current block
RC readCurrentBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
{

int pageNum;
  FILE *myfile;
 myfile=fopen(fHandle->fileName,"r+");
 if (pageNum > fHandle->totalNumPages && pageNum < 0)
 {
   fclose(myfile);
      return RC_READ_NON_EXISTING_PAGE;
     }
      else
      {
        pageNum=fHandle->curPagePos;
          fseek(myfile,(pageNum)*PAGE_SIZE, SEEK_SET);
            fread(memPage,sizeof(char),PAGE_SIZE,myfile);
              return RC_OK;
              fseek(myfile,(pageNum)*PAGE_SIZE, SEEK_SET);
  fread(memPage,sizeof(char),PAGE_SIZE,myfile);
  return RC_OK;
}
}

//next block
RC readNextBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
{
 int pageNum;
  FILE *myfile;
myfile=fopen(fHandle->fileName,"r+");
 if (pageNum > fHandle->totalNumPages && pageNum < 0)
   {

  return RC_READ_NON_EXISTING_PAGE;
   }
   else
   {
 pageNum=fHandle->curPagePos+1;
 fseek(myfile,(pageNum)*PAGE_SIZE, SEEK_SET);
  fread(memPage,sizeof(char),PAGE_SIZE,myfile);
return RC_OK;
 fseek(myfile,(pageNum)*PAGE_SIZE, SEEK_SET);
 fread(memPage,sizeof(char),PAGE_SIZE,myfile);
return RC_OK;
}
}

// last block
RC readLastBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
{
 int pageNum;

  FILE *myfile;
myfile=fopen(fHandle->fileName,"r+");
 if (pageNum > fHandle->totalNumPages && pageNum < 0)
   {

  return RC_READ_NON_EXISTING_PAGE;
   }
   else
   {
 pageNum=fHandle->totalNumPages;
 fseek(myfile,(pageNum)*PAGE_SIZE, SEEK_SET);
  fread(memPage,sizeof(char),PAGE_SIZE,myfile);
return RC_OK;
 fseek(myfile,(pageNum)*PAGE_SIZE, SEEK_SET);
 fread(memPage,sizeof(char),PAGE_SIZE,myfile);
return RC_OK;
}
}

//Write Block
RC writeBlock (int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage)
{
 FILE *myfile;
myfile = fopen(fHandle->fileName, "wb");
fseek (myfile,(PAGE_SIZE * pageNum),SEEK_SET);
int val=fwrite ( memPage,1, PAGE_SIZE , myfile);
fHandle->curPagePos=pageNum;
return RC_OK ;
}

//Ensure Capacity
RC ensureCapacity(int numOfPages, SM_FileHandle *fHandle){
if (fHandle->fileName == NULL){
return RC_FILE_NOT_FOUND;
}
else{
if (fHandle->totalNumPages < numOfPages){
FILE *myfile;
myfile = fHandle->mgmtInfo;
int val = (numOfPages - fHandle->totalNumPages);
SM_PageHandle ph = (SM_PageHandle) malloc(PAGE_SIZE);
int j = 0;
                 do
                   {
                       if(j<val)
                       {
                           ph[j]=j%10+'0';
                        fwrite(ph, PAGE_SIZE, sizeof(ph), myfile);
                       }
                       j++;
                    }while(j!=val);
               int i = fseek(myfile,0, SEEK_END);
fHandle->curPagePos = i + 1;
fHandle->totalNumPages = numOfPages;
}
}return RC_OK;
}

//Append Empty Block
RC appendEmptyBlock(SM_FileHandle *fHandle)
{
FILE *myfile;
myfile = fopen(fHandle->fileName,"r");
if(myfile!=NULL)
{
createPageFile(fHandle->fileName);
}
}

//Write Current Block
RC writeCurrentBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)
{
int pos = getBlockPos(fHandle->curPagePos);
writeBlock (pos, fHandle, memPage);
}
        

