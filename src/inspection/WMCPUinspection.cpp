#include "WMCPUinspection.h"



WMCPUInspection::WMCPUInspection(){

}

WMCPUInspection::~WMCPUInspection(){

}

void WMCPUInspection::exec(std::shared_ptr<Packet> pkt){
    
	#ifdef VERBOSE
    		struct timeval start, end, diff;
    		gettimeofday(&end, nullptr);
    		timersub(&end, &(pkt.get()->virtualTime), &diff);
    		this->lock();
    		pkt->computeStatistics(this->getStats());
    		this->getStats()->sumWaitingTime += diff.tv_sec * 1000.0 + diff.tv_usec / 1000.0;
    		this->unlock();

    		if( gettimeofday(&start, nullptr) != 0)
    		{
        		std::cerr << "Fail to get current time" << std::endl;
        		exit(-1);
    		}
	#endif

    	pkt.get()->init();
    	if(nextInput && pkt.get()->size_payload_ > 0){
 		//nextInput = false;
		#ifdef VERBOSE
    			//std::cout<<">>>>>>>>>>>>>>>>payload_[ ]: " <<reinterpret_cast<char*>( pkt.get()->payload_) <<std::endl;
    			//std::cout<< "size: " << pkt.get()->size_payload_ <<std::endl;
		#endif
	 	this->excWuManberCore( reinterpret_cast<char*>(pkt.get()->payload_) );
    	}

	#ifdef VERBOSE
    
    		if( gettimeofday(&end, nullptr) != 0)
    		{
        		std::cerr << "Fail to get current time" << std::endl;
        		exit(-1);
    		}
    		timersub(&end, &start, &diff);
    		this->lock();
    		this->getStats()->sumProcTime += diff.tv_sec * 1000.0 + diff.tv_usec / 1000.0;
    		this->unlock();
	#endif
   	 
}

void WMCPUInspection::excWuManberCore(std::string  nextData){

        		std::vector<std::vector<std::string>> tabelaHASH = std::vector<std::vector<std::string>> (tbShift.size(),std::vector<std::string>());
			#ifdef VERBOSE
				//cout<< ">>>>>>>>>>>tabelaHASH: "<<tabelaHASH.size() <<endl;	
			#endif
	
        		std::vector<std::vector<std::string>> tabelaPREFIX = std::vector<std::vector<std::string>>(tbShift.size(),std::vector<std::string>());
			#ifdef VERBOSE
				//cout<< ">>>>>>>>>>>tabelaPREFIX: "<<tabelaPREFIX.size() <<endl;	
			#endif


			std::string dataTemp = nextData;
			#ifdef VERBOSE
				//std::cout<<"dataTemp: "<<dataTemp <<std::endl;
			#endif
			int N = dataTemp.length();
    			#ifdef VERBOSE
    				//cout <<">>>>>>>>>>>>>N: "<<N<< endl;
    			#endif


        		int pos = m;
    			#ifdef VERBOSE
    				//cout <<">>>>>>>>>>>>>pos: "<<pos<< endl;
    			#endif

        		int pref = m - B2;
    			#ifdef VERBOSE
    				//cout <<">>>>>>>>>>>>>pref: "<<pref<< endl;
    			#endif
        		while(pos<=N){
    				#ifdef VERBOSE
    					//cout <<"      while>>>>>>>>>>>>>pos: "<<pos<< endl;
    				#endif
            			int tPos_B1 = (pos - B +1) - 1; 
            			int tPos = (pos) - 1;
            			//int i = Hash(data.substr(tPos_B1,B),c,M);
            			int i = Hash(dataTemp.substr(tPos_B1,B),c,M);
    				#ifdef VERBOSE
    					//cout <<"      while>>>>>>>>>>>>>Hash i: "<<i<< endl;
    				#endif
            			if (tbShift[i] == 0){//tbShift[i]
		    			
		    			#ifdef VERBOSE
						//cout<< ">>>>>>>>>>>tbShift: "<<tbShift[i] <<endl;	
	            			#endif
		    				
                			if( !(tabelaHASH[i].empty()) ){
                    				if (pref == 0){
                        				//std::cout<<"Sem prefixos"<<std::endl;
                    				}else{
                        				int tPos_B_1 = (pos - B2 -1);
                        				int tPos_B = (pos - B2) - 1;
                        				//int j = Hash(data.substr(tPos_B_1,tPos_B),c, M);
                        				int j = Hash(dataTemp.substr(tPos_B_1,tPos_B),c, M);
                        				//std::vector<int> listaPadroes = AdcTodosPadroesTabela(data.substr(tPos_B_1,B),B,nP,padroes);

                        				//AdcTodosPadroesTabela(data.substr(tPos_B_1,B));
                        				std::vector<int> listaPadroes;
                        				listaPadroes = AdcTodosPadroesTabela(dataTemp.substr(tPos_B_1,B));

                        				for (int lp = 0; lp < listaPadroes.size(); ++lp) {
                            					tabelaPREFIX[j].push_back(padroes[ listaPadroes[lp] ]);
                        				}
						
							std::string subData = dataTemp.substr(0,pos);
							std::vector<std::string> listPotenPadr = tabelaPREFIX[j];
                        				MatchPadroes(listPotenPadr,subData);

							//listaPadroes.clear();
							//subData.clear();
							//listPotenPadr.clear();
                    				}
                			}else{
						std::vector<int> listaPadroes;	
                    				listaPadroes = AdcTodosPadroesTabela(dataTemp.substr(tPos_B1,B));
                    				
						for (int lp = 0; lp < listaPadroes.size(); ++lp) {
                        				tabelaHASH[i].push_back(padroes[ listaPadroes[lp] ]);
                    				}

						std::string subData = dataTemp.substr(0,pos);
						std::vector<std::string> listPotenPadr = tabelaHASH[i];
                    				MatchPadroes(listPotenPadr,subData);
				

						//listaPadroes.clear();
						//subData.clear();
						//listPotenPadr.clear();
                			}		
                			pos++;
            			}else{
                			pos = pos + tbShift[i];
            			}

        		}
		
		//data.clear();	 
  
}

