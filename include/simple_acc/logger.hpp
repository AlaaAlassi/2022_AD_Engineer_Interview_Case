#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

using namespace std;

class logger
{
public:
    logger(string filePath) : file_path_(filePath)
    {
        ofstream ofs(filePath.c_str(), ios_base::out | ios_base::trunc);
        ofs.close();
    }

    void log(string logMsg)
    {
        ofstream ofs(file_path_.c_str(), ios_base::out | ios_base::app);
        ofs << logMsg << '\t' << logMsg << '\n';
        ofs.close();
    }

private:
    string file_path_;
};

#endif // LOGGER_H
