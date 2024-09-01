#include <stdio.h>
#include <time.h>

int main() {
    time_t t;
    struct tm *tm_info;
    char data_hora[20];  // Variável para armazenar a data e hora formatada

    // Obtém o tempo atual
    time(&t);

    // Converte o tempo para a estrutura tm
    tm_info = localtime(&t);

    // Formata a data e hora em uma única string
    sprintf(data_hora, "%02d/%02d/%04d %02d:%02d:%02d",
            tm_info->tm_mday,
            tm_info->tm_mon + 1,
            tm_info->tm_year + 1900,
            tm_info->tm_hour,
            tm_info->tm_min,
            tm_info->tm_sec);

    // Imprime a data e hora armazenada na variável
    printf("Data e Hora Atual: %s\n", data_hora);

    return 0;
}
