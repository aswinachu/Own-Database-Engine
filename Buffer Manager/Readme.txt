ASSIGNMENT 2 - BUFFER MANAGER

TEAM MEMBERS :
1)ASWIN ACHUTHAN (A20361329)
2)GOPIKAA MANIKANDAN(A20359996)
3)VIKNESHKUMAR THIRUMOORTHY(A20354393)

CONTENTS :
1)Instructions to run the code
2)Description of functions used
3)Additional MACROS in dberror.h

***********************************************************************************************

1)Instructions to run the code
------------------------------

In the terminal,navigate to the assignment directory.

------For FIFO test case------
Type: 
	make -f make_file.mk
        ./buffermgr 

------For LRU test case---
Type: 
	make -f makefile.mk
        ./buffer_mgr


**************************************************************************************************

2)Description of functions used
-------------------------------

	Function :initBufferPool
	-------------------------


1)Open page file and allocate the memory.
2)Check if buffer page size is 0 and initialize the value.
3)Initialize other Values in sd.


	Function :shutdownBufferPool
	----------------------------
	
1)Initially force values(if any) to write before shutting down.
2)Check if the data is present in the buffer.
3)After checking data through pin page functionality, destory the buffer pool.

	
	Function : forceFlushPool
	-------------------------

1)Checks all dirty pages whether the fix count is 0.
2)If the fix count is zero then write to disk from buffer pool.
3)Assign the value of dirty page as 0.
4)On success,return RC_OK to the calling function. 

	Function : markDirty
	---------------------
1)Check if the pagenumber of the buffer management is equal to the pagenumber of the pagehandle.
2)Assign the value of dirty page to 1 and returns RC_OK on success.
3)On error,RC_ERROR is called.


	Function : unpinPage
	---------------------
	
1)Check if the pagenumber of the buffer management is equal to the pagenumber of the pagehandle.
2)Decrement the value of fixedcount in the buffer.
3)On Success,return RC_OK to the calling function.


	Function : forcePage
	--------------------
1)Check if the pagenumber of the buffer management is equal to the pagenumber of the pagehandle.
2)Open the page in pagehandle.
3)Write the current content of the page back to the page file on disk .
4)Assign the dirtypage value to 0 once it is written to the page file on disk.
3)Increase the count of pages written.
4)On success,return RC_OK to the calling function.


	Function : pinPage 
	------------------
1)Check if the page is present in the buffer pool or not , If Not

	a)Open a page in pagehandle and allocate the memory .
	b)Ensure the capacity of the page and read the particular block.
	c)Assign the value for page frame.

2)Check if the page is already present in the buffer pool.If yes,	
	
	a)Traverse the contents of the page frame till last.
	b)Increase the fix count of the page
	c)Check if the replacement strategy is either FIFO or LRU .If not,throw an appropriate error code(RC_ALGORITHM_NOT_IMPLEMENTED).


3)On success,return RC_OK to the calling function.


 Statistics Functions
-------------------------

	Function : getFrameContents
	----------------------------
	
1)Initialize the buffer pagesize
2)Traverse till the end of pagesize and read the page numbers to the array.
3)Returns an array of PageNumber(of size numPages).
 
	Function : getDirtyFlags
	------------------------
	
1)Initialize the buffer pagesize
2)Traverse till the end of pagesize and check if the dirtypage is equal to one or not.
3)Returns an array of bool(of size numPages).


	Function : getFixCounts
	------------------------

1)Initialize the buffer pagesize
2)Traverse till the end of pagesize and read the page numbers to the array.
3)Returns an array of PageNumber(of size numPages).
	

	Function : getNumReadIO
	------------------------

1)Refer to the pool manager structure,which contains the information of the pages read.
2)Return the pages read. 


	Function: getNumWriteIO
	-----------------------
	
1)Refer to the pool manager structure,which contains the information of the pages written.
2) Return the pages written. 

***********************************************************************************************************

3)Additional MACROS
-------------------
	
	
We have included the following additional error checks in dberror.h

-> define RC_ERROR 5				
-> define RC_PINNED_PAGES_STILL_IN_BUFFER 6
-> define RC_ALGORITHM_NOT_IMPLEMENTED 7

*************************************************************************************************************
