#include "utils.hpp"

list<TI> inicializarTI(){
    list<TI> tabelaDeInstrucoes;

    tabelaDeInstrucoes.push_back(novaInstrucao( "ADD", 1, 1, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao( "SUB", 1, 2, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao( "MULT", 1, 3, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao( "DIV", 1, 4, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao( "JMP", 1, 5, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao( "JMPN", 1, 6, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao( "JMPP", 1, 7, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao( "JMPZ", 1, 8, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao( "COPY", 2, 9, 3));
    tabelaDeInstrucoes.push_back(novaInstrucao( "LOAD", 1, 10, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao( "STORE", 1, 11, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao( "INPUT", 1, 12, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao( "OUTPUT", 1, 13, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao( "STOP", 0, 14, 1));

    return tabelaDeInstrucoes;
}

TI novaInstrucao(string mnemonico, int operandos, int codigo, int tamanho){
    TI instrucao;
    instrucao.codigo = codigo;
    instrucao.nome = mnemonico;
    instrucao.operandos = operandos;
    instrucao.tamanho = tamanho;
    return instrucao;
}

list<TD> inicializarTD(){
    list<TD> tabelaDeDiretivas;

    tabelaDeDiretivas.push_back(novaDiretiva( "SECTION", 1, 0));
    tabelaDeDiretivas.push_back(novaDiretiva( "SPACE", -1, -1));
    tabelaDeDiretivas.push_back(novaDiretiva( "CONST", 1, 1));

    return tabelaDeDiretivas;
}

list<TD> inicializarTDPre(){
    list<TD> tabelaDeDiretivasPre;
    tabelaDeDiretivasPre.push_back(novaDiretiva( "MACRO", 0, 0));
    tabelaDeDiretivasPre.push_back(novaDiretiva( "EQU", 1, 0));
    tabelaDeDiretivasPre.push_back(novaDiretiva( "IF", 1, 0));

    return tabelaDeDiretivasPre;
}

TD novaDiretiva(string mnemonico, int operandos, int tamanho){
    TD diretiva;
    diretiva.nome = mnemonico;
    diretiva.operandos = operandos;
    diretiva.tamanho = tamanho;
    return diretiva;
}

TS novoSimbolo(string simbolo, int valor){
    TS simb;
    simb.nome = simbolo;
    simb.valor = valor;
    return simb;
}

TS novoSimbolo(string simbolo, int valor, bool cte, int tam, string valorCte, bool isLabel){
    TS simb;
    simb.nome = simbolo;
    simb.valor = valor;
    simb.cte = cte;
    simb.tam = tam;
    simb.valorCte = valorCte;
    simb.isLabel = isLabel;
    return simb;
}

void split(string& str, vector<string>& dest){
	dest.clear();
	string buffer{""};
	for(auto c:str){
        if(c == ';') break;
		if(c != ' ' && c != '	' && c != '\r' && c != '\n') buffer+=c; else
		if(buffer != "") { dest.push_back(buffer); buffer = ""; }
	}
	if(buffer != "") dest.push_back(buffer);
	dest.push_back("\n");
}

string upCase(const string& s){
    string s2 = s;
    for (int i=0; i<s.length(); i++)
        s2[i] = toupper(s[i]);
    return s2;
}

bool validLabel(const string& label){
	if(isdigit(label.at(0)) || label.length() > 50){
		return false;
	}else{
		for(auto c:label){
			if(!isalpha(c) && !isdigit(c) && c != '_' && c != ':'){
				return false;
			}
		}
	}
	return true;
}

bool validVar(const string& var){
	if(isdigit(var.at(0)) || var.length() > 50){
		return false;
	}else{
		for(auto c:var){
			if(!isalpha(c) && !isdigit(c) && c != '_'){
				return false;
			}
		}
	}
	return true;
}

bool isLabel(const string& token){
	return token.back() == ':';
}

void errLex(int line){
    cout<<"Linha " << line <<": Erro lexico\n";
}

void errSin(int line){
    cout<<"Linha " << line <<": Erro sintatico\n";
}

void errSem(int line){
    cout<<"Linha " << line <<": Erro semantico\n";
}

bool validConst(string arg){
    //neg
    if(arg.at(0) == '-'){
      arg = arg.substr(1);
    }
    //hex
    if(arg.size()>1 && arg.at(0) == '0' && arg.at(1) == 'x'){
        arg = arg.substr(2);
    }

    for(auto c:arg){
        if(!isdigit(c))
           return false;
    }
    return true;
}

string takeFName(string fName){
	string buff = "";
	for(auto c:fName){
		if(c == '.') return buff;
		(c != '/')? buff+=c:buff="";
		
	}
}

void copyVector(int start, int end, vector<string> oldVector, vector<string>* newVector){
    for(int i = start; i < end; i++){
        newVector->push_back(oldVector[i]);
    }
}

bool isNumber(string s){
    for(auto c:s){
        if(!isdigit(c)) return false;
    }
    return true;
}

void printError(string msgErro, int line){
    cout << RED << "Linha " << line << ":" << msgErro << endl;
}

void printError(string msgErro){
    cout << RED << msgErro << endl;
}