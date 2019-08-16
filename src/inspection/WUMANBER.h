#ifndef WU_WANBER_WUMANBER_H
#define WU_WANBER_WUMANBER_H

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
/*
 *  * Algoritmo Wu-Manber: String matching de multi padrões
 *       * N - tamanho do texto de entrada (capturado da rede)
 *            * nP - número de padrões
 *                 * m - padrão de menor de tamanho
 *                      * M = m*nP - tamanho de todos os padrões
 *                           * c - tamanho do alfabeto 122(z) - 65(A) = 57
 *                                * B - bloco de string - logc 2*M                        
 *                                */

//2.1 - Verificar o tamanho da tabela. Usando 122(z) - 65(A) = c = 57
////int tamAfbt = 57;
////int M = pow(tamAfbt , B);
//
double BlcStr(int c, int M);

int TmhTodosPadroes(int m, int nP);

int TmhMenorPadrao(std::vector<std::string> padroes);

void MatchPadroes(int idx,std::string subData, std::vector<std::string> listPotenPadr);

#endif //WU_WANBER_WUMANBER_H

