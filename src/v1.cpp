#include <iostream>
#include <string>
#include <filesystem>
#include <system_error>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <vector>
#include <iomanip>

void recursive_directory_iterator(
    std::filesystem::path dir, 
    std::string search_term, 
    int &len,
    std::vector<std::filesystem::directory_entry> &results,
    int &inaccessible
);
std::string str_tolower(std::string s);
void output_format(std::vector<std::filesystem::directory_entry> results, int longest_name);

int main(int argc, char **argv)
{

    if (argc == 1)
    {
        std::cerr << "Error: No search term provided!\n";
        return 1;
    }
    else if (argc >= 3)
    {
        std::cerr << "Error: Too many search terms. Please provide only one search term!\n";
        return 1;
    }

    std::string search_term = argv[1];
    std::string lowered_search_term = str_tolower(search_term);

    std::filesystem::path home = getenv("HOME"); //Add a check to make sure the HOME path exists.
    //std::filesystem::path test = "."; // Test path

    std::vector<std::filesystem::directory_entry> results;
    int longest_fn_len = 0;
    int inaccessible = 0;

    // Recursively iterates over all files and directories located in the user's home directory
    recursive_directory_iterator(home, lowered_search_term, longest_fn_len, results, inaccessible);

    ++longest_fn_len;
    output_format(results, longest_fn_len);
    if (inaccessible == 1)
    {
        std::cout << "Some directories could not be searched due to an error!" << '\n';
    }


    return 0;
}

// -------------------------------------------------------------------------------------------------------------------

void recursive_directory_iterator(
    std::filesystem::path dir, 
    std::string search_term, 
    int &len,
    std::vector<std::filesystem::directory_entry> &results,
    int &inaccessible
)
{
    for(auto const& dir_entry : std::filesystem::directory_iterator{dir})
    {
        if(!(dir_entry.is_symlink()) && dir_entry.is_directory())
        {
            // std::cout << "Directory found: " << dir_entry.path() << '\n' << '\n';
            std::filesystem::path dir = dir_entry.path();
            std::string dirname = dir.filename();

            if(str_tolower(dirname).find(search_term) != dirname.npos)
            {
                if (dirname.length() > len)
                {
                    len = dirname.length();
                }
                results.push_back(dir_entry);
            }

            try{
                recursive_directory_iterator(dir, search_term, len, results, inaccessible);
            }
            catch(...){
                // std::cerr << "Unable to access directory at: " << dir << '\n';
                inaccessible = 1;
            }
        }
        else
        {
            std::string dir_path = dir_entry.path();
            std::string filename = dir_entry.path().filename();

            if(str_tolower(filename).find(search_term) != filename.npos)
            {
                if (filename.length() > len)
                {
                    len = filename.length();
                }
                results.push_back(dir_entry);
            }
        }
    }
}

// -------------------------------------------------------------------------------------------------------------------

/*
Function: Takes in a string, transform any character that has a lowercase form into that form in place, then return the 
string.
Input: A std::string s
Output: A std::string s
Example: 
Given the input std::string s = "ABC"
The expected output would be std::string s = "abc"
*/
std::string str_tolower(std::string s)
{
    //Casts the input and output to be of type unsigned char to prevent undefined behaviour as a result of using tolower()
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return tolower(static_cast<unsigned char> (c));});

    return s;
}

// -------------------------------------------------------------------------------------------------------------------

void output_format(std::vector<std::filesystem::directory_entry> results, int longest_name)
{
    for (std::filesystem::directory_entry dir_entry : results)
    {
        std::cout << std::setw(longest_name) << std::left << dir_entry.path().filename() << std::left << '\t' << dir_entry.path() << '\n';
    }
}
