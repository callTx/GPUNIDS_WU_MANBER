#ifndef WU_WANBER_HASH_H
#define WU_WANBER_HASH_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <stdio.h>


std::vector<std::vector<std::string>> tabelaIdxHash(std::string data, int B,std::vector<std::string> padroes, int nP, int c, int M);

std::vector<std::vector<std::string>> vecPermu(int B,int nP,std::vector<std::string> padroes);

std::vector<std::vector<std::string>> TabelaHash(std::vector<std::vector<std::string>> vecperm,int c,int M );

int Hash(std::string strB, int c, int M);

std::vector<int> AdcTodosPadroesTabela(std::string str,int B,int nP,std::vector<std::string> padroes);

std::vector<std::string> extraiAlfabeto(std::string data);

std::vector<std::string> ordenaAlfabeto(std::vector<std::string> vecL);

bool contemLetra(std::vector<std::string> vecLetras, std::string l);

#endif //WU_WANBER_HASH_H

