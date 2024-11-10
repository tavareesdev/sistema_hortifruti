#include <stdio.h>      // Biblioteca para entrada e saída padrão (printf, fgets)
#include <stdlib.h>     // Biblioteca para funções de utilidade geral (snprintf, system)
#include <string.h>     // Biblioteca para manipulação de strings (strcmp, strcspn)
#include <unistd.h>     // Biblioteca para chamadas ao sistema POSIX (sleep)
#include <time.h>       // Biblioteca para manipulação de tempo (time)
#include <conio.h>
#include <stdbool.h>
#include <locale.h>

#define MAX_IDS 100 // Limite de armazenamento de IDs

#define MAX_OUTPUT 1035

// Define o número máximo de produtos no sistema
#define MAX_PRODUTOS 100

// Define o tamanho máximo permitido para o nome de um produto
#define MAX_NOME 50

// Define o tamanho do buffer para leitura de arquivos ou execução de comandos
#define BUFFER_SIZE 4096

// Define a largura padrão de uma linha, possivelmente para impressão ou exibição formatada
#define LARGURA_LINHA 30

#define MAX_SAIDA 200

/**
 * Função: Login
 * -----------------
 * Realiza o processo de autenticação do usuário, solicitando nome de usuário e senha
 * e verificando as credenciais através de um script Python externo.
 *
 * Retorno:
 *  - int: Retorna 1 se o login foi bem-sucedido, 0 em caso de falha.
 *
 * Descrição:
 *  1. A função inicia solicitando que o usuário insira seu nome de usuário e senha.
 *  2. As entradas são lidas e qualquer quebra de linha é removida para evitar erros.
 *  3. Um comando é montado para chamar um script Python externo, passando o nome de usuário e senha como argumentos.
 *  4. O comando é executado, e o resultado do script é lido.
 *  5. Se o script retorna "Login bem-sucedido!", a função confirma o login e permite o acesso ao sistema.
 *  6. Se o login falhar, o usuário é solicitado a tentar novamente.
 */
// Variáveis globais para armazenar o ID, tipo e nome do usuário
int user_id;
char user_name[50];
int user_type;

void obter_senha(char *senha, int tamanho) {
    int i = 0;
    char ch;
    
    printf("Digite sua senha: ");
    while ((ch = getch()) != '\r' && i < tamanho - 1) {  // '\r' é o Enter no Windows
        if (ch == '\b' && i > 0) {  // Permite apagar com Backspace
            printf("\b \b");
            i--;
        } else if (ch != '\b') {
            senha[i++] = ch;
            printf("*");  // Exibe * no lugar do caractere digitado
        }
    }
    senha[i] = '\0';  // Termina a string
    printf("\n");
}

int Login() {
    char username[50], password[50];
    int login_sucesso = 0;

    while (!login_sucesso) {
        printf("Digite seu nome de usuário: ");
        fgets(username, 50, stdin);
        username[strcspn(username, "\n")] = 0;

        obter_senha(password, 50);  // Usa a função obter_senha para ocultar entrada

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

        result[strcspn(result, "\r\n")] = 0;

        // Verifica se o login foi bem-sucedido e captura os dados do usuário
        if (strstr(result, "Usuario ou senha incorretos.") == NULL && strstr(result, "Erro") == NULL) {
            sscanf(result, "%d,%[^,],%d", &user_id, user_name, &user_type);
            printf("\nLogin realizado com sucesso!\n");
            printf("Acessando o sistema, aguarde...\n");
            sleep(3);
            login_sucesso = 1;
        } else {
            printf("\nUsuário ou senha incorretos. Tente novamente.\n");
        }
    }

    return login_sucesso;
}

/**
 * Função de cadastro para diferentes tipos de entidades (Funcionário, Cliente, Produto) e opções de controle do sistema.
 *
 * Esta função exibe um menu para o usuário escolher o tipo de cadastro ou opções de controle do sistema. Dependendo da escolha, ela permite o cadastro de um novo funcionário, cliente ou produto. Também pode cancelar a operação atual ou encerrar o sistema.
 *
 * A função realiza o seguinte:
 *
 * 1. Exibe um menu com as opções disponíveis:
 *    - 1: Cadastro de Funcionário
 *    - 2: Cadastro de Cliente
 *    - 3: Cadastro de Produto
 *    - 4: Cancelar Operação
 *    - 9: Encerrar o Sistema
 *
 * 2. Após a escolha do usuário, realiza a seguinte ação com base na opção selecionada:
 *    - **Opção 1: Cadastro de Funcionário**
 *      - Solicita e válida os seguintes dados do funcionário:
 *        - Nome (não pode estar vazio e não pode conter caracteres especiais)
 *        - Data de Nascimento (no formato dd/mm/yyyy)
 *        - CPF (apenas números)
 *        - RG (apenas números)
 *        - Nome de Usuário (não pode estar vazio e não pode conter caracteres especiais)
 *        - Senha (não pode estar vazia e não pode conter caracteres especiais)
 *        - Tipo de Usuário (deve ser um valor entre 1 e 4)
 *      - Executa um comando Python para cadastrar o funcionário e captura a saída do comando.
 *      - Em caso de erro na execução do comando, retorna ao menu de cadastro.
 *
 *    - **Opção 2: Cadastro de Cliente**
 *      - Solicita e válida os seguintes dados do cliente:
 *        - Nome (não pode estar vazio)
 *        - CPF (apenas números)
 *        - RG (apenas números)
 *        - Data de Nascimento (no formato dd/mm/aaaa)
 *      - Executa um comando Python para cadastrar o cliente e captura a saída do comando.
 *      - Em caso de erro na execução do comando, retorna ao menu de cadastro.
 *
 *    - **Opção 3: Cadastro de Produto**
 *      - Solicita e válida os seguintes dados do produto:
 *        - Nome (não pode estar vazio e não pode conter caracteres especiais)
 *        - Quantidade (apenas números)
 *        - Tipo de Venda (deve ser "Granel" ou "Peso")
 *        - Preço por unidade (um valor numérico)
 *      - Executa um comando Python para cadastrar o produto.
 *
 *    - **Opção 4: Cancelar Operação**
 *      - Retorna ao menu principal.
 *
 *    - **Opção 9: Encerrar o Sistema**
 *      - Exibe uma mensagem de encerramento e fecha o sistema após uma pausa de 3 segundos.
 *
 * A função utiliza as funções `system()`, `printf()`, `scanf()`, `fgets()`, e `popen()` para interagir com o usuário e executar comandos externos.
 *
 *  return Retorna 0 ao finalizar a função.
 */
