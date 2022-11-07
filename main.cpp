#include <iostream>
#include <fstream>
#include "include/ReadWrite.h"
// #include "boost/filesystem.hpp"
#include <filesystem>

namespace fs = std::filesystem;

int main()
{
    CReadWrite rw("demoFile.bin","/home/skhan/dummy_projects/fileReadWrite/ReadWrite/src/binaryTextfile");
    // for (int i = 1 ; i <= 5; i++)
    // {
    // rw.writeFile("This is demo Msg " + std::to_string(i));
    // }

    for (int i = 1; i < 4; i++)
    {
        std::string str = rw.readFile();
        if (str == "")
        {
            break;
        }
        else {
            std::cout << str << std::endl;
        }
    }

    std::ifstream input;
    input.open("/home/skhan/dummy_projects/fileReadWrite/ReadWrite/src/binaryTextfile/file_offset.bin",std::ios::in);
    if (input.is_open())
    {
        int off;
        input.read((char *)&off, sizeof(int));
        std::cout << "final offset " << off << std::endl;
    }
    input.close();
    // fs::path filePath = "/home/skhan/dummy_projects/fileReadWrite/ReadWrite/src/binaryTextfile";
    // if (fs::exists(filePath) && fs::is_directory(filePath))
    // {
    //     std::cout << "Directory Exists" << std::endl;
    // }
    // else if (fs::exists(filePath) && fs::is_regular_file(filePath))
    // {
    //     std::cout << "File Exists. File size is " << fs::file_size(filePath) << std::endl;
    // }
    // else{
    //      std::cerr << "Directory Does not Exists" << std::endl;
    // }

    std::cout << "Done Writing" << std::endl;
    return 0;
}