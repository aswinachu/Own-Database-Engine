# 🌳 B+-Tree Index Manager

A specialized component of the Own Database Engine that implements efficient B+-tree indexing for fast data retrieval and manipulation operations.

## 📋 Table of Contents
1. [🚀 Getting Started](#getting-started)
2. [🔧 Function Documentation](#function-documentation)
3. [📁 Important Files](#important-files)

---

## 🎯 Component Overview

The **B+-Tree Index Manager** is the indexing layer of the database engine that provides fast access to data through B+-tree data structures. This component handles all index-related operations including creation, deletion, searching, and maintenance of B+-tree indexes.

### 🔑 **Key Features**
- **Efficient Indexing**: B+-tree implementation for logarithmic search complexity
- **Memory Management**: Integration with buffer manager for optimal performance
- **Flexible Operations**: Create, open, close, and delete indexes
- **Fast Retrieval**: Quick key-based lookups and range scans
- **Integer Support**: Optimized for integer key types

### 🎯 **Use Cases**
- Database indexing for performance optimization
- Range queries and sequential access
- Primary and secondary index management
- Educational B+-tree implementation study

---

## 📁 Important Files

### 🌳 **Core B+-Tree Implementation**
- **`btree_mgr.c`** & **`btree_mgr.h`** - Main B+-tree index manager implementation
- **`tables.h`** - Data structure definitions for tables and schemas

### 📊 **Record Management Integration**
- **`record_mgr.c`** & **`record_mgr.h`** - Record manager for table operations
- **`record_mgr_data_structures.c`** & **`record_mgr_data_structures.h`** - Record data structures
- **`rm_serializer.c`** - Record serialization and deserialization utilities

### 🧠 **Buffer Management Integration**
- **`buffer_mgr.c`** & **`buffer_mgr.h`** - Buffer pool management with multiple replacement strategies
- **`buffer_mgr_stat.c`** & **`buffer_mgr_stat.h`** - Buffer statistics and monitoring

### 💾 **Storage Layer Integration**
- **`storage_mgr.c`** & **`storage_mgr.h`** - Low-level file I/O and page management

### 🔧 **Supporting Components**
- **`expr.c`** & **`expr.h`** - Expression evaluation and condition handling
- **`dberror.c`** & **`dberror.h`** - Error codes and error management system
- **`dt.h`** - Common data type definitions

### 🧪 **Testing & Build**
- **`test_assign4_1.c`** - Main test suite for B+-tree functionality
- **`test_expr.c`** - Expression testing utilities
- **`test_helper.h`** - Testing framework support
- **`makefile.mk`** - Build configuration

---

## 🚀 Getting Started

### Prerequisites
- Make sure you have a C compiler installed
- Navigate to the B+Tree Manager directory in your terminal

### Building and Running
```bash
# Build the project
make -f makefile.mk

# Run the B+-Tree manager
./btree_mgr
```

---

## 🔧 Function Documentation

### 🎯 Index Manager Functions

#### `initIndexManager()`
- **Purpose**: Initializes the Index Manager
- **Action**: Allocates necessary memory for the index manager
- **Returns**: Error code indicating success or failure

#### `shutdownIndexManager()`
- **Purpose**: Cleanly shuts down the Index Manager
- **Action**: Frees all allocated memory using `free()`
- **Returns**: Error code indicating success or failure

### 🌲 B+-Tree Manager Functions

#### `createBtree()`
- **Purpose**: Creates a new B+-tree index
- **Validation**: Checks if the data type is Integer
- **Action**: Initializes the B+-tree structure
- **Returns**: Error code indicating success or failure

#### `openBtree()`
- **Purpose**: Opens an existing B+-tree index
- **Validation**: Verifies that the B+-tree has been created
- **Action**: Prepares the B+-tree for operations
- **Returns**: Error code indicating success or failure

#### `closeBtree()`
- **Purpose**: Closes an active B+-tree index
- **Validation**: Ensures the tree exists before closing
- **Action**: Safely closes the B+-tree and releases resources
- **Returns**: Error code indicating success or failure

#### `deleteBtree()`
- **Purpose**: Permanently removes a B+-tree index
- **Action**: Deletes the B+-tree index and removes the associated page file
- **Returns**: Error code indicating success or failure

### 🔑 Key Operations

#### `findKey()`
- **Purpose**: Searches for a specific key in the B+-tree
- **Process**: 
  1. Uses the current `BTreeHandle` pointer to navigate through nodes
  2. Searches for the specified key
- **Returns**: 
  - **Success**: Record ID (RID) for the found key
  - **Failure**: `RC_IM_KEY_NOT_FOUND` error code if the key doesn't exist

#### `insertKey()`
- **Purpose**: Inserts a new key-value pair into the B+-tree
- **Process**:
  1. Validates the current `BTreeHandle` pointer
  2. Performs validation checks (e.g., if value is 0)
  3. Inserts the new key and record pointer pair
- **Returns**:
  - **Success**: Error code indicating successful insertion
  - **Failure**: `RC_IM_KEY_ALREADY_EXISTS` if the key already exists

#### `deleteKey()`
- **Purpose**: Removes a key from the B+-tree index
- **Process**:
  1. Validates the `BTreeHandle` size and initialization
  2. Initializes pointers, index page, and index slot to zero
  3. Removes the specified key from the index
- **Returns**:
  - **Success**: Error code indicating successful deletion
  - **Failure**: `RC_IM_KEY_NOT_FOUND` if the key doesn't exist in the index

---

## 📝 Notes
- All functions return error codes defined in `dberror.h`
- Ensure proper error handling when calling these functions
- The B+-tree implementation supports Integer data types
- Memory management is handled automatically by the manager functions
- This component integrates with the Buffer Manager for page-level operations

## 🐛 Troubleshooting
If you encounter build errors, ensure:
- All source files are present in the directory
- The makefile is correctly configured
- You have appropriate permissions to create and modify files
- Dependencies from other components are properly linked

## 🔗 Integration
This component is designed to work with:
- **Buffer Manager**: For page-level memory management
- **Record Manager**: For record storage and retrieval
- **Storage Manager**: For persistent file operations
