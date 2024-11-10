#include <stdio.h>
#include <locale.h>

int main() {
    // Configura a localidade para UTF-8
    setlocale(LC_ALL, "Portuguese");

    // Exemplo de texto com caracteres especiais
    printf("Olá, Mundo!\n");

    return 0;
}
