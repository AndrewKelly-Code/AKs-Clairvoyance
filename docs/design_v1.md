# Design Analysis
status: draft | date: 22-10-26 | version: 1.0 <br>
- Related documents: requirements_v1.md

## 1. Introduction
This document describes the proposed technical solution to implement the version 1 of a command-line file search application for macOS devices. The application is to complete recursive directory traversal to locate the file that matches the query supplied by the user.

## 2. Design Goals and Constraints
1. The application must be used in the command-line interface 
2. The application must compile, execute and successfully complete all automated test on a macOS device
3. The application is to be developed using C++ and its Standard libraries
4. The application must locate and return files matching the search query without using an index
5. The application must continue searching if it encounters a directory that it cannot access

## 3. System Architecture

## 4. Component Design
### 4.1 Command-line Entry Point
**Responsibility:** 
- This component is responsible for invoking the application, taking a user input from the command-line argument using argc and argv, validating the input and initiating the search of the filesystem. It will also print out appropriate error messages to the terminal using std::cerr for errors that occurs inside this component.
**Inputs:**
- The input for this component is one string, taken from as a command-line argument through argc and argv[]. This input is the search term that will be used to match file and directory names.
- An example of a valid input would be "query photos", where query invokes the application and photos is the search term used to match file and directory names.
- Examples of invalid inputs would be:
    - "query" | Too few arguments provided
    - "query cat photos" | Too many arguments provided
**Output:**
- Passes the validated serach term to the search component. 
- It will display an appropriate error message to the terminal for the specific errors that can be encountered in this component.
**Dependency:**
- None, it does not depend on any other internal or external application component

### 4.2 File System Search and Traversal
**Responsibilities:**
- This component is reponsible for traversing the file system of the macOS device, retrieving files and directories that matches the user's search query, and storing the files inside an appropriate structure. 
- If it encounters a directory that it could not access, it will continue it search and print out a simple error message stating that it could access certain directories. 
**Inputs:**
- It takes one string provided by the user through the command line after the input has been validated by the Command-Line Entry Point component.
**Outputs:**
- A list of files and directories, along with the path to those files and directories. 
- An error message stating that it cannot access certain directories, if it came across one that it could not access
**Dependencies:**
- Depends on componenet 4.1 to validate the input
### 4.2.1 File Name Matching 
**Respoonsibility:**
- Matches the name of a file to the search term. The files will be match according to whether or not the file contains a substring that matches exactly to the search term provided.
**Inputs:**
- One string from the command-line terminal
**Outputs:**
- Files and directories whose name contains the substring that matches the input string
**Dependencies:**
- Validated input from the user
- std::string to be able to use functions available to that library for substring pattern matching

## 5. Data and Control Flow

## 6. Error Handling and Edge Cases

## 7. Design Decisions and Trade-offs
### 7.1 Command-Line Arguments VS. Interactive Inputs
- Using argc and argv over std::cin

