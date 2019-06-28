/* 
Passagem zero do montador, retira espacos, tabs e quebras de linha desnecessarios.
Processa as diretivas de pre-processamento EQU e IF e MACRO
Recebe o arquivo <nome>.asm contendo o codigo do usuario.
Gera um arquivo pre-processado <nome>.pre salvo em /out 

Erros detectados (somente relacionados com diretivas de pre processamento):
-- Nome de rotulo invalido
-- Rotulo nao definido (todo IF deve ter um EQU antes)
-- Rotulo repetido
-- Diretiva sem argumento
-- Diretiva com argumento invalido'
*/

#include "../inc/pre_processador.hpp"

MNDT novaMacro(string simbolo, int valor, string def){
    MNDT macro;
    macro.nome = simbolo;
    macro.arg = valor;
	macro.def = def;
    return macro;
}

void equ(const string& label, string arg, list<TS>& tab, int line){
	if(arg == "/n" || !validConst(arg) || !validLabel(label)){ 
		errLex(line); //argumento ausente ou argumento invalido ou label invalida
	}
	else{
		if(inList(label,tab))
			errSem(line);
		else	
			tab.push_back(novoSimbolo((label), stoi(arg)));
	}
}

bool ifd(string label, list<TS>& tab, int line){
	bool b;
	TS simbol;
	if(label == "\n" || !validLabel(label)){
		errLex(line); //label ausente ou invalida
		b = true;
	}else{
		if(inList(label,tab,simbol)){
			if(simbol.valor == 0)
				b = false;
			else
				b = true;
		}else{			
			errSem(line);
			b = true;
		}
	}
	return b;
}

void writeLine(string& labelAnt, vector<string> &tokens, ofstream &fw){
	int t;
	if(labelAnt != ""){
		fw << labelAnt << ": ";
		labelAnt = "";
	}
	fw << tokens[0];
	for(t=1;t<tokens.size()-1;t++){
		fw << " " << tokens[t];
	}
}

void writeMacroDef(MNDT* macroElem, vector<string> tokens){
	macroElem->def += tokens[0];
	for(int t=1;t<tokens.size()-1;t++){
		macroElem->def += " ";
		macroElem->def += tokens[t];
	}
}

void subArgsMacro(const vector<string> &argMacro, vector<string> &tokens){
	char ic;
	for(int t = 0; t<tokens.size();t++){
		ic = '1';
		for(int i=0;i<argMacro.size();i++){
			if(tokens[t] == argMacro[i]){
				tokens[t] = "#";
				tokens[t] += ic;
			}else
			if(tokens[t] == argMacro[i]+","){
				tokens[t] = "#";
				tokens[t] += ic;
				tokens[t] += ",";
			}
			ic++;
		}
	}
}

