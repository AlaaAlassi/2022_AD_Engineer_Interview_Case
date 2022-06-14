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

    void log(float val1,float val2,float val3,float val4,float val5)
    {
        ofstream ofs(file_path_.c_str(), ios_base::out | ios_base::app);
        ofs << val1 << ' ' << val2<< ' ' << val3<< ' ' << val4<< ' ' << val5 << '\n';
        ofs.close();
    }

private:
    string file_path_;
};

#endif // LOGGER_H
