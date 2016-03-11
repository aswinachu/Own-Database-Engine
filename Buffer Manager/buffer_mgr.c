//including required header files
#include <stdio.h>
#include <stdlib.h>
#include "buffer_mgr.h"
#include "storage_mgr.h"
#include <math.h>

//defining structure
typedef struct Structure_Details
{
  SM_PageHandle data;
  PageNumber pagenum;
  int dirtyPage;
  int fixedcount;
  int freq_used;	
  int nr;
}Structure_Details;

//declaring and initializing values, pointers
int buffpg_size = 0;
int next = 0; 
int writeIO = 0; 
int strike = 0; 
SM_FileHandle fh;
Structure_Details *sd;
Structure_Details *pin;

//initializing bufferpool - creating a buffer pool for an existing page file
RC initBufferPool(BM_BufferPool *const bm, const char *const pageFileName,const int numPages, ReplacementStrategy strategy,void *stratData)
{
  sd = malloc(sizeof(Structure_Details)*numPages); //allocating memory
  buffpg_size =numPages;	
  int i=0;
  //checking if buffer page size is 0 and initializes value 
  while(i<buffpg_size)
  {
    sd[i].data = NULL;
    sd[i].pagenum = -1;
    sd[i].dirtyPage = 0;
    sd[i].fixedcount = 0;
    sd[i].freq_used = 0;	
    sd[i].nr = 0;
    i++;
  }
  bm->pageFile = (char *)pageFileName;
  bm->numPages = numPages;
  bm->strategy = strategy; // passing parameters for the page replacement strategy
  bm->mgmtData = sd;
  writeIO = 0;
  return RC_OK;
 }
//shut down the created buffer pool
RC shutdownBufferPool(BM_BufferPool *const bm)
{
  sd = (Structure_Details *)bm->mgmtData;
  forceFlushPool(bm); // force values(if any) to write before shutting down.
  int i=0;	
  while(i<buffpg_size) // checking if data is present in the buffer.
  {
    if(sd[i].fixedcount != 0)
    return RC_PINNED_PAGES_STILL_IN_BUFFER;
    i++;
  }
  free(sd); // destorys the buffer pool
  bm->mgmtData = NULL;
  return RC_OK;
}
//writing data and flushing pool
RC forceFlushPool(BM_BufferPool *const bm)
{
  sd = (Structure_Details *)bm->mgmtData;
  int i=0;
  while(i<buffpg_size)	 
  { 
    if((sd[i].dirtyPage == 1) && (sd[i].fixedcount == 0)) // //checks all dirty pages (with fix count 0)
    { 
      openPageFile (bm->pageFile, &fh);
      writeBlock (sd[i].pagenum, &fh, sd[i].data); // writing to disk from the buffer pool.
      sd[i].dirtyPage = 0;
      writeIO++;
    }
    i++;
  }	
  return RC_OK;
}

//make page Dirty
RC markDirty (BM_BufferPool *const bm, BM_PageHandle *const page)
{
  sd = (Structure_Details *)bm->mgmtData;
  int i;
  for(i=0;i<buffpg_size;i++)
    {
      if(sd[i].pagenum == page->pageNum)
      {
        sd[i].dirtyPage = 1;
        return RC_OK;   //if success it returns OK 
      }     
    }   
  return RC_ERROR;
}

//unPinPage
RC unpinPage (BM_BufferPool *const bm, BM_PageHandle *const page)
{
  sd = (Structure_Details *)bm->mgmtData;
  int i=0;
  while(i<buffpg_size)  // checks each page and removes the fixedcount	
  {
    if(sd[i].pagenum == page->pageNum)
    {
      sd[i].fixedcount--;
      break;		
    }
  i++;		
  }
  return RC_OK;
}

//forePage
RC forcePage (BM_BufferPool *const bm, BM_PageHandle *const page)
{
  int i=0;
  while(i<buffpg_size)	// checks each page and writes the current content of the page back to the page file on disk.
    {
    if(sd[i].pagenum == page->pageNum)
    {		
     openPageFile (bm->pageFile, &fh);
     writeBlock (sd[i].pagenum, &fh, sd[i].data);
     sd[i].dirtyPage = 0; //once written dirtypage is cleared
     writeIO++;
    }
  i++;
  }	
  return RC_OK;
}
//FIFO
void FIFO(BM_BufferPool *const bm, Structure_Details *node)  
{
  int i=0;
  int prev = next%buffpg_size;
  sd = (Structure_Details *) bm->mgmtData;
  while(i<buffpg_size) // checks if the page size is greater than 0
  {
    if(sd[prev].fixedcount == 0) 
	  {
      if(sd[prev].dirtyPage == 1) // checks if dirtypage is present and writes it to the disk
	    {
        openPageFile (bm->pageFile, &fh);
        writeBlock (sd[prev].pagenum, &fh, sd[prev].data);
        writeIO++;
	    }
    	 sd[prev].data = node->data;
    	 sd[prev].pagenum = node->pagenum;
    	 sd[prev].dirtyPage = node->dirtyPage;
    	 sd[prev].fixedcount = node->fixedcount;
    	 break;
	  }
	  else
	  {
       prev++;
	     if(prev%buffpg_size == 0)
       prev=0;
	  }
    i++;
  }
}

