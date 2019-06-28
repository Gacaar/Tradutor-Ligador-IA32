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

int main(int argc, char const *argv[]){
    string line;
    vector<string> tokens;    

    //Faz o pre processamento 
    string fileIn = takeFName(argv[1]);
    preProc(fileIn+".asm");             //Gera arquivo .pre

    //Abre o arquivo e comeca a traducao
    ifstream fr(fileIn+".pre");
	ofstream fw(fileIn+".s");

    while(!getline(fr,line)){
        split(line,tokens);
        
        if(line == "SECTION TEXT"){

        }
        else if(line == "SECTION DATA"){

        }
        else if(tokens[0] == "ADD"){

        }
        else if(tokens[0] == "SUB"){
            
        }
        else if(tokens[0] == "MULT"){
            
        }
        else if(tokens[0] == "DIV"){
            
        }
        else if(tokens[0] == "JMP"){
            
        }
        else if(tokens[0] == "JMPN"){
            
        }
        else if(tokens[0] == "JMPP"){
            
        }
        else if(tokens[0] == "JMPZ"){
            
        }
        else if(tokens[0] == "COPY"){
            
        }
        else if(tokens[0] == "LOAD"){
            
        }
        else if(tokens[0] == "STORE"){
            
        }
        else if(tokens[0] == "INPUT"){
            
        }
        else if(tokens[0] == "OUTPUT"){
            
        }
        else if(tokens[0] == "C_INPUT"){
            
        }
        else if(tokens[0] == "C_OUTPUT"){
            
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
            
        }
    }
}



