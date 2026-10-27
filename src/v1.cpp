#include <iostream>
#include <string>
#include <filesystem>
#include <system_error>
#include <cstdlib>
#include <cctype>
#include <algorithm>

void recursive_directory_iterator(std::filesystem::path dir, std::string search_term);
std::string str_tolower(std::string s);

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

    // Recursively iterates over all files and directories located in the user's home directory
    recursive_directory_iterator(home, lowered_search_term);

    return 0;
}

void recursive_directory_iterator(std::filesystem::path dir, std::string search_term)
{
    for(auto const& dir_entry : std::filesystem::directory_iterator{dir})
    {
        if(dir_entry.is_directory())
        {
            // std::cout << "Directory found: " << dir_entry.path() << '\n' << '\n';
            std::filesystem::path dir = dir_entry.path();
            try{
                recursive_directory_iterator(dir, search_term);
            }
            catch(...){
                // std::cerr << "Unable to access directory at: " << dir << '\n';
            }
        }
        else
        {
            std::string result = dir_entry.path();

            if(str_tolower(result).find(search_term) != result.npos)
            {
                std::cout << dir_entry.path() << '\n';
            }
        }
    }
}

std::string str_tolower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return tolower(c);});

    return s;
}