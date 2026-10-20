# V0.1 Technical Research
## Goals for this research
- Be able to obtain the path to the current directory
- Be able to list the files inside the current directory
- Be able to list the files inside a given directory, taken from the user's input from the terminal
- Be able to continue searching for files if the system comes across a file that it doesn't have permission for
- Be able to list all the files it found that it could not access
- Be able to terminate the search with an appropriate error message when it is given a path that doesn't exist

## Main sources to investigate
- std::filesystem on cppreference
    - For file discovery 
