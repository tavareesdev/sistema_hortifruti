#include <stdio.h>
#include <stdlib.h>

int main() {
    int qtd1 = 0, qtd2 = 0, branco = 0, nulo = 0, total = 0, totalVal = 0, valor;
    float por1 = 0, por2 = 0, porBranco = 0, porNulo = 0, porTotal = 0;

    printf("Digite o numero do seu candidato (1 - Candidato Renan, 2 - Candidato Gabriel, 3 - Branco, 4 - Nulo, -1 - Cancela Operacao): ");
    scanf("%d", &valor);

    // Loop para contar os votos
    while (valor != -1) {
        if (valor == 1) {
            qtd1++;
        } else if (valor == 2) {
            qtd2++;
        } else if (valor == 3) {
            branco++;
        } else if (valor == 4) {
            nulo++;
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }

        total++; // Incrementa o total de votos

        printf("Digite o numero do seu candidato (1 - Candidato Renan, 2 - Candidato Gabriel, 3 - Branco, 4 - Nulo, -1 - Cancela Operacao): ");
        scanf("%d", &valor);
    }

    // Cálculo do total de votos válidos (excluindo brancos e nulos)
    totalVal = qtd1 + qtd2;

    // Evita divisão por zero
    if (total > 0) {
        // Calculando as porcentagens
        por1 = (qtd1 * 100.0) / total;
        por2 = (qtd2 * 100.0) / total;
        porBranco = (branco * 100.0) / total;
        porNulo = (nulo * 100.0) / total;
        porTotal = (totalVal * 100.0) / total;
    }

    // Exibe os resultados
    printf("\nQuantidade de votos para o candidato Renan: %d votos (%.2f%%)\n", qtd1, por1);
    printf("Quantidade de votos para o candidato Gabriel: %d votos (%.2f%%)\n", qtd2, por2);
    printf("Quantidade de votos em Branco: %d votos (%.2f%%)\n", branco, porBranco);
    printf("Quantidade de votos Nulo: %d votos (%.2f%%)\n", nulo, porNulo);
    printf("Quantidade de votos Válidos: %d votos (%.2f%%)\n", totalVal, porTotal);

    // Verifica o vencedor
    if (qtd1 > qtd2) {
        printf("\nCandidato Renan venceu!\n");
    } else if (qtd2 > qtd1) {
        printf("\nCandidato Gabriel venceu!\n");
    } else {
        printf("\nEmpate entre os candidatos!\n");
    }

    return 0;
}