int WMCPUInspection::buildMatchingMachine(std::string rules){
    
    	std::string line;
    	ifstream file(rules.c_str(), std::ifstream::in);
    	maxs_ = 0;
    	while(getline(file,line))
    	{
        	padroes.push_back(line);    
        	maxs_ += line.size();
    	}

    	#ifdef VERBOSE
       	/*cout<<">>>>>>>padroes: "<<endl;
       	for(int i=0 ; i<padroes.size() ; i++){
	
		cout<<">>>>>>>>>>>>>>>" <<padroes[i]<<endl;
	}*/
    	#endif 
	
		
    	m = TmhMenorPadrao();
    	#ifdef VERBOSE
    
    		//cout<<">>>>>>>>>>> m: "<< m <<endl; 
    	#endif
	

    	nP = padroes.size();
    
    	#ifdef VERBOSE
    
    		//cout<<">>>>>>>>>>> nP: "<< nP <<endl; 
    	#endif
	
    	M = TmhTodosPadroes();
    
    	#ifdef VERBOSE 
    		//cout<<">>>>>>>>>>> M: "<< M <<endl; 
    	#endif



    	//c = 94;  

    	B = BlcStr(); 
    	#ifdef VERBOSE 
    		//cout<<">>>>>>>>>>> B: "<< B <<endl; 
    	#endif
    
    	B2 = B;

		#ifdef VERBOSE
			cout<< "Inicializando tabelas........................... " <<endl;	
		#endif
	    
    	tabelaIdxHash();

		#ifdef VERBOSE
			//cout<< ">>>>>>>>>>>tabelaidx.size(): "<<tabelaidx.size() <<endl;	
		#endif

		tabelaShift();

		
		#ifdef VERBOSE
			//cout<< ">>>>>>>>>>>tabelaSHIFT: "<<tbShift.size() <<endl;	
		#endif


		/*
			tabelaHASH = std::vector<std::vector<std::string>> (tbShift.size(),std::vector<std::string>());
		#ifdef VERBOSE
			//cout<< ">>>>>>>>>>>tabelaHASH: "<<tabelaHASH.size() <<endl;	
		#endif
		
			tabelaPREFIX = std::vector<std::vector<std::string>>(tbShift.size(),std::vector<std::string>());
		#ifdef VERBOSE
			//cout<< ">>>>>>>>>>>tabelaPREFIX: "<<tabelaPREFIX.size() <<endl;	
		#endif
		*/

		return 1;

}

