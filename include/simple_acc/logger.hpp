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
    /**
     * @brief Constructs a new logger object and creat a .dat
     * or clear the content if a file with the same name exists
     *
     * @param[in] file_path       Relative path to the file
     * were data will be logged to file
     */
    logger(string file_path) : file_path_(file_path)
    {
        ofstream ofs(file_path_.c_str(), ios_base::out | ios_base::trunc);
        ofs.close();
    }
    /**
     * @brief Log data as key-value pair, where the key
     * is the name of the signal.
     *
     * @param[in] name       The name of the logged signal
     * @param[in] value      The value of the logged signal
     */
    void log(string name, float value)
    {
        if (logged_data_.count(name) == 0)
        {
            signals_name.push_back(name);
        }
        logged_data_[name].push_back(value);
    }
    /**
     * @brief Save the logged data
     */
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

        if (!signals_name.empty())
        {
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
            cout << "Data saved to: " << file_path_ << '\n';
        }
        else
        {
            cout << "No signals were logged " << '\n';
        }
    }

private:
    string file_path_;
    unordered_map<std::string, vector<float>> logged_data_;
    vector<string> signals_name;
};

#endif // LOGGER_H
