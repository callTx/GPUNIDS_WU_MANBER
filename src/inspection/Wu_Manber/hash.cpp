#include "header/hash.h"

using  namespace std;

std::vector<std::vector<std::string>> tabelaIdxHash(std::string data,int B, std::vector<std::string> padroes, int nP, int c, int M){

 std::vector<std::vector<std::string>> vecpermu;
    vecpermu = vecPermu(B,nP,padroes);
std::vector<std::vector<std::string>> tabelaHash = TabelaHash(vecpermu,c,M);

    return tabelaHash;
}



std::vector<std::vector<std::string>> TabelaHash(std::vector<std::vector<std::string>> vecperm,int c,int M ){

int vpSize = 0;
    for (int j = 0; j < vecperm.size(); ++j) {
       vpSize = vpSize+ vecperm[j].size();
    }

    std::vector<std::vector< std::string> > hash(vpSize,std::vector<std::string>());

 for (int k = 0; k < vecperm.size(); ++k) {
        int len  = vecperm[k].size();
        for (int i = 0; i < len ; ++i) {
            int h  = Hash( vecperm[k].at(i) ,c,M);
            std::string str = vecperm[k].at(i);


            if(h+1<=hash.size()) {
                if (std::find(hash[h].begin(),hash[h].end(),str) == hash[h].end() ){
                    hash[h].push_back(str);
                }

            }else{
                hash.resize(h + 1);

                hash[h].push_back(str);

            }

        }

    }

    int sZ = hash.size()-1;
    if (hash[sZ].empty()){
        hash[sZ].push_back("*");
    }else{
        hash.resize(sZ+2);
        hash[sZ+1].push_back("*");
    }

    return hash;
}

int Hash(std::string strBloco, int c, int M){
    
    int hash = 0;
    for (int i = 0; i <strBloco.length() ; ++i) {
        hash = hash + strBloco[i] * pow(c,i);
    }

    hash  = hash % M;
    return hash;
}

std::vector<std::vector<std::string>> vecPermu(int B,int nP,std::vector<std::string> padroes){

    std::vector<std::vector<std::string>> perm(nP, std::vector<std::string>());
    
    for (int i = 0; i < padroes.size() ; ++i) {
        std::string strTemp = padroes[i];
        std::string subStrPerm;

        int idxInicio = 0;
        int idxFim = B -1;
        while(idxFim<strTemp.length()){
            

            subStrPerm = strTemp.substr(idxInicio,B);

            


            if (idxInicio==idxFim){
                
                perm[i].push_back(subStrPerm);
                idxFim = idxFim + 1;
                idxInicio = idxFim;
            }else{
                
                perm[i].push_back(subStrPerm);
               
                idxInicio = idxInicio + 1;
                idxFim = idxFim + 1;

            }

        }

    }


    return perm;

}

std::vector<int> AdcTodosPadroesTabela(std::string str,int B,int nP,std::vector<std::string> padroes){
    std::vector<std::vector<std::string>> perm(nP, std::vector<std::string>());

    perm = vecPermu(B,nP,padroes);
    std::vector<int> listaPadroes;
    for (int k = 0; k <padroes.size() ; ++k) {
        if (std::find(perm[k].begin(),perm[k].end(),str) != perm[k].end() ){

            listaPadroes.push_back(k);
        }
    }

    return listaPadroes;
}


std::vector<std::string> extraiAlfabeto(std::string data){

    std::vector<std::string> vecLetras;

    for (int x = 0; x < data.length(); ++x) {
        std::string letra;
        letra = data[x];

        if(vecLetras.empty()) {

            vecLetras.push_back(letra);
        } else{
            if ( !contemLetra(vecLetras, letra ) ){
                vecLetras.push_back(letra);
            }
        }

    }

    return vecLetras;
}

std::vector<std::string> ordenaAlfabeto(std::vector<std::string> vecL){


    char *ch;

    std::vector<int> asciiDecVec;
    std::vector<std::string> asciiDecVecOrd;
    for (int i = 0; i < vecL.size(); ++i) {
        std::vector<char> writable(vecL.at(i).begin(),vecL.at(i).end());
        writable.push_back('\0');
        ch =  &*writable.begin();

        int asciiDec = static_cast<int>(*ch);
        asciiDecVec.push_back( asciiDec );
    }

    std::sort(asciiDecVec.begin(),asciiDecVec.end());

    std::string c;
    for (int j = 0; j < asciiDecVec.size(); ++j) {
        c = static_cast<char>(asciiDecVec.at(j));
        asciiDecVecOrd.push_back(c);
    }

    return asciiDecVecOrd;
}

bool contemLetra(std::vector<std::string> vecLetras, std::string l){
    for (int i = 0; i < vecLetras.size(); ++i) {
        if(vecLetras[i] == l){

            return  true;

        }
    }

    return  false;
}