int Cadastro() {
    int escolha;
    system("cls");
    printf("|==============================|\n");
    printf("|           CADASTRO           |\n");
    printf("|                              |\n");
    printf("|       Tipo de Cadastro:      |\n");
    printf("| 1 - Funcionário(a)           |\n");
    printf("| 2 - Cliente                  |\n");
    printf("| 3 - Produto                  |\n");
    printf("| 4 - Cancelar operação        |\n");
    printf("| 9 - Encerrar o sistema       |\n");
    printf("|                              |\n");
    printf("|==============================|\n");
    printf("\nDigite o número da opção desejada: ");

    while (1) {
        if (scanf("%d", &escolha) == 1) {  // Verifica se a entrada é um número
            if (escolha < 5 || escolha == 9) {
                break;  // Saída do loop se a escolha for válida
            }
            printf("Opção inválida! Digite uma opção válida: ");
        } else {
            printf("Opção inválida! Digite uma opção válida: ");
            while (getchar() != '\n');  // Limpa o buffer de entrada
        }
    }

    while (getchar() != '\n');

    if (escolha == 1) {
        if (user_type != 3 && user_type != 4) {
            char nome_funcionario[50], data_nasc_func[50], usuario_func[50], senha_funcionario[50];
            int cpf_funcionario, rg_funcionario, tipo_funcionario;

            // Nome do Funcionário
            while (1) {
                printf("\nDigite o nome do(a) novo(a) funcionário(a) (ou 'exit' para voltar): ");
                fgets(nome_funcionario, 50, stdin);
                nome_funcionario[strcspn(nome_funcionario, "\n")] = 0;  // Remover a quebra de linha

                if (strcmp(nome_funcionario, "exit") == 0) {
                    Cadastro();  // Voltar ao menu
                    return;
                } else if (strlen(nome_funcionario) == 0) {
                    printf("Nome do funcionário não pode ser vazio. Tente novamente.\n");
                } else {
                    break;  // Se o nome não estiver vazio, sai do loop
                }
            }

            // Data de Nascimento
            while (1) {
                printf("Digite a data de nascimento (dd/mm/aaaa) (ou 'exit' para voltar): ");
                fgets(data_nasc_func, 50, stdin);
                data_nasc_func[strcspn(data_nasc_func, "\n")] = 0;  // Remover a quebra de linha

                if (strcmp(data_nasc_func, "exit") == 0) {
                    Cadastro();  // Voltar ao menu
                    return;
                } else if (strlen(data_nasc_func) == 0) {
                    printf("Data de nascimento não pode ser vazia. Tente novamente.\n");
                } else {
                    break;  // Se a data de nascimento não estiver vazia, sai do loop
                }
            }

            // CPF
            while (1) {
                printf("Digite o CPF do(a) funcionário(a) com apenas números: ");
                if (scanf("%i", &cpf_funcionario) != 1) {
                    printf("Entrada inválida. Tente novamente.\n");
                    while (getchar() != '\n'); // Limpar o buffer
                } else {
                    break;  // Se o CPF for válido, sai do loop
                }
            }
            getchar(); // Limpar o buffer

            // RG
            while (1) {
                printf("Digite o RG do(a) funcionário(a) com apenas números: ");
                if (scanf("%i", &rg_funcionario) != 1) {
                    printf("Entrada invaálida. Tente novamente.\n");
                    while (getchar() != '\n'); // Limpar o buffer
                } else {
                    break;  // Se o RG for válido, sai do loop
                }
            }
            getchar(); // Limpar o buffer

            // Nome de Usuário
            while (1) {
                printf("Digite um nome de usuário para o(a) funcionário(a) (ou 'exit' para voltar): ");
                fgets(usuario_func, 50, stdin);
                usuario_func[strcspn(usuario_func, "\n")] = 0;  // Remover a quebra de linha

                if (strcmp(usuario_func, "exit") == 0) {
                    Cadastro();  // Voltar ao menu
                    return;
                } else if (strlen(usuario_func) == 0) {
                    printf("Nome de usuário não pode ser vazio. Tente novamente.\n");
                } else {
                    break;  // Se o nome de usuário não estiver vazio, sai do loop
                }
            }

            // Senha
            while (1) {
                printf("Digite uma senha para o(a) funcionário(a) (ou 'exit' para voltar): ");
                fgets(senha_funcionario, 50, stdin);
                senha_funcionario[strcspn(senha_funcionario, "\n")] = 0;  // Remover a quebra de linha

                if (strcmp(senha_funcionario, "exit") == 0) {
                    Cadastro();  // Voltar ao menu
                    return;
                } else if (strlen(senha_funcionario) == 0) {
                    printf("Senha não pode ser vazia. Tente novamente.\n");
                } else {
                    break;  // Se a senha não estiver vazia, sai do loop
                }
            }

            // Tipo de Usuário
            while (1) {
                printf("Digite o tipo de usuário para o(a) funcionário(a), sendo 1 = Administrador, 2 = Gerente, 3 = Supervisor, 4 = Funcionario: ");
                if (scanf("%i", &tipo_funcionario) != 1 || tipo_funcionario < 1 || tipo_funcionario > 4) {
                    printf("Tipo de usuário inválido. Tente novamente.\n");
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
        } else {
            printf("\nVocê não tem permissão para acessar essa funcionalidade!\n");
            printf("\nVoltando para o menu de cadastro, aguarde...");
            sleep(2);
            Cadastro();
        }
    } else if (escolha == 2) {
        if (user_type != 4) {
            char nome_cliente[50], data_nasc_cli[50];
            int cpf_cliente, rg_cliente;

            // Nome
            while (1) {
                printf("Digite o nome do(a) cliente: ");
                fgets(nome_cliente, 100, stdin);
                nome_cliente[strcspn(nome_cliente, "\n")] = 0;  // Remover a quebra de linha

                if (strlen(nome_cliente) == 0) {
                    printf("Nome não pode estar vazio. Tente novamente.\n");
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
                printf("Digite o CPF do(a) cliente com apenas números: ");
                if (scanf("%i", &cpf_cliente) != 1) {
                    printf("Entrada inválida. Tente novamente.\n");
                    while (getchar() != '\n'); // Limpar o buffer
                } else {
                    break;  // Se o CPF for válido, sai do loop
                }
            }
            getchar(); // Limpar o buffer

            // RG
            while (1) {
                printf("Digite o RG do(a) cliente com apenas números: ");
                if (scanf("%i", &rg_cliente) != 1) {
                    printf("Entrada inválida. Tente novamente.\n");
                    while (getchar() != '\n'); // Limpar o buffer
                } else {
                    break;  // Se o RG for válido, sai do loop
                }
            }
            getchar(); // Limpar o buffer

            // Data de Nascimento
            while (1) {
                printf("Digite a data de nascimento do usuário (dd/mm/aaaa): ");
                fgets(data_nasc_cli, 11, stdin);
                data_nasc_cli[strcspn(data_nasc_cli, "\n")] = 0;  // Remover a quebra de linha

                if (strlen(data_nasc_cli) == 0) {
                    printf("Data de nascimento não pode estar vazia. Tente novamente.\n");
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
        } else {
            printf("\nVocê não tem permissão para acessar essa funcionalidade!\n");
            printf("\nVoltando para o menu de cadastro, aguarde...");
            sleep(2);
            Cadastro();
        }
    } else if (escolha == 3) {
        int escolha;
        system("cls");
        printf("|==============================|\n");
        printf("|      CADASTRO DE PRODUTO     |\n");
        printf("|                              |\n");
        printf("|         Tipo de Venda:       |\n");
        printf("| 1 - Peso                     |\n");
        printf("| 2 - Granel                   |\n");
        printf("| 3 - Cancelar operacao        |\n");
        printf("| 9 - Encerrar o sistema       |\n");
        printf("|                              |\n");
        printf("|==============================|\n");
        printf("\nDigite o número da opção desejada: ");

        while (1) {
            if (scanf("%d", &escolha) == 1) {  // Verifica se a entrada é um número
                if (escolha < 4 || escolha == 9) {
                    break;  // Saída do loop se a escolha for válida
                }
                printf("Opção inválida! Digite uma opção válida: ");
            } else {
                printf("Opção inválida! Digite uma opção válida: ");
                while (getchar() != '\n');  // Limpa o buffer de entrada
            }
        }

        while (getchar() != '\n');

        char nome_produto[50], tipo_venda[50];
        float preco, qtd_produto;
        
        if (escolha == 1 || escolha == 2 ){
            if (escolha == 1) {

                strcpy(tipo_venda, "Peso");

                while (1) {
                    printf("\nDigite o nome do novo produto (ou 'exit' para voltar): ");
                    fgets(nome_produto, 50, stdin);
                    nome_produto[strcspn(nome_produto, "\n")] = 0;  // Remove a quebra de linha

                    if (strcmp(nome_produto, "exit") == 0) {
                        Cadastro();  // Voltar ao menu
                        return 0;    // Encerra a função atual
                    } else if (strlen(nome_produto) == 0) {
                        printf("Nome do produto não pode ser vazio. Tente novamente.\n");
                    } else {
                        break;  // Se o nome do produto for válido, sai do loop
                    }
                }

                // Solicita a quantidade do produto
                while (1) {
                    printf("Digite a quantidade do produto por Kg: ");
                    if (scanf("%f", &qtd_produto) == 1) {
                        getchar(); // Limpa o '\n' residual
                        break;  // Se a entrada for válida, sai do loop
                    } else {
                        printf("Entrada inválida. Digite apenas números.\n");
                        while (getchar() != '\n');  // Limpa o buffer de entrada
                    }
                }

                // Solicita o preço do produto
                while (1) {
                    printf("Digite o preço do produto por Kg: ");
                    if (scanf("%f", &preco) == 1) {
                        getchar(); // Limpa o '\n' residual
                        break;  // Se a entrada for válida, sai do loop
                    } else {
                        printf("Entrada inválida. Digite apenas números.\n");
                        while (getchar() != '\n');  // Limpa o buffer de entrada
                    }
                }

                getchar(); // Limpar o buffer de entrada
            } else if (escolha == 2) {

                strcpy(tipo_venda, "Granel");

                while (1) {
                    printf("\nDigite o nome do novo produto (ou 'exit' para voltar): ");
                    fgets(nome_produto, 50, stdin);
                    nome_produto[strcspn(nome_produto, "\n")] = 0;  // Remove a quebra de linha

                    if (strcmp(nome_produto, "exit") == 0) {
                        Cadastro();  // Voltar ao menu
                        return 0;    // Encerra a função atual
                    } else if (strlen(nome_produto) == 0) {
                        printf("Nome do produto não pode ser vazio. Tente novamente.\n");
                    } else {
                        break;  // Se o nome do produto for válido, sai do loop
                    }
                }

                // Solicita a quantidade do produto
                while (1) {
                    printf("Digite a quantidade do produto: ");
                    if (scanf("%f", &qtd_produto) == 1) {
                        getchar(); // Limpa o '\n' residual
                        break;  // Se a entrada for válida, sai do loop
                    } else {
                        printf("Entrada inválida. Digite apenas números.\n");
                        while (getchar() != '\n');  // Limpa o buffer de entrada
                    }
                }

                // Solicita o preço do produto
                while (1) {
                    printf("Digite o preço do produto por unidade: ");
                    if (scanf("%f", &preco) == 1) {
                        getchar(); // Limpa o '\n' residual
                        break;  // Se a entrada for válida, sai do loop
                    } else {
                        printf("Entrada inválida. Digite apenas números.\n");
                        while (getchar() != '\n');  // Limpa o buffer de entrada
                    }
                }

                getchar(); // Limpar o buffer de entrada
            }

            // Chamar a função Python para cadastrar o cliionário
            char command[512];
            snprintf(command, sizeof(command),
                "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" \"%s\" \"%.2f\" \"%f\" \"%s\"",
                nome_produto, qtd_produto, preco, tipo_venda);

            int ret = system(command);
            if (ret != 0) {
                printf("Não foi possível cadastrar o produto. Tente novamente com um nome diferente.\n");
            }

        } else if (escolha == 3){
            menu();
        } else if (escolha == 9){
            printf("Encerrando o sistema...\n");
            sleep(3);
            exit(0);
        }
    } else if (escolha == 4){
        menu();
    } else if (escolha == 9){
        printf("Encerrando o sistema...\n");
        sleep(3);
        exit(0);
    }
    return 0;
}

/**
 * Exibe um menu para o usuário selecionar o tipo de busca a ser realizada (Funcionário, Cliente, Produto)
 * e executa as operações correspondentes, como buscar, editar ou excluir registros no sistema.
 *
 * int Retorna 0 se a operação for concluída com sucesso, e -1 em caso de erro.
 *
 * A função `Busca()` permite ao usuário buscar por registros específicos (Funcionário, Cliente, Produto) no sistema.
 * Após selecionar o tipo de busca, o usuário pode inserir o nome para realizar a busca. Se o registro for encontrado,
 * a função oferece opções para editar ou excluir o registro. Caso a operação seja bem-sucedida, a função retorna ao
 * menu principal. Em caso de erro ou se o registro não for encontrado, a função retorna à tela de busca.
 *
 * O menu principal inclui as seguintes opções:
 * - 1: Buscar Funcionário(a)
 * - 2: Buscar Cliente(a)
 * - 3: Buscar Produto
 * - 4: Cancelar operação e retornar ao menu anterior
 * - 9: Encerrar o sistema
 *
 * A função utiliza chamadas ao sistema para executar scripts Python que manipulam dados em arquivos Excel.
 * Dependendo da entrada do usuário, as operações subsequentes incluem edição ou exclusão dos registros encontrados.
 *
 * A função faz uso de bibliotecas padrão como `stdio.h` e `stdlib.h`, e assume que scripts Python estão localizados
 *       em um diretório específico do sistema de arquivos.
 */

int Busca() {
    int escolha;
    system("cls");
    printf("|==============================|\n");
    printf("|            BUSCA             |\n");
    printf("|                              |\n");
    printf("|       Tipo de Busca:         |\n");
    printf("| 1 - Funcionário(a)           |\n");
    printf("| 2 - Cliente                  |\n");
    printf("| 3 - Produto                  |\n");
    printf("| 4 - Cancelar operação        |\n");
    printf("| 9 - Encerrar o sistema       |\n");
    printf("|                              |\n");
    printf("|==============================|\n");
    printf("\nDigite o número da opção desejada: ");

    while (1) {
        if (scanf("%d", &escolha) == 1) {  // Verifica se a entrada é um número
            if ((escolha >= 1 && escolha <= 4) || escolha == 9) {
                break;  // Saída do loop se a escolha for válida
            }
            printf("Opção inválida! Digite uma opção válida: ");
        } else {
            printf("Opção inválida! Digite uma opção válida: ");
            while (getchar() != '\n');  // Limpa o buffer de entrada
        }
    }

    // Limpa o buffer do teclado após uma entrada válida
    while (getchar() != '\n');

    if (escolha == 1) {
        if (user_type != 3 && user_type != 4) {
            char nome[50];
            int opcao = 0;

            printf("\nDigite o nome do(a) funcionário(a) para buscar (ou digite 'Todos' para visualizar todos os(as) funcionarios(as)): ");
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = 0;

            char command[512];
            snprintf(command, sizeof(command),
                    "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" buscar funcionário \"%s\"", nome);
            system(command);

            FILE *fp;
            char output[1035];

            // Usar popen para capturar a saída do comando Python
            fp = popen(command, "r");
            if (fp == NULL) {
                printf("Falha ao executar o comando.\n");
                exit(1);
            }

            int ids[100]; // Armazena IDs dos funcionários encontrados
            int count = 0;

            while (fgets(output, sizeof(output), fp) != NULL) {
                if (strstr(output, "Nenhum") != NULL) {
                    // Se houver uma mensagem de erro, retorne para a tela de cadastro
                    pclose(fp);
                    sleep(2);
                    Busca();  // Voltar ao menu de cadastro
                    return;
                } else {
                    // Aqui armazenamos os IDs encontrados na busca
                    if (sscanf(output, "%d", &ids[count]) == 1) {
                        count++;
                    }
                }
            }

            if (count == 0) {
                printf("Nenhum funcionário encontrado.\n");
                pclose(fp);
                sleep(2);
                Busca();  // Voltar ao menu de cadastro
                return;
            }

            pclose(fp);

            printf("\n1 - Editar funcionário(a)\n");
            printf("2 - Excluir funcionário(a)\n");
            printf("3 - Voltar\n\n");
            printf("Digite uma das opcoes para prosseguir: ");
            scanf("%i", &opcao);

            while (opcao < 1 || opcao > 3) {
                printf("Opção inválida! Digite uma opção válida: ");
                scanf("%i", &opcao);
            }

            // Limpa o buffer do teclado
            while (getchar() != '\n');

            if (opcao == 1) {
                int id_funcionario;
                int id_existe = 0;

                // Loop para garantir que o usuário insira um ID válido
                do {
                    printf("\nDigite o ID do(a) funcionário(a) conforme a tabela acima: ");
                    scanf("%i", &id_funcionario);
                    while (getchar() != '\n'); // Limpa o buffer

                    // Verifica se o ID inserido existe na lista de IDs
                    id_existe = 0;
                    for (int i = 0; i < count; i++) {
                        if (ids[i] == id_funcionario) {
                            id_existe = 1;
                            break;
                        }
                    }

                    if (!id_existe) {
                        printf("O ID inserido não existe! Tente novamente.\n");
                    }
                } while (!id_existe); // Repete até encontrar um ID válido

                char novo_nome[50], novo_cpf[50], novo_rg[50], nova_data_nasc[50], novo_usuario[50], nova_senha[50];

                printf("Digite o novo nome do(a) funcionário(a) (ou pressione Enter para manter o atual): ");
                fgets(novo_nome, sizeof(novo_nome), stdin);
                novo_nome[strcspn(novo_nome, "\n")] = 0;

                printf("Digite o novo CPF do(a) funcionário(a) (ou pressione Enter para manter o atual): ");
                fgets(novo_cpf, sizeof(novo_cpf), stdin);
                novo_cpf[strcspn(novo_cpf, "\n")] = 0;

                printf("Digite o novo RG do(a) funcionário(a) (ou pressione Enter para manter o atual): ");
                fgets(novo_rg, sizeof(novo_rg), stdin);
                novo_rg[strcspn(novo_rg, "\n")] = 0;

                printf("Digite a nova data de nascimento do(a) funcionário(a) (ou pressione Enter para manter a atual): ");
                fgets(nova_data_nasc, sizeof(nova_data_nasc), stdin);
                nova_data_nasc[strcspn(nova_data_nasc, "\n")] = 0;

                printf("Digite o novo nome de usuário do(a) funcionário(a) (ou pressione Enter para manter o atual): ");
                fgets(novo_usuario, sizeof(novo_usuario), stdin);
                novo_usuario[strcspn(novo_usuario, "\n")] = 0;

                printf("Digite a nova senha do(a) funcionário(a) (ou pressione Enter para manter a atual): ");
                fgets(nova_senha, sizeof(nova_senha), stdin);
                nova_senha[strcspn(nova_senha, "\n")] = 0;

                snprintf(command, sizeof(command),
                        "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" editar funcionário \"%i\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"",
                        id_funcionario, novo_nome, novo_cpf, novo_rg, nova_data_nasc, novo_usuario, nova_senha);
                system(command);

            } else if (opcao == 2) {
                int id_funcionario;
                char confirmacao[50];
                int id_existe = 0;

                // Loop para garantir que o usuário insira um ID válido
                do {
                    printf("\nDigite o ID do(a) funcionário(a) conforme a tabela acima: ");
                    scanf("%i", &id_funcionario);
                    while (getchar() != '\n'); // Limpa o buffer

                    // Verifica se o ID inserido existe na lista de IDs
                    id_existe = 0;
                    for (int i = 0; i < count; i++) {
                        if (ids[i] == id_funcionario) {
                            id_existe = 1;
                            break;
                        }
                    }

                    if (!id_existe) {
                        printf("ID inválido! O ID inserido não existe. Tente novamente.\n");
                    }
                } while (!id_existe); // Repete até encontrar um ID válido

                printf("Tem certeza que deseja exclui-lo(a)? (Digite 'Sim' ou 'Não'): ");
                fgets(confirmacao, sizeof(confirmacao), stdin);
                confirmacao[strcspn(confirmacao, "\n")] = 0;

                while (strcmp(confirmacao, "Sim") != 0 && strcmp(confirmacao, "Não") != 0) {
                    printf("Opção inválida! Digite 'Sim' ou 'Não': ");
                    fgets(confirmacao, sizeof(confirmacao), stdin);
                    confirmacao[strcspn(confirmacao, "\n")] = 0;
                }

                if (strcmp(confirmacao, "Sim") == 0) {
                    snprintf(command, sizeof(command),
                            "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" excluir funcionário \"%i\"",
                            id_funcionario);
                    system(command);
                } else {
                    return Busca();
                }
            } else if (opcao == 3) {
                return Busca();
            }
        } else {
            printf("\nVocê não tem permissão para acessar essa funcionalidade!\n");
            printf("\nVoltando para o menu de busca, aguarde...");
            sleep(2);
            Busca();
        }
    } if (escolha == 2) {
        if (user_type != 4) {
            char nome[50];
            int opcao = 0;

            printf("\nDigite o nome do(a) cliente(a) para buscar (ou digite 'Todos' para visualizar todos os(as) clientes(as)): ");
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = 0;

            char command[512];
            snprintf(command, sizeof(command),
                    "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" buscar cliente \"%s\"", nome);

            FILE *fp;
            char output[1035];
            int ids[100]; // Armazena IDs para validação posterior
            int count = 0;

            // Usar popen para capturar a saída do comando Python
            fp = popen(command, "r");
            if (fp == NULL) {
                printf("Falha ao executar o comando.\n");
                exit(1);
            }

            printf("\nTabela de Clientes:\n");
            while (fgets(output, sizeof(output), fp) != NULL) {
                printf("%s", output);
                if (sscanf(output, "%d", &ids[count]) == 1) {
                    count++;
                }
            }

            if (count == 0) {
                printf("Nenhum cliente encontrado.\n");
                pclose(fp);
                sleep(2);
                Busca();  // Voltar ao menu de busca
                return;
            }

            pclose(fp);

            printf("\n1 - Editar cliente(a)\n");
            printf("2 - Excluir cliente(a)\n");
            printf("3 - Voltar\n\n");
            printf("Digite uma das opcoes para prosseguir: ");
            scanf("%i", &opcao);

            while (opcao < 1 || opcao > 3) {
                printf("Opção inválida! Digite uma opção válida: ");
                scanf("%i", &opcao);
            }

            // Limpa o buffer do teclado
            while (getchar() != '\n');

            if (opcao == 1) {
                char novo_nome[50], novo_cpf[50], novo_rg[50], nova_data_nasc[50];
                int id_cliente;

                int id_existe = 0;

                // Loop para garantir que o usuário insira um ID válido
                do {
                    printf("\nDigite o ID do(a) cliente conforme a tabela acima: ");
                    scanf("%i", &id_cliente);
                    while (getchar() != '\n'); // Limpa o buffer

                    // Verifica se o ID inserido existe na lista de IDs
                    id_existe = 0;
                    for (int i = 0; i < count; i++) {
                        if (ids[i] == id_cliente) {
                            id_existe = 1;
                            break;
                        }
                    }

                    if (!id_existe) {
                        printf("O ID inserido não existe! Tente novamente.\n");
                    }
                } while (!id_existe); // Repete até encontrar um ID válido

                printf("Digite o novo nome do(a) cliente (ou pressione Enter para manter o atual): ");
                fgets(novo_nome, sizeof(novo_nome), stdin);
                novo_nome[strcspn(novo_nome, "\n")] = 0;

                printf("Digite o novo CPF do(a) cliente (ou pressione Enter para manter o atual): ");
                fgets(novo_cpf, sizeof(novo_cpf), stdin);
                novo_cpf[strcspn(novo_cpf, "\n")] = 0;

                printf("Digite o novo RG do(a) cliente (ou pressione Enter para manter o atual): ");
                fgets(novo_rg, sizeof(novo_rg), stdin);
                novo_rg[strcspn(novo_rg, "\n")] = 0;

                printf("Digite a nova data de nascimento do(a) cliente (ou pressione Enter para manter o atual): ");
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

                // Verifica se o ID inserido existe na lista de IDs
                int id_existe = 0;
                for (int i = 0; i < count; i++) {
                    if (ids[i] == id_cliente) {
                        id_existe = 1;
                        break;
                    }
                }

                if (!id_existe) {
                    printf("ID inválido! O ID inserido não existe.\n");
                    return;
                }

                printf("Tem certeza que deseja excluí-lo(a)? (Digite 'Sim' ou 'Não'): ");
                fgets(confirmacao, sizeof(confirmacao), stdin);
                confirmacao[strcspn(confirmacao, "\n")] = 0;

                while (strcmp(confirmacao, "Sim") != 0 && strcmp(confirmacao, "Não") != 0) {
                    printf("Opção inválida! Digite 'Sim' ou 'Não': ");
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
        } else {
            printf("\nVocê não tem permissão para acessar essa funcionalidade!\n");
            printf("\nVoltando para o menu de busca, aguarde...");
            sleep(2);
            Busca();
        }
    } else if (escolha == 3) {
        char nome[50];
        int opcao = 0;

        printf("\nDigite o nome do produto para buscar (ou digite 'Todos' para visualizar todos os produtos): ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = 0; // Remove a quebra de linha

        // Monta o comando para executar o script Python
        char command[512];
        snprintf(command, sizeof(command),
            "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" \"%s\"", nome);

        // Abre o pipe para capturar a saída do comando Python
        FILE *fp = popen(command, "r");
        if (fp == NULL) {
            printf("Falha ao executar o comando.\n");
            exit(1);
        }

        // Lê a saída do comando e armazena os IDs
        int ids_validos[MAX_IDS];
        int num_ids = 0;
        char output[MAX_OUTPUT];

        printf("\nTabela de Produtos:\n");
        while (fgets(output, sizeof(output), fp) != NULL) {
            // Imprime cada linha da saída para que o usuário veja os produtos
            printf("%s", output);

            // Extrai o ID de cada linha (assumindo que o ID é o primeiro valor numérico)
            int id_temp;
            if (sscanf(output, "%d", &id_temp) == 1) {
                ids_validos[num_ids] = id_temp;
                num_ids++;
                if (num_ids >= MAX_IDS) {
                    break; // Evita exceder o limite de armazenamento
                }
            }
        }
        pclose(fp);

        // Verifica se algum ID foi lido
        if (num_ids == 0) {
            printf("Nenhum produto foi encontrado.\n");
            sleep(2);
            Busca(); // Retorna para a função Busca se não houver produtos
            return;
        }

        // Exibe as opções para o usuário
        printf("\n1 - Editar produto \n");
        printf("2 - Excluir produto \n");
        printf("3 - Voltar\n\n");
        printf("Digite uma das opções para prosseguir: ");
        scanf("%i", &opcao);

        while (opcao < 1 || opcao > 3) {
            printf("Opção inválida! Digite uma opção válida: ");
            scanf("%i", &opcao);
        }

        // Limpa o buffer do teclado
        while (getchar() != '\n');

        if (opcao == 1) {
            int id_produto;
            bool id_valido = false;

            // Solicita o ID do usuário e válida se ele existe na lista de IDs válidos
            do {
                printf("\nDigite o ID do produto conforme a tabela acima: ");
                scanf("%i", &id_produto);
                while (getchar() != '\n'); // Limpa o buffer de entrada

                for (int i = 0; i < num_ids; i++) {
                    if (id_produto == ids_validos[i]) {
                        id_valido = true;
                        break;
                    }
                }

                if (!id_valido) {
                    printf("ID inválido. Por favor, digite um ID que exista na tabela.\n");
                }
            } while (!id_valido);

            // Solicita o novo nome do produto
            char novo_nome[50] = "", novo_tipo[50] = "", entrada[50];
            float novo_preco = -1.0, nova_quantidade = -1.0;

            printf("Digite o novo nome do produto (ou pressione Enter para manter o atual): ");
            fgets(novo_nome, sizeof(novo_nome), stdin);
            novo_nome[strcspn(novo_nome, "\n")] = 0;

            // Solicita o novo preço do produto
            while (1) {
                printf("Digite o novo preço do produto (ou pressione Enter para manter o atual): ");
                if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
                    entrada[strcspn(entrada, "\n")] = 0;

                    if (strlen(entrada) == 0) {
                        break; // Mantém o preço atual
                    }

                    if (sscanf(entrada, "%f", &novo_preco) == 1) {
                        break;
                    } else {
                        printf("Entrada inválida. Digite apenas números.\n");
                    }
                }
            }

            // Solicita a nova quantidade do produto
            while (1) {
                printf("Digite a nova quantidade do produto (ou pressione Enter para manter o atual): ");
                if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
                    entrada[strcspn(entrada, "\n")] = 0;

                    if (strlen(entrada) == 0) {
                        break; // Mantém a quantidade atual
                    }

                    if (sscanf(entrada, "%f", &nova_quantidade) == 1) {
                        break;
                    } else {
                        printf("Entrada inválida. Digite apenas números.\n");
                    }
                }
            }

            // Solicita o novo tipo do produto
            printf("Digite o novo tipo do produto (Granel ou Peso): ");
            fgets(novo_tipo, sizeof(novo_tipo), stdin);
            novo_tipo[strcspn(novo_tipo, "\n")] = 0;

            while (1) {
                if (strcmp(novo_tipo, "Granel") != 0 && strcmp(novo_tipo, "Peso") != 0 && strlen(novo_tipo) > 0) {
                    printf("Opção inválida! Digite uma opção válida (Granel ou Peso): ");
                    fgets(novo_tipo, sizeof(novo_tipo), stdin);
                    novo_tipo[strcspn(novo_tipo, "\n")] = 0;
                } else {
                    break;
                }
            }

            // Monta o comando para chamar o Python
            snprintf(command, sizeof(command),
                    "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" \"%i\" \"%s\" \"%.2f\" \"%.2f\" \"%s\" \"editar produto\"",
                    id_produto, 
                    (strlen(novo_nome) > 0 ? novo_nome : "Atual"),
                    novo_preco, nova_quantidade, (strlen(novo_tipo) > 0 ? novo_tipo : "Atual"));
            system(command);
        } else if (opcao == 2) {
            int id_produto;
            char confirmacao[50];

            printf("\nDigite o ID do produto conforme a tabela acima: ");
            scanf("%i", &id_produto);
            while (getchar() != '\n'); // Limpa o buffer

            printf("Tem certeza que deseja excluí-lo? (Digite 'Sim' ou 'Não'): ");
            fgets(confirmacao, sizeof(confirmacao), stdin);
            confirmacao[strcspn(confirmacao, "\n")] = 0;

            while (strcmp(confirmacao, "Sim") != 0 && strcmp(confirmacao, "Não") != 0) {
                printf("Opção inválida! Digite 'Sim' ou 'Não': ");
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
    } else if (escolha == 4){
        menu();
    } else if (escolha == 9){
        printf("Encerrando o sistema...\n");
        sleep(3);
        exit(0);
    }
}

/**
 * Exibe um menu para o usuário realizar a pesagem de um produto, cancelar a operação ou encerrar o sistema.
 *
 * int Retorna 0 se a operação for concluída com sucesso, e não retorna em caso de encerramento do sistema.
 *
 * A função `Pesagem()` apresenta ao usuário um menu com as seguintes opções:
 * - 1: Pesar produto
 * - 2: Cancelar operação e retornar ao menu principal
 * - 9: Encerrar o sistema
 *
 * A função utiliza um loop para garantir que a entrada do usuário seja válida, permitindo apenas as opções 1, 2 ou 9.
 * Caso uma entrada inválida seja fornecida, a função solicita uma nova entrada até que uma opção válida seja escolhida.
 *
 * Quando o usuário escolhe a opção 1 (Pesar produto), a função:
 * - Executa um script Python (`excel_utils.py`) para manipular dados relacionados ao produto.
 * - Verifica se houve erros durante a execução do script.
 * - Solicita ao usuário que insira o preço e a quantidade em gramas (peso) do produto.
 * - Calcula o valor total com base no preço.
 * - Exibe o valor total a ser pago pelo produto.
 *
 * Se o usuário selecionar a opção 2 (Cancelar operação), a função retorna ao menu principal chamando a função `menu()`.
 * Se a opção 9 (Encerrar o sistema) for escolhida, a função exibe uma mensagem de encerramento e finaliza o programa.
 *
 * A função faz uso das seguintes bibliotecas padrão:
 * - `stdio.h` para entrada e saída padrão.
 * - `stdlib.h` para controle de processos e uso do comando `system()`.
 * - `string.h` para manipulação de strings.
 *
 * A função assume que o script Python está localizado em um diretório específico do sistema de arquivos,
 * e que ele é capaz de manipular corretamente os dados relacionados ao produto. Também é esperado que
 * o script Python retorne mensagens adequadas para indicar se o produto foi encontrado ou não.
 */

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
    printf("\nDigite o número da opção desejada: ");

    while (1) {
        if (scanf("%d", &escolha) == 1) {  // Verifica se a entrada é um número
            if ((escolha >= 1 && escolha <= 2) || escolha == 9) {
                break;  // Saída do loop se a escolha for válida
            }
            printf("Opção inválida! Digite uma opção válida: ");
        } else {
            printf("Opção inválida! Digite uma opção válida: ");
            while (getchar() != '\n');  // Limpa o buffer de entrada
        }
    }

    // Limpa o buffer do teclado após uma entrada válida
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

        if (strstr(output, "Nenhum") != NULL) {
            // Se houver uma mensagem de erro, retorne para a tela de cadastro
            pclose(fp);
            sleep(2);
            Busca();  // Voltar ao menu de cadastro
            return 0;
        } else {
            float peso, preco;

            printf("\n\n(OS PRECOS PARA OS PRODUTOS POR PESO NA TABELA SAO POR KG)\n");

            while (1) {
                printf("\nDigite o preço do produto conforme a tabela acima: ");
                if (scanf("%f", &preco) == 1) {
                    break;  // Se a entrada for válida, sai do loop
                } else {
                    printf("Entrada inválida.\n");
                    while (getchar() != '\n');  // Limpa o buffer de entrada
                }
            }

            while (1) {
                printf("\nDigite a quantidade do peso que deseja: ");
                if (scanf("%f", &peso) == 1) {
                    break;  // Se a entrada for válida, sai do loop
                } else {
                    printf("Entrada inválida.\n");
                    while (getchar() != '\n');  // Limpa o buffer de entrada
                }
            }

            float total = preco * peso;

            printf("O valor total é de : %.2f reais", total);

            while (1) {
                printf("\n\nDeseja fazer outra pesagem? (1 - Sim, 2 - Não): ");
                if (scanf("%d", &opcao) == 1) {
                    break;  // Se a entrada for válida, sai do loop
                } else {
                    printf("Entrada inválida.\n");
                    while (getchar() != '\n');  // Limpa o buffer de entrada
                }
            }

            if (opcao == 1){
                Pesagem();
            } else {
                menu();
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

struct Produto {
    int id;
    char nome[MAX_NOME];
    float quantidade;  // Adicionada a quantidade
    float precoPorKg;
    char tipoVenda[MAX_NOME]; // Adicionado tipo de venda
};

/**
 * Processa a saída de um script Python e popula um array de estruturas `Produto` com as informações extraídas.
 *
 * A saída gerada pelo script Python, que deve ser uma string contendo várias linhas de dados dos produtos.
 * Um array de estruturas `Produto` onde os dados extraídos serão armazenados.
 * Um ponteiro para um inteiro que será atualizado com o número total de produtos processados.
 *
 * Esta função processa a saída do script Python, onde cada linha da saída contém informações sobre um produto.
 * As informações são extraídas e armazenadas em um array de estruturas `Produto`, que inclui os seguintes campos:
 * - `id`: Identificador numérico do produto.
 * - `nome`: Nome do produto.
 * - `quantidade`: Quantidade disponível ou comprada.
 * - `precoPorKg`: Preço do produto por quilograma.
 * - `tipoVenda`: Tipo de venda (por unidade, por peso, etc.).
 *
 * O processo é realizado da seguinte forma:
 * 1. A função inicializa o contador de `totalProdutos` para 0.
 * 2. Utiliza `strtok` para dividir a saída do script Python em linhas.
 * 3. Para cada linha, a função tenta extrair os campos `id`, `nome`, `quantidade`, `precoPorKg` e `tipoVenda` usando `sscanf`.
 * 4. Se a linha contém os campos necessários, os dados são copiados para a estrutura `Produto` correspondente no array.
 * 5. O contador de `totalProdutos` é incrementado para refletir o número de produtos processados.
 * 6. O processo continua até que todas as linhas sejam processadas ou o limite de `MAX_PRODUTOS` seja atingido.
 *
 * É importante garantir que a saída do script Python siga o formato esperado para que os dados sejam corretamente extraídos.
 *       O limite de produtos processados é definido por `MAX_PRODUTOS`, e os tamanhos de strings são limitados por `MAX_NOME`.
 *
 * Se a saída do script Python estiver em um formato inesperado ou corrompido, a função pode não processar corretamente os produtos.
 */

void processar_saida_python(const char *saida, struct Produto produtos[], int *totalProdutos) {
    *totalProdutos = 0;

    char linha[256];
    char *linha_ptr = strtok((char *)saida, "\n");

    while (linha_ptr != NULL && *totalProdutos < MAX_PRODUTOS) {
        int id;
        char nome[MAX_NOME];
        float quantidade;  // Alterado para float
        float preco;
        char tipoVenda[MAX_NOME];

        int camposLidos = sscanf(linha_ptr, "%d %49s %f %f %49s", &id, nome, &quantidade, &preco, tipoVenda);

        if (camposLidos >= 5) {
            produtos[*totalProdutos].id = id;
            strncpy(produtos[*totalProdutos].nome, nome, MAX_NOME);
            produtos[*totalProdutos].quantidade = quantidade;
            produtos[*totalProdutos].precoPorKg = preco;
            strncpy(produtos[*totalProdutos].tipoVenda, tipoVenda, MAX_NOME);
            (*totalProdutos)++;
        }

        linha_ptr = strtok(NULL, "\n");
    }
}

/**
 * Executa um script Python para obter dados de produtos, processa a saída e popula um array de estruturas `Produto`.
 *
 * Um array de estruturas `Produto` onde os dados extraídos serão armazenados.
 * Um ponteiro para um inteiro que será atualizado com o número total de produtos processados.
 *
 * Esta função realiza as seguintes etapas:
 * 1. Constrói o comando para executar um script Python (`excel_utils.py`) localizado em um caminho específico.
 * 2. Executa o comando usando `_popen`, o que cria um processo filho para rodar o script Python e redireciona a saída do script para um pipe.
 * 3. Lê a saída do script Python através do pipe, armazenando os dados em um buffer (`output`).
 * 4. Fecha o pipe usando `_pclose`.
 * 5. Adiciona um terminador nulo ao final da string de saída para garantir que seja uma string C válida.
 * 6. Chama a função `processar_saida_python` para processar a saída do script e preencher o array `produtos` com as informações extraídas.
 *
 * O script Python deve estar localizado no caminho especificado e deve ser capaz de ser executado corretamente através do comando de sistema.
 * O buffer `output` deve ser grande o suficiente para conter toda a saída do script Python. A constante `BUFFER_SIZE` deve ser definida
 * adequadamente para acomodar a saída esperada.
 *
 * Se ocorrer um erro ao tentar executar o comando ou ao ler a saída, a função exibirá uma mensagem de erro usando `perror`
 * e retornará sem processar nenhum produto.
 *
 */

void ProcessarProdutos(struct Produto produtos[], int *totalProdutos) {
    char command[512];
    char output[BUFFER_SIZE];
    FILE *fp;

    snprintf(command, sizeof(command),
        "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" \"Todos\"");

    // Executa o comando e redireciona a saída para um pipe
    fp = _popen(command, "r");
    if (fp == NULL) {
        perror("popen");
        return;
    }

    // Lê a saída do comando
    size_t bytesRead = fread(output, sizeof(char), sizeof(output) - 1, fp);
    _pclose(fp);

    // Adiciona um terminador nulo à string
    output[bytesRead] = '\0';

    // Processa a saída
    processar_saida_python(output, produtos, totalProdutos);
}

// Função para limpar a tela (compatível com Windows e Unix)
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função para preencher espaços para alinhamento à direita
void preencherEspacos(int textoLength) {
    int espacos = LARGURA_LINHA - 2 - textoLength; // Subtraindo 2 por conta das bordas laterais "| "
    for (int i = 0; i < espacos; i++) {
        printf(" ");
    }
}

// Função para buscar um produto pelo ID
struct Produto* buscarProduto(struct Produto produtos[], int totalProdutos, int id) {
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].id == id) {
            return &produtos[i];  // Retorna o endereço do produto
        }
    }
    return NULL;  // Retorna NULL se não encontrar
}

// Função para exibir todos os produtos carregados
void exibirProdutos(struct Produto produtos[], int totalProdutos) {
    printf("\nPRODUTOS:");
    for (int i = 0; i < totalProdutos; i++) {
        printf("\nID: %-4d Nome: %-20s R$ %-5.2f Tipo de Venda: %-10s",
            produtos[i].id,
            produtos[i].nome,
            produtos[i].precoPorKg,
            produtos[i].tipoVenda);
    }
}

/**
 * Gera uma nota fiscal para uma compra realizada, incluindo informações sobre o cliente, o vendedor,
 * os produtos vendidos, o total da compra e a forma de pagamento. A nota fiscal é registrada em um
 * arquivo de texto no formato "NomeCliente(dd-mm-yyyy_hh:mm).txt".
 *
 * Esta função realiza as seguintes etapas:
 * 1. Obtém a data e hora atuais para inclusão na nota fiscal.
 * 2. Gera um nome de arquivo baseado no nome do cliente e na data/hora da compra.
 * 3. Abre um arquivo para escrita, onde a nota fiscal será registrada.
 * 4. Escreve informações básicas no arquivo, incluindo:
 *    - Data e hora da compra
 *    - Nome do cliente
 *    - CPF do cliente, se fornecido
 *    - Nome do funcionário responsável pela venda
 *    - Forma de pagamento escolhida (cartão de crédito, cartão de débito, dinheiro ou PIX),
 *      incluindo o número de parcelas se for cartão de crédito.
 * 5. Registra detalhes dos produtos vendidos, incluindo nome, quantidade, preço unitário e subtotal.
 * 6. Calcula e registra o total da compra.
 * 7. Fecha o arquivo e verifica se houve erros durante o fechamento.
 *
 * A função assume que os arrays `itensVendidos` e `quantidadesVendidas` têm tamanho suficiente
 * para armazenar `numProdutos` elementos.
 */

void gerarNotaFiscal(const char *nomeCliente, const char *cpf, const char *nomeFuncionario, struct Produto itensVendidos[], float quantidadesVendidas[], int numProdutos, float totalCompra, int formaPagamento, int parcelas) {
    // Obter data e hora atuais
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Gerar o nome do arquivo no formato "NomeCliente(dd-mm-yyyy_hh:mm).txt"
    char nomeArquivo[200];
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%s_%02d-%02d-%d_%02d_%02d.txt",
             nomeCliente, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);

    // Abrir o arquivo para escrita
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de nota fiscal.\n");
        return;
    }

    // Escrever informações básicas no arquivo
    fprintf(arquivo, "========== NOTA FISCAL ==========\n");
    fprintf(arquivo, "Data da compra: %02d/%02d/%d %02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
    fprintf(arquivo, "Nome do(a) cliente: %s\n", nomeCliente);
    fprintf(arquivo, "CPF do(a) cliente: %s\n", cpf);
    fprintf(arquivo, "Nome do(a) funcionário(a): %s\n", nomeFuncionario);
    fprintf(arquivo, "Forma de Pagamento: ");

    switch (formaPagamento) {
        case 1:
            fprintf(arquivo, "Cartão de Crédito (%d parcelas)\n", parcelas);
            break;
        case 2:
            fprintf(arquivo, "Cartão de Débito\n");
            break;
        case 3:
            fprintf(arquivo, "Dinheiro\n");
            break;
        case 4:
            fprintf(arquivo, "PIX\n");
            break;
        default:
            fprintf(arquivo, "Forma de pagamento desconhecida\n");
    }

    fprintf(arquivo, "---------------------------------\n");

    // Escrever informações dos produtos
    for (int i = 0; i < numProdutos; i++) {
        if (itensVendidos[i].nome != NULL && quantidadesVendidas[i] > 0) {
            fprintf(arquivo, "Produto: %s\n", itensVendidos[i].nome);
            fprintf(arquivo, "Quantidade: %.2f kg\n", quantidadesVendidas[i]);
            fprintf(arquivo, "Preço unitário: R$ %.2f\n", itensVendidos[i].precoPorKg);
            fprintf(arquivo, "Subtotal: R$ %.2f\n", itensVendidos[i].precoPorKg * quantidadesVendidas[i]);
            fprintf(arquivo, "---------------------------------\n");
        }
    }

    // Escrever total da compra
    fprintf(arquivo, "TOTAL DA COMPRA: R$ %.2f\n", totalCompra);
    fprintf(arquivo, "=================================\n");

    // Fechar o arquivo e verificar erros
    if (fclose(arquivo) == EOF) {
        printf("Erro ao fechar o arquivo.\n");
    } else {
        printf("\nNota fiscal gerada com sucesso: %s\n", nomeArquivo);
    }
}

/**
 * Gerencia o processo de pagamento de uma compra, incluindo a solicitação de CPF na nota, escolha da forma de pagamento,
 * verificação de parcelamento e confirmação de pagamento. Em seguida, registra a compra se o pagamento for bem-sucedido.
 *
 * Esta função realiza as seguintes etapas:
 * 1. Pergunta ao usuário se deseja incluir CPF na nota e, se sim, solicita o CPF do cliente se não fornecido.
 * 2. Apresenta as opções de formas de pagamento (cartão de crédito, cartão de débito, dinheiro, PIX).
 * 3. Caso o pagamento seja com cartão de crédito, verifica se o cliente deseja parcelar a compra e pergunta o número de parcelas (até 3x).
 * 4. Pede confirmação se o pagamento foi realizado com sucesso.
 * 5. Se o pagamento for confirmado, chama a função `salvarCompra` para registrar os detalhes da compra.
 * 6. Caso o pagamento não seja confirmado, exibe uma mensagem indicando que o pagamento não foi realizado.
 *
 * A função contém laços para validação de entradas, garantindo que o usuário insira opções válidas (por exemplo, 'Sim' ou 'Não', número de parcelas, etc.).
 *
 * A função assume que os arrays `itensVendidos` e `quantidadesVendidas` têm tamanho suficiente para armazenar `numProdutos` elementos.
 * Também assume que a função `Caixa()` existe e é responsável por retornar ao menu principal ou encerrar a operação.
 */

void Pagamento(const char* nome, const char* cpf, int idCompra, const char *nomeVendedor, struct Produto itensVendidos[], float quantidadesVendidas[], int numProdutos, float totalCompra) {

    int opcaoPag, qtdParcela;
    char opcaoCPF[50], opcaoParcela[50], confirmacao[50], CPFcliente[12]; // Inicializa com o CPF passado

    strcpy(CPFcliente, cpf);

    while (getchar() != '\n');

    printf("Deseja CPF na nota? (Digite 'Sim' ou 'Não'): ");
    fgets(opcaoCPF, sizeof(opcaoCPF), stdin);
    opcaoCPF[strcspn(opcaoCPF, "\n")] = 0;

    while (strcmp(opcaoCPF, "Sim") != 0 && strcmp(opcaoCPF, "Não") != 0) {
        printf("Opção inválida! Digite 'Sim' ou 'Não': ");
        fgets(opcaoCPF, sizeof(opcaoCPF), stdin);
        opcaoCPF[strcspn(opcaoCPF, "\n")] = 0;
    }

    if (strcmp(opcaoCPF, "Sim") == 0) {
        if (cpf != 0) {
            printf("CPF do(a) cliente: %s\n", cpf);
        } else {
            printf("Digite o CPF usando apenas números: ");
            fgets(CPFcliente, sizeof(CPFcliente), stdin);
            CPFcliente[strcspn(CPFcliente, "\n")] = 0;
            printf("CPF do(a) cliente: %s\n", CPFcliente);
        }
    }

    printf("\n1 - Cartão de crédito\n2 - Cartão de débito\n3 - Dinheiro\n4 - PIX\n\n");
    printf("Escolha uma das formas de pagamento acima: ");
    scanf("%i", &opcaoPag);

    while (opcaoPag < 1 || opcaoPag > 4) {
        printf("Opção inválida! Digite uma opção válida: ");
        scanf("%i", &opcaoPag);
    }

    while (getchar() != '\n');

    if (opcaoPag == 1) {
        printf("Deseja parcelar em ate 3x sem juros? (Responda com 'Sim' ou 'Não'): ");
        fgets(opcaoParcela, sizeof(opcaoParcela), stdin);
        opcaoParcela[strcspn(opcaoParcela, "\n")] = 0;

        while (strcmp(opcaoParcela, "Sim") != 0 && strcmp(opcaoParcela, "Não") != 0) {
            printf("Opção inválida! Digite 'Sim' ou 'Não': ");
            fgets(opcaoParcela, sizeof(opcaoParcela), stdin);
            opcaoParcela[strcspn(opcaoParcela, "\n")] = 0;
        }

        if (strcmp(opcaoParcela, "Sim") == 0) {
            printf("Quer parcelar em quantas vezes? (ate 3x sem juros): ");
            scanf("%i", &qtdParcela);

            while (qtdParcela < 2 || qtdParcela > 3) {
                printf("Opção inválida! Digite um número de parcelas valido (2 ou 3): ");
                scanf("%i", &qtdParcela);
            }
        } else {
            qtdParcela = 1;
        }
    } else {
        qtdParcela = 1;
    }

    printf("O pagamento foi realizado com sucesso? (Responda com 'Sim' ou 'Não'): ");
    fgets(confirmacao, sizeof(confirmacao), stdin);
    confirmacao[strcspn(confirmacao, "\n")] = 0;

    while (strcmp(confirmacao, "Sim") != 0 && strcmp(confirmacao, "Não") != 0) {
        printf("Opção inválida! Digite 'Sim' ou 'Não': ");
        fgets(confirmacao, sizeof(confirmacao), stdin);
        confirmacao[strcspn(confirmacao, "\n")] = 0;
    }

    if (strcmp(confirmacao, "Sim") == 0) {
        gerarNotaFiscal(nome, CPFcliente, nomeVendedor, itensVendidos, quantidadesVendidas, numProdutos, totalCompra, opcaoPag, qtdParcela);

        // Atualizar estoque
        for (int i = 0; i < numProdutos; i++) {
            if (quantidadesVendidas[i] > 0) {
                char command[512];
                snprintf(command, sizeof(command),
                    "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" \"atualizar_estoque\" \"%s\" %.2f",
                    itensVendidos[i].nome, quantidadesVendidas[i]);  // Passando a quantidade como float

                // Executa o comando Python para atualizar o estoque
                system(command);
            }
        }
    } else {
        printf("Pagamento não realizado.\n");
    }

    printf("Finalizando a operacao...\n");
    sleep(3);
    Caixa();
}

/**
 * Gerencia o processo de venda em um terminal de caixa, permitindo a seleção de produtos, cálculo do total da compra,
 * aplicação de descontos e, ao final, chama a função de pagamento.
 *
 *
 * Esta função realiza as seguintes operações:
 * 1. Exibe uma interface de terminal para que o operador selecione os produtos e insira as quantidades compradas.
 * 2. Calcula o total da compra com base nos produtos selecionados e quantidades inseridas.
 * 3. Aplica um desconto de 10% se o nome do cliente for fornecido.
 * 4. Permite que o operador finalize a compra ao inserir um ID de produto 0.
 * 5. Chama a função `Pagamento` para processar o pagamento da compra.
 *
 * A função usa laços e validações para garantir que o usuário insira valores válidos (por exemplo, quantidade de produtos, ID do produto).
 *
 * Esta função assume que o array `itensVendidos` e `quantidadesVendidas` podem armazenar até 100 itens.
 * Caso o número de itens vendidos possa exceder esse valor, é necessário ajustar os arrays para evitar estouro de memória.
 */

void caixaTerminal(struct Produto produtos[], int totalProdutos, int cpf, char nome[50], int id) {
    int idProduto;
    float quantidade;
    float totalCompra = 0, desconto;
    int numProdutos = 0;
    struct Produto itensVendidos[100];
    float quantidadesVendidas[100];
    char novoCPF[50];

    snprintf(novoCPF, sizeof(novoCPF), "%d", cpf);

    while (1) {
        limparTela();

        printf("|=============================|\n");
        printf("|            CAIXA            |\n");
        printf("|-----------------------------|\n");

        for (int i = 0; i < numProdutos; i++) {
            int len;

            len = snprintf(NULL, 0, "Produto: %s", itensVendidos[i].nome);
            printf("| Produto: %s", itensVendidos[i].nome);
            preencherEspacos(len);
            printf("|\n");

            len = snprintf(NULL, 0, "Quantidade: %.2f", quantidadesVendidas[i]);
            printf("| Quantidade: %.2f", quantidadesVendidas[i]);
            preencherEspacos(len);
            printf("|\n");

            len = snprintf(NULL, 0, "Subtotal: R$ %.2f", itensVendidos[i].precoPorKg * quantidadesVendidas[i]);
            printf("| Subtotal: R$ %.2f", itensVendidos[i].precoPorKg * quantidadesVendidas[i]);
            preencherEspacos(len);
            printf("|\n");
            printf("|-----------------------------|\n");
        }

        int lenTotalItens = snprintf(NULL, 0, "Total de itens: %d", numProdutos);
        printf("| Total de itens: %d", numProdutos);
        preencherEspacos(lenTotalItens);
        printf("|\n");

        int lenTotalCompra = snprintf(NULL, 0, "Total da compra: R$ %.2f", totalCompra);
        printf("| Total da compra: R$ %.2f", totalCompra);
        preencherEspacos(lenTotalCompra);
        printf("|\n");
        printf("|=============================|\n");

        if (strcmp(nome, "") != 0) {
            printf("Nome do(a) cliente: %s\n", nome);
            printf("(Esta compra esta tendo um desconto de 10 por centro no valor total)\n");
        }

        printf("Nome do(a) funcionário(a): %s\n", user_name);

        exibirProdutos(produtos, totalProdutos);

        printf("\n\nDigite o ID do produto conforme a tabela acima(ou 0 para finalizar a compra): ");
        scanf("%d", &idProduto);

        if (idProduto == 0) {
            break;
        }

        struct Produto* produtoSelecionado = buscarProduto(produtos, totalProdutos, idProduto);

        if (produtoSelecionado != NULL) {
            printf("Digite a quantidade desejada de acordo com o tipo de venda: ");
            scanf("%f", &quantidade);

            if (quantidade > produtoSelecionado->quantidade) {
                printf("Quantidade selecionada e maior do que a disponivel (%.2f). Por favor, escolha uma quantidade menor ou igual a %.2f.\n", produtoSelecionado->quantidade, produtoSelecionado->quantidade);
                sleep(2);
            } else if (quantidade > 0) {
                totalCompra += produtoSelecionado->precoPorKg * quantidade;
                if (strcmp(nome, "") != 0) {
                    desconto = totalCompra * 0.10;
                    totalCompra = totalCompra - desconto;
                }
                itensVendidos[numProdutos] = *produtoSelecionado;
                quantidadesVendidas[numProdutos] = quantidade;
                numProdutos++;

                // Atualiza a quantidade disponível no estoque
                produtoSelecionado->quantidade -= quantidade;
            } else {
                printf("Quantidade inválida.\n");
                sleep(2);
            }
        } else {
            printf("Produto não encontrado.\n");
            sleep(2);
        }
    }

    printf("\nPagamento:\n");
    Pagamento(nome, novoCPF, id, user_name, itensVendidos, quantidadesVendidas, numProdutos, totalCompra);
}

typedef struct {
    int id;
    char nome[100];
    char cpf[12];
} Cliente;

/**
 * Função principal que gerencia a operação de um caixa de supermercado.
 *
 * Esta função exibe um menu com opções para continuar uma operação de caixa com ou sem um cliente,
 * cancelar a operação atual ou encerrar o sistema. Dependendo da escolha do operador, a função pode:
 * - Buscar informações de clientes de um arquivo ou banco de dados.
 * - Iniciar a função `caixaTerminal` para processar uma venda.
 * - Cancelar a operação atual.
 * - Encerrar o sistema.
 *
 * int Retorna 0 ao final da execução, ou 1 em caso de erro.
 *
 * A função segue os seguintes passos:
 * 1. Processa os produtos disponíveis na loja através da função `ProcessarProdutos`.
 * 2. Exibe um menu de opções ao operador.
 * 3. Lida com a escolha do operador, com validação para entradas inválidas.
 * 4. Dependendo da escolha, pode buscar um cliente em um arquivo/banco de dados utilizando um comando Python,
 *    e em seguida, passar as informações para a função `caixaTerminal`.
 */

int Caixa() {
    int escolha;
    struct Produto produtos[MAX_PRODUTOS];
    int totalProdutos = 0;

    // Processar produtos
    ProcessarProdutos(produtos, &totalProdutos);

    // Opções do menu
    system("cls");
    printf("|==============================|\n");
    printf("|            CAIXA             |\n");
    printf("|                              |\n");
    printf("| 1 - Continuar com cliente    |\n");
    printf("| 2 - Continuar sem cliente    |\n");
    printf("| 3 - Cancelar operacao        |\n");
    printf("| 9 - Encerrar o sistema       |\n");
    printf("|==============================|\n");
    printf("\nDigite a opção desejada: ");

    while (1) {
        if (scanf("%d", &escolha) != 1) {
            // Se não for um número, limpe o buffer de entrada
            while (getchar() != '\n');
            printf("Entrada inválida. Digite um número: ");
        } else if (escolha < 1 || escolha > 3 && escolha != 9) {
            printf("Opção inválida. Digite novamente: ");
        } else {
            break;
        }
    }

    char command[512], nome[50] = "";
    int cpf = 0, id = 0;

    if (escolha == 1) {
        snprintf(command, sizeof(command),
            "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" buscar cliente \"Todos\"");
        FILE *fp = popen(command, "r");
        if (fp == NULL) {
            printf("Falha ao executar o comando.\n");
            return 1;
        }

        char output[1035];
        while (fgets(output, sizeof(output), fp) != NULL) {
            if (strstr(output, "Nenhum") != NULL) {
                // Se houver uma mensagem de erro, retorne para a tela de cadastro
                pclose(fp);
                sleep(2);
                Busca();  // Voltar ao menu de cadastro
                return 1;
            } else {
                // Imprime a saída do comando python (lista de clientes)
                printf("%s", output);
            }
        }
        pclose(fp);

        int id_cliente;
        printf("\nDigite o ID do(a) cliente conforme a tabela acima: ");
        scanf("%i", &id_cliente);

        snprintf(command, sizeof(command),
                "python \"C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\excel_utils.py\" buscar cliente \"%i\"", id_cliente);

        fp = popen(command, "r");
        if (fp == NULL) {
            printf("Erro ao executar comando.\n");
            return 1;
        }

        Cliente cliente;
        char nome_completo[100];  // Buffer temporário para armazenar o nome completo

        while (fgets(output, sizeof(output), fp) != NULL) {
            // Captura o ID, o nome completo e o CPF
            // %d para o ID, %[^0-9] para capturar o nome até que encontre um número (início do CPF), %s para o CPF
            sscanf(output, "%d %99[^0-9] %s", &cliente.id, nome_completo, cliente.cpf);

            // Copia o nome completo para o campo 'nome' da estrutura Cliente, removendo espaços extras
            strncpy(cliente.nome, nome_completo, sizeof(cliente.nome) - 1);
            cliente.nome[sizeof(cliente.nome) - 1] = '\0';  // Certifica-se de que a string seja terminada corretamente

            // Chama a função com CPF como string
            caixaTerminal(produtos, totalProdutos, cliente.cpf, cliente.nome, cliente.id);
        }

    }else if(escolha == 2){
        // Continuar com ou sem cliente
        caixaTerminal(produtos, totalProdutos, cpf, nome, id);
    }else if(escolha == 3){
        // Cancelar operação
        printf("Operação cancelada.\n");
        sleep(1);
        menu();
    }else if(escolha == 3){
        // Encerrar o sistema
        printf("Sistema encerrado.\n");
        exit(0);
    }
    return 0;
}

/**
 * Gerencia as opções selecionadas no menu principal.
 *
 * Esta função redireciona o fluxo do programa para diferentes telas ou funcionalidades com base na opção escolhida pelo usuário.
 * Após selecionar uma opcao, a função exibirá uma mensagem de transição e aguardará por um curto período antes de chamar a função correspondente.
 *
 * Inteiro que representa a opção selecionada pelo usuário no menu principal.
 * As opções válidas são:
 * - 1: Tela de Cadastro
 * - 2: Tela de Busca
 * - 3: Tela de Pesagem
 * - 4: Tela de Caixa
 *
 * - Se a opção fornecida for 1, a função exibirá uma mensagem e chamará a função `Cadastro()`.
 * - Se a opção fornecida for 2, a função exibirá uma mensagem e chamará a função `Busca()`.
 * - Se a opção fornecida for 3, a função exibirá uma mensagem e chamará a função `Pesagem()`.
 * - Se a opção fornecida for 4, a função exibirá uma mensagem e chamará a função `Caixa()`.
 * - Se a opção fornecida não for válida, a função exibirá uma mensagem de erro.
 *
 * Após executar a função correspondente, a função `system("pause")` é chamada para pausar a execução e permitir que o usuário veja a mensagem exibida.
 *
 */

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
            printf("\nIndo para a tela de caixa, aguarde...");
            sleep(2);
            Caixa();
            break;
        default:
            printf("Opção inválida!\n");
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
    printf("|       Menu de operações:     |\n");
    printf("| 1 - Cadastro                 |\n");
    printf("| 2 - Busca                    |\n");
    printf("| 3 - Pesagem                  |\n");
    printf("| 4 - Caixa                    |\n");
    printf("| 9 - Encerrar o sistema       |\n");
    printf("|                              |\n");
    printf("|==============================|\n");
    printf("\nDigite o número da opção desejada: ");

    while (1) {
        if (scanf("%d", &escolha) == 1) {  // Verifica se a entrada é um número
            if (escolha < 6 || escolha == 9) {
                break;  // Saída do loop se a escolha for válida
            }
            printf("Opção inválida! Digite uma opção válida: ");
        } else {
            printf("Opção inválida! Digite uma opção válida: ");
            while (getchar() != '\n');  // Limpa o buffer de entrada
        }
    }
    if (escolha != 9) {
        GerenciaOpcoes(escolha);
        return escolha;
    } else {
        printf("Encerrando o sistema...\n");
        sleep(3);
        exit(0);
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
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
