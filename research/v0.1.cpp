#include <iostream>
#include <filesystem>
#include <string>

int main(){

    std::filesystem::path p1 = std::filesystem::current_path();

    std::cout << p1 << '\n';

    for(auto const& dir_entry : std::filesystem::directory_iterator{p1}){
        std::cout << dir_entry.path().filename() << '\n';
    }


    return 0;
}