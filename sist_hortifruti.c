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

    while (1) {
        if (scanf("%d", &escolha) == 1) {  // Verifica se a entrada é um número
            if (escolha < 5 || escolha == 9) {
                break;  // Saída do loop se a escolha for valida
            }
            printf("Opcao invalida! Digite uma opcao valida: ");
        } else {
            printf("Opcao invalida! Digite uma opcao valida: ");
            while (getchar() != '\n');  // Limpa o buffer de entrada
        }
    }

    while (getchar() != '\n');

    if (escolha == 1) {
        char nome_funcionario[50], data_nasc_func[50], usuario_func[50], senha_funcionario[50];
        int cpf_funcionario, rg_funcionario, tipo_funcionario;

        // Nome do Funcionário
        while (1) {
            printf("\nDigite o nome do(a) novo(a) funcionario(a) sem o uso de caracteres especiais (ou 'exit' para voltar): ");
            fgets(nome_funcionario, 50, stdin);
            nome_funcionario[strcspn(nome_funcionario, "\n")] = 0;  // Remover a quebra de linha
            
            if (strcmp(nome_funcionario, "exit") == 0) {
                Cadastro();  // Voltar ao menu
                return;
            } else if (strlen(nome_funcionario) == 0) {
                printf("Nome do funcionario nao pode ser vazio. Tente novamente.\n");
            } else {
                break;  // Se o nome não estiver vazio, sai do loop
            }
        }

        // Data de Nascimento
        while (1) {
            printf("Digite a data de nascimento no seguinte formato: dd/mm/yyyy (ou 'exit' para voltar): ");
            fgets(data_nasc_func, 50, stdin);
            data_nasc_func[strcspn(data_nasc_func, "\n")] = 0;  // Remover a quebra de linha
            
            if (strcmp(data_nasc_func, "exit") == 0) {
                Cadastro();  // Voltar ao menu
                return;
            } else if (strlen(data_nasc_func) == 0) {
                printf("Data de nascimento nao pode ser vazia. Tente novamente.\n");
            } else {
                break;  // Se a data de nascimento não estiver vazia, sai do loop
            }
        }

        // CPF
        while (1) {
            printf("Digite o CPF do(a) funcionario(a) com apenas numeros: ");
            if (scanf("%i", &cpf_funcionario) != 1) {
                printf("Entrada invalida. Tente novamente.\n");
                while (getchar() != '\n'); // Limpar o buffer
            } else {
                break;  // Se o CPF for válido, sai do loop
            }
        }
        getchar(); // Limpar o buffer

        // RG
        while (1) {
            printf("Digite o RG do(a) funcionario(a) com apenas numeros: ");
            if (scanf("%i", &rg_funcionario) != 1) {
                printf("Entrada invalida. Tente novamente.\n");
                while (getchar() != '\n'); // Limpar o buffer
            } else {
                break;  // Se o RG for válido, sai do loop
            }
        }
        getchar(); // Limpar o buffer

        // Nome de Usuário
        while (1) {
            printf("Digite um nome de usuario para o(a) funcionario(a) sem o uso de caracteres especiais (ou 'exit' para voltar): ");
            fgets(usuario_func, 50, stdin);
            usuario_func[strcspn(usuario_func, "\n")] = 0;  // Remover a quebra de linha
            
            if (strcmp(usuario_func, "exit") == 0) {
                Cadastro();  // Voltar ao menu
                return;
            } else if (strlen(usuario_func) == 0) {
                printf("Nome de usuario nao pode ser vazio. Tente novamente.\n");
            } else {
                break;  // Se o nome de usuário não estiver vazio, sai do loop
            }
        }

        // Senha
        while (1) {
            printf("Digite uma senha para o(a) funcionario(a) sem o uso de caracteres especiais (ou 'exit' para voltar): ");
            fgets(senha_funcionario, 50, stdin);
            senha_funcionario[strcspn(senha_funcionario, "\n")] = 0;  // Remover a quebra de linha
            
            if (strcmp(senha_funcionario, "exit") == 0) {
                Cadastro();  // Voltar ao menu
                return;
            } else if (strlen(senha_funcionario) == 0) {
                printf("Senha nao pode ser vazia. Tente novamente.\n");
            } else {
                break;  // Se a senha não estiver vazia, sai do loop
            }
        }

        // Tipo de Usuário
        while (1) {
            printf("Digite o tipo de usuario para o(a) funcionario(a), sendo 1 = Administrador, 2 = Gerente, 3 = Supervisor, 4 = Funcionario: ");
            if (scanf("%i", &tipo_funcionario) != 1 || tipo_funcionario < 1 || tipo_funcionario > 4) {
                printf("Tipo de usuario invalido. Tente novamente.\n");
                while (getchar() != '\n'); // Limpar o buffer
            } else {
                break;  // Se o tipo de usuário for válido, sai do loop
            }
        }
        getchar(); // Limpar o buffer

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
    } else if (escolha == 2) {
        char nome_cliente[50], data_nasc_cli[50];
        int cpf_cliente, rg_cliente;

        // Nome
        while (1) {
            printf("Digite o nome do usuario: ");
            fgets(nome_cliente, 100, stdin);
            nome_cliente[strcspn(nome_cliente, "\n")] = 0;  // Remover a quebra de linha
            
            if (strlen(nome_cliente) == 0) {
                printf("Nome nao pode estar vazio. Tente novamente.\n");
            } else {
                if (strcmp(nome_cliente, "exit") == 0) {
                    Cadastro();  // Voltar ao menu
                    return;
                }else{
                    break;  // Se o nome não estiver vazio, sai do loop
                }
            }
        }

        // CPF
        while (1) {
            printf("Digite o CPF do(a) cliente com apenas numeros: ");
            if (scanf("%i", &cpf_cliente) != 1) {
                printf("Entrada invalida. Tente novamente.\n");
                while (getchar() != '\n'); // Limpar o buffer
            } else {
                break;  // Se o CPF for válido, sai do loop
            }
        }
        getchar(); // Limpar o buffer

        // RG
        while (1) {
            printf("Digite o RG do(a) cliente com apenas numeros: ");
            if (scanf("%i", &rg_cliente) != 1) {
                printf("Entrada invalida. Tente novamente.\n");
                while (getchar() != '\n'); // Limpar o buffer
            } else {
                break;  // Se o RG for válido, sai do loop
            }
        }
        getchar(); // Limpar o buffer

        // Data de Nascimento
        while (1) {
            printf("Digite a data de nascimento do usuario (dd/mm/aaaa): ");
            fgets(data_nasc_cli, 11, stdin);
            data_nasc_cli[strcspn(data_nasc_cli, "\n")] = 0;  // Remover a quebra de linha
            
            if (strlen(data_nasc_cli) == 0) {
                printf("Data de nascimento nao pode estar vazia. Tente novamente.\n");
            } else {
                break;  // Se a data de nascimento não estiver vazia, sai do loop
            }
        }

        // Chamar a função Python para cadastrar o funcionário e capturar a saída
        char command[512];
        snprintf(command, sizeof(command),
            "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" cadastrar cliente \"%s\" \"%d\" \"%s\" \"%d\"",
            nome_cliente, cpf_cliente, data_nasc_cli, rg_cliente);
        
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
    } else if (escolha == 3) {
        char nome_produto[50], tipo_venda[50];
        int qtd_produto;
        float preco;

        while (1) {
            printf("\nDigite o nome do novo produto sem o uso de caracteres especiais (ou 'exit' para voltar): ");
            fgets(nome_produto, 50, stdin);
            nome_produto[strcspn(nome_produto, "\n")] = 0;  // Remove a quebra de linha
            
            if (strcmp(nome_produto, "exit") == 0) {
                Cadastro();  // Voltar ao menu
                return 0;    // Encerra a função atual
            } else if (strlen(nome_produto) == 0) {
                printf("Nome do produto nao pode ser vazio. Tente novamente.\n");
            } else {
                break;  // Se o nome do produto for válido, sai do loop
            }
        }

        // Solicita a quantidade do produto
        while (1) {
            printf("Digite a quantidade do produto com apenas numeros: ");
            if (scanf("%d", &qtd_produto) == 1) {
                break;  // Se a entrada for valida, sai do loop
            } else {
                printf("Entrada invalida. Digite apenas numeros.\n");
                while (getchar() != '\n');  // Limpa o buffer de entrada
            }
        }

        getchar(); // Limpar o buffer de entrada

        // Solicita o tipo de venda
        while (1) {
            printf("Digite o tipo de venda do novo produto (Granel ou Peso): ");
            fgets(tipo_venda, 50, stdin);
            tipo_venda[strcspn(tipo_venda, "\n")] = 0;  // Remove a quebra de linha
            
            if (strlen(tipo_venda) == 0) {
                printf("Tipo de venda nao pode ser vazio. Tente novamente.\n");
            } else if (strcmp(tipo_venda, "Granel") != 0 && strcmp(tipo_venda, "Peso") != 0) {
                printf("Opção invalida! Digite uma opção valida (Granel ou Peso): ");
            } else {
                break;  // Se o tipo de venda for válido, sai do loop
            }
        }

        // Solicita o preco do produto
        while (1) {
            printf("Digite o preco por unidade do produto por %s: ", &tipo_venda);
            if (scanf("%f", &preco) == 1) {
                break;  // Se a entrada for valida, sai do loop
            } else {
                printf("Entrada invalida. Digite apenas numeros.\n");
                while (getchar() != '\n');  // Limpa o buffer de entrada
            }
        }

        getchar(); // Limpar o buffer de entrada

        // Chamar a função Python para cadastrar o cliionário
        char command[512];
        snprintf(command, sizeof(command),
            "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" \"%s\" \"%d\" \"%f\" \"%s\"",
            nome_produto, qtd_produto, preco, tipo_venda);
        
        system(command);
    } else if (escolha == 4){
        menu();
    } else if (escolha == 9){
        printf("Encerrando o sistema...\n");
        sleep(3);
        exit(0);
    }
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

    while (1) {
        if (scanf("%d", &escolha) == 1) {  // Verifica se a entrada é um número
            if ((escolha >= 1 && escolha <= 4) || escolha == 9) {
                break;  // Saída do loop se a escolha for valida
            }
            printf("Opcao invalida! Digite uma opcao valida: ");
        } else {
            printf("Opcao invalida! Digite uma opcao valida: ");
            while (getchar() != '\n');  // Limpa o buffer de entrada
        }
    }

    // Limpa o buffer do teclado após uma entrada valida
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

        FILE *fp;
        char output[1035];

        // Usar popen para capturar a saída do comando Python
        fp = popen(command, "r");
        if (fp == NULL) {
            printf("Falha ao executar o comando.\n");
            exit(1);
        }

        while (fgets(output, sizeof(output), fp) != NULL) {
            if (strstr(output, "Nenhum") != NULL) {
                // Se houver uma mensagem de erro, retorne para a tela de cadastro
                pclose(fp);
                sleep(2);
                Busca();  // Voltar ao menu de cadastro
                return 0;
            } else{
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
            }
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

        FILE *fp;
        char output[1035];

        // Usar popen para capturar a saída do comando Python
        fp = popen(command, "r");
        if (fp == NULL) {
            printf("Falha ao executar o comando.\n");
            exit(1);
        }

        while (fgets(output, sizeof(output), fp) != NULL) {
            if (strstr(output, "Nenhum") != NULL) {
                // Se houver uma mensagem de erro, retorne para a tela de cadastro
                pclose(fp);
                sleep(2);
                Busca();  // Voltar ao menu de cadastro
                return;
            } else{
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
            }
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

        FILE *fp;
        char output[1035];

        // Usar popen para capturar a saída do comando Python
        fp = popen(command, "r");
        if (fp == NULL) {
            printf("Falha ao executar o comando.\n");
            exit(1);
        }

        while (fgets(output, sizeof(output), fp) != NULL) {
            if (strstr(output, "Nenhum") != NULL) {
                // Se houver uma mensagem de erro, retorne para a tela de cadastro
                pclose(fp);
                sleep(2);
                Busca();  // Voltar ao menu de cadastro
                return;
            } else {

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
                    char novo_nome[50], novo_preco[50], novo_tipo[50];
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

                    while (1) {
                        printf("Digite o novo tipo do produto (Granel ou Peso): ");
                        fgets(novo_tipo, 50, stdin);
                        novo_tipo[strcspn(novo_tipo, "\n")] = 0;  // Remove a quebra de linha
                        
                        if (strlen(novo_tipo) == 0) {
                            printf("Tipo de venda nao pode ser vazio. Tente novamente.\n");
                        } else if (strcmp(novo_tipo, "Granel") != 0 && strcmp(novo_tipo, "Peso") != 0) {
                            printf("Opção invalida! Digite uma opção valida (Granel ou Peso): ");
                        } else {
                            break;  // Se o tipo de venda for válido, sai do loop
                        }
                    }

                    snprintf(command, sizeof(command),
                        "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" \"%i\" \"%s\" \"%s\" \"%i\" \"%s\" editar produto\"",
                        id_produto, novo_nome, novo_preco, nova_quantidade, novo_tipo);
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
        }
    } else if (escolha == 4){
        menu();
    } else if (escolha == 9){
        printf("Encerrando o sistema...\n");
        sleep(3);
        exit(0);
    }
}

int Pesagem() {
    int escolha;
    system("cls");
    printf("|==============================|\n");
    printf("|            PESAGEM           |\n");
    printf("|                              |\n");
    printf("| 1 - Pesar produto            |\n");
    printf("| 2 - Cancelar operacao        |\n");
    printf("| 9 - Encerrar o sistema       |\n");
    printf("|                              |\n");
    printf("|==============================|\n");
    printf("\nDigite o numero da opcao desejada: ");

    while (1) {
        if (scanf("%d", &escolha) == 1) {  // Verifica se a entrada é um número
            if ((escolha >= 1 && escolha <= 2) || escolha == 9) {
                break;  // Saída do loop se a escolha for valida
            }
            printf("Opcao invalida! Digite uma opcao valida: ");
        } else {
            printf("Opcao invalida! Digite uma opcao valida: ");
            while (getchar() != '\n');  // Limpa o buffer de entrada
        }
    }

    // Limpa o buffer do teclado após uma entrada valida
    while (getchar() != '\n');

    if (escolha == 1) {
        char nome[50] = "Todos";
        int opcao;

        char command[512];
        snprintf(command, sizeof(command),
            "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" \"%s\"", nome);
        system(command);

        FILE *fp;
        char output[1035];

        // Usar popen para capturar a saída do comando Python
        fp = popen(command, "r");
        if (fp == NULL) {
            printf("Falha ao executar o comando.\n");
            exit(1);
        }

        while (fgets(output, sizeof(output), fp) != NULL) {
            if (strstr(output, "Nenhum") != NULL) {
                // Se houver uma mensagem de erro, retorne para a tela de cadastro
                pclose(fp);
                sleep(2);
                Busca();  // Voltar ao menu de cadastro
                return 0;
            } else {
                float peso, preco;

                while (1) {
                    printf("\nDigite o preco do produto conforme a tabela acima (tendo 100g como base): ");
                    if (scanf("%f", &preco) == 1) {
                        break;  // Se a entrada for valida, sai do loop
                    } else {
                        printf("Entrada invalida.\n");
                        while (getchar() != '\n');  // Limpa o buffer de entrada
                    }
                }

                while (1) {
                    printf("Digite a quantidade do peso que deseja (tendo 100g como base): ");
                    if (scanf("%f", &peso) == 1) {
                        break;  // Se a entrada for valida, sai do loop
                    } else {
                        printf("Entrada invalida.\n");
                        while (getchar() != '\n');  // Limpa o buffer de entrada
                    }
                }

                float total = preco * peso;

                printf("O valor total e de : %.2f reais", total);

            }
        }

    } else if (escolha == 2){
        menu();
    } else if (escolha == 9){
        printf("Encerrando o sistema...\n");
        sleep(3);
        exit(0);
    }
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
            printf("\nIndo para a tela de pesagem, aguarde...");
            sleep(2);
            Pesagem();
            break;
        case 4:
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
    printf("| 4 - Caixa                    |\n");
    printf("| 9 - Encerrar o sistema       |\n");
    printf("|                              |\n");
    printf("|==============================|\n");
    printf("\nDigite o numero da opcao desejada: ");

    while (1) {
        if (scanf("%d", &escolha) == 1) {  // Verifica se a entrada é um número
            if (escolha < 5 || escolha == 9) {
                break;  // Saída do loop se a escolha for valida
            }
            printf("Opcao invalida! Digite uma opcao valida: ");
        } else {
            printf("Opcao invalida! Digite uma opcao valida: ");
            while (getchar() != '\n');  // Limpa o buffer de entrada
        }
    }
    if (escolha != 9){
        GerenciaOpcoes(escolha);
        return escolha;
    }else{
        printf("Encerrando o sistema...\n");
        sleep(3);
        exit(0);
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