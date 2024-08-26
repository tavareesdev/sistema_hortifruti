#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
 
main ()
 
{
int menu;
float  R1, R2, R3, RT, VR1, VR2, VR3, PR1, PR2, PR3, E, PE, IE, IR1, IR2, IR3, R, I;
 
//****************************** MENU ***********************************
 
printf("\t\t Programa para calculo circuito serie ou paralelo\n");
printf("Escolha uma das opcoes:\n\t1 - Calculo circuito serie\n\t2 - Calculo circuito paralelo\n\n");
scanf("%d",&menu);
    switch (menu){     //vairavel de controle do menu
     // calculo do circuito em serie
     // Leitura e amazenamento das informações do circuito serie
        case 1:{
        system ("cls");                                 
        printf ("\t\tCalculo de circuito serie:\n\n");  
        printf("Digite a tensao do circuito (V): ");    
        scanf("%f",&E);                                 
        printf("Digite o valor do resistor R1 (Ohms): "); 
        scanf("%f",&R1);                                  
        printf("Digite o valor do resistor R2 (Ohms): "); 
        scanf("%f",&R2);                                  
        printf("Digite o valor do resistor R3 (Ohms): "); 
        scanf("%f",&R3);  
        
//Cálculo das variaveis do circuito serie      
                           
        RT= R1+R2+R3;
        IE= E/RT;    
        PE= IE*E;
        IR1=IR2=IR3=IE;
        VR1= IR1*R1;
        VR2= IR2*R2;       
        VR3= IR3*R3;
        PR1= VR1*IR1;
        PR2= VR2*IR2;
        PR3= VR3*IR3;
        
        // impressão dos resultados
        
        printf("\n\n\t\t\tResultados:\n\n");
        printf("Soma dos resistores: %.3f (Ohms)\n\n",RT);
        printf("Corrente da fonte: %.3f A\n\n",IE);
        printf("Potencia da fonte: %.3f Watts\n\n",PE);
        printf("Corrente R1: %.3f A\n\n",IR1);
        printf("Corrente R2: %.3f A\n\n",IR2);
        printf("Corrente R3: %.3f A\n\n",IR3);
        printf("Tensão R1: %.3f V\n\n",VR1); 
        printf("Tensão R2: %.3f V\n\n",VR2);
        printf("Tensão R3: %.3f V\n\n",VR3);
        printf("Potencia R1: %.3f Watts\n\n",PR1);
        printf("Potencia R2: %.3f Watts\n\n",PR2);
        printf("Potencia R3: %.3f Watts\n\n",PR3);
         break;
    }
        //calculo do circuito em paralelo
        // Leitura e amazenamento das informações do circuito paralelo
        case 2:{  
        system("cls");
        printf ("\t\tCalculo de circuito paralelo:\n\n");
        printf("Digite a tensao do circuito (V): ");
        scanf("%f",&E);
        printf("Digite o valor do resistor R1 (Ohms): ");
        scanf("%f",&R1);
        printf("Digite o valor do resistor R2 (Ohms): ");
        scanf("%f",&R2);
        printf("Digite o valor do resistor R3 (Ohms): ");
        scanf("%f",&R3);
        
        //Cálculo das variaveis do circuito paralelo
        
        RT= (R1*R2*R3)/(R2*R3+R1*R2+R1*R3);
        IE= E/RT;
        PE= IE*E;
        IR1= E/R1;
        IR2= E/R2;
        IR3= E/R3;
        VR1=VR2=VR3=E;
        PR1= VR1*IR1;
        PR2= VR2*IR2;
        PR3= VR3*IR3;
        
        // impressão dos resultados
        
        printf("\n\n\t\t\tResultados:\n\n");
        printf("Soma dos resistores: %.3f (Ohms)\n\n",RT);
        printf("Corrente da fonte: %.3f A\n\n",IE);
        printf("Potencia da fonte: %.3f Watts\n\n",PE);
        printf("Corrente R1: %.3f A\n\n",IR1);
        printf("Corrente R2: %.3f A\n\n",IR2);
        printf("Corrente R3: %.3f A\n\n",IR3);
        printf("Tensão R1: %.3f V\n\n",VR1);
        printf("Tensão R2: %.3f V\n\n",VR2);
        printf("Tensão R3: %.3f V\n\n",VR3);
        printf("Potencia R1: %.3f Watts\n\n",PR1);
        printf("Potencia R2: %.3f Watts\n\n",PR2);
        printf("Potencia R3: %.3f Watts\n\n",PR3);
         break;
         
         // Informa que a opção escolhida é invalida
         
           default:{ 
            printf("Escolha incorreta no menu!");
            break;
                }
    }
            
}
}