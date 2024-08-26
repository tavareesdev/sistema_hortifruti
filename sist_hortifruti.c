#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Função de login
int Login() {
    char username[50], password[50];
    int login_sucesso = 0;

    while (!login_sucesso) {
        printf("Digite seu nome de usuario: ");
        fgets(username, 50, stdin);
        username[strcspn(username, "\n")] = 0;  // Remover a quebra de linha

        printf("Digite sua senha: ");
        fgets(password, 50, stdin);
        password[strcspn(password, "\n")] = 0;  // Remover a quebra de linha

        char command[512];
        snprintf(command, sizeof(command),
            "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" \"%s\" \"%s\"",
            username, password);
        
        FILE* pipe = _popen(command, "r");
        if (!pipe) {
            printf("Erro ao executar o comando.\n");
            return 0;
        }

        char result[256];
        if (fgets(result, sizeof(result), pipe) == NULL) {
            printf("Erro ao ler a saída do comando.\n");
            _pclose(pipe);
            return 0;
        }
        _pclose(pipe);
        
        // Remove possíveis quebras de linha
        result[strcspn(result, "\r\n")] = 0;
        
        // Verifica se o login foi bem-sucedido
        if (strcmp(result, "Login bem-sucedido!") == 0) {
            printf("\nLogin realizado com sucesso!\n");
            printf("Acessando o sistema, aguarde...\n");
            sleep(3);
            login_sucesso = 1;
        } else {
            printf("\nUsuario ou senha incorretos. Tente novamente.\n");
        }
    }

    return login_sucesso;
}

