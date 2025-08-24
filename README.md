# 🗄️ Own Database Engine

A comprehensive database engine implementation featuring a multi-layered architecture with storage management, buffer management, record management, and B+ Tree indexing capabilities.

## 📋 Table of Contents
1. [🚀 Project Overview](#project-overview)
2. [🏗️ System Architecture](#system-architecture)
3. [🔧 Core Components](#core-components)
4. [📁 Project Structure](#project-structure)
5. [🚀 Getting Started](#getting-started)
6. [🧪 Testing](#testing)
7. [📚 Learning Outcomes](#learning-outcomes)
8. [🔍 Use Cases](#use-cases)
9. [📝 Notes](#notes)

---

## 🚀 Project Overview

The **Own Database Engine** is a complete database management system that demonstrates fundamental database concepts through a layered architecture. This project serves as both an educational tool and a foundation for understanding how modern database systems work internally.

### 🎯 **Key Objectives**
- Implement a complete database engine from scratch
- Demonstrate multi-layered database architecture
- Provide hands-on experience with database internals
- Showcase efficient data structures and algorithms

---

## 🏗️ System Architecture

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                           🗄️ Database Engine                                │
│                          (User Interface -CLI)                              │
└─────────────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                        🌳 B+-Tree Index Layer                              │
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
```

---

## 🔧 Core Components

### 🌳 **B+ Tree Index Manager**
- **Purpose**: Provides efficient indexing for fast data retrieval and manipulation
- **Features**: 
  - Create, open, close, and delete B+-tree indexes
  - Insert, delete, and search operations
  - Tree scanning capabilities
  - Support for Integer data types
- **Location**: `B+Tree Manger/`

### 📊 **Record Manager**
- **Purpose**: Manages table operations, record storage, and schema handling
- **Features**:
  - Table creation, opening, and deletion
  - CRUD operations (Create, Read, Update, Delete)
  - Conditional scanning with search conditions
  - Schema management and record serialization
- **Location**: `Record Manager/`

### 🧠 **Buffer Manager**
- **Purpose**: Implements memory management with multiple page replacement strategies
- **Features**:
  - Multiple replacement strategies (FIFO, LRU, Clock, LFU, LRU-K)
  - Page pinning and unpinning
  - Dirty page management
  - Buffer pool statistics and monitoring
- **Location**: `Buffer Manager/`

### 💾 **Storage Manager**
- **Purpose**: Handles low-level file I/O operations and page management
- **Features**:
  - Page file creation, opening, and closing
  - Block reading and writing operations
  - Sequential and random page access
  - File capacity management
- **Location**: `Storage Manager/`

---

## 📁 Project Structure

```
Own-Database-Engine/
├── 🌳 B+Tree Manger/          # B+-Tree indexing implementation
├── 🧠 Buffer Manager/         # Buffer pool management
├── 📊 Record Manager/         # Record and table management
├── 💾 Storage Manager/        # File I/O and page management
└── 📖 README.md              
```

---

## 🚀 Getting Started

### Prerequisites
- C compiler (GCC recommended)
- Make utility
- Basic understanding of database concepts

### Building Individual Components
Each component can be built independently:

```bash
# B+-Tree Manager
cd "B+Tree Manger"
make -f makefile.mk

# Buffer Manager
cd "../Buffer Manager"
make -f makefile.mk

# Record Manager
cd "../Record Manager"
make -f makefile.mk

# Storage Manager
cd "../Storage Manager"
make -f makefile.mk
```

### Running Tests
Each component includes its own test suite:

```bash
# B+-Tree Manager
cd "B+Tree Manger"
make -f makefile.mk
./btree_mgr

# Buffer Manager (FIFO)
cd "../Buffer Manager"
make -f make_file.mk
./buffermgr

# Buffer Manager (LRU)
cd "../Buffer Manager"
make -f makefile.mk
./buffer_mgr

# Record Manager
cd "../Record Manager"
make -f makefile.mk
./record_mgr

# Storage Manager (Basic)
cd "../Storage Manager"
make -f makefile.mk
./assign1

# Storage Manager (Advanced)
cd "../Storage Manager"
make -f makefile2.mk
./assign2
```

---

## 🧪 Testing

Each component includes comprehensive test suites:
- **Storage Manager**: Basic and advanced file I/O operations
- **Buffer Manager**: FIFO and LRU replacement strategies
- **Record Manager**: Table operations and record handling
- **B+-Tree Manager**: Index operations and tree management

---

## 📚 Learning Outcomes

This project demonstrates:
- **Database Architecture**: Multi-layered design principles
- **Memory Management**: Efficient buffer pool strategies
- **Data Structures**: B+-tree implementation and optimization
- **File I/O**: Low-level storage management
- **Error Handling**: Robust error management systems
- **Performance Optimization**: Multiple replacement strategies

---

## 🔍 Use Cases

- **Educational**: Learning database internals
- **Research**: Database algorithm experimentation
- **Development**: Foundation for custom database systems
- **Prototyping**: Testing database design concepts

---

## 📝 Notes

- Each component is designed to work independently
- Components can be integrated for full database functionality
- Error handling is consistent across all layers
- Performance optimization is a key focus area