void WMCPUInspection::tabelaShift(){
	
    tbShift =  std::vector<int>(tabelaidx.size(),int());
    
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
		    /*
		    if(b1 == 10542){
		    	#ifdef VERBOSE
				//cout<< ">>>>>>>>>>>tbShift[10542]: "<<tbShift[10542] <<endl;	
	            	#endif
		    }
		    */
                }else {
                    std::vector<int>::iterator result = std::min_element(std::begin(min), std::end(min));
                    tbShift.insert(tbShift.begin() + b1, result.operator*());
                    tbShift.erase(tbShift.begin() + b1 + 1);
		   /* 
		    if(b1 == 10542){
		    	#ifdef VERBOSE
				//cout<< ">>>>>>>>>>>tbShift[10542]: "<<tbShift[10542] <<endl;	
	            	#endif
		    }
		  */
                }
                
            }
        }


    }


}

int WMCPUInspection::TmhMenorPadrao(){
	
    std::vector<int> sizePadroes;
    for (int i = 0; i <padroes.size() ; ++i) {
        sizePadroes.push_back(padroes[i].size());
    }
    auto minElem = std::min_element(std::begin(sizePadroes), std::end(sizePadroes));
    //std::cout<<minElem.operator*()+"\n"<<std::endl;

   
    return minElem.operator*();
}

int WMCPUInspection::TmhTodosPadroes(){

    int TodosP = m * nP;

    return  TodosP;
}

double WMCPUInspection::BlcStr(){

    	double blcStr = log10(2*M)/log10(c);
    	//double B = std::ceil(blcStr);
    	double Blc = std::round(blcStr);
	return Blc;
}

void WMCPUInspection::tabelaIdxHash(){

    	vecPermu();
	
	#ifdef VERBOSE
		//cout<< ">>>>>>>>>>>>>>>padroes.length: " <<padroes.size() <<endl;	
	        //cout<< "data.length: "<< data.length()<< endl;
		//cout<< ">>>>>>>>>>>>>nP: "<<nP <<endl;	
		//cout<< ">>>>>>>>>>>>vecpermu: "<<vecpermu.size() <<endl;	
		//cout<< ">>>>>>>>>>>tabelaHash: "<<tabelaidx.size() <<endl;	
	
	#endif

	TabelaHash();
	
	
}

void WMCPUInspection::vecPermu(){

    vecpermu = std::vector<std::vector<std::string>>(nP,std::vector<std::string>());
 
    for (int i = 0; i < padroes.size() ; ++i) {
        std::string strTemp = padroes[i];
        std::string subStrPerm;

        int idxInicio = 0;
        int idxFim = B -1;
        while(idxFim<strTemp.length()){
            

            subStrPerm = strTemp.substr(idxInicio,B);

            


            if (idxInicio==idxFim){
                
               vecpermu[i].push_back(subStrPerm);
                idxFim = idxFim + 1;
                idxInicio = idxFim;
            }else{
                
                vecpermu[i].push_back(subStrPerm);
               
                idxInicio = idxInicio + 1;
                idxFim = idxFim + 1;

            }

        }

    }


}

