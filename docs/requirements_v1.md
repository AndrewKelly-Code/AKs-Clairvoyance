# Search File Engine V1 - Requirements Analysis

## 1. Introduction

### 1.1 Purpose
The purpose of the product is to allow for users of a macOS device to be able to search for and retrieve the location of relevant files and directories that were specified by the user's input

### 1.2 Problem Statement
Personal computers could have very large amount of files and directories, which makes it tedious, time-comsuming, and error proned when trying to find a specific file or directory manually. 

### 1.3 Intended User Group
The intended user group for this product is all user that owns a personal computer that runs on the macOS. 

## 2. Project Scope

### 2.1 In Scope
1. The application shall take an input from the user, which is exactly one string
2. The application shall use an internal pattern matching system to retrieve files and directories that matches the input given by the user
3. The application shall display the result in a format that shows the name and location of the retrieved files and directories
4. Everything must happen inside the terminal of the user's personal computer
5. The application shall always begin its search from the user's home directory

### 2.2 Out of Scope
1. The application shall not have a Graphics User Interface
2. The application shall not allow users to search from the current working director
3. The application shall not allow users to search using a specified path
4. The application shall not allow users to execute or open files or directories through the application
5. The application shall not provide users with the ability to navigate between directories
6. The application shall not support searches of external storage devices
7. The application shall not have a internal ranking system for how results shall be displayed

## 3. Functional Requirements

### FR-01: Recursive Directory Traversal
The application shall be able to recursively traverse through the home directory and all accessible subdirectories, listing the files and directories it encountered.
### FR-01 Acceptance Critieria:
1. The application shall identify all files and directories located directly within that test directory.
2. The application shall also be able to identify files and directories inside subdirectories that are located in the test directory, regardless of depth.

## FR-02: Full Path Retrival 
The application shall retrive the full path of the files that it identifies during traversal.
### FR-02 Acceptance Criteria:
1. The application shall identify the full path of the files and directories of the home directory
2. The application shall also identify the full path of the files and directories located inside the subdirectories of the home directory, no matter the depth.

### FR-03: Output Format
The application shall display the retrieved file name and full path in two columns. The first column is located to the left and will contain the name of the file or directory. The second column located to the right of the first shall contain the full path of the file or directory on that same line. 
### FR-03 Acceptance Criteria:
1. The application shall retrieve the name of the files and directories directly inside the home directory, and inside the subdirectories no matter the depth.
2. The output of the result shall have the name of the file or directory inside the first column 
3. The full path of the file or directory shall be displayed in the second column.
4. Every displayed full path shall correctly identify the corresponding file or directory within the filesystem

### FR-04: Case Insensitive Substring Pattern Matching
The application shall match the user's query using case-insensitive, substring pattern matching against filenames and directories it encounters during directory traversal
### FR-04 Acceptance Criteria:
1. A test directory shall be created with files that contain the substring photo, such as Photo.jpg, cat_photos.jpg, etc... along with file names that don't match the query, such as dog_image.jpg.
2. The application shall be invoked using the specified unique command, followed by the search term "photo". 
3. The application shall return all files and directories that it encounters that contains the search term as a substring, regardless of case sensitivity.
4. Each entry shall only be returned once

### FR-05: Invoking the Application
The application shall provide a command-line interface that allow users to invoke the application from the command line
### FR-05 Acceptance Criteria:
1. The unique command term, followed by the search query shall be given as an input into the command-line of the terminal
2. The application shall then perform the search of the provided query 
3. If no search query was provided, the application shall display an error message that a search query must be provided for the application to function

### FR-06: Inaccessible Directory Handling
The system shall print out an error message in the terminal at the end of the search, without terminating the search
### FR-06 Acceptance Criteria
1. A test directory will be created that contains a directory that is known to require escalated privilages to access
2. The application is invoked with a search query
3. The application shall return all the files and directories that matches the search query, and is accessible by the applciation, dispite encountering inaccessible files.
4. The application shall continue to search for files and directories without terminating early when encountering an inaccessible file
5. The application shall print a message in the terminal after the result, saying that certain directories were inaccessible during the search

## 4. Non-Functional Requirements

### NFR-01: Latest macOS Version Support
The application shall be supported on macOS Tahoe version 26.5.2
### NFR-01 Acceptance Criteria: 
1. The application compiles on the specified macOS version.
2. The compiled application should be able to execute without platform related errors.
3. The application is able to pass all automated functional requirement tests.

## 5. Assumptions and Constraints


