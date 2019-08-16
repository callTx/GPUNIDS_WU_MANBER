#ifndef WMGPU_INSPECTION_H
#define WMGPU_INSPECTION_H

#include "../util/Packet.h"
#include "inspection.h"
#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <cuda_runtime.h>
#include "../util/helper_cuda.h"

#define MAXC_ 127

//#define N (2048*204*)
//#define THREADS_PER_BLOCK 512

using namespace std;

class WMGPUInspection : public Inspection
{
    private:

	int N = 33; //(2048 * 2048) //@@@ tamanho do vetor
	//int M = THREADS_PER_BLOCK = 8;//512 //  
	int M_ = 8;

	// bool nextInput =true;
    int maxs_;
	// std::vector<std::string> strFile;
	// std::vector<std::string> padroes;
	int m;
	int nP;
	int M;
	int c=94; //[Null] ... a,b,c ... z, {. |. }
	double B;
	int B2;
	std::vector<std::vector<std::string>> vecpermu;
	std::vector<std::vector<std::string>> tabelaidx;
	std::vector<int> tbShift;	
	// std::vector<std::vector<std::string>> tabelaHASH_;
	// std::vector<std::vector<std::string>> tabelaPREFIX_; 

	std::vector<std::string> padroes;

    public:
        WMGPUInspection();
		WMGPUInspection(const Inspection &) = delete;
		WMGPUInspection& operator = (const Inspection &) = delete;
        ~WMGPUInspection();

        virtual void exec(std::shared_ptr<Packet> pkt);

        int buildMatchingMachine(std::string rules, int bufferSize, int nThreads);
		int TmhMenorPadrao();
		int TmhTodosPadroes();
		double BlcStr();

		void tabelaIdxHash();
		void vecPermu(); 
		void TabelaHash();
		// void readfilesPadroes(std::string input);
		// void readfilesData(std::string pkt);
		void tabelaShift();
		int Hash(std::string strBloco, int c, int M);

		void cuda_sample_random_ints(int* x,int N);
		void cuda_sample_print_ints(int* x,int N);
};

#endif