// Função de cadastro
// Função de cadastro
int Cadastro() {
    int escolha;
    system("cls");
    printf("|==============================|\n");
    printf("|           CADASTRO           |\n");
    printf("|                              |\n");
    printf("|       Tipo de Cadastro:      |\n");
    printf("| 1 - Funcionario(a)           |\n");
    printf("| 2 - Cliente                  |\n");
    printf("| 3 - Produto                  |\n");
    printf("| 4 - Cancelar operacao        |\n");
    printf("| 9 - Encerrar o sistema       |\n");
    printf("|                              |\n");
    printf("|==============================|\n");
    printf("\nDigite o numero da opcao desejada: ");
    scanf("%i", &escolha);
    while ((escolha < 1 || escolha > 4) && (escolha != 9)) {
        printf("Opcao invalida! Digite uma opcao valida: ");
        scanf("%i", &escolha);
    }

    while (getchar() != '\n');

    if (escolha == 1) {
        char nome_funcionario[50], data_nasc_func[50], usuario_func[50], senha_funcionario[50];
        int cpf_funcionario, rg_funcionario, tipo_funcionario;

        printf("\nDigite o nome do(a) novo(a) funcionario(a) sem o uso de caracteres especiais (ou 'exit' para voltar): ");
        fgets(nome_funcionario, 50, stdin);
        nome_funcionario[strcspn(nome_funcionario, "\n")] = 0;  // Remover a quebra de linha
        
        if (strcmp(nome_funcionario, "exit") == 0) {
            Cadastro();  // Voltar ao menu
            return;
        }
        
        printf("Digite a data de nascimento no seguinte formato: dd/mm/yyyy (ou 'exit' para voltar): ");
        fgets(data_nasc_func, 50, stdin);
        data_nasc_func[strcspn(data_nasc_func, "\n")] = 0;  // Remover a quebra de linha

        if (strcmp(data_nasc_func, "exit") == 0) {
            Cadastro();  // Voltar ao menu
            return;
        }

        printf("Digite o CPF do(a) funcionario(a) com apenas numeros: ");
        scanf("%i", &cpf_funcionario);
        getchar(); // Limpar o buffer

        printf("Digite o RG do(a) funcionario(a) com apenas numeros: ");
        scanf("%i", &rg_funcionario);
        getchar(); // Limpar o buffer

        printf("Digite um nome de usuario para o(a) funcionario(a) sem o uso de caracteres especiais (ou 'exit' para voltar): ");
        fgets(usuario_func, 50, stdin);
        usuario_func[strcspn(usuario_func, "\n")] = 0;  // Remover a quebra de linha

        if (strcmp(usuario_func, "exit") == 0) {
            Cadastro();  // Voltar ao menu
            return;
        }

        printf("Digite uma senha para o(a) funcionario(a) sem o uso de caracteres especiais (ou 'exit' para voltar): ");
        fgets(senha_funcionario, 50, stdin);
        senha_funcionario[strcspn(senha_funcionario, "\n")] = 0;  // Remover a quebra de linha

        if (strcmp(senha_funcionario, "exit") == 0) {
            Cadastro();  // Voltar ao menu
            return;
        }

        printf("Digite o tipo de usuario para o(a) funcionario(a), sendo 1 = Administrador, 2 = Gerente, 3 = Supervisor, 4 = Funcionario: ");
        scanf("%i", &tipo_funcionario);

        // Chamar a função Python para cadastrar o funcionário e capturar a saída
        char command[512];
        snprintf(command, sizeof(command),
            "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" \"%s\" \"%d\" \"%s\" \"%d\" \"%s\" \"%s\" \"%d\"",
            nome_funcionario, cpf_funcionario, data_nasc_func, rg_funcionario, usuario_func, senha_funcionario, tipo_funcionario);
        
        FILE *fp;
        char output[1035];

        // Usar popen para capturar a saída do comando Python
        fp = popen(command, "r");
        if (fp == NULL) {
            printf("Falha ao executar o comando.\n");
            exit(1);
        }

        // Ler a saída do comando
        while (fgets(output, sizeof(output), fp) != NULL) {
            printf("%s", output);
            if (strstr(output, "Erro") != NULL) {
                // Se houver uma mensagem de erro, retorne para a tela de cadastro
                pclose(fp);
                sleep(4);
                Cadastro();  // Voltar ao menu de cadastro
                return;
            }
        }

        // Fechar o processo
        pclose(fp);

        printf("Funcionario cadastrado com sucesso!\n");
        sleep(2);
    } else if (escolha == 3) {
        char nome_produto[50];
        int qtd_produto;
        float preco;

        printf("\nDigite o nome do novo produto sem o uso de caracteres especiais (ou 'exit' para voltar): ");
        fgets(nome_produto, 50, stdin);
        nome_produto[strcspn(nome_produto, "\n")] = 0;  // Remover a quebra de linha
        
        if (strcmp(nome_produto, "exit") == 0) {
            Cadastro();  // Voltar ao menu
        }

        printf("Digite a quantidade do produto com apenas numeros: ");
        scanf("%i", &qtd_produto);
        getchar(); // Limpar o buffer

        printf("Digite o preco por unidade do produto com apenas numeros: ");
        scanf("%f", &preco);
        getchar(); // Limpar o buffer

        // Chamar a função Python para cadastrar o cliionário
        char command[512];
        snprintf(command, sizeof(command),
            "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" \"%s\" \"%d\" \"%f\"",
            nome_produto, qtd_produto, preco);
        
        system(command);
    }
    menu();
    return 0;
}

