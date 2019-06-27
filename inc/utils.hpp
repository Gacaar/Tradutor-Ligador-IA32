#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

const string RED = "\x1b[31m";
const string PURPLE = "\x1b[35m";
const string COLOR_RESET = "\x1b[0m";
const string ERRO_LEXICO_MSG = "Erro léxico";
const string ERRO_SINTATICO_MSG = "Erro sintático";
const string ERRO_SEMANTICO_MSG = "Erro semântico";
enum Tipos {
        VARIAVEL,
        INSTRUCAO,
        ROTULO,
		DIRETIVA
};


//linha da tabela de simbolos
typedef struct TS{
    string nome;
    int valor;
    bool cte;
    int tam;
    string valorCte;
    bool isLabel;
} TS;

//linha da tabela de instruções
typedef struct TI{
    string nome;
    int operandos;
    int codigo;
    int tamanho;
} TI;

//linha da tabela de diretivas
typedef struct TD{
    string nome;
    int operandos;
    int tamanho;
} TD;

list<TI> inicializarTI();

TI novaInstrucao(string mnemonico, int operandos, int codigo, int tamanho);

list<TD> inicializarTD();

list<TD> inicializarTDPre();

TD novaDiretiva(string mnemonico, int operandos, int tamanho);

TS novoSimbolo(string simbolo, int valor);

TS novoSimbolo(string simbolo, int valor, bool cte, int tam, string valorCte, bool isLabel);

//Divide a string str em elementos e passa para o vetor dest, finalizando com um "/0"
//Ignora espacos, tabs e comentarios
void split(string& str, vector<string>& dest);

string upCase(const string& s);

bool validLabel(const string& label);

bool validVar(const string& var);

bool isLabel(const string& token);

template <typename T>
bool inList(const string& nome, T list){
	for(auto l:list){
		if(upCase(l.nome)==upCase(nome)){
			return true;
		}
	}
	return false;
}

template <typename T, typename Y>
bool inList(const string& nome, T list, Y& elem){
	for(auto l:list){
		if(upCase(l.nome)==upCase(nome)){
            elem = l;
			return true;
		}
	}
	return false;
}

void errLex(int line);

void errSin(int line);

void errSem(int line);

bool validConst(string arg);

string takeFName(string fName);

void copyVector(int start, int end, vector<string> oldVector, vector<string> *newVector);

bool isNumber(string s);

void printError(string msgErro, int line);

void printError(string msgErro);

#endif