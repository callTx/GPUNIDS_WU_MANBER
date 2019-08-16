#include "shift.h"


std::vector<int> tabelaShift(std::vector<std::vector<std::string>> tabelaidx ,int B, std::vector<std::string> padroes,int m) {


    std::vector<int> tbShift(tabelaidx.size(),int());
    
    for (int b1 = 0; b1 <tabelaidx.size() ; ++b1) {
        if (!tabelaidx[b1].empty()) {
            for (int b2 = 0; b2 < tabelaidx[b1].size(); ++b2) {
                std::string blocoStr = tabelaidx[b1].at(b2);
                std::vector<int> min;
               
                for (int p = 0; p < padroes.size(); ++p) {
                    

                    std::string pdr;
                    std::vector<char> writable(padroes.at(p).begin(), padroes.at(p).end());
                    writable.push_back('\0');
                    pdr = &*writable.begin();
                    std::string s;

                    int q=0;

                    
                    int idxInicio = 0;
                    int idxFim = B - 1;
                    while (idxFim < pdr.length()){
                        
                        s = pdr.substr(idxInicio,B);
                        if (!blocoStr.find(s)){
                            q = idxFim + 1;

                        }
                        if (idxInicio == idxFim){
                            idxFim = idxFim + 1;
                            idxInicio = idxFim;
                        }else{
                            idxInicio = idxInicio+1;
                            idxFim = idxFim + 1;
                        }
                        if (idxFim == pdr.length() && q > 0){
                            while ((m - q) < 0) {
                                q = q - 1;
                            }

                            min.push_back(m - q);
                        }
                    }
                    

                } 
                if (min.empty()){
                    tbShift.insert(tbShift.begin()+b1,m - B +1);
                    tbShift.erase(tbShift.begin()+b1+1);
                }else {
                    std::vector<int>::iterator result = std::min_element(std::begin(min), std::end(min));
                    tbShift.insert(tbShift.begin() + b1, result.operator*());
                    tbShift.erase(tbShift.begin() + b1 + 1);
                }
                
            }
        }


    }


    return tbShift;
}

