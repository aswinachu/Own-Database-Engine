# 🧠 Buffer Manager

A specialized component of the Own Database Engine that implements efficient memory management through buffer pools with multiple page replacement strategies.

## 📋 Table of Contents
1. [Component Overview](#component-overview)
2. [Getting Started](#getting-started)
3. [Important Files](#important-files)
4. [Function Documentation](#function-documentation)
5. [Replacement Strategies](#replacement-strategies)
6. [Notes](#notes)
7. [Troubleshooting](#troubleshooting)
8. [Integration](#integration)
9. [Performance Considerations](#performance-considerations)

---

## Component Overview

The **Buffer Manager** is the memory management layer of the database engine that manages a fixed number of pages in memory (page frames) that represent pages from page files. This component implements sophisticated buffer pool management with multiple replacement strategies for optimal performance.

### 🔑 **Key Features**
- **Buffer Pool Management**: Efficient management of multiple buffer pools
- **Multiple Replacement Strategies**: FIFO, LRU, Clock, LFU, and LRU-K implementations
- **Page Pinning**: Control over page retention in memory
- **Dirty Page Management**: Efficient handling of modified pages
- **Statistics Monitoring**: Comprehensive buffer pool performance metrics

### 🎯 **Use Cases**
- Database memory optimization
- Page replacement algorithm research
- Performance tuning and analysis
- Educational memory management study

---

## Getting Started

### Prerequisites
- Make sure you have a C compiler installed
- Navigate to the Buffer Manager directory in your terminal

### Building and Running
```bash
# Build the project
make -f makefile.mk

# Run the buffer manager tests
./test_buffer_fifo
./test_buffer_lru
```

---

## Important Files

### 🧠 **Core Buffer Management**
- **`buffer_mgr.c`** & **`buffer_mgr.h`** - Main buffer manager implementation
- **`buffer_mgr_stat.c`** & **`buffer_mgr_stat.h`** - Buffer statistics and monitoring

### 💾 **Storage Integration**
- **`storage_mgr.c`** & **`storage_mgr.h`** - Low-level file I/O and page management

### 🔧 **Supporting Components**
- **`dberror.c`** & **`dberror.h`** - Error codes and error management system
- **`dt.h`** - Common data type definitions

### 🧪 **Testing & Build**
- **`test_buffer_fifo.c`** - FIFO replacement strategy test suite
- **`test_buffer_lru.c`** - LRU replacement strategy test suite
- **`test_helper.h`** - Testing framework support
- **`makefile.mk`** - Build configuration


---

## Function Documentation

### 🎯 Buffer Pool Management

#### `initBufferPool()`
- **Purpose**: Initializes a new buffer pool
- **Parameters**: Buffer pool, page file name, number of pages, replacement strategy
- **Action**: Sets up the buffer pool with specified configuration
- **Returns**: Error code indicating success or failure

#### `shutdownBufferPool()`
- **Purpose**: Cleanly shuts down a buffer pool
- **Action**: Flushes all dirty pages and frees allocated memory
- **Returns**: Error code indicating success or failure

#### `forceFlushPool()`
- **Purpose**: Forces all dirty pages to be written to disk
- **Action**: Writes all modified pages back to their page files
- **Returns**: Error code indicating success or failure

### 📄 Page Access Operations

#### `pinPage()`
- **Purpose**: Pins a page in the buffer pool
- **Action**: Loads the specified page into memory if not already present
- **Returns**: Error code indicating success or failure

#### `unpinPage()`
- **Purpose**: Unpins a page from the buffer pool
- **Action**: Decrements the pin count and may make the page eligible for replacement
- **Returns**: Error code indicating success or failure

#### `markDirty()`
- **Purpose**: Marks a page as dirty (modified)
- **Action**: Indicates that the page has been modified and needs to be written back
- **Returns**: Error code indicating success or failure

#### `forcePage()`
- **Purpose**: Forces a specific page to be written to disk
- **Action**: Immediately writes the page back to its page file
- **Returns**: Error code indicating success or failure

### 📊 Statistics and Monitoring

#### `getFrameContents()`
- **Purpose**: Retrieves the current page numbers in each frame
- **Returns**: Array of page numbers currently in the buffer pool

#### `getDirtyFlags()`
- **Purpose**: Retrieves the dirty status of each frame
- **Returns**: Array of boolean flags indicating which pages are dirty

#### `getFixCounts()`
- **Purpose**: Retrieves the pin count of each frame
- **Returns**: Array of integers showing how many times each page is pinned

#### `getNumReadIO()`
- **Purpose**: Gets the total number of read I/O operations
- **Returns**: Count of read operations performed

#### `getNumWriteIO()`
- **Purpose**: Gets the total number of write I/O operations
- **Returns**: Count of write operations performed

---

## Replacement Strategies

### **FIFO (First In, First Out)**
- **Description**: Replaces the oldest page in the buffer pool
- **Use Case**: Simple and predictable behavior
- **Performance**: Moderate, good for sequential access patterns

### **LRU (Least Recently Used)**
- **Description**: Replaces the page that hasn't been accessed for the longest time
- **Use Case**: Temporal locality in access patterns
- **Performance**: Good for most access patterns

### **Clock**
- **Description**: Approximates LRU with lower overhead using a circular buffer
- **Use Case**: Efficient LRU approximation
- **Performance**: Good balance of performance and overhead

### **LFU (Least Frequently Used)**
- **Description**: Replaces the page with the lowest access frequency
- **Use Case**: Frequency-based access patterns
- **Performance**: Good for stable access patterns

### **LRU-K**
- **Description**: Enhanced LRU that considers the Kth most recent access
- **Use Case**: Sophisticated temporal locality
- **Performance**: Excellent for complex access patterns

---

## Notes
- Each buffer pool can handle only one page file
- Multiple buffer pools can be open simultaneously
- Page replacement strategy is determined at initialization
- Dirty pages are automatically written back when replaced
- Statistics are maintained for performance analysis

## Troubleshooting
If you encounter build errors, ensure:
- All source files are present in the directory
- The makefile is correctly configured
- You have appropriate permissions to create and modify files
- Dependencies from other components are properly linked

## Integration
This component is designed to work with:
- **Storage Manager**: For page file operations
- **Record Manager**: For record-level operations
- **B+-Tree Manager**: For index operations
- **Higher-level Components**: For complete database functionality

## Performance Considerations
- **Buffer Pool Size**: Larger pools reduce I/O but increase memory usage
- **Replacement Strategy**: Choose based on your access pattern characteristics
- **Page Pinning**: Minimize unnecessary pinning to improve replacement efficiency
- **Dirty Page Management**: Balance between performance and data consistency