void WMCPUInspection::TabelaHash(){
	
	int vpSize = 0;
	for(int j= 0; j< vecpermu.size();j++){
		vpSize = vpSize + vecpermu[j].size();
 	}

 	tabelaidx = std::vector<std::vector<std::string>> (vpSize, std::vector<std::string>());

 	for (int k = 0; k < vecpermu.size(); ++k) {
        	int len  = vecpermu[k].size();
        	for (int i = 0; i < len ; ++i) {
            		int h  = Hash( vecpermu[k].at(i) ,c,M);
            		std::string str = vecpermu[k].at(i);
            		if(h+1<=tabelaidx.size()) {
                		if (std::find(tabelaidx[h].begin(),tabelaidx[h].end(),str) == tabelaidx[h].end() ){
                    			tabelaidx[h].push_back(str);
                		}

            		}else{
                		tabelaidx.resize(h + 1);

                		tabelaidx[h].push_back(str);

            		}

        	}
		
	}

	int sZ = tabelaidx.size()-1;
   	if (tabelaidx[sZ].empty()){
        	tabelaidx[sZ].push_back("*");
    	}else{
        	tabelaidx.resize(sZ+2);
        	tabelaidx[sZ+1].push_back("*");
    	}

}

void WMCPUInspection::readfilesPadroes(std::string input){


    std::vector<std::string> strFiles;
    std::string s;
    char out;
    std::fstream fs(input,std::fstream::in);
    if (fs.is_open()) {
        while (!fs.eof() &&  (out = fs.get()) ) {
            //fs >> std::noskipws>>out;
            if(out == '\n' || out=='\377'){
                strFiles.push_back(s);
                s="";
            }else{
                s+=out;
            }
            std::cout << out;
        }
    }
    fs.close();


}

void WMCPUInspection::readfilesData(std::string pkt){


    std::vector<std::string> strFiles;
    std::string s;
    char out;
    std::fstream fs(pkt,std::fstream::in);
    if (fs.is_open()) {
        while (!fs.eof() &&  (out = fs.get()) ) {
            //fs >> std::noskipws>>out;
            if(out == '\n' || out=='\377'){
                strFiles.push_back(s);
                s="";
            }else{
                s+=out;
            }
            //std::cout << out;
        }
    }
    fs.close();

}


int WMCPUInspection::Hash(std::string strBloco, int c, int M){
    
    int hash = 0;
    for (int i = 0; i <strBloco.length() ; ++i) {
        hash = hash + strBloco[i] * pow(c,i);
	hash = hash % M;
    }

    #ifdef VERBOSE
	//std::cout<<"   >>>>c: "<<c<<std::endl;
    #endif 
    #ifdef VERBOSE
	//std::cout<<"   >>>>M: "<<M<<std::endl;
    #endif 
    #ifdef VERBOSE
	//std::cout<<"   >>>>Hash: "<<hash<<std::endl;
    #endif
 
    //hash  = hash % M;
    #ifdef VERBOSE
	//std::cout<<"   >>>>has % M: "<<hash<<std::endl;
    #endif 
    return hash;
}

std::vector<int> WMCPUInspection::AdcTodosPadroesTabela(std::string str){

	std::vector<int> listaPadroes;
    	for (int k = 0; k <padroes.size() ; ++k) {
        	if (std::find(vecpermu[k].begin(),vecpermu[k].end(),str) != vecpermu[k].end() ){

            		listaPadroes.push_back(k);
        	}
    	}
	return listaPadroes;
}

void WMCPUInspection::MatchPadroes(std::vector<std::string> listPotenPadr, std::string subData){

    for (unsigned t = 0; t <listPotenPadr.size() ; ++t) { 
        bool match = true;
        std::string str =listPotenPadr.at(t); 
        int _final = subData.size()-1;
        //int _final = dataTemp.size()-1;
        for (int ch = listPotenPadr.at(t).length()-1; ch>=0 ; --ch) { 
		if(_final>=0){
            		if( str.at(ch) ==  subData.at(_final)) {
                		_final = _final - 1;
            		}else{
                		match = false;
                		break;
            		}
		}else{
			match= false;
			break;
		}		

        }

        if (match){
            int posicao = _final+1;
    	    #ifdef VERBOSE
            		//std::cout<<"\r"<<">>>>>>>>>>>>  Na posicao "<<posicao<<", ha um match com o padrao: "<<listPotenPadr.at(t)<<std::endl;
    	    #endif
		
        }
    }
}