void LRU(BM_BufferPool *const bm, Structure_Details *node)
{
  sd=(Structure_Details *) bm->mgmtData;
  int i=0;
  int prev;
  int minimum;
  while(i<buffpg_size)
  {
    if(sd[i].fixedcount == 0)
    {
      prev= i;
      minimum = sd[i].freq_used;
      break;
    }
    i++;
  }
    i=prev+1;
    while(i<buffpg_size)	
    {
      if(sd[i].freq_used < minimum)
      {
        prev = i;
        minimum = sd[i].freq_used;
      }
    i++;
    }
    if(sd[prev].dirtyPage == 1) // checks if dirty page present and writes it to disk
    { 
      openPageFile (bm->pageFile, &fh);
      writeBlock (sd[prev].pagenum, &fh, sd[prev].data);
      writeIO++;
    }
    sd[prev].data = node->data;
    sd[prev].pagenum = node->pagenum;
    sd[prev].dirtyPage = node->dirtyPage;
    sd[prev].fixedcount = node->fixedcount;
    sd[prev].freq_used = node->freq_used;
}
//pinPage
RC pinPage (BM_BufferPool *const bm, BM_PageHandle *const page, const PageNumber pageNum)
{
  sd = (Structure_Details *)bm->mgmtData;
  if(sd[0].pagenum == -1) 
  {
   openPageFile (bm->pageFile, &fh);
   sd[0].data = (SM_PageHandle) malloc(PAGE_SIZE);
   ensureCapacity(pageNum,&fh);
   readBlock(pageNum, &fh, sd[0].data);
   sd[0].pagenum = pageNum;
   sd[0].fixedcount++;
   next = 0;
   strike = 0;
   sd[0].freq_used = strike;	
   sd[0].nr = 0;	
   page->pageNum = pageNum;
   page->data = sd[0].data;
   return RC_OK;		
  }
   else
   {	
      int i=0;
      int buffer_check = 0;
      while(i<buffpg_size)		
      {
        if(sd[i].pagenum != -1)
        {	
	         if(sd[i].pagenum == pageNum)  
	         { 
              sd[i].fixedcount++;
            	buffer_check = 1;
            	strike++;
	            if(bm->strategy == RS_LRU)
              sd[i].freq_used = strike;
	            page->pageNum = pageNum;
	            page->data = sd[i].data;
              break;
	         }				
        }
        else	
        {
            openPageFile (bm->pageFile, &fh);
            sd[i].data = (SM_PageHandle) malloc(PAGE_SIZE);
            readBlock(pageNum, &fh, sd[i].data);
            sd[i].pagenum = pageNum;
            sd[i].fixedcount = 1;
            sd[i].nr = 0;
            next++;	
            strike++;
      	    if(bm->strategy == RS_LRU)
        	  sd[i].freq_used = strike;				
        	  page->pageNum = pageNum;
        	  page->data = sd[i].data;
        	  buffer_check = 1;
        	  break;
        }
        i++;
      }
      if(buffer_check == 0)
      {		
            pin = (Structure_Details *)malloc(sizeof(Structure_Details));		
            openPageFile (bm->pageFile, &fh);
            pin->data = (SM_PageHandle) malloc(PAGE_SIZE);
            readBlock(pageNum, &fh, pin->data);
            pin->pagenum = pageNum;
            pin->dirtyPage = 0;		
            pin->fixedcount = 1;
            pin->nr = 0;
            next++;
            strike++;
            if(bm->strategy == RS_LRU )
            pin->freq_used = strike;
            page->pageNum = pageNum;
            page->data = pin->data;			
            if(bm->strategy == RS_FIFO)
            {
                FIFO(bm,pin);
               }	
               else if (bm->strategy == RS_LRU)				
               {
                LRU(bm,pin);
               }	
               else
               {
                return RC_ALGORITHM_NOT_IMPLEMENTED;
               }
            }
      return RC_OK;
    }	
  }

// get frame contents
PageNumber *getFrameContents (BM_BufferPool *const bm)
{
  PageNumber *val = malloc(sizeof(PageNumber)*buffpg_size);
  sd= (Structure_Details *)bm->mgmtData;
  int i=0;
  while(i<buffpg_size) //function returns an array of PageNumbers (of size numPages)
  {
    val[i] = sd[i].pagenum;
    i++;
  }
  return val;
}

//get dirty flags
bool *getDirtyFlags (BM_BufferPool *const bm)
{
  bool *val = malloc(sizeof(bool)*buffpg_size);
  sd= (Structure_Details *)bm->mgmtData;
  int i=0;	
  while(i<buffpg_size) // returns an array of bools (of size numPages)
  {
    if(sd[i].dirtyPage == 1)
    {
      val[i]= true;
    }
    else
    {
      val[i]=false;
    }
    i++;
  }	
  return val;
}

//get fix counts
int *getFixCounts (BM_BufferPool *const bm)
{
  int *val = malloc(sizeof(int)*buffpg_size);
  sd= (Structure_Details *)bm->mgmtData;
  int i=0;	
  while(i<buffpg_size) //returns an array of ints (of size numPages) 
  {
  val[i] = sd[i].fixedcount;
  i++;
  }
  return val;
}

int getNumReadIO (BM_BufferPool *const bm)
{
  return (next+1);
}

int getNumWriteIO (BM_BufferPool *const bm)
{
  return writeIO;
}

