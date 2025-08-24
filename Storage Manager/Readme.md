# 💾 Storage Manager

A specialized component of the Own Database Engine that handles low-level file I/O operations, page management, and persistent storage operations.

## 📋 Table of Contents
1. [🚀 Getting Started](#getting-started)
2. [🔧 Function Documentation](#function-documentation)
3. [📁 Important Files](#important-files)

---

## 🎯 Component Overview

The **Storage Manager** is the foundational storage layer of the database engine that provides the lowest level of abstraction for file operations. This component handles page-based file management, block I/O operations, and provides the persistent storage foundation for all other database components.

### 🔑 **Key Features**
- **Page File Management**: Create, open, close, and destroy page files
- **Block I/O Operations**: Efficient reading and writing of fixed-size blocks
- **Sequential Access**: Sequential navigation through file pages
- **Random Access**: Direct access to specific page numbers
- **Capacity Management**: Dynamic file expansion and page allocation
- **Fixed Page Size**: Consistent PAGE_SIZE blocks for all operations

### 🎯 **Use Cases**
- Database file system operations
- Page-level storage management
- Low-level I/O performance optimization
- Educational storage system study
- Foundation for higher-level database components

---

## 📁 Important Files

### 💾 **Core Storage Management**
- **`storage_mgr.c`** & **`storage_mgr.h`** - Main storage manager implementation

### 🔧 **Supporting Components**
- **`dberror.c`** & **`dberror.h`** - Error codes and error management system

### 🧪 **Testing & Build**
- **`test_storage_basic.c`** - Basic storage operations test suite
- **`test_storage_advanced.c`** - Advanced storage management tests
- **`test_helper.h`** - Testing framework support
- **`makefile.mk`** - Build configuration

---

## 🚀 Getting Started

### Prerequisites
- Make sure you have a C compiler installed
- Navigate to the Storage Manager directory in your terminal

### Building and Running
```bash
# Build the project
make -f makefile.mk

# Run the storage manager tests
./test_storage_basic
./test_storage_advanced
```

---

## 🔧 Function Documentation

### 🎯 Storage Manager Initialization

#### `initStorageManager()`
- **Purpose**: Initializes the storage management system
- **Action**: Sets up the storage manager for file operations
- **Returns**: Void (no return value)

### 📁 Page File Operations

#### `createPageFile()`
- **Purpose**: Creates a new page file with initial capacity
- **Parameters**: File name
- **Action**: Creates file and initializes with one empty page
- **Returns**: Error code indicating success or failure

#### `openPageFile()`
- **Purpose**: Opens an existing page file for operations
- **Parameters**: File name, file handle structure
- **Action**: Opens file and initializes file handle metadata
- **Returns**: Error code indicating success or failure

#### `closePageFile()`
- **Purpose**: Closes an open page file
- **Parameters**: File handle structure
- **Action**: Closes file and updates metadata
- **Returns**: Error code indicating success or failure

#### `destroyPageFile()`
- **Purpose**: Permanently removes a page file
- **Parameters**: File name
- **Action**: Deletes file from file system
- **Returns**: Error code indicating success or failure

### 📖 Block Reading Operations

#### `readBlock()`
- **Purpose**: Reads a specific block from a page file
- **Parameters**: Page number, file handle, memory buffer
- **Action**: Reads specified page into provided buffer
- **Returns**: Error code indicating success or failure

#### `readFirstBlock()`
- **Purpose**: Reads the first page of a file
- **Parameters**: File handle, memory buffer
- **Action**: Reads first page and updates current position
- **Returns**: Error code indicating success or failure

#### `readPreviousBlock()`
- **Purpose**: Reads the previous page relative to current position
- **Parameters**: File handle, memory buffer
- **Action**: Reads previous page and updates current position
- **Returns**: Error code indicating success or failure

#### `readCurrentBlock()`
- **Purpose**: Reads the page at current position
- **Parameters**: File handle, memory buffer
- **Action**: Reads current page without changing position
- **Returns**: Error code indicating success or failure

#### `readNextBlock()`
- **Purpose**: Reads the next page relative to current position
- **Parameters**: File handle, memory buffer
- **Action**: Reads next page and updates current position
- **Returns**: Error code indicating success or failure

#### `readLastBlock()`
- **Purpose**: Reads the last page of a file
- **Parameters**: File handle, memory buffer
- **Action**: Reads last page and updates current position
- **Returns**: Error code indicating success or failure

### ✍️ Block Writing Operations

#### `writeBlock()`
- **Purpose**: Writes a specific block to a page file
- **Parameters**: Page number, file handle, memory buffer
- **Action**: Writes buffer content to specified page
- **Returns**: Error code indicating success or failure

#### `writeCurrentBlock()`
- **Purpose**: Writes to the page at current position
- **Parameters**: File handle, memory buffer
- **Action**: Writes buffer content to current page
- **Returns**: Error code indicating success or failure

### 🔧 Utility Functions

#### `getBlockPos()`
- **Purpose**: Gets the current block position in a file
- **Parameters**: File handle
- **Returns**: Current page number (0-indexed)

#### `appendEmptyBlock()`
- **Purpose**: Adds a new empty page to the end of a file
- **Parameters**: File handle
- **Action**: Extends file by one page and updates metadata
- **Returns**: Error code indicating success or failure

#### `ensureCapacity()`
- **Purpose**: Ensures file has specified number of pages
- **Parameters**: Number of pages, file handle
- **Action**: Extends file if necessary to meet capacity requirement
- **Returns**: Error code indicating success or failure

---

## 📊 Data Structures

### **SM_FileHandle**
```c
typedef struct SM_FileHandle {
  char *fileName;        // Name of the page file
  int totalNumPages;     // Total number of pages in file
  int curPagePos;        // Current page position (0-indexed)
  void *mgmtInfo;        // Management information
} SM_FileHandle;
```

### **SM_PageHandle**
```c
typedef char* SM_PageHandle;  // Pointer to page data buffer
```

---

## 📝 Notes
- All pages have a fixed size defined by PAGE_SIZE
- Page numbers are 0-indexed
- File operations maintain current position for sequential access
- Error handling is consistent across all operations
- Files are automatically extended when needed

## 🐛 Troubleshooting
If you encounter build errors, ensure:
- All source files are present in the directory
- The makefile is correctly configured
- You have appropriate permissions to create and modify files
- PAGE_SIZE constant is properly defined

## 🔗 Integration
This component is designed to work with:
- **Buffer Manager**: For page-level memory management
- **Record Manager**: For table file operations
- **B+-Tree Manager**: For index file operations
- **Higher-level Components**: For complete database functionality

## 📊 Performance Considerations
- **Page Size**: Optimize PAGE_SIZE for your storage system
- **Sequential Access**: Use sequential operations when possible
- **File Positioning**: Minimize random access operations
- **Capacity Planning**: Pre-allocate capacity when known
- **Error Handling**: Implement proper error recovery for production use

## 🔍 Implementation Details
- **File Format**: Binary page files with fixed-size blocks
- **Page Layout**: Each page contains raw data without metadata
- **Position Tracking**: Current position is maintained for sequential operations
- **Capacity Management**: Files are automatically extended as needed
- **Error Recovery**: Robust error handling for file system operations
