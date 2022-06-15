#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <list>

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

    void log(string name, float value){
        if(logged_data_.count(name) == 0){
            signals_name.push_back(name);
        }
        logged_data_[name].push_back(value);
    }

    void saveLoggedData()
    {
        for (int j = 0; j < signals_name.size(); j++)
        {
            ofstream ofs(file_path_.c_str(), ios_base::out | ios_base::app);
            ofs << signals_name.at(j);
            if (j == signals_name.size() - 1)
            {
                ofs << '\n';
            }
            else
            {
                ofs << ' ';
            }
            ofs.close();
        }

        for (int i = 0; i < logged_data_[signals_name[0]].size(); i++)
        {
            ofstream ofs(file_path_.c_str(), ios_base::out | ios_base::app);
            for (int j = 0; j < signals_name.size(); j++)
            {
                ofs << logged_data_[signals_name.at(j)].at(i);
                if (j == signals_name.size() - 1)
                {
                    ofs << '\n';
                }
                else
                {
                    ofs << ' ';
                }
            }
            ofs.close();
        }
        cout << "Data saved to: " << file_path_ <<'\n';
    }

private:
    string file_path_;
    unordered_map<std::string, vector<float>> logged_data_;
    vector<string> signals_name;
};

#endif // LOGGER_H
