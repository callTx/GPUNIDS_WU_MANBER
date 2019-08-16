#include "header/readfiles.h"

std::vector<std::string> readfiles(std::string input){
    std::ifstream ifs;

    ifs.open(input);
    char out[100];
    std::vector<std::string> str;
    if (ifs.is_open()){
        while(!ifs.eof()){
            ifs>>out;
            str.push_back(out);

        }
    }
    ifs.close();

    return  str;
}

std::string readData(std::string input){
    std::ifstream ifs;

    ifs.open(input);
    char out;
    std::string str;
    if (ifs.is_open()){
        while(!ifs.eof() ){
            ifs>>out;
            str.push_back(out);

        }
        str.pop_back();
    }
    ifs.close();

    return str;
}