int Busca() {
    int escolha;
    system("cls");
    printf("|==============================|\n");
    printf("|            BUSCA             |\n");
    printf("|                              |\n");
    printf("|       Tipo de Busca:         |\n");
    printf("| 1 - Funcionario(a)           |\n");
    printf("| 2 - Cliente                  |\n");
    printf("| 3 - Produto                  |\n");
    printf("| 4 - Cancelar operacao        |\n");
    printf("| 9 - Encerrar o sistema       |\n");
    printf("|                              |\n");
    printf("|==============================|\n");
    printf("\nDigite o numero da opcao desejada: ");
    scanf("%i", &escolha);

    while ((escolha < 1 || escolha > 4) && (escolha != 9)) {
        printf("Opcao invalida! Digite uma opcao valida: ");
        scanf("%i", &escolha);
    }

    // Limpa o buffer do teclado
    while (getchar() != '\n');

    if (escolha == 1) {
        char nome[50];
        int opcao = 0;

        printf("\nDigite o nome do(a) funcionario(a) para buscar (ou digite 'Todos' para visualizar todos os(as) funcionarios(as)): ");
        fgets(nome, 50, stdin);
        nome[strcspn(nome, "\n")] = 0; 

        char command[512];
        snprintf(command, sizeof(command),
            "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" buscar funcionario \"%s\"", nome);
        system(command);

        printf("1 - Editar funcionario(a) \n");
        printf("2 - Excluir funcionario(a) \n");
        printf("3 - Voltar\n\n");
        printf("Digite uma das opcoes para prosseguir: ");
        scanf("%i", &opcao);

        while (opcao < 1 || opcao > 3) {
            printf("Opcao invalida! Digite uma opcao valida: ");
            scanf("%i", &opcao);
        }

        // Limpa o buffer do teclado
        while (getchar() != '\n');

        if (opcao == 1) {
            char novo_nome[50], novo_cpf[50], novo_rg[50], nova_data_nasc[50], novo_usuario[50], nova_senha[50];
            int id_funcionario;

            printf("\nDigite o ID do(a) funcionario(a) conforme a tabela acima: ");
            scanf("%i", &id_funcionario);

            while (getchar() != '\n'); // Limpa o buffer

            printf("Digite o novo nome do(a) funcionario(a) (ou pressione Enter para manter o atual): ");
            fgets(novo_nome, sizeof(novo_nome), stdin);
            novo_nome[strcspn(novo_nome, "\n")] = 0;

            printf("Digite o novo CPF do(a) funcionario(a) (ou pressione Enter para manter o atual): ");
            fgets(novo_cpf, sizeof(novo_cpf), stdin);
            novo_cpf[strcspn(novo_cpf, "\n")] = 0;

            printf("Digite o novo RG do(a) funcionario(a) (ou pressione Enter para manter o atual): ");
            fgets(novo_rg, sizeof(novo_rg), stdin);
            novo_rg[strcspn(novo_rg, "\n")] = 0;

            printf("Digite a nova data de nascimento do(a) funcionario(a) (ou pressione Enter para manter a atual): ");
            fgets(nova_data_nasc, sizeof(nova_data_nasc), stdin);
            nova_data_nasc[strcspn(nova_data_nasc, "\n")] = 0;

            printf("Digite o novo nome de usuario do(a) funcionario(a) (ou pressione Enter para manter a atual): ");
            fgets(novo_usuario, sizeof(novo_usuario), stdin);
            novo_usuario[strcspn(novo_usuario, "\n")] = 0;

            printf("Digite a nova senha do(a) funcionario(a) (ou pressione Enter para manter a atual): ");
            fgets(nova_senha, sizeof(nova_senha), stdin);
            nova_senha[strcspn(nova_senha, "\n")] = 0;

            snprintf(command, sizeof(command),
                "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" editar funcionario \"%i\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"",
                id_funcionario, novo_nome, novo_cpf, novo_rg, nova_data_nasc, novo_usuario, nova_senha);
            system(command);
        } else if (opcao == 2) {
            int id_funcionario;
            char confirmacao[50];

            printf("\nDigite o ID do(a) funcionario(a) conforme a tabela acima: ");
            scanf("%i", &id_funcionario);

            while (getchar() != '\n'); // Limpa o buffer

            printf("Tem certeza que deseja exclui-lo(a)? (Digite 'Sim' ou 'Nao'): ");
            fgets(confirmacao, sizeof(confirmacao), stdin);
            confirmacao[strcspn(confirmacao, "\n")] = 0;

            while (strcmp(confirmacao, "Sim") != 0 && strcmp(confirmacao, "Nao") != 0) {
                printf("Opcao invalida! Digite 'Sim' ou 'Nao': ");
                fgets(confirmacao, sizeof(confirmacao), stdin);
                confirmacao[strcspn(confirmacao, "\n")] = 0;
            }

            if (strcmp(confirmacao, "Sim") == 0) {
                snprintf(command, sizeof(command),
                    "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" excluir funcionario \"%i\"",
                    id_funcionario);
                system(command);
            } else {
                return Busca();
            }
        } else if (opcao == 3) {
            return Busca();
        }
    } if (escolha == 2) {
        char nome[50];
        int opcao = 0;

        printf("\nDigite o nome do(a) cliente(a) para buscar (ou digite 'Todos' para visualizar todos os(as) clientes(as)): ");
        fgets(nome, 50, stdin);
        nome[strcspn(nome, "\n")] = 0; 

        char command[512];
        snprintf(command, sizeof(command),
            "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" buscar cliente \"%s\"", nome);
        system(command);

        printf("1 - Editar cliente(a) \n");
        printf("2 - Excluir cliente(a) \n");
        printf("3 - Voltar\n\n");
        printf("Digite uma das opcoes para prosseguir: ");
        scanf("%i", &opcao);

        while (opcao < 1 || opcao > 3) {
            printf("Opcao invalida! Digite uma opcao valida: ");
            scanf("%i", &opcao);
        }

        // Limpa o buffer do teclado
        while (getchar() != '\n');

        if (opcao == 1) {
            char novo_nome[50], novo_cpf[50], novo_rg[50], nova_data_nasc[50];
            int id_cliente;

            printf("\nDigite o ID do(a) cliente conforme a tabela acima: ");
            scanf("%i", &id_cliente);

            while (getchar() != '\n'); // Limpa o buffer

            printf("Digite o novo nome do(a) cliente (ou pressione Enter para manter o atual): ");
            fgets(novo_nome, sizeof(novo_nome), stdin);
            novo_nome[strcspn(novo_nome, "\n")] = 0;

            printf("Digite o novo CPF do(a) cliente (ou pressione Enter para manter o atual): ");
            fgets(novo_cpf, sizeof(novo_cpf), stdin);
            novo_cpf[strcspn(novo_cpf, "\n")] = 0;

            printf("Digite o novo RG do(a) cliente (ou pressione Enter para manter o atual): ");
            fgets(novo_rg, sizeof(novo_rg), stdin);
            novo_rg[strcspn(novo_rg, "\n")] = 0;

            printf("Digite a nova data de nascimento do(a) cliente (ou pressione Enter para manter a atual): ");
            fgets(nova_data_nasc, sizeof(nova_data_nasc), stdin);
            nova_data_nasc[strcspn(nova_data_nasc, "\n")] = 0;

            snprintf(command, sizeof(command),
                "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" editar cliente \"%i\" \"%s\" \"%s\" \"%s\" \"%s\"",
                id_cliente, novo_nome, novo_cpf, novo_rg, nova_data_nasc);
            system(command);
        } else if (opcao == 2) {
            int id_cliente;
            char confirmacao[50];

            printf("\nDigite o ID do cliente conforme a tabela acima: ");
            scanf("%i", &id_cliente);

            while (getchar() != '\n'); // Limpa o buffer

            printf("Tem certeza que deseja exclui-lo(a)? (Digite 'Sim' ou 'Nao'): ");
            fgets(confirmacao, sizeof(confirmacao), stdin);
            confirmacao[strcspn(confirmacao, "\n")] = 0;

            while (strcmp(confirmacao, "Sim") != 0 && strcmp(confirmacao, "Nao") != 0) {
                printf("Opcao invalida! Digite 'Sim' ou 'Nao': ");
                fgets(confirmacao, sizeof(confirmacao), stdin);
                confirmacao[strcspn(confirmacao, "\n")] = 0;
            }

            if (strcmp(confirmacao, "Sim") == 0) {
                snprintf(command, sizeof(command),
                    "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" excluir cliente \"%i\"",
                    id_cliente);
                system(command);
            } else {
                return Busca();
            }
        } else if (opcao == 3) {
            return Busca();
        }
    } else if (escolha == 3) {
        char nome[50];
        int opcao = 0;

        printf("\nDigite o nome do produto para buscar (ou digite 'Todos' para visualizar todos os produtos): ");
        fgets(nome, 50, stdin);
        nome[strcspn(nome, "\n")] = 0; 

        char command[512];
        snprintf(command, sizeof(command),
            "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" \"%s\"", nome);
        system(command);

        printf("1 - Editar produto \n");
        printf("2 - Excluir produto \n");
        printf("3 - Voltar\n\n");
        printf("Digite uma das opcoes para prosseguir: ");
        scanf("%i", &opcao);

        while (opcao < 1 || opcao > 3) {
            printf("Opcao invalida! Digite uma opcao valida: ");
            scanf("%i", &opcao);
        }

        // Limpa o buffer do teclado
        while (getchar() != '\n');

        if (opcao == 1) {
            char novo_nome[50], novo_preco[50];
            int id_produto, nova_quantidade;

            printf("\nDigite o ID do produto conforme a tabela acima: ");
            scanf("%i", &id_produto);

            while (getchar() != '\n'); // Limpa o buffer

            printf("Digite o novo nome do produto (ou pressione Enter para manter o atual): ");
            fgets(novo_nome, sizeof(novo_nome), stdin);
            novo_nome[strcspn(novo_nome, "\n")] = 0;

            printf("Digite o novo preco do produto (ou pressione Enter para manter o atual): ");
            fgets(novo_preco, sizeof(novo_preco), stdin);
            novo_preco[strcspn(novo_preco, "\n")] = 0;

            printf("Digite a nova quantidade do produto (ou pressione Enter para manter a atual): ");
            scanf("%i", &nova_quantidade);

            snprintf(command, sizeof(command),
                "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" \"%i\" \"%s\" \"%s\" \"%i\" editar produto\"",
                id_produto, novo_nome, novo_preco, nova_quantidade);
            system(command);
        } else if (opcao == 2) {
            int id_produto;
            char confirmacao[50];

            printf("\nDigite o ID do produto conforme a tabela acima: ");
            scanf("%i", &id_produto);

            while (getchar() != '\n'); // Limpa o buffer

            printf("Tem certeza que deseja exclui-lo? (Digite 'Sim' ou 'Nao'): ");
            fgets(confirmacao, sizeof(confirmacao), stdin);
            confirmacao[strcspn(confirmacao, "\n")] = 0;

            while (strcmp(confirmacao, "Sim") != 0 && strcmp(confirmacao, "Nao") != 0) {
                printf("Opcao invalida! Digite 'Sim' ou 'Nao': ");
                fgets(confirmacao, sizeof(confirmacao), stdin);
                confirmacao[strcspn(confirmacao, "\n")] = 0;
            }

            if (strcmp(confirmacao, "Sim") == 0) {
                snprintf(command, sizeof(command),
                    "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" excluir produto \"%i\"",
                    id_produto);
                system(command);
            } else {
                return Busca();
            }
        } else if (opcao == 3) {
            return Busca();
        }
    }
    return 0;
}

