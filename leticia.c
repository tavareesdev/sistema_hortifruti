#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
    char output[1024];  // Buffer para armazenar a saída do comando
    int id_cliente = 3;  // Exemplo de valor para id_cliente
    FILE *fp;

    // Monta o comando
    snprintf(command, sizeof(command),
             "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" buscar cliente \"%i\"", id_cliente);

    // Abre um processo para rodar o comando e captura a saída
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Falha ao executar o comando.\n");
        return 1;
    }

    // Lê a saída do comando
    while (fgets(output, sizeof(output), fp) != NULL) {
        printf("%s", output);  // Imprime a saída capturada
    }

    // Fecha o processo
    pclose(fp);

    return 0;
}