string preProc(string fileIn){
	bool wMacro = false, macroErr = false, theEnd;
	int lineCount = 0;
	string line, labelEqu = "", nomeLabel = "", labelAnt = "";
    list<TS> tabelaDeEqus;
	list<TD> tabelaDirPre = inicializarTDPre();
    vector<string> tokens;
	vector<MNDT> macros;
	MNDT* macroElem;
	MNDT macElem;
    ifstream fr(fileIn);
	string fileName = takeFName(fileIn);
	ofstream fw(fileName+".pre");
	fstream macroF;

	string nameMacro, macroWrite;
	int numParamMacro, tm;
	vector<string> argMacro, argMacroIn; 

	theEnd = !getline(fr,line);

	while(!theEnd){
		split(line,tokens);
		if(!wMacro){
			lineCount++; //No modo macro nao conta linha
		}else{
			//substitui args na macro
			for(int t=0;t<tokens.size();t++){
				if(tokens[t].front()=='#'){
					if(tokens[t].back() == ','){
						tokens[t] = argMacro[stoi(tokens[t].substr(1,2))-1];
						tokens[t] += ',';
					}else{
						tokens[t] = argMacro[stoi(tokens[t].substr(1,2))-1];
					}
				}
			}
		}
		if(tokens[0] != "\n"){
			nomeLabel = "";
			for(int t=0;t<tokens.size();t++){
				//LABEL
				if(isLabel(tokens[t])){
					if(nomeLabel == "" && labelAnt == ""){ 
						nomeLabel = (tokens[t]);
						nomeLabel = nomeLabel.substr(0,nomeLabel.size()-1);
					}else{ //+ de 1 label na linha: ignora, escreve a linha e vai pra proxima
						writeLine(labelAnt, tokens, fw);
						if(!fr.eof())
							fw << "\n";
						break;
					}
				}
				else if(inList(upCase(tokens[t]),tabelaDirPre)){
					if(upCase(tokens[t]) == "EQU"){
						if(nomeLabel != "")
							labelEqu = nomeLabel;
						else 
							if(labelAnt != ""){
								labelEqu = labelAnt;
								labelAnt = "";
							}else{
								errSin(lineCount); //label ausente
							}
						if(labelEqu != ""){
							equ(upCase(labelEqu), tokens[t+1], tabelaDeEqus, lineCount);
							nomeLabel = "/0";
						}
					}else if(upCase(tokens[t]) == "IF"){
						if(!ifd(upCase(tokens[t+1]), tabelaDeEqus, lineCount)){
							if(wMacro){
								if(!getline(macroF,line)){
									wMacro = false;
									macroF.close();
								}
							}
							else{
								lineCount++;
								if(!getline(fr,line)){
									theEnd = true;
								}
							}
						}
					}
					// //Se MACRO
					else if(upCase(tokens[t]) == "MACRO"){
						macroErr = false;
						if(wMacro){
							break;
						}
						//Verifica nome
						if(nomeLabel != ""){
							nameMacro = nomeLabel;
							labelAnt = "";
						}else if(labelAnt != ""){
							nameMacro = labelAnt;
							labelAnt = "";
							// nameMacro = nameMacro.substr(0,nameMacro.size()-1);
						}else{
							errSin(lineCount);
							macroErr = true;
							nameMacro = ":";
						}
						
						if(!validLabel(nameMacro)){
							errLex(lineCount);
							macroErr = true;
						}
						//Verifica duplicidade
						if(inList(nameMacro, macros)){
							errSem(lineCount);
							macroErr = true;
						}
						//Verifica argumentos
						argMacro.clear();
						tm = t+1;
						while(tokens[tm] != "\n"){
							if(tokens[tm].back() != ',' && tokens[tm+1] != "\n"){
								errSin(lineCount);
								macroErr = true;
								break;
							}else if(tokens[tm].back() == ','){
								tokens[tm].substr(0,tokens[tm].size()-1).swap(tokens[tm]);
							}else
							if(tokens[tm].front() != '&' || tm-t>3){
								errSin(lineCount);
								macroErr = true;
								break;
							}
							argMacro.push_back(tokens[tm]);
							tm++;
						}
						//Pula a macro em caso de erro
						if(macroErr){
							macroErr = false;
							do{
								lineCount++;
								getline(fr,line);
								split(line,tokens);
							}while(upCase(tokens[0]) != "END");
							break;
						}

						// Grava a macro na tabela
						macros.push_back(novaMacro("", argMacro.size(), ""));
						macroElem = &macros.back();
						lineCount++;
						getline(fr,line);
						split(line,tokens);
						while(upCase(tokens[0]) != "END"){
							if(inList(upCase(tokens[0]), macros, macElem)){
								macroErr = false;
								//Expandir macro na macro
								//Verificar args
								argMacroIn.clear();
								tm = 1;
								while(tokens[tm] != "\n"){
									if(tokens[tm].back() != ',' && tokens[tm+1] != "\n"){
										errSin(lineCount);
										macroErr = true;
										break;
									}else if(tokens[tm].back() == ','){
										tokens[tm].substr(0,tokens[tm].size()-1).swap(tokens[tm]);
									}
									argMacroIn.push_back(tokens[tm]);
									tokens[tm] = "";
									tm++;
								}
								if(tm>4){
									errSin(lineCount);
									macroErr = true;
								}else
								if(tm != macElem.arg+1){
									errSem(lineCount);
									macroErr = true;
								}
								//Substituir args
								if(!macroErr){
									tokens[0] = "";
									for(int t=0;t<macElem.def.size();t++){
										if(macElem.def[t]=='#'){
											t++;
											tokens[0] += argMacroIn[(int)(macElem.def[t]-'0')-1];
										}else{
											tokens[0] += macElem.def[t];
										}
									}
								}
							}

							subArgsMacro(argMacro, tokens);

							writeMacroDef(macroElem, tokens);

							//Macro sem END
							if(fr.eof()){
								errSem(lineCount);
								break;
							}
							lineCount++;
							getline(fr,line);
							split(line,tokens);
							
							if(upCase(tokens[0]) != "END"){
								macroElem->def += '\n';
							}
						}

						macros.back().nome = nameMacro;
					}
					break;
				}
				else if(inList(tokens[t],macros,macElem) && !wMacro){
					//verificar argumentos
					argMacro.clear();
					tm = t+1;
					while(tokens[tm] != "\n"){
						if(tokens[tm].back() != ',' && tokens[tm+1] != "\n"){
							tm = 100; //joga erro sintatico
							break;
						}else if(tokens[tm].back() == ','){
							tokens[tm].substr(0,tokens[tm].size()-1).swap(tokens[tm]);
						}
						argMacro.push_back(tokens[tm]);
						tm++;
					}
					if(tm-t>4){
						errSin(lineCount);
					}else
					if(tm-t != macElem.arg+1){
						errSem(lineCount);
					}else{
						wMacro = true;
						macroF.open("mac.txt",std::ofstream::trunc | std::ofstream::out);
						macroF << macElem.def;
						macroF.close();
						macroF.open("mac.txt");
						break;		
					}
				}
				else if(tokens[t]=="\n"){
					if(nomeLabel != "\0") labelAnt=nomeLabel;
				}
				else{
					writeLine(labelAnt, tokens, fw);
					if(!fr.eof())
						fw << "\n";
					break;
				}
			}
		}
		if(wMacro){
			if(!getline(macroF,line)){
				wMacro = false;
				macroF.close();
				remove("mac.txt");
			}
		}
		if(!wMacro){
			if(!getline(fr,line)){
				theEnd = true;
			}
		}
	}
	return fileName+".pre";
}
/* 
Ler a linha, incrementar counter e separar
nomeLabel = "";
Procurar Labels ou diretivas de pre-processamento na lista
	Se elemento 0 for NULL, proxima linha
	Se achou label, verifica validade, verifica se nomeLabel = "" e guarda em nomeLabel
	Se achou diretiva (nao le mais essa linha):
		Se EQU, verifica se nomeLabel != "" (se for, verifica labelAnt), verifica se existe argumento e se eh valido
			Procura label L na tabela e, se nao achar, salvar
			nomeLabel = "\0" (a label foi usada) 
		SE IF, verifica se existe argumento e eh valido, verifica na tab, incrementa e pula se true	
		SE MACRO, verifica nome valido e num de arg
			Salvar nome e numero de variaveis na MNDT, ativar wMacro. Se labelAnt!="" guarda em labelAntMacro
		SE END, verifica se esta em modo macro
			Desativa wMacro e recupera labelAntMacro se !=""
	Se fim da linha
		Se nomeLabel != "\0" -> labelAnt = nomeLabel
	Se nao
		Verifica se ha labelAnt nao usada (perde a linha que a label apareceu, mas como ja eh 
			verificado se ha erro na label aqui entao nao importa mais)
		Copia linha, salva o numero da linha e prox linha
			
	*/

/* 
Se MACRO, verifica nome, verifica duplicidade e num de args (Em caso de erro tem que pular a macro)
	Salva labelAnt
	Salva os args
	Salva a definicao: (conta linhas, ate END, mas erro se nao tem END)
		Se nomeMacro
			Expande macro (nao como abaixo, so copia mesmo)
		Se arg
			Substitui por #
		Se label, diretiva ou outro: faz nada
	Salva o nome e num de args (tem que ser depois pra evitar recursao)
Se nomeMacro, verifica nome, se existe, num de args
	wMacro = true (nao conta linhas)
	Salva os args
	Processa as linhas normalmentte (como aproveitar oq ja existe?)
Se END
	volta labelAnt
	wMacro = false

*/