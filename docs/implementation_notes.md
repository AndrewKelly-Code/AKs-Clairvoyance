# Recursive Directory Iterator Function Using directory_iterator
## Why it's needed
- This function is needed to allow for recursive directory iterating, no matter the depth, while also providing more flexibility to handle errors
## Previous consideration
- Previously, an implementation using recursive_directory_iterator was used, but it wasn't able to reliably handle EPERM or "Operation Not Permitted" system error on macOS devices.
- When this was encountered, it would turn the recursive_directory_iterator into an end iterator, which cannot be used to continue directory traversal.
- A copy of the iterator could not be made either, as the copy would be pointing to the same iterator object, which would still suffer from the same issues
- It was also not possible to return the iterator back to the state it was previously in before it turned into an end iterator when an error is encountered.
- There was also no built in options from the standard library that allows the app to skip files that would produce the EPERM system error.
## Proposed solution
- I would create a for loop that loops through all files and directory that the location that I specified, which is the user's home path. 
- I would then check each file to see if it's a regular file or a directory
- This is possible as every object returned by directory_iterator is a directory_entry object which supports the class functions is_regular_file, and is_directory which returns a bool for if the current object is a regular file or a directory respectively.
- If it's a regular file, it would print out the path to that file in the terminal
- If it's a directory, it would then call this function again, but this time the directory supplied to directory_iterator would be the path to the file that's currently being pointed to by the parent iterator
- The end condition for the recursive function is when all iterators instances of the iterator becomes an end iterator, either through iterating over all objects in their directory, or encountering an error.
- Since this function is being built to handle "Operation Not Permitted" errors, I expect that it can also handle "Access Denied" errors as well, as the only thing this is concerned with is that the directory traversal continues after it encounters an error.
## Input
- A std::filesystem::path variable that stores the path that the directory is located at
## Expected output
- The function is void, as it's only expected to print out the path of the files located inside it
- If given a directory structure such as:
home_dir: file1, file2, dir1, dir2
dir1: file3, file4
dir2: file5, file6
The expected output would be:
file1, file2, dir1, file3, file4, dir2, file5, file6
- Using the same directory structure as above, but this time there's an "Operation Not Permitted" or a "Access Denied" error, the expected output would be:
file1, file2, dir1, error, dir2, file5, file6
## Error Handling
- For now, I won't have the function specifically handle the error message printing, but in the future I expect myself to implement a exception handler inside this function that catches the exception thrown by the child iterator when ever it encounters an error, and print out a message to the terminal such as "Unable to access the directory: {directory_path}" or something similar
- A try-catch block was used to handle exception thrown by directory_iterator as I just found out that exceptions, if not caught by the function that called it, will be thrown to the parent function. This will continue until it's either caught or it terminates the program prematurely. 
- The current implementation uses a catch-all block that just cerr the message that says that the program was unable to access a certain path.

## Possible Logic Problems
- It might be possible that the iterator never becomes an end iterator in certain circumstances. I'm not sure of when that's possible just yet, but I'm pretty sure that I've seen it in documentation somewhere that it is possible.