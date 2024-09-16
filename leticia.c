#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

int is_number(const char *str) {
    // Verifica se cada caractere da string é um dígito
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0; // Não é um número
        }
    }
    return 1; // É um número
}

int main() {
    char input[100];
    
    printf("Digite um número: ");
    fgets(input, sizeof(input), stdin);
    
    // Remove o caractere de nova linha se presente
    input[strcspn(input, "\n")] = '\0';
    
    // Usar strtol para conversão e validação
    char *endptr;
    errno = 0; // Limpa errno antes de chamar strtol
    long number = strtol(input, &endptr, 10);
    
    // Verifica se a conversão foi bem-sucedida e se não houve caracteres inválidos
    if (errno != 0 || *endptr != '\0' || endptr == input || number < INT_MIN || number > INT_MAX) {
        printf("Entrada inválida. Por favor, digite apenas números.\n");
    } else {
        printf("Você digitou o número: %ld\n", number);
    }
    
    return 0;
}
