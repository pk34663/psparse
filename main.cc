#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <regex>
#include <map>

std::map<std::string,std::string> day2int = {
    {"Mon","1"},
    {"Tue","2"},
    {"Wed","3"},
    {"Thu","4"},
    {"Fri","5"},
    {"Sat","6"},
    {"Sun","7"}
};

std::map<std::string,std::string> month2int = {
    {"Jan","1"},
    {"Feb","2"},
    {"Mar","3"},
    {"Apr","4"},
    {"May","5"},
    {"Jun","6"},
    {"Jul","7"},
    {"Aug","8"},
    {"Sep","9"},
    {"Oct","10"},
    {"Nov","11"},
    {"Dec","12"}
};

//Input string example:
//Sat 16 Nov 20:00:46 GMT 2019

inline std::string datestr2posix(std::vector<std::string> in)
{
    std::string ret = in[5] + "-" + month2int[in[2]] + "-" + in[1] + "T" + in[3];

    return ret;
}

int main(int argc, char *argv[])
{
    std::string strbuffer;
    std::ifstream in;
    std::regex r("^(Sat|Sun|Mon|Tue|Wed|Thurs|Fri).*$");
    std::regex header("^.*PID.*$");
    std::string date = "";

    in.open(argv[1]);
    if (in.is_open())
    {
        while(getline(in,strbuffer))
        {
            //split using iterator implementation
            std::istringstream iss(strbuffer);
            std::vector<std::string> items((std::istream_iterator<std::string>(iss)),std::istream_iterator<std::string>());
            //for(auto i : items)
            if(std::regex_match(items[0],r))
            {
                date = datestr2posix(items);
            }
            else if(std::regex_match(items[0],header))
            {
                std::cout << "header" << std::endl;
                continue;
            }
            else if(date != "")
            {
                std::cout << date <<","<< items[0] <<","<< items[1] <<"," <<
                             items[2] <<","<< items[4] << std::endl;
            }
        }
    }
    in.close();
    return (0);
}
