#include "dberror.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "storage_mgr.h"
#include <math.h>

//initial storage manager
void initStorageManager (void)
{

}

//Create Page
RC createPageFile (char *fileName)
{
  FILE *myfile = fopen(fileName, "w+");
  char *p = calloc(PAGE_SIZE,sizeof(char));
  if(myfile == NULL)
{
    return RC_FILE_NOT_FOUND;
 }
    fwrite(p, sizeof(char), PAGE_SIZE, myfile);
    fclose(myfile);  
    free(p);
    return RC_OK;
}

//Open Page
RC openPageFile (char *fileName, SM_FileHandle *fHandle)
{
  FILE *myfile = NULL;
  myfile = fopen(fileName, "r+");  
  if(myfile == NULL)
{
    return RC_FILE_NOT_FOUND;
}
    fHandle->fileName = fileName;
    fHandle->mgmtInfo = myfile;
    fHandle->totalNumPages = 1;
    fHandle->curPagePos = 0;
    fseek(myfile, 0, SEEK_SET);
    fwrite(fileName,PAGE_SIZE,0,myfile);
    fclose(myfile);
    return RC_OK;
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
  if(remove(fileName) == -1)
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
  FILE *myfile;
  myfile = fopen(fHandle->fileName, "r"); 
  if(myfile == NULL)
  {
  return RC_FILE_NOT_FOUND;
  }
  fseek(myfile, (pageNum * PAGE_SIZE), SEEK_SET);
  if(fread(memPage, 1, PAGE_SIZE, myfile) > PAGE_SIZE)
  {
    return RC_ERROR;
  }
     fHandle->curPagePos = ftell(myfile); 
     fclose(myfile); 
     return RC_OK;
}

//Get Block Position
int getBlockPos (SM_FileHandle *fHandle)
{
  return fHandle->curPagePos;
}

//First Block
RC readFirstBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
{
  FILE *myfile;
  myfile = fopen(fHandle->fileName, "r+");    
  if(myfile == NULL)
{
    return RC_FILE_NOT_FOUND; 
}
int i=0;
while(i<PAGE_SIZE)
{
  memPage[i] = fgetc(myfile);
  i++;
  }
  fHandle->curPagePos = ftell(myfile);
  fclose(myfile); 
  return RC_OK;
}

//Previous Block
RC readPreviousBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
{
  int pageNum;
  FILE *myfile;
  myfile = fopen(fHandle->fileName, "r+");    
  if(myfile == NULL)
{
    return RC_FILE_NOT_FOUND; 
}
    pageNum = ceil((float)fHandle->curPagePos/(float)PAGE_SIZE);     
    fseek(myfile,(PAGE_SIZE*(pageNum - 2)),SEEK_SET);
    int i=0;
    while(i<PAGE_SIZE)
    { 
      memPage[i] = fgetc(myfile);
      i++;
    }
    fHandle->curPagePos = ftell(myfile);
    fclose(myfile); 
    return RC_OK;       	
}

//Current Block
RC readCurrentBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
{ 
  int pageNum;
  FILE *myfile;
  myfile = fopen(fHandle->fileName, "r+");    
  if(myfile == NULL)
{
    return RC_FILE_NOT_FOUND; 
}
    pageNum = ceil((float)fHandle->curPagePos/(float)PAGE_SIZE);     
    fseek(myfile,(PAGE_SIZE*(pageNum - 1)),SEEK_SET);
    int i=0;
    while(i<PAGE_SIZE)
    { 
      memPage[i] = fgetc(myfile);
      i++;
    }
    fHandle->curPagePos = ftell(myfile);
    fclose(myfile); 
    return RC_OK;
}

//Next Block
RC readNextBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
{
  int pageNum;
  FILE *myfile;
  myfile = fopen(fHandle->fileName, "r+");    
  if(myfile == NULL)
{
    return RC_FILE_NOT_FOUND; 
}
    pageNum = ceil((float)fHandle->curPagePos/(float)PAGE_SIZE);     
    fseek(myfile,(PAGE_SIZE*(pageNum)),SEEK_SET);
    int i=0;
    while(i<PAGE_SIZE)
    { 
      memPage[i] = fgetc(myfile);
      i++;
    }
    fHandle->curPagePos = ftell(myfile);
    fclose(myfile); 
    return RC_OK;       
}

//Last Block
RC readLastBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
{
  FILE *myfile;
  myfile = fopen(fHandle->fileName, "r+");  
  if(myfile == NULL)
{
    return RC_FILE_NOT_FOUND; 
} 
  fseek(myfile,((fHandle->totalNumPages - 1) * PAGE_SIZE),SEEK_SET);
  int i=0;
  while(i<PAGE_SIZE)
  { 
    memPage[i] = fgetc(myfile);
    i++;
  }
  fHandle->curPagePos = ftell(myfile);
  fclose(myfile);     
  return RC_OK;
}

//Write Block
RC writeBlock (int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage)
{
  FILE *myfile;
  int cur_pos = (pageNum)*PAGE_SIZE;
  myfile = fopen(fHandle->fileName, "r+"); 
  if(pageNum!=0)
  { 
  fHandle->curPagePos = cur_pos;
  fclose(myfile);
  writeCurrentBlock(fHandle,memPage);   
  }
  else
  { 
    fseek(myfile,cur_pos,SEEK_SET);  
    int i=0;
    while(i<PAGE_SIZE)
    {
     fputc(memPage[i],myfile);
     i++;
    }
    fHandle->curPagePos = ftell(myfile);
    fclose(myfile);
  } 
  return RC_OK;
}

//Write Current Block
RC writeCurrentBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
{
  FILE *myfile;
  myfile = fopen(fHandle->fileName, "r+");
  if(myfile == NULL) 
  {
    return RC_FILE_NOT_FOUND;
  }
  int curPos;
  curPos = fHandle->curPagePos;
  fseek(myfile,curPos,SEEK_SET);
  fwrite(memPage,1,strlen(memPage),myfile);
  fHandle->curPagePos = ftell(myfile);
  fclose(myfile); 
  return RC_OK;
}

//Append Empty Block
RC appendEmptyBlock (SM_FileHandle *fHandle)
{
FILE *myfile;
myfile = fopen(fHandle->fileName,"r");
if(myfile!=NULL)
{
createPageFile(fHandle->fileName);
}
}

//Ensure Capacity
RC ensureCapacity (int numberOfPages, SM_FileHandle *fHandle)
{
int numOfPages;
if (fHandle->fileName == NULL)
{
return RC_FILE_NOT_FOUND;
}
else
{
if (fHandle->totalNumPages < numOfPages)
{
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
}
return RC_OK;
}

