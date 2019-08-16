#include"WMGPUinspection.h"

void WMGPUInspection::exec(std::shared_ptr<Packet> pkt)
{



}


WMGPUInspection::WMGPUInspection()
{

}

WMGPUInspection::~WMGPUInspection()
{
}

void WMGPUInspection::cuda_sample_random_ints(int* x,int N){

	for(int i=0; i<N;i++){
		x[i]=rand();
	}
}

void WMGPUInspection::cuda_sample_print_ints(int* x,int N){

	for(int i=0; i<N;i++){
		std::cout<<"x["<<i<<"]: "<<x[i]<<std::endl;
	}
}

__global__ void add(int *a,int *b,int *c,int n){
	//*c= *a+ *b; //Heterogeneous computing
	//c[blockIdx.x] = a[blockIdx.x] + b[blockIdx.x]; //Blocks
	//c[threadIdx.x] = a[threadIdx.x] + b[threadIdx.x]; //Threads
	
	int index = threadIdx.x + blockIdx.x * blockDim.x; //
	if(index < n) c[index] = a[index] + b[index];
}

int WMGPUInspection::buildMatchingMachine(std::string rules, int bufferSize, int nThreads)
{
		std::cout<<"nThreads: "<<nThreads<<std::endl;
		
		// (14-15/05) getilne -- TmhMenorPadrao() -- padroes.size() -- TmhTodosPadroes() -- BlcStr -- B2=B --  tabeleIdxHash() -- vecPermu() -- TabelaHash() 

		//TODO (20/05) buildMatchingMachine

		std::string line;
    	ifstream file(rules.c_str(), std::ifstream::in);
    	maxs_ = 0;
    	while(getline(file,line))
    	{
        	padroes.push_back(line);    
        	maxs_ += line.size();
		}
		
		m = TmhMenorPadrao();
		nP = padroes.size();
		M = TmhTodosPadroes();
		B = BlcStr(); 
		B2 = B;
		#ifdef VERBOSE
			cout<< "Inicializando tabelas........................... " <<endl;	
		#endif

		tabelaIdxHash();
		tabelaShift();

		return 1;

		/*
		int *a,*b,*c;
		//int a,b,c;
		int *d_a,*d_b,*d_c; 
		// size= sizeof(int);
		//std::cout<<"N: "<<N<<std::endl;
		int size = N * sizeof(int);

		//Aloca espaco para o device copiar de a,b,c
		cudaMalloc( (void **)&d_a,size );		
		cudaMalloc( (void **)&d_b,size );		
		cudaMalloc( (void **)&d_c,size );
		
		a = (int*)malloc(size);
		cuda_sample_random_ints(a,N);
		b= (int*)malloc(size);
		cuda_sample_random_ints(b,N);
		c= (int*)malloc(size);


		//a =2;
		//b =7;
		//copia a,b para o device
		cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);		
		cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);	

		//Launch o kernel add() na GPU
		//add<<<N,1>>>(d_a,d_b,d_c); //blocks
		//add<<<1,N>>>(d_a,d_b,d_c); //threads

		
		//	@ N/THREADS_PER_BLOCK  = blocks number
		
		//add<<<N/THREADS_PER_BLOCK,THREADS_PER_BLOCK>>>(d_a,d_b,d_c); //threads_per_block with vector multiple of blockDim.x = M 

		add<<<(N+M-1)/M, M >>>(d_a,d_b,d_c,N); //threads_per_block with vector which is not multiple of the blockDim.x = M	

		//Copiar os resultados de volta p/ host
		cudaMemcpy(c,d_c,size,cudaMemcpyDeviceToHost);

		//cuda_sample_print_ints(c,N);
		//std::cout<<"c: "<<c<<std::endl;
		
		//Cleanup
		cudaFree(d_a);
		cudaFree(d_b);
		cudaFree(d_c);

		//char *cudaGetErrorString(cudaError_t);
		//printf("%s\n",cudaGetErrorString(cudaGetLastError()));

		return 0;
		*/
}

int WMGPUInspection::TmhMenorPadrao(){
	
    std::vector<int> sizePadroes;
    for (int i = 0; i <padroes.size() ; ++i) {
        sizePadroes.push_back(padroes[i].size());
    }
    auto minElem = std::min_element(std::begin(sizePadroes), std::end(sizePadroes));
    //std::cout<<minElem.operator*()+"\n"<<std::endl;

   
    return minElem.operator*();
}

int WMGPUInspection::TmhTodosPadroes(){

    int TodosP = m * nP;

    return  TodosP;
}

double WMGPUInspection::BlcStr(){

	double blcStr = log10(2*M)/log10(c);
	//double B = std::ceil(blcStr);
	double Blc = std::round(blcStr);
return Blc;
}

void WMGPUInspection::tabelaIdxHash(){

	vecPermu();
	
	TabelaHash();


}

void WMGPUInspection::vecPermu(){

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

void WMGPUInspection::TabelaHash(){
	
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

int WMGPUInspection::Hash(std::string strBloco, int c, int M){
    
    int hash = 0;
    for (int i = 0; i <strBloco.length() ; ++i) {
        hash = hash + strBloco[i] * pow(c,i);
	hash = hash % M;
    }

    return hash;
}

void WMGPUInspection::tabelaShift(){
	
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