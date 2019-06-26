/* Tradutor de Assembly inventado para Assembly IA32
Entrada: arquivo .asm (Assembly inventado) - Considerar que não possui erros
Saida:   arquivo .s (IA32)
Obs.: Tradução só contem seção .DATA e .TEXT, variaveis não inicializadas serão inicializadas com valor '0'
Assembly inventado possui novas instruções:
C_INPUT, C_OUTPUT, S_INPUT, S_OUTPUT, H_INPUT, H_OUTPUT
As instruções INPUT, OUTPUT e as instruções acima devem ter funções em IA32 pré-prontas, a tradução será um Call
Todas as instruções devem ser traduzidas para 32 bits
*/