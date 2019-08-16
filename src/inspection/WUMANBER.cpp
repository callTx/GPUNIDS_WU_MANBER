#include "WUMANBER.h"

double BlcStr(int c, int M){
    	double blcStr = log10(2*M)/log10(c);
    	//double B = std::ceil(blcStr);
    	double B = std::round(blcStr);
	return B;

}

int TmhTodosPadroes(int m, int nP){
    int M = m * nP;

    return  M;
}

int TmhMenorPadrao(std::vector<std::string> padroes){
   

    std::vector<int> sizePadroes;
    for (int i = 0; i <padroes.size() ; ++i) {
        sizePadroes.push_back(padroes[i].size());
    }
    auto minElem = std::min_element(std::begin(sizePadroes), std::end(sizePadroes));
    std::cout<<minElem.operator*()+"\n"<<std::endl;

   
    return minElem.operator*();
}

void MatchPadroes(int idx,std::string subData, std::vector<std::string> listPotenPadr){

    for (unsigned t = 0; t <listPotenPadr.size() ; ++t) { 
        bool match = true;
        std::string str =listPotenPadr.at(t); 
        int final = subData.size()-1;
        for (int ch = listPotenPadr.at(t).length()-1; ch>=0 ; --ch) { 

            if( str.at(ch) ==  subData.at(final)) {
                final = final - 1;
            }else{
                match = false;
                break;
            }

        }

        if (match){
            int pos = final+1;
    	    #ifdef VERBOSE
            		std::cout<<"\r"<<">>>>>>>>>>>>  Na posicao "<<pos<<", ha um match com o padrao "<<listPotenPadr[t]<<std::endl;
    	    #endif
        }
    }
}
