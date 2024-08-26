#include <stdio.h>
#include <stdlib.h>

int main() {
    char nome[50];  
    float n1;  
    float n2;
    float npim;  
    float exame;  

    printf("Digite o nome do Aluno: ");    
    fgets(nome, 50, stdin);  
    printf("Digite a primeira nota: "); 
    scanf("%f",&n1);
    printf("Digite a segunda nota: "); 
    scanf("%f",&n2);
    printf("Digite a nota do PIM: "); 
    scanf("%f",&npim);

    float media = (((n1 + n2)/2)*0.8) + (npim * 0.2);

    printf("A media de %s e: %.2f\n", nome, media);
    
    if(media >= 7) {
        printf("%s foi Aprovado(a)!\n", nome);
    } 
    else { 
        printf("Digite a nota do Exame: "); 
        scanf("%f",&exame);

        float mediafinal = (media + exame) / 2;

        if(media >= 5) {
            printf("A media de %s e: %.2f\n", nome, mediafinal);
            printf("%s foi Aprovado(a)!\n", nome);
        } 
        else { 
            printf("A media de %s e: %.2f\n", nome, mediafinal);
            printf("%s foi Reprovado(a)!\n", nome);
        }
    }
    
    
    
    return 0;
}
