#include <iostream>

int main(int argc, char** argv){

    if (argc == 1){
        std::cerr << "Error: No search term provided!\n";
    }
    else if (argc >= 3){
        std::cerr << "Error: Too many search terms. Please provide only one search term!\n";
    }
    
    return 0;
}