#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 10000

int contar_pre_cadastros(char *entrada) {
    int total = 0;
    char *token = strtok(entrada, ";");
    
    while (token) {
        while (*token == ' ') token++; // Remove espaços extras no início
        if (*token) total++; // Garante que só conta tokens válidos
        token = strtok(NULL, ";");
    }
    return total;
}

int validar_sequencia(char *entrada) {
    int linha = 1, posicao = 1;
    int anterior = 0, inicio, fim;
    char *token = strtok(entrada, ";");
    
    while (token) {
        if (sscanf(token, "%d-%d", &inicio, &fim) == 2) {
            if (inicio > fim || (anterior != 0 && inicio <= anterior)) {
                printf("Erro Identificado. Verifique a quebra na linha %d, posição %d: %s\n", linha, posicao, token);
                return 0;
            }
            anterior = fim;
        } else {
            printf("Erro de formatação na entrada na linha %d, posição %d: %s\n", linha, posicao, token);
            return 0;
        }
        token = strtok(NULL, ";");
        posicao++;
    }
    return 1;
}

int main() {
    char entrada[MAX_INPUT], copia[MAX_INPUT];
    printf("Digite a sequência de quebra: ");
    fgets(entrada, MAX_INPUT, stdin);
    entrada[strcspn(entrada, "\n")] = 0; // Remove o '\n'

    strcpy(copia, entrada);
    if (validar_sequencia(entrada)) {
        int total_cadastros = contar_pre_cadastros(copia);
        printf("Quebra correta. Deverá ser gerado %d Pré cadastros.\n", total_cadastros);
    } else {
        printf("Quebra incorreta. Verifique os erros acima.\n");
    }
    
    return 0;
}