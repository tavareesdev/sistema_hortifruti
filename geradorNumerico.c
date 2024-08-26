#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
// Declara��o de vari�veis globais
int opcao, opcaoant=0;
int quant; // vari�vel para receber a quantidade de n�meros a ser gerado 
int lista[100000]; // matriz unidimencional, ou seja, um vetor de 100 mil c�lulas

// Cita��o dos m�todos que ser�o detalhados abaixo
int menu();
void GerenciaOpcoes();
void GeraMostraPares();
void GeraMostraImpares();
void GeraMostraMultiplos();
void Quantidade();
void MostraUltimo();
int TestaPrimo(int num);
void GeraMostraPrimos();

int main()
{
	setlocale(LC_ALL, "portuguese");
	do
	{
		opcao = menu();
		GerenciaOpcoes();
	}while(opcao != 9);
}

int menu() // m�todo do tipo fun��o, que retorna valor
{
	int escolha;
	system("cls");
	printf("|==============================|\n");
	printf("|       SISTEMA NUMEROS        |\n");
	printf("|                              |\n");
	printf("|       Menu de operacoes:     |\n");
	printf("| 1 - Gera e Mostra Pares      |\n");
	printf("| 2 - Gera e Mostra Impares    |\n");
	printf("| 3 - Gera e Mostra Multiplos  |\n");
	printf("| 4 - Mostra a ultima geracao  |\n");
	printf("| 5 - Testa Numero Primo       |\n");
	printf("| 6 - Gera Numeros Primo       |\n");
	printf("| 9 - Encerrar o sistema       |\n");
	printf("|                              |\n");
	printf("|==============================|\n");
	printf("  Digite o numero da opcao desejada: ");
	scanf("%i",&escolha);
	while ((escolha < 1 || escolha > 6) && (escolha !=9))
	{
		printf("Opcao invalida! Digite uma opcao valida: ");
		scanf("%i",&escolha);
	}
	return escolha;
}

void GerenciaOpcoes() // m�todo do tipo procedimento
{
	int num, div;
	switch(opcao)
	{
		case 1:
			GeraMostraPares();
			opcaoant = opcao;
			break;
		case 2:
			GeraMostraImpares();
			opcaoant = opcao;
			break;
		case 3:
			GeraMostraMultiplos();
			opcaoant = opcao;
			break;
		case 4:
			if (opcaoant != 0)
				MostraUltimo();
				else
					printf("\nImpossivel mostrar ultima geracao, pois nenhum numero foi gerado ainda \n"); 
			break;
		case 5:
			system("cls");
				printf("SISTEMA NUMEROS\n\n");
				printf("Testa se um numero e primo\n");
				printf("Digite um numero a ser testado: ");
				scanf("%i", & num);
				div = TestaPrimo(num);
				if (div == 0 )
					printf("O numero %i e primo\n",num);
				else
					printf("O numero %i nao e primo, pois e divisivel por %i\n",num,div);
				break;
		case 6:
			GeraMostraPrimos();
			opcaoant = opcao;
			break;
	}
	system("pause");
}

void GeraMostraPares() // m�todo do tipo procedimento
{
	int cont=1;
	system("cls");
	printf("SISTEMA NUMEROS\n\n");
	printf("Gera e Mostra Numeros Pares\n");
	Quantidade();
	//for(cont=1; cont <= quant; cont++) // cont++ = cont + 1
	while(cont <= quant)
	{
		printf("%i ", cont * 2);
		lista[cont-1] = cont * 2;
		if (cont % 10 == 0) printf("\n");
		cont++;
	}
	printf("\n");
}

void GeraMostraImpares() // m�todo do tipo procedimento
{
	int cont=1;
	system("cls");
	printf("SISTEMA NUMEROS\n\n");
	printf("Gera e Mostra Numeros Impares\n");
	Quantidade();
	//for(cont=1; cont <= quant; cont++) // cont = cont + 1
	do
	{
		printf("%i ", cont * 2 - 1);
		lista[cont-1] = cont * 2 - 1;
		if (cont % 10 == 0) printf("\n");
		cont++;
	}while(cont <= quant);
	printf("\n");
}

void GeraMostraMultiplos()
{
	int cont, mult;
	system("cls");
	printf("SISTEMA NUMEROS\n\n");
	printf("Gera e Mostra Numeros Multiplos\n");
	printf("\nMultiplo de qual numero? ");
	scanf("%i", &mult);
	while (mult < 1 || mult > 1111)
	{
		printf("Multiplo deve ser um numero inteiro entre 1 e 1111! Informe multiplo de qual numero: ");
		scanf("%i", &mult);
	}
	Quantidade();
	printf("\n");
	for(cont=1; cont <= quant; cont++) // cont = cont + 1
	{
		printf("%i ", cont * mult);
			lista[cont-1] = cont * mult;
		if (cont % 10 == 0) printf("\n");
	}
	printf("\n");
}

void Quantidade()
{
	printf("\nQuantos numeros gerar? ");
	scanf("%i", &quant);
	while (quant < 1 || quant > 100000)
	{
		printf("Quantidade deve ser um numero inteiro entre 1 e 100000! Digite quantos numeros gerar: ");
		scanf("%i", &quant);
	}
}

void MostraUltimo()
{
	int i;
	system("cls");
	printf("SISTEMA NUMEROS\n\n");
	printf("Mostra Ultimos Numeros Gerados ");
	switch(opcaoant)
	{
		case 1: 
			printf("(PARES)\n\n");
			break;
		case 2:
			printf("(IMPARES)\n\n");
			break;
		case 3:
			printf("(MULTIPLOS)\n\n");
			break;
		case 6:
			printf("(NUMEROS PRIMOS)\n\n");
			break;
	}
	for(i=0;i<quant;i++)
	{
		printf("%i ", lista[i]);
		if((i+1) % 10 == 0) printf("\n");
	}
	printf("\n\n");
}

int TestaPrimo(int num)
{
	int i, div=0;
	for(i=2;i<num;i++)
	{
		if (num % i == 0)
		{
			div = i;
			break;
		}
	}
	return div;
}

void GeraMostraPrimos() // m�todo do tipo procedimento
{
	int cont=1,primo=0,cand;
	system("cls");
	printf("SISTEMA NUMEROS\n\n");
	printf("Gera e Mostra Numeros Primos\n");
	Quantidade();
	for(cont=1; cont <= quant; cont++) // cont++ = cont + 1
	{
		for(cand=primo+1;cand<3000000;cand++)
			if (TestaPrimo(cand)==0)
			{
				primo = cand;
				break;
			}
		printf("%i ", primo);
		lista[cont-1] = primo;
		if (cont % 10 == 0) printf("\n");
	}
	printf("\n");
}
