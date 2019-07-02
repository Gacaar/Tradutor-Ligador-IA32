/* Tradutor de Assembly inventado para Assembly IA32
Entrada: arquivo .asm (Assembly inventado) - Considerar que não possui erros
Saida:   arquivo .s (IA32)
Obs.: Tradução só contem seção .DATA e .TEXT, variaveis não inicializadas serão inicializadas com valor '0'
Seção .DATA vem sempre no final
Assembly inventado possui novas instruções:
C_INPUT, C_OUTPUT, S_INPUT, S_OUTPUT, H_INPUT, H_OUTPUT
As instruções INPUT, OUTPUT e as instruções acima devem ter funções em IA32 pré-prontas, a tradução será um Call
Toda função retorna o numero de caracteres lidos/escritos em AX
No total são 20 instruções e 5 diretivas (não tem Macro)
Todas as instruções devem ser traduzidas para 32 bits
*/

#include "../inc/tradutor.hpp"

ofstream sectionText;
ofstream sectionData;
ofstream functions;

void writeFunc(string fileName){
    ifstream fr("src/" + fileName);
    
    string line;
    bool section = 0;

    while(getline(fr,line)){
        if(line == "section .data"){
            section = 0;
        }else if(line == "section .text"){
            section = 1; 
        }else if(!section){
            sectionData << line << endl;
        }else{
            functions << line << endl;
        }
    }
}

void mergeFiles(ofstream &fw){
    sectionData.close();
    sectionText.close();
    functions.close();

    ifstream data("sectionData.s");
    ifstream text("sectionText.s");
    ifstream func("functions.s");

    fw << data.rdbuf();
    fw << text.rdbuf();
    fw << func.rdbuf();

    data.close();
    text.close();
    func.close();

    remove("sectionData.s");
    remove("sectionText.s");
    remove("functions.s");

    fw.close();
}

void swapLine(string line, bool *section, vector<string> tokens){
    if(line == "SECTION TEXT"){
            *section = 0;
        }else if(line == "SECTION DATA"){
            *section = 1;
        }else if(tokens[0] == "ADD"){
            sectionText << "add dword ebx, " << tokens[1] << endl;   
        }
        else if(tokens[0] == "SUB"){
            sectionText << "sub dword ebx, " << tokens[1] << endl;  
        }
        else if(tokens[0] == "MULT"){
            sectionText << "mv dword ebx, " << tokens[1] << endl;
            sectionText << "imul dword ebx\n";  
            sectionText << "mv dword ebx, eax\n";
        }
        else if(tokens[0] == "DIV"){
            sectionText << "mv dword ebx, " << tokens[1] << endl;
            sectionText << "imul dword ebx\n";
            sectionText << "mv dword ebx, eax\n"; 
        }
        else if(tokens[0] == "JMP"){
            sectionText << "jmp " << tokens[1] << endl;
        }
        else if(tokens[0] == "JMPN"){
            sectionText << "cmp ebx, 0\n";
            sectionText << "jb " << tokens[1] << endl;
        }
        else if(tokens[0] == "JMPP"){
            sectionText << "cmp ebx, 0\n";
            sectionText << "ja " << tokens[1] << endl;
        }
        else if(tokens[0] == "JMPZ"){
            sectionText << "cmp ebx, 0\n";
            sectionText << "je " << tokens[1] << endl;
        }
        else if(tokens[0] == "COPY"){
            if(tokens.size() == 4){
                sectionText << "mv dword " << tokens[2] << ", " << tokens[1].substr(0, tokens[1].size()-1) << endl;
            }else if(tokens.size() == 6){
                if(tokens[2] == "+"){
                    sectionText << "mv dword ecx, " << tokens[3].substr(0, tokens[3].size()-1) << endl;
                    sectionText << "mv dword " << tokens[4] << ", [" << tokens[1] << " + ecx*4]" << endl;
                }else{
                    sectionText << "mv dword ecx, " << tokens[4] << endl;
                    sectionText << "mv dword [" << tokens[2] << " + ecx*4], " << tokens[1].substr(0, tokens[1].size()-1) << endl;
                }
            }else if(tokens.size() == 8){
                sectionText << "mv dword ecx, " << tokens[3].substr(0, tokens[3].size()-1) << endl;
                sectionText << "mv dword edx, " << tokens[6] << endl;
                sectionText << "mv dword [" << tokens[4] << " + edx*4], [" << tokens[1] << " + ecx*4]" << endl;
            }
        }
        else if(tokens[0] == "LOAD"){
            sectionText << "mv dword ebx, " << tokens[1] << "\n";
        }
        else if(tokens[0] == "STORE"){
            sectionText << "mv dword "<< tokens[1] << ", ebx" << "\n";
        }
        else if(tokens[0] == "INPUT"){
            
        }
        else if(tokens[0] == "OUTPUT"){
            
        }
        else if(tokens[0] == "C_INPUT"){
            sectionText << "push eax" << endl;
            sectionText << "call LeerChar" << endl;
            sectionText << "pop eax" << endl;
            sectionText << "mov [" << tokens[1] << "],eax" << endl;
            writeFunc("LeerChar.s");
        }
        else if(tokens[0] == "C_OUTPUT"){
            sectionText << "mov eax, [" << tokens[1] << "]" << endl;
            sectionText << "push eax" << endl;
            sectionText << "call EscreveChar" << endl;
            writeFunc("EscreverChar.s");
        }
        else if(tokens[0] == "H_INPUT"){
            
        }
        else if(tokens[0] == "H_OUTPUT"){
            
        }
        else if(tokens[0] == "S_INPUT"){
            
        }
        else if(tokens[0] == "S_OUTPUT"){
            
        }
        else if(tokens[0] == "STOP"){
            sectionData << "mov eax, 1" << endl;
            sectionData << "mov ebx, 0" << endl;
            sectionData << "int 80h" << endl;
        }else if(*section){
            if(tokens[1] == "SPACE"){
                sectionData << tokens[0].substr(0, tokens[0].length() - 1) << " db";
                if(tokens.size() == 4){
                    int vectorSize = stoi(tokens[2]);
                    for(int i = 0; i < vectorSize; i++){
                        if(i != vectorSize - 1)
                            sectionData << " 0,"; 
                        else
                            sectionData << " 0"; 
                    }
                    sectionData << endl;
                }else{
                    sectionData << " 0\n"; 
                }
            }else if(tokens[1] == "CONST"){
                sectionData << tokens[0].substr(0, tokens[0].length() - 1) << " EQU " << tokens[2] << endl;
            }
        }else{
            sectionText << tokens[0] << " ";
            tokens.erase(tokens.begin());
            for(int i = 0; i < tokens.size(); i++){
                if(i != tokens.size() - 1)
                    line += tokens[i] + " ";
                else
                    line += tokens[i];
            }
            swapLine(line, section, tokens);
        }
}

int main(int argc, char const *argv[]){
    string line;
    vector<string> tokens;    
    bool section = 0;

    //Faz o pre processamento 
    string fileIn = takeFName(argv[1]);
    preProc(fileIn+".asm");             //Gera arquivo .pre

    //Abre o arquivo e comeca a traducao
    ifstream fr(fileIn+".pre");
	ofstream fw(fileIn+".s");
    sectionText.open("sectionText.s", std::ofstream::out);
    sectionData.open("sectionData.s", std::ofstream::out);
    functions.open("functions.s", std::ofstream::out);

    sectionData << "section .data\n";
    sectionText << "section .text\n";

    while(getline(fr,line)){
        split(line,tokens);
        swapLine(line, &section, tokens);
    }
    mergeFiles(fw);
}



