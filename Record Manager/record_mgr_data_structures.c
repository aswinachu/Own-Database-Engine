#include <stdio.h>
#include <stdlib.h>
#include "record_mgr.h"
#include "buffer_mgr.h"
#include "storage_mgr.h"
#include "dt.h"
#include "record_mgr_data_structures.h"

// Provides the first available free slot of a particular page 
extern int freeSpace(char *value, int sizeOfRecord)
{
temp.val = 0;
temp.numOfSlots = ceil(4096/sizeOfRecord);    //PAGE_SIZE = 4096 bytes
while(temp.val<temp.numOfSlots)
{
if (value[temp.val * sizeOfRecord] != '$')
{
return temp.val;
}
temp.val++;
}
return -1;
}

int get_set_attributes(Schema *schema, int attrNum, int *final)
{
  temp.attributeOffset=1;
  temp.position = 0;
   for(temp.position = 0; temp.position < attrNum; temp.position++)
    switch (schema->dataTypes[temp.position])
      {
      case DT_STRING:
	temp.attributeOffset = temp.attributeOffset + schema->typeLength[temp.position]; 
	break;
      case DT_INT:
	temp.attributeOffset = temp.attributeOffset + sizeof(int); 
	break;
      case DT_FLOAT:
	temp.attributeOffset = temp.attributeOffset + sizeof(float); 
	break;
      case DT_BOOL:
	temp.attributeOffset = temp.attributeOffset + sizeof(bool); 
	break;
      }
  
  *final = temp.attributeOffset;
  return RC_OK;
}
