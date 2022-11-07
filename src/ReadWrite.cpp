#include "ReadWrite.h"
CReadWrite::CReadWrite(std::string fileName, std::string filePath) : m_fileName(fileName), m_filePath(filePath)
{
    init();
}

CReadWrite::~CReadWrite()
{
    if (file->is_open())
    {
        file->close();
    }

    if (offsetFile->is_open())
    {
        file->close();
    }
}

void CReadWrite::init()
{

    if (!directoryExists(m_filePath))
    {
        if (createDirectory(m_filePath))
        {
            std::cout << "Directory Created '" << m_filePath <<"'" << std::endl;
        }
        else
        {
            std::cerr << "Unable to create Directory" << std::endl;
        }
    }

    std::filesystem::path path = m_filePath + "/" + m_fileName;
    file = std::make_unique<std::fstream>();
    file->open(path.c_str(), std::ios::binary | std::ios::in | std::ios::app);

    std::string offsetPath = m_filePath + "/file_offset.bin";

    if (fileExists(offsetPath))
    {
        std::ifstream input;
        input.open(offsetPath);
        if (input.is_open())
        {
            input.seekg(0);
            input.read((char *)&offset, sizeof(int));
            input.close();
            std::cout << "starting from offset " << offset << std::endl;
        }
        else
        {
            std::cerr << "Could not open offset file" << offset << std::endl;
        }

        // offsetFile->read((char *)&offset, sizeof(int));
    }
    else
    {
        offset = 0;
    }

    offsetFile = std::make_unique<std::ofstream>();
    offsetFile->open(offsetPath.c_str(), std::ios::out);
}

void CReadWrite::removeFiles()
{
    std::cout << "Removing files" << std::endl;
    if (directoryExists(m_filePath))
    {
        if (std::filesystem::remove_all(std::filesystem::path(m_filePath)))
        {
            std::cout << "Directory '" << m_filePath <<"' Removed SUCESSFULLY" << std::endl;
        }
        else
        {
            std::cerr << "Directory Remove Failed" << std::endl;
        }
    }

    if (file->is_open())
    {
        file->close();
    }

    if (offsetFile->is_open())
    {
        file->close();
    }
}

std::string CReadWrite::readFile()
{
    std::string str{""};
    if (file->is_open())
    {
        int buffSize = 0;
        file->seekg(this->offset);
        char *buff;
        file->read((char *)&buffSize, sizeof(int));
        buff = new char[buffSize];
        file->read(buff, buffSize);
        if (file->eof())
        {
            removeFiles();
            return str;
        }
        offset = offset + buffSize + 4;
        updateOffsetFile();
        str = buff;

        delete buff;
        buff = nullptr;
    }
    else
    {
        std::cerr << "file not found. " << __PRETTY_FUNCTION__ << std::endl;
    }

    return str;
}

void CReadWrite::writeFile(std::string str)
{
    if (file->is_open())
    {
        str = str ;
        int size = str.length();
        file->write((char *)&size, sizeof(int));
        file->write(str.c_str(), str.length());
    }
    else
    {
        std::cerr << "file not found. " << __PRETTY_FUNCTION__ << std::endl;
    }
}

bool CReadWrite::directoryExists(const std::string &path)
{
    std::filesystem::path filePath = path;
    return std::filesystem::exists(filePath) && std::filesystem::is_directory(filePath);
}

bool CReadWrite::fileExists(const std::string &fileName)
{
    std::filesystem::path filePath = fileName;
    return std::filesystem::exists(filePath) && (std::filesystem::is_regular_file(filePath) || std::filesystem::is_other(filePath));
}

bool CReadWrite::createDirectory(const std::string &path)
{
    std::filesystem::path filePath = path;
    return std::filesystem::create_directory(path);
}

void CReadWrite::updateOffsetFile()
{
    if (!file->eof() && offsetFile->is_open())
    {
        offsetFile->seekp(offsetFile->beg);
        offsetFile->write((char *)&offset, sizeof(int));
    }
    else
    {
        std::cerr << "file not found. " << __PRETTY_FUNCTION__ << std::endl;
    }
}

int CReadWrite::fileSize(const std::string &path)
{
    std::filesystem::path filePath = path;
    return std::filesystem::file_size(filePath);
}