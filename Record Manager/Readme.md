# 📊 Record Manager

A specialized component of the Own Database Engine that handles table operations, record storage, and schema management with comprehensive CRUD operations.

## 📋 Table of Contents
1. [Component Overview](#component-overview)
2. [Getting Started](#getting-started)
3. [Important Files](#important-files)
4. [Function Documentation](#function-documentation)
6. [Notes](#notes)
7. [Troubleshooting](#troubleshooting)
8. [Integration](#integration)
9. [Performance Considerations](#performance-considerations)

---

## Component Overview

The **Record Manager** is the table and record management layer of the database engine that handles all operations related to tables, records, and schemas. This component provides a complete interface for creating, modifying, and querying database tables with flexible schema support.

### 🔑 **Key Features**
- **Table Management**: Create, open, close, and delete tables
- **CRUD Operations**: Complete Create, Read, Update, Delete functionality
- **Schema Management**: Flexible table schema definition and management
- **Conditional Scanning**: Search and filter records based on conditions
- **Record Serialization**: Efficient record storage and retrieval
- **Buffer Integration**: Seamless integration with buffer manager for performance

### 🎯 **Use Cases**
- Database table operations
- Record-level data management
- Schema design and modification
- Conditional data retrieval
- Educational database operations study

---

## Getting Started

### Prerequisites
- Make sure you have a C compiler installed
- Navigate to the Record Manager directory in your terminal

### Building and Running
```bash
# Build the project
make -f makefile.mk

# Run the record manager tests
./test_record_operations
```

---

## Important Files

### 📊 **Core Record Management**
- **`record_mgr.c`** & **`record_mgr.h`** - Main record manager implementation
- **`record_mgr_data_structures.c`** & **`record_mgr_data_structures.h`** - Record data structures

### 🔄 **Record Operations**
- **`rm_serializer.c`** - Record serialization and deserialization utilities

### 🧠 **Buffer Integration**
- **`buffer_mgr.c`** & **`buffer_mgr.h`** - Buffer pool management integration
- **`buffer_mgr_stat.c`** & **`buffer_mgr_stat.h`** - Buffer statistics

### 💾 **Storage Integration**
- **`storage_mgr.c`** & **`storage_mgr.h`** - Low-level file I/O operations

### 🔧 **Supporting Components**
- **`expr.c`** & **`expr.h`** - Expression evaluation and condition handling
- **`dberror.c`** & **`dberror.h`** - Error codes and error management system
- **`dt.h`** - Common data type definitions
- **`tables.h`** - Table and schema data structures

### 🧪 **Testing & Build**
- **`test_record_operations.c`** - Main test suite for record management
- **`test_expr.c`** - Expression testing utilities
- **`test_helper.h`** - Testing framework support
- **`makefile.mk`** - Build configuration

---

## Function Documentation

### 🎯 Table Management

#### `initRecordManager()`
- **Purpose**: Initializes the Record Manager
- **Action**: Sets up the record management system
- **Returns**: Error code indicating success or failure

#### `shutdownRecordManager()`
- **Purpose**: Cleanly shuts down the Record Manager
- **Action**: Frees allocated resources and closes open tables
- **Returns**: Error code indicating success or failure

#### `createTable()`
- **Purpose**: Creates a new table with specified schema
- **Parameters**: Table name, schema definition
- **Action**: Creates table file and initializes table structure
- **Returns**: Error code indicating success or failure

#### `openTable()`
- **Purpose**: Opens an existing table for operations
- **Parameters**: Table data structure, table name
- **Action**: Loads table metadata and prepares for operations
- **Returns**: Error code indicating success or failure

#### `closeTable()`
- **Purpose**: Closes an open table
- **Parameters**: Table data structure
- **Action**: Flushes changes and releases table resources
- **Returns**: Error code indicating success or failure

#### `deleteTable()`
- **Purpose**: Permanently removes a table
- **Parameters**: Table name
- **Action**: Deletes table file and all associated data
- **Returns**: Error code indicating success or failure

### 📝 Record Operations

#### `insertRecord()`
- **Purpose**: Inserts a new record into a table
- **Parameters**: Table data, record to insert
- **Action**: Adds record to table and updates metadata
- **Returns**: Error code indicating success or failure

#### `deleteRecord()`
- **Purpose**: Removes a record from a table
- **Parameters**: Table data, record ID (RID)
- **Action**: Removes record and updates table metadata
- **Returns**: Error code indicating success or failure

#### `updateRecord()`
- **Purpose**: Modifies an existing record
- **Parameters**: Table data, updated record
- **Action**: Replaces existing record with new data
- **Returns**: Error code indicating success or failure

#### `getRecord()`
- **Purpose**: Retrieves a specific record from a table
- **Parameters**: Table data, record ID (RID), record buffer
- **Action**: Loads record data into provided buffer
- **Returns**: Error code indicating success or failure

### 🔍 Scanning and Search

#### `startScan()`
- **Purpose**: Initiates a table scan with search conditions
- **Parameters**: Table data, scan handle, search condition
- **Action**: Sets up scan context and prepares for iteration
- **Returns**: Error code indicating success or failure

#### `next()`
- **Purpose**: Retrieves the next record in a scan
- **Parameters**: Scan handle, record buffer
- **Action**: Loads next matching record into buffer
- **Returns**: Error code indicating success or failure

#### `closeScan()`
- **Purpose**: Closes an active table scan
- **Parameters**: Scan handle
- **Action**: Cleans up scan resources
- **Returns**: Error code indicating success or failure

### 🏗️ Schema Management

#### `createSchema()`
- **Purpose**: Creates a new table schema
- **Parameters**: Number of attributes, attribute names, data types, type lengths, key info
- **Action**: Allocates and initializes schema structure
- **Returns**: Pointer to created schema

#### `freeSchema()`
- **Purpose**: Frees a schema structure
- **Parameters**: Schema to free
- **Action**: Deallocates schema memory
- **Returns**: Error code indicating success or failure

#### `getRecordSize()`
- **Purpose**: Calculates the size of a record with given schema
- **Parameters**: Schema definition
- **Returns**: Size in bytes of a record

### 🔧 Record Utilities

#### `createRecord()`
- **Purpose**: Allocates a new record structure
- **Parameters**: Record pointer, schema
- **Action**: Creates and initializes record buffer
- **Returns**: Error code indicating success or failure

#### `freeRecord()`
- **Purpose**: Frees a record structure
- **Parameters**: Record to free
- **Action**: Deallocates record memory
- **Returns**: Error code indicating success or failure

#### `getAttr()`
- **Purpose**: Retrieves an attribute value from a record
- **Parameters**: Record, schema, attribute number, value buffer
- **Action**: Extracts attribute value into buffer
- **Returns**: Error code indicating success or failure

#### `setAttr()`
- **Purpose**: Sets an attribute value in a record
- **Parameters**: Record, schema, attribute number, new value
- **Action**: Updates attribute value in record
- **Returns**: Error code indicating success or failure

---

## Notes
- Each table is stored in a separate page file
- Records are accessed through the buffer manager for optimal performance
- Schema modifications require table recreation
- Scan operations support complex search conditions
- Error handling is consistent across all operations

## Troubleshooting
If you encounter build errors, ensure:
- All source files are present in the directory
- The makefile is correctly configured
- You have appropriate permissions to create and modify files
- Dependencies from other components are properly linked

## Integration
This component is designed to work with:
- **Buffer Manager**: For page-level memory management
- **Storage Manager**: For file I/O operations
- **B+-Tree Manager**: For index operations
- **Expression System**: For search condition evaluation

## Performance Considerations
- **Table Size**: Larger tables benefit from proper indexing
- **Scan Operations**: Use appropriate search conditions to limit results
- **Buffer Usage**: Leverage buffer manager for frequently accessed pages
- **Schema Design**: Optimize attribute ordering for common access patterns



