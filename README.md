# Own-Database-Engine
Building database engine with storage manager, buffer manager, record manager and B+ Tree manager.

Storage Manager  
It is a module that is capable of reading blocks from a file on disk into memory and writing blocks from memory to a file on disk. The storage manager deals with pages (blocks) of fixed size (PAGE_SIZE). In addition to reading and writing pages from a file, it provides methods for creating, opening, and closing files. The storage manager has to maintain several types of information for an open file: The number of total pages in the file, the current page position (for reading and writing), the file name, and a POSIX file descriptor or FILE pointer. 

Buffer Manager
The buffer manager manages a fixed number of pages in memory that represent pages from a page file managed by the storage manager. The memory pages managed by the buffer manager are called page frames or frames for short. We call the combination of a page file and the page frames storing pages from that file a Buffer Pool. The Buffer manager will handle more than one open buffer pool at the same time. However, there are on;y one buffer pool for each page file. Each buffer pool uses one page replacement strategy that is determined when the buffer pool is initialized. Implement two replacement strategies FIFO and LRU.

Record Manager
The record manager handles tables with a fixed schema. Clients can insert records, delete records, update records, and scan through the records in a table. A scan is associated with a search condition and only returns records that match the search condition. Each table  stored in a separate page file and your record manager will access the pages of the file through the buffer manager implemented.

Implementing B+-tree
The index will be backed up by a page file and pages of the index can be accessed through your buffer manager. Each node occupy one page.  A B+-tree stores pointer to records (the RID introduced in the Record Manager) index by a keys of a given datatype. Pointers to intermediate nodes are represented by the page number of the page the node is stored in.
