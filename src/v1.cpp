#include <iostream>
#include <string>
#include <filesystem>
#include <system_error>
#include <cstdlib>

void recursive_directory_iterator(std::filesystem::path dir);

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

    std::filesystem::path home = getenv("HOME"); // Change this to the path of the user's home directory

    // Recursively iterates over all files and directories located in the user's home directory
    recursive_directory_iterator(home);

    return 0;
}

void recursive_directory_iterator(std::filesystem::path dir)
{
    for(auto const& dir_entry : std::filesystem::directory_iterator{dir})
    {
        if(dir_entry.is_directory())
        {
            std::cout << "Directory found: " << dir_entry.path() << '\n' << '\n';
            std::filesystem::path dir = dir_entry.path();
            try{
                recursive_directory_iterator(dir);
            }
            catch(...){
                std::cerr << "Unable to access directory at: " << dir << '\n';
            }
        }
        else
        {
            std::cout << dir_entry.path() << '\n';
        }
    }
}