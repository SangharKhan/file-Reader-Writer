#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

class CReadWrite
{
private:
    int offset;
    std::string m_fileName;
    std::string m_filePath;
    std::unique_ptr<std::fstream> file = nullptr;
    std::unique_ptr<std::ofstream> offsetFile = nullptr;
    void updateOffsetFile();
    void init();
    void removeFiles();
public:
    CReadWrite(std::string, std::string = "./binaryTextfile");
    ~CReadWrite();
    std::vector<std::string> getData();
    void writeFile(std::string);
    bool directoryExists(const std::string&);
    bool fileExists(const std::string&);
    bool createDirectory(const std::string&);
    int fileSize(const std::string&);
    std::string readFile();
};
