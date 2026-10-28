# Design Analysis
status: draft | date: 22-10-26 | version: 1.0 <br>
- Related documents: requirements_v1.md

## 1. Introduction
This document describes the proposed technical solution to implement the version 1 of a command-line file search application for macOS devices. The application is to complete recursive directory traversal to locate the file that matches the query supplied by the user.

## 2. Design Goals and Constraints
1. The application must be used in the command-line interface 
2. The application is to be developed using C++ and its Standard libraries
3. The application must locate and return files matching the search query without using an index
4. The application must continue searching if it encounters a directory that it cannot access

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
- If it encounters a directory that it could not access, it will continue its search, until it has reached all files and directories that it has access to
**Inputs:**
- It takes one string provided by the user through the command line after the input has been validated by the Command-Line Entry Point component.
**Outputs:**
- A list of files and directories, along with the path to those files and directories. 
- An error message stating that it cannot access certain directories, if it came across one that it could not access, without printing out the exact error, or which directory it could not access.
**Dependencies:**
- Depends on componenet 4.1 to validate the input
### 4.2.1 File Name Matching 
**Respoonsibility:**
- Matches the name of a file to the search term. The files will be match according to whether or not the file contains a substring that matches the search term provided, with case-insensitivity.
**Inputs:**
- One string from the command-line terminal
**Outputs:**
- Files and directories whose name contains the substring that matches the input string with case-insensitivity
**Dependencies:**
- Valid input from the user
- Custom tolower() function to transform an input into its lowercase form.
### 4.3 Output Formatting
**Responsibility**
- It's responsible for displaying the results of the program using two columns for each row. 
**Inputs**
- The vector containing the results from the recursive directory iterator function
- The length of the longest filename name found
**Outputs**
- two columns, the first column containing only the filename, the second containing the full path to the associated filename in the first column
- The columns must be align for each row
**Dependencies**
- The recursive directory iterator function

## 5. Data and Control Flow
1. A user would call the app from the CLI in the terminal, supplying it will one string which is the search query.
2. The string would be passed into Main, which would check to see if the correct amount of arguments were given by the user
3. The string would be passed into the recursive directory iterator
4. The recursive directory iterator function would search through all files it has access to, starting at the user's home directory.
5. It would store the results that matches the search query in a vector that was supplied to the function by reference
6. The result vector would then be passed to the output function, which would display the filename and path of the objects stored inside the vector

## 6. Error Handling and Edge Cases
- Appropriate messages are printed to the user in regards to the number of arguments supplied from the terminal
- Currently, only one vague message saying that some directories could not be searched due to an error. Future iterations of the application would make it more clear which directories it did not have access to.

## 7. Design Decisions and Trade-offs
### 7.1 Command-Line Arguments VS. Interactive Inputs
- Using argc and argv over std::cin 
- This is done because it's expected that the user would execute the command and would not be required to interact with the program further while it's running. 
### 7.2 std::filesystem::directory_iterator VS. std::filesystem::recursive_directory_iterator
- directory_iterator was chosen over recursive_directory_iterator as the program required finer control over how it would handle inaccessibly directories, particularly directories that produced a "Operation Not Permitted" or EPERM errors.
- recursive_directory_iterator would terminate prematurely before all files and directories that it had access to was searched, so I needed to create a wrapper function around directory_iterator that reproduced the functionality of recursive_directory_iterator, but still continued to search after it encounters any errors.


