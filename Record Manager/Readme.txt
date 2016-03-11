ASSIGNMENT 3 - RECORD MANAGER

TEAM MEMBERS :
1)ASWIN ACHUTHAN (A20361329)
2)GOPIKAA MANIKANDAN(A20359996)
3)VIKNESHKUMAR THIRUMOOORTHY(A20354393)

------------------------------------------------------------------------

1)Instructions to run the code
------------------------------

1) Go to terminal,navigate to the assignment directory.

2) Type: 
	make -f makefile.mk

3) Type:
	./record_mgr

---------------------------------------------------------------------------

2)Description of functions used

	Function : createTable
	-----------------------
		
1) Create a new table along with initializing the bufferpool.
2) The page size is set to the BM_PageHandle.
3) A condition to check whether the initial value is assigned to the bufferpool , if the value is not assigned then the values are assigned and incremented repectively.
4) Page creation is done where we check whether the page is created or not and if created we are trying to open and write on the page.

	Function : openTable
	---------------------
	
1) Pin the page that is opened from the bufferpool.
2) Check for the condition whether the value is less than number of attributes and then allocate the memory location for the name attribute. 
3) Check for the condition whether the value is less than number of attibutes and the size of the integer , then allocate the memory location for the data type. 
4) Unpin the page that was opened. 

	Function : closeTable
	-----------------------------
1) Close the table and return a success message upon success.


	Function : deleteTable
	------------------------------
	
1) Destroys the particular table by calling destroy page function.
	
	Function : getNumTuples
	-------------------------

1) Gets number of tuples/records from the management data.

	Function : insertRecord
	-------------------------
		
1) Pins the page as where the slot is free to insert the new record.
2) Condition check whetehr the keyslot is less than zero,where pagesize is incremented and the value to the new record is added.
3) Mark the particular record as dirty as it was recently modified and update the content in the memory by moving the content to the memory.
4) Pin the record which was modified recently.

	Function : deleteRecord
	---------------------
1) Opens the page to access and checks whether it is been pinned
2) Moves the content and then marks it as dirty followed by unpinning it.

	Function : updateRecord
	----------------------------
1) Gets the particular record id as where the update needs to be done.
2) Pins the particular location and updates the record.
3) Moves the content to the memory by marking it dirty and then unpins it.

	Function : getRecord
	---------------------------
1) Pins the page from where the record need to be fetched.
2) Gets the value of record in a pointer value.
3) Moves the content to the memory and then unpin the record.


	Function : startScan
	------------------------
1) Scans the particular record.


	Function : next
	------------------------

1) Check if all values are scanned.
2) Moves all the values scanned to the memory.
3) Checks if the value of float or boolean is true and then unpin the page.
4) Unpin all the pages that were scanned and then return all tuples are scanned.

	Function: closeScan
	---------------------
	
1) Check if all the records are scanned and if the condition is satisfied mark the management data as null and free it.
2) If the condition is failed , unpin the pages that are pinned and return ok.

	Function : getRecordSize
	-------------------------------
	
1)Checks the condition for the total number of attributes and if t=it is satisfied it then checks for the datatype.
2) Checks whether it is integer or string and then returns attributeoffset. 


	Function : createRecord
	-----------------------------
	
1) Checks whetehr a temp value is lesser than the sizof integer.
2) If the datatype is integer assign the value of sizof integer along with temp value to the record size , the process is carried out for all types of data.
3) Return success on the creation of record.

	Function : freeRecord
	----------------------

1) A record is made free by calling free function.

	Function : getAttr
	------------------
1) Stores the value from pointer to temp value and then checks for the datatype and increases datatype value accordingly.
2) Returns the value stored and returns ok.


	Function : setAttr
	------------------
1) Stores the value from pointer to temp value and then checks for the datatype and increases datatype value accordingly.
2) The values are set.


------------------------------------------------------------------------------------------------------------------------

3)Additional header files.

	a)record_mgr_data_structures.c
        b)record_mgr_data_structures.h