void GerenciaOpcoes(int opcao) {
    switch (opcao) {
        case 1:
            printf("\nIndo para a tela de cadastro, aguarde...");
            sleep(2);
            Cadastro();
            break;
        case 2:
            printf("\nIndo para a tela de busca, aguarde...");
            sleep(2);
            Busca();
            break;
        case 3:
            printf("3\n");
            break;
    }
    system("pause");
}

// Funções do menu e gerenciamento
int menu() {
    int escolha;
    system("cls");
    printf("|==============================|\n");
    printf("|      SISTEMA HORTIFRUTI      |\n");
    printf("|                              |\n");
    printf("|       Menu de operacoes:     |\n");
    printf("| 1 - Cadastro                 |\n");
    printf("| 2 - Busca                    |\n");
    printf("| 3 - Pesagem                  |\n");
    printf("| 9 - Encerrar o sistema       |\n");
    printf("|                              |\n");
    printf("|==============================|\n");
    printf("\nDigite o numero da opcao desejada: ");
    scanf("%i", &escolha);
    while ((escolha < 1 || escolha > 3) && (escolha != 9)) {
        printf("Opcao invalida! Digite uma opcao valida: ");
        scanf("%i", &escolha);
    }
    if (escolha != 9){
        GerenciaOpcoes(escolha);
        return escolha;
    }else{
        return 0;
    }
}

int main() {
    int opcao;
    system("cls");
    printf("|==============================|\n");
    printf("|        BEM VINDO AO          |\n");
    printf("|      SISTEMA HORTIFRUTI      |\n");
    printf("|==============================|\n");
    printf("\n\n");

    if (Login()) {
        do {
            opcao = menu();
            if (opcao != 9) {
                GerenciaOpcoes(opcao);
            }
        } while (opcao != 9);
    }

    return 0;
}