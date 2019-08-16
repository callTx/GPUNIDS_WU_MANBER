#include "readfiles.h"

std::vector<std::string> readfiles(std::string input){
    std::vector<std::string> str;
    std::string s;
    char out;
    std::fstream fs(input,std::fstream::in);
    if (fs.is_open()) {
        while (!fs.eof() &&  (out = fs.get()) ) {
            //fs >> std::noskipws>>out;
            if(out == '\n' || out=='\377'){
                str.push_back(s);
                s="";
            }else{
                s+=out;
            }
            std::cout << out;
        }
    }
    fs.close();

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

