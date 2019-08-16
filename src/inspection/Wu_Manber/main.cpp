#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "header/readfiles.h"
#include "header/hash.h"
#include "header/WUMANBER.h"
#include "header/shift.h"



int main(int argc, char **argv) {

	//OBS: Os vectors são passados por valor (cópia). Valores vectors pequenos podem não interferir no desempenho, porém
	//valores grandes podem interferir no desempenho.

	
	//>>>>>>>>>>>>> Parte 1 - 
	std::cout << "Algortimo WU-MANBER!\n" << std::endl;
        std::string dirPadres = "../teste/padroes/";
        std::string dirData = "../teste/data/";


    
        std::vector<std::string> padroes = readfiles(dirPadres+"padroes.txt");

      
        std::string data = readData(dirData+"data.txt");

     
        int m = TmhMenorPadrao(padroes);
        int nP = padroes.size();
        int M = TmhTodosPadroes(m,nP);
        int c = 57; 
	//122(z) - 65(A)   A,B,C, ..., Z, ..., a,b, ...,z
	double B = BlcStr(c,M);
        std::vector<std::vector<std::string>> tabelaidx = tabelaIdxHash(data,B,padroes,nP, c, M);

        std::vector<int> tabelaSHIFT = tabelaShift(tabelaidx,B,padroes,m);

        std::vector<std::vector<std::string>> tabelaHASH(tabelaSHIFT.size(),std::vector<std::string>());

        std::vector<std::vector<std::string>> tabelaPREFIX(tabelaSHIFT.size(),std::vector<std::string>());
        int B2 = B;

        int N = data.length();
        int pos = m;
        int pref = pos - B2;
        while(pos<=N){
            int tPos_B1 = (pos - B +1) - 1; 
            int tPos = (pos) - 1;
            int i = Hash(data.substr(tPos_B1,tPos),c,M);
            if (tabelaSHIFT[i] == 0){
                if( !(tabelaHASH[i].empty()) ){
                    if (pref == 0){
                        std::cout<<"Sem prefixos"<<std::endl;
                    }else{
                        int tPos_B_1 = (pos - B2 -1);
                        int tPos_B = (pos - B2) - 1;
                        int j = Hash(data.substr(tPos_B_1,tPos_B),c, M);
                        std::vector<int> listaPadroes = AdcTodosPadroesTabela(data.substr(tPos_B_1,B),B,nP,padroes);
                        for (int lp = 0; lp < listaPadroes.size(); ++lp) {
                            tabelaPREFIX[j].push_back(padroes[ listaPadroes[lp] ]);
                        }
                        MatchPadroes(j,data.substr(0,pos),tabelaPREFIX[j]);
                    }
                }else{
                    std::vector<int>  listaPadroes = AdcTodosPadroesTabela(data.substr(tPos_B1,B),B,nP,padroes);
                    for (int lp = 0; lp < listaPadroes.size(); ++lp) {
                        tabelaHASH[i].push_back(padroes[ listaPadroes[lp] ]);
                    }
                    MatchPadroes(i,data.substr(0,pos),tabelaHASH[i]);
                }
                pos++;
            }else{
                pos = pos + tabelaSHIFT[i];
            }

        }
    std::cout<<std::endl;
    std::cout<<"\r"<<"Fim-Algoritmo!"<<std::flush;
    return 0;
}
