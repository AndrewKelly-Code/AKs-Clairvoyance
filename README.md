# Clairvoyance version 1.0.0 - A MacOS File Search Engine
## 1. Overview
A lightweight command-line file search application written in C++. It recursively searches the user's home directory for files and directories matching a specified search term and displays matching results with their full paths.

## 2. Features
### Recursive Directory Iteration
- The program is able to recursively search through all directories it has access to.
- It continues to search even when it encounters an error, making sure that all directories that it has permissions for are reached before returning the results.
### File and directory retrival
- It retrieves the name and full path of the files and directories that matches the search query provided by the user.
- It only takes in one string for matching.
- It uses substring matching, with case-insensitivity.
### Output Formatting
- It formats the results into two columns for better readability
- The first column displays the file or directory name
- The second column displays the full path associated with the file or directory in the first column

## 3. Prerequisites
- A macOS device of at least version 26.5.2 (Different version of macOS has not been manually tested, but should still work for version 1 of this app)
- Clang or another C++ compiler 
- C++ version 17 or newer
- A command line interface
- Git

## 4. Installation & build
1. Clone the repository into your preferred directory using the following command: <br>
git clone https://github.com/AndrewKelly-Code/clairvoyance.git 

2. Navigate into the directory labelled src

3. Build the program using the following command: <br>
clang++ -std=c++17 v1.cpp -o query

4. Run the program using the following command in the src directory: <br>
./query search-term | less -S

<br>Where search-term is replaced by the string that you wish for the program to match the files it found against. It's case-insensitive

5. You will be asked by the system to grant permission to allow the app that you're using the command-line interface (CLI) to launch this program in, the default being Terminal, to access certain restricted directories. If you do not allow access to these directories, the program will not be able to search the contents inside those directories. <br>
NOTE: Granting access to those directories are not just for this program, but all programs that are ran through the command-line interface. This can be managed in the system's settings.

6. You can quit out of the pager view by pressing q on your keyboard

## 5. Examples

## 6. Known Limitations
- The program does not provide the user with the ability to open or launch the files and directory found
- The program does not provide the user with the ability to traverse into the directory that is displayed in the output
- The program only takes one string as an argument to be used for the search
- The program only does a exact match, with case-insensitivity, for the search term entered
- The program does not display which directories it did not have access to 

## 7. Testing
V1 was tested manually during development by executing the program through the terminal and inspecting its behaviour and output.

Individual functions were also tested informally during development. No automated test suite is currently included.

## 8. Documentations
- The requirements documentation are located in /docs/requirements_v1.md
- The designs documentation are located in /docs/design_v1.md
- The implementation documentation for some features are located in /docs/implementation_notes.md

## 9. Future Improvements
- The ability to search at different locations
- The ability to search with multiple different search terms
- The output would first display the directories found, before displaying the regular files found
- The program would have an internal ranking system that would rank each results based on rules
- The results displayed would be based on the internal score received by the internal ranking system, where the results are displayed based on score from highest to lowest
- The program will match files and directories based on other conditions, not just substrings
- The program will have the ability to display the information properly without needing the user to explicitly use | less -S



