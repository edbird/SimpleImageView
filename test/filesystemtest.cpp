

#include <string>
#include <iostream>
#include <filesystem>


int main()
{
    
    std::string path = ".";
    for(const auto &entry: std::filesystem::directory_iterator(path))
    {
        std::cout << "this ..." << std::endl;
        std::string path_string = entry.path();
        std::cout << path_string << std::endl;
        std::cout << std::endl;

        std::cout << "... should be the same as this ..." << std::endl;
        std::cout << entry.path() << std::endl;
        std::cout << "... but it isn't" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    }


    return 0;
}