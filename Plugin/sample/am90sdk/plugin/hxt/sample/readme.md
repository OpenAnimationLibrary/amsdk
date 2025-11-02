# Microsoft Foundation Class Library: `sample`

---

## Overview

This sample DLL was created for you by the **Class Wizard**.  
The DLL demonstrates the basic use of the **Microsoft Foundation Classes (MFC)** and serves as a starting point for creating your own DLLs.

This document summarizes all the components that make up your `sample` DLL.

---

## Project Components

### `sample.dsp`
This project file contains project-level information and is used to build a single project or subproject.  
Other users can share the `.dsp` file but should export their makefiles locally.

### `sample.h`
The main header file for the DLL, where the class **`CSampleApp`** is declared.

### `sample.cpp`
The main source file for the DLL. This file contains the implementation of **`CSampleApp`**.

### `sample.rc`
A listing of all Microsoft Windows resources used by the program.  
It includes icons, bitmaps, and cursors stored in the **`RES`** subdirectory.  
This file can be directly edited within **Microsoft Visual C++**.

### `sample.clw`
Contains information used by the **Class Wizard** to edit existing classes or add new ones.  
It also stores data required to build and modify message maps, dialog data maps, and prototype member functions.

### `res\sample.rc2`
Holds resources that are **not edited** by Microsoft Visual C++.  
Place any resources that cannot be edited by the Resource Editor here.

### `sample.def`
Contains DLL-specific information required for execution under Microsoft Windows.  
Defines parameters such as the **name**, **description**, and **exported functions** of the DLL.

---

## Other Standard Files

### `StdAfx.h`, `StdAfx.cpp`
Used to create **precompiled header files** (`sample.pch`) and a **precompiled type file** (`StdAfx.obj`).

### `Resource.h`
The standard header file that defines new resource IDs.  
Microsoft Visual C++ reads and updates this file automatically.

---

## Additional Notes

The **Class Wizard** inserts `TODO:` comments in the source code to indicate  
where you can add or modify functionality.

---
