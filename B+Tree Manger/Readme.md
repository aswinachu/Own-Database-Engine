# 🌳 B+-Tree Index Manager

## 📋 Table of Contents
1. [🚀 Getting Started](#getting-started)
2. [🔧 Function Documentation](#function-documentation)
3. [📁 Important Files](#important-files)

---

## 🎯 Project Summary

The **B+-Tree Index Manager** is a comprehensive database management system that implements a complete storage and indexing infrastructure. This project demonstrates the fundamental concepts of database systems through multiple interconnected layers:

### 🏗️ **Architecture Overview**
- **Storage Manager**: Handles low-level file I/O operations and page management
- **Buffer Manager**: Implements memory management with multiple replacement strategies (FIFO, LRU, Clock, LFU, LRU-K)
- **Record Manager**: Manages table operations, record storage, and schema handling
- **B+-Tree Index Manager**: Provides efficient indexing for fast data retrieval and manipulation

### 🔑 **Key Features**
- **Multi-layered Design**: Clean separation of concerns from storage to indexing
- **Flexible Buffer Management**: Multiple page replacement strategies for optimal performance
- **Comprehensive Indexing**: Full B+-tree implementation with insert, delete, and search operations
- **Record Management**: Complete CRUD operations for database records
- **Error Handling**: Robust error management system with detailed return codes

### 🎯 **Use Cases**
- Educational database systems
- Small to medium-scale database applications
- Database engine research and development
- Understanding database internals and algorithms

---

## 🖼️ **System Architecture Diagram**

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                           B+-Tree Index Manager                            │
│                              (User Interface)                              │
└─────────────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                        🎯 B+-Tree Index Layer                              │
│  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────────────────────┐ │
│  │   createBtree   │  │    findKey      │  │      insertKey              │ │
│  │   openBtree     │  │   deleteKey     │  │      deleteBtree            │ │
│  │   closeBtree    │  │  openTreeScan   │  │      closeTreeScan          │ │
│  └─────────────────┘  └─────────────────┘  └─────────────────────────────┘ │
└─────────────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                      📊 Record Management Layer                            │
│  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────────────────────┐ │
│  │  createTable    │  │   insertRecord  │  │      getRecord              │ │
│  │   openTable     │  │   deleteRecord  │  │      updateRecord           │ │
│  │   closeTable    │  │    startScan    │  │       next                  │ │
│  └─────────────────┘  └─────────────────┘  └─────────────────────────────┘ │
└─────────────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                      🧠 Buffer Management Layer                            │
│  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────────────────────┐ │
│  │ initBufferPool  │  │    pinPage      │  │      markDirty              │ │
│  │shutdownBufferPool│  │   unpinPage    │  │      forcePage              │ │
│  │                 │  │                 │  │                             │ │
│  │ Replacement Strategies: FIFO, LRU, Clock, LFU, LRU-K                  │ │
│  └─────────────────┘  └─────────────────┘  └─────────────────────────────┘ │
└─────────────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                      💾 Storage Management Layer                           │
│  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────────────────────┐ │
│  │ createPageFile  │  │   readBlock     │  │      writeBlock             │ │
│  │  openPageFile   │  │  readNextBlock  │  │     writeCurrentBlock       │ │
│  │  closePageFile  │  │ readCurrentBlock│  │     appendEmptyBlock        │ │
│  └─────────────────┘  └─────────────────┘  └─────────────────────────────┘ │
└─────────────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                           📁 File System                                   │
│                        (Page Files, Index Files)                          │
└─────────────────────────────────────────────────────────────────────────────┘

Legend:
├─► Data Flow Direction
└─► Layer Dependencies
```

---

## 📁 Important Files

### 🌳 **Core B+-Tree Implementation**
- **`btree_mgr.c`** & **`btree_mgr.h`** - Main B+-tree index manager implementation
- **`tables.h`** - Data structure definitions for tables and schemas

### 📊 **Record Management System**
- **`record_mgr.c`** & **`record_mgr.h`** - Record manager for table operations
- **`record_mgr_data_structures.c`** & **`record_mgr_data_structures.h`** - Record data structures
- **`rm_serializer.c`** - Record serialization and deserialization utilities

### 🧠 **Buffer Management**
- **`buffer_mgr.c`** & **`buffer_mgr.h`** - Buffer pool management with multiple replacement strategies
- **`buffer_mgr_stat.c`** & **`buffer_mgr_stat.h`** - Buffer statistics and monitoring

### 💾 **Storage Layer**
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
- Navigate to the project directory in your terminal

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

## 🐛 Troubleshooting
If you encounter build errors, ensure:
- All source files are present in the directory
- The makefile is correctly configured
- You have appropriate permissions to create and modify files
