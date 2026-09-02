#include <stdio.h>
#include <stdbool.h>

// Fazer com que o tamanho da palavra seja indefinido e que tenha o tamanho de cada palavra

// Converte um único caractere para minúsculo
char letraMinuscula(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}

// Converte uma string inteira para minúsculo
void stringParaMinuscula(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = letraMinuscula(str[i]);
    }
}

// Verifica se o caractere já está gravado no vetor de tentativas
bool caracterRepetido(char *tentativas, char tentativaAtual) {
    for (int i = 0; tentativas[i] != '\0'; i++) {
        if (tentativas[i] == tentativaAtual) {
            return true;
        }
    }
    return false;
}

// Verifica se o caracter digitado é um dos caracteres da palavra
bool caracterCorreto(char *palavra, char tentativaAtual){
    for(int i = 0; palavra[i] != '\0'; i++){
        if(palavra[i] == tentativaAtual)
            return true;
    }
    return false;
}

// Insere os caracteres corretos em um vetor
void caracteresCorretos(char *tentativasCorretas, char tentativaAtual){
    int i = 0;

    // Procura o primeiro índice vazio ('\0') no vetor de acertos
    while (tentativasCorretas[i] != '\0') {
        i++;
    }

    // Insere o novo caractere correto no espaço vago
    tentativasCorretas[i] = tentativaAtual;

    // Garante o fechamento da string para o printf("%s") funcionar
    tentativasCorretas[i + 1] = '\0';
}

// Imprimir
void imprimirPalavra(char *palavra, char *tentativasCorretas){

    for(int i = 0; palavra[i] != '\0'; i++){
        int encontrada =  0; // Variável utilizada para controle de caracteres corretos
        // Contantemente a variável reinicializada com zero para controle de iteração

        for(int j = 0; tentativasCorretas[j] != '\0'; j++){
            if(tentativasCorretas[j] == palavra[i]){
                encontrada = 1;
                break; // Não precisa percorrer o vetor em busca de outro caracter correto
            }

        }

        if(encontrada)
            printf("%c ", palavra[i]);
        else
            printf("_ ");
    }
}

// Função responsável por imprimir o status atual do jogo
void exibirStatusJogo(char *palavra, char *tentativasCorretas, char *tentativas, char tentativaAtual,  int limiteErros){

    printf("\n-----------------------------\n");
    // Exibe a palavra em tempo real de acordo com acertos
    printf("Palavra atual: ");
    imprimirPalavra(palavra, tentativasCorretas);

    // Exibe os caracteres errados já digitados
    printf("\nCaracter Inseridos: %s\n", tentativas);

   // Exibe os caracteres corretos já digitados excluindo os errados
    printf("Caracteres Corretos: %s\n", tentativasCorretas);
    printf("-----------------------------\n\n");

    // Validar possível erro na inserção do caracter e incremeto do limite de erros
    if(!caracterCorreto(palavra, tentativaAtual))
        limiteErros++;
    printf("Limite de Erros 10\nErros atuais %d\n", (limiteErros));
}

// Função para inserção de caracteres válidos que não se repetem
void obterCaracterValido(char *palavra, char tentativaAtual, char qtdeTentativas, char *tentativas, char *tentativasCorretas){
    //
    int tentativaValida = 0;

    // Loop até o usuário digitar uma letra inédita
    while (!tentativaValida) {
        printf("Insira um caractere: ");
        scanf(" %c", &tentativaAtual);

        // Padroniza a tentativa do usuário para minúscula
        tentativaAtual = letraMinuscula(tentativaAtual);

        if (caracterRepetido(tentativas, tentativaAtual)) {
            printf("\nCaractere repetido! Tente novamente.\n");
        }
        else{
            // Salva a nova letra no vetor de tentativas
            tentativas[qtdeTentativas] = tentativaAtual;
            if(caracterCorreto(palavra, tentativaAtual))
                caracteresCorretos(tentativasCorretas, tentativaAtual);
            tentativaValida = 1; // Encerra o loop de validação
        }

    }

}

int main() {
    char palavra[30]; // Vetor para armazenar palavra a ser descoberta
    char tentativas[27] = {0}; // Vetor para guardar até 26 letras + '\0'
    char tentativasCorretas[30] = {0}; // Vetor para guardar as tentivas corretas
    char tentativaAtual;

    int limiteErros = 0; // Variável para contagem de Erros
    int qtdeTentativas = 0; // Variável responsável pela inserção dos caracteres no local correto

    // Função para inserir respetiva palavra no vetor destinado a esta palavra
    sprintf(palavra, "PreSTAdOR");

    // Normaliza a palavra secreta para minúsculas logo no início
    stringParaMinuscula(palavra);

    do {


        obterCaracterValido(palavra, tentativaAtual, qtdeTentativas, tentativas, tentativasCorretas);

        exibirStatusJogo(palavra, tentativasCorretas, tentativas, tentativaAtual, limiteErros);

        // Incremento da variável no contagem de erros


        qtdeTentativas++; // Incremento de variável auxiliar responsável pela inserção do valores
    } while (limiteErros < 10);

    return 0;
}
