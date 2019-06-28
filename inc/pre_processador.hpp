#ifndef PRE_PROCESSADOR_HPP
#define PRE_PROCESSADOR_HPP

#include <iostream>
#include "../inc/utils.hpp"
#include <string>

//Nome, numero de argumentos e definicao da macro
typedef struct MNDT{
    string nome;
    int arg;
    string def;
} MNDT;

TS novaMacro(string simbolo, int valor);

void equ(const string& label, string arg, list<TS>& tab, int line);

//se false, pula prox linha. Em caso de erro retorna true
bool ifd(string label, list<TS>& tab, int line);

void writeLine(string& labelAnt, vector<string> &tokens, ofstream &fw);

void writeMacroDef(MNDT* macroElem, vector<string> tokens);

void subArgsMacro(const vector<string> &argMacro, vector<string> &tokens);

string preProc(string fileIn);

#endif