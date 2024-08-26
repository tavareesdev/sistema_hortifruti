import pandas as pd
import sys
import openpyxl
import time

# Caminho para o arquivo da planilha
planilha_caminho = 'C:\\Users\\gtava\\OneDrive\\Documentos\\project\\output\\database.xlsx'

def ler_dados_planilha(sheet_name):
    try:
        df = pd.read_excel(planilha_caminho, sheet_name=sheet_name, dtype=str)
        return df
    except FileNotFoundError:
        print(f"Arquivo não encontrado: {planilha_caminho}")
        return None
    except Exception as e:
        print(f"Erro ao ler o arquivo: {e}")
        return None

def escrever_dados_planilha(df, sheet_name):
    try:
        with pd.ExcelWriter(planilha_caminho, engine='openpyxl', mode='a', if_sheet_exists='overlay') as writer:
            df.to_excel(writer, sheet_name=sheet_name, index=False)
    except Exception as e:
        print(f"Erro ao escrever no arquivo: {e}")


def gerar_id_unico(df):
    """Gera um novo ID único."""
    if df.empty or 'ID' not in df.columns:
        return 1
    else:
        ids_existentes = pd.to_numeric(df['ID'], errors='coerce').dropna().astype(int)
        if ids_existentes.empty:
            return 1
        else:
            return ids_existentes.max() + 1

def cadastrar_funcionario(nome, cpf, data_nascimento, rg, username, password, tipo):
    # Lê os dados atuais das planilhas
    df_funcionarios = ler_dados_planilha('Funcionarios')
    df_users = ler_dados_planilha('Users')

    if df_funcionarios is not None and df_users is not None:
        # Verifica se o CPF ou RG já existem na planilha 'Funcionarios'
        cpf_existente = df_funcionarios['CPF'].astype(str).str.contains(str(cpf)).any()
        rg_existente = df_funcionarios['RG'].astype(str).str.contains(str(rg)).any()

        # Verifica se o Username já existe na planilha 'Users'
        username_existente = df_users['Username'].astype(str).str.contains(str(username)).any()

        if cpf_existente:
            print("Erro: Já existe um funcionario cadastrado com este CPF. Voltando a tela de cadastro...")
            time.sleep(3)
        elif rg_existente:
            print("Erro: Já existe um funcionario cadastrado com este RG. Voltando a tela de cadastro...")
            time.sleep(3)
        elif username_existente:
            print("Erro: Já existe um usuario cadastrado com este Username. Voltando a tela de cadastro...")
            time.sleep(3)
        else:
            # Gera um novo ID único
            novo_id = gerar_id_unico(df_funcionarios)

            # Adiciona o novo funcionário à planilha 'Funcionarios'
            novo_funcionario = pd.DataFrame({
                'ID': [novo_id],
                'Nome': [nome],
                'CPF': [cpf],
                'Data de Nascimento': [data_nascimento],
                'RG': [rg]
            })
            df_funcionarios = pd.concat([df_funcionarios, novo_funcionario], ignore_index=True)

            # Adiciona o novo usuário à planilha 'Users'
            novo_usuario = pd.DataFrame({
                'ID': [novo_id],
                'Username': [username],
                'Password': [password],
                'Tipo': [tipo]
            })
            df_users = pd.concat([df_users, novo_usuario], ignore_index=True)

            # Escreve os dados de volta nas planilhas
            escrever_dados_planilha(df_funcionarios, 'Funcionarios')
            escrever_dados_planilha(df_users, 'Users')

            print("Cadastro realizado com sucesso!")
    else:
        print("Erro ao ler as planilhas.")

def cadastrar_cliente(nome, cpf, data_nascimento, rg):
    # Lê os dados atuais das planilhas
    df_cliente = ler_dados_planilha('Clientes')

    if df_cliente is not None:
        novo_id = gerar_id_unico(df_cliente)
        # Adiciona o novo funcionário à planilha 'cliente'
        novo_cliente = pd.DataFrame({
            'ID': [novo_id],
            'Nome': [nome],
            'CPF': [cpf],
            'Data de Nascimento': [data_nascimento],
            'RG': [rg]
        })
        df_cliente = pd.concat([df_cliente, novo_cliente], ignore_index=True)

        # Escreve os dados de volta nas planilhas
        escrever_dados_planilha(df_cliente, 'Clientes')

        print("Cadastro realizado com sucesso!")
    else:
        print("Erro ao ler as planilhas.")

def cadastrar_produto(nome, preco, qtd_produto):
    # Lê os dados atuais das planilhas
    df_produto = ler_dados_planilha('Produtos')

    # Gera um novo ID único
    novo_id = gerar_id_unico(df_produto)

    if df_produto is not None:
        try:
            # Converte o preço para float e arredonda para duas casas decimais
            preco_float = float(preco)  # Converte para float
            preco_arredondado = round(preco_float, 2)  # Arredonda para duas casas decimais
        except ValueError:
            print("Erro: O preço deve ser um número válido.")
            return
        
        # Adiciona o novo produto à planilha 'produto'
        novo_produto = pd.DataFrame({
            'ID': [novo_id],
            'Nome': [nome],
            'Preco': [preco_arredondado],
            'Quantidade': [qtd_produto]
        })
        df_produto = pd.concat([df_produto, novo_produto], ignore_index=True)

        # Escreve os dados de volta nas planilhas
        escrever_dados_planilha(df_produto, 'Produtos')

        print("Cadastro realizado com sucesso!")
    else:
        print("Erro ao ler as planilhas.")

def validar_login(username, password):
    df_users = ler_dados_planilha('Users')
    if df_users is not None:
        user_exists = df_users[(df_users['Username'] == username) & (df_users['Password'] == password)]
        if not user_exists.empty:
            print("Login bem-sucedido!")
            return True
        else:
            print("Usuario ou senha incorretos.")
            return False
    else:
        print("Erro ao ler a planilha de usuários.")
        return False
    
def buscar_produto(nome):
    df = ler_dados_planilha('Produtos')

    if nome != 'Todos':
        if not isinstance(nome, str):
            print("O nome do produto deve ser uma string.")
            return
        resultado = df[df['Nome'].str.contains(nome.strip(), case=False, na=False)]
    else:
        resultado = df

    if not resultado.empty:
        resultado = resultado.to_string(index=False)
        print("\n" + resultado + "\n")
    else:
        print("Nenhum produto encontrado.")

def editar_produto(novo_nome, novo_preco, nova_quantidade, id_produto):
    # Lê os dados atuais da planilha 'Produtos'
    df_produto = ler_dados_planilha('Produtos')
    print(id_produto)
    if df_produto is not None:
        # Localiza o produto pelo ID
        produto_idx = df_produto[df_produto['ID'] == id_produto].index

        if not produto_idx.empty:
            # Atualiza os campos se o usuário forneceu novos valores
            if novo_nome:
                df_produto.at[produto_idx[0], 'Nome'] = novo_nome
            if novo_preco:
                df_produto.at[produto_idx[0], 'Preco'] = round(float(novo_preco), 2)
            if nova_quantidade:
                df_produto.at[produto_idx[0], 'Quantidade'] = int(nova_quantidade)

            # Salva as alterações na planilha
            escrever_dados_planilha(df_produto, 'Produtos')

            print("Produto atualizado com sucesso!")
        else:
            print("Produto com o ID especificado não foi encontrado.")
    else:
        print("Erro ao ler a planilha.")

def excluir_produto(id_produto):
    # Carregar o arquivo Excel
    wb = openpyxl.load_workbook(planilha_caminho)
    
    # Selecionar a planilha "produtos"
    ws = wb['Produtos']
    
    # Percorrer as linhas da planilha a partir da segunda linha
    for row in ws.iter_rows(min_row=2):
        # Acessar o valor na primeira coluna (ID) e garantir que ambos são strings para comparação
        id_valor = str(row[0].value)
        id_produto_str = str(id_produto)
        
        # Verificar se o ID corresponde ao que queremos excluir
        if id_valor == id_produto_str:
            # Excluir a linha
            ws.delete_rows(row[0].row)
            break
    
    # Salvar o arquivo sem afetar outras planilhas
    wb.save(planilha_caminho)
    print(f"Produto foi excluido com sucesso.")

def buscar_funcionario(nome):
    df = ler_dados_planilha('Funcionarios')

    if nome != 'Todos':
        if not isinstance(nome, str):
            print("O nome do funcionario deve ser uma string.")
            return
        resultado = df[df['Nome'].str.contains(nome.strip(), case=False, na=False)]
    else:
        resultado = df

    if not resultado.empty:
        resultado = resultado.to_string(index=False)
        print("\n" + resultado + "\n")
    else:
        print("Nenhum funcionario encontrado.")

def editar_funcionario(novo_nome, novo_cpf, novo_rg, nova_data_nasc, novo_user, nova_senha, id_funcionario):
    # Lê os dados atuais da planilha 'funcionarios'
    df_funcionario = ler_dados_planilha('Funcionarios')

    if df_funcionario is not None:
        # Localiza o funcionario pelo ID
        funcionario_idx = df_funcionario[df_funcionario['ID'] == id_funcionario].index

        if not funcionario_idx.empty:
            # Atualiza os campos se o usuário forneceu novos valores
            if novo_nome:
                df_funcionario.at[funcionario_idx[0], 'Nome'] = novo_nome
            if novo_cpf:
                df_funcionario.at[funcionario_idx[0], 'CPF'] = novo_cpf
            if novo_rg:
                df_funcionario.at[funcionario_idx[0], 'RG'] = novo_rg
            if nova_data_nasc:
                df_funcionario.at[funcionario_idx[0], 'Data de Nascimento'] = nova_data_nasc

            # Salva as alterações na planilha
            escrever_dados_planilha(df_funcionario, 'Funcionarios')

            a =1
        else:
            print("Funcionario com o ID especificado não foi encontrado.")
    else:
        print("Erro ao ler a planilha.")

    df_funcionario = ler_dados_planilha('Users')

    if df_funcionario is not None:
        # Localiza o funcionario pelo ID
        funcionario_idx = df_funcionario[df_funcionario['ID'] == id_funcionario].index

        if not funcionario_idx.empty:
            # Atualiza os campos se o usuário forneceu novos valores
            if novo_user:
                df_funcionario.at[funcionario_idx[0], 'Username'] = novo_user
            if nova_senha:
                df_funcionario.at[funcionario_idx[0], 'Password'] = nova_senha

            # Salva as alterações na planilha
            escrever_dados_planilha(df_funcionario, 'Users')

            a =1 
        else:
            print("funcionario com o ID especificado não foi encontrado.")
    else:
        print("Erro ao ler a planilha.")

    if a == 1:
        print("Funcionario atualizado com sucesso!")

def excluir_funcionario(id_funcionario):
    # Carregar o arquivo Excel
    wb = openpyxl.load_workbook(planilha_caminho)
    
    # Selecionar a planilha "Funcionarios"
    ws = wb['Funcionarios']
    
    # Percorrer as linhas da planilha a partir da segunda linha
    for row in ws.iter_rows(min_row=2):
        # Acessar o valor na primeira coluna (ID) e garantir que ambos são strings para comparação
        id_valor = str(row[0].value)
        id_funcionario_str = str(id_funcionario)
        
        # Verificar se o ID corresponde ao que queremos excluir
        if id_valor == id_funcionario_str:
            # Excluir a linha
            ws.delete_rows(row[0].row)
            break
    
    # Salvar o arquivo sem afetar outras planilhas
    wb.save(planilha_caminho)

    # Selecionar a planilha "Funcionarios"
    ws = wb['Users']
    
    # Percorrer as linhas da planilha a partir da segunda linha
    for row in ws.iter_rows(min_row=2):
        # Acessar o valor na primeira coluna (ID) e garantir que ambos são strings para comparação
        id_valor = str(row[0].value)
        id_funcionario_str = str(id_funcionario)
        
        # Verificar se o ID corresponde ao que queremos excluir
        if id_valor == id_funcionario_str:
            # Excluir a linha
            ws.delete_rows(row[0].row)
            break
    
    # Salvar o arquivo sem afetar outras planilhas
    wb.save(planilha_caminho)
    print(f"Funcionario(a) foi excluido(a) com sucesso.")

def buscar_cliente(nome):
    df = ler_dados_planilha('Clientes')

    if nome != 'Todos':
        if not isinstance(nome, str):
            print("O nome do(a) cliente deve ser uma string.")
            return
        resultado = df[df['Nome'].str.contains(nome.strip(), case=False, na=False)]
    else:
        resultado = df

    if not resultado.empty:
        resultado = resultado.to_string(index=False)
        print("\n" + resultado + "\n")
    else:
        print("Nenhum cliente encontrado.")

def editar_cliente(novo_nome, novo_cpf, novo_rg, nova_data_nasc, id_cliente):
    # Lê os dados atuais da planilha 'clientes'
    df_cliente = ler_dados_planilha('Clientes')

    if df_cliente is not None:
        # Localiza o cliente pelo ID
        cliente_idx = df_cliente[df_cliente['ID'] == id_cliente].index

        if not cliente_idx.empty:
            # Atualiza os campos se o usuário forneceu novos valores
            if novo_nome:
                df_cliente.at[cliente_idx[0], 'Nome'] = novo_nome
            if novo_cpf:
                df_cliente.at[cliente_idx[0], 'CPF'] = novo_cpf
            if novo_rg:
                df_cliente.at[cliente_idx[0], 'RG'] = novo_rg
            if nova_data_nasc:
                df_cliente.at[cliente_idx[0], 'Data de Nascimento'] = nova_data_nasc

            # Salva as alterações na planilha
            escrever_dados_planilha(df_cliente, 'Clientes')

            a =1
        else:
            print("cliente com o ID especificado não foi encontrado.")
    else:
        print("Erro ao ler a planilha.")

    df_cliente = ler_dados_planilha('Users')

    print("Cliente atualizado com sucesso!")

def excluir_cliente(id_cliente):
    # Carregar o arquivo Excel
    wb = openpyxl.load_workbook(planilha_caminho)
    
    # Selecionar a planilha "clientes"
    ws = wb['Clientes']
    
    # Percorrer as linhas da planilha a partir da segunda linha
    for row in ws.iter_rows(min_row=2):
        # Acessar o valor na primeira coluna (ID) e garantir que ambos são strings para comparação
        id_valor = str(row[0].value)
        id_cliente_str = str(id_cliente)
        
        # Verificar se o ID corresponde ao que queremos excluir
        if id_valor == id_cliente_str:
            # Excluir a linha
            ws.delete_rows(row[0].row)
            break
    
    # Salvar o arquivo sem afetar outras planilhas
    wb.save(planilha_caminho)
    print(f"Cliente foi excluido(a) com sucesso.")

if __name__ == "__main__":
    if "excluir" in sys.argv and "produto" in sys.argv:
        id_produto = sys.argv[3]
        excluir_produto(id_produto)
    elif "excluir" in sys.argv and "funcionario" in sys.argv:
        id_funcionario = sys.argv[3]
    elif "excluir" in sys.argv and "cliente" in sys.argv:
        id_cliente = sys.argv[3]
        excluir_cliente(id_cliente)
    elif "buscar" in sys.argv and "funcionario" in sys.argv:
        funcionario = sys.argv[3]
        buscar_funcionario(funcionario)
    elif "buscar" in sys.argv and "cliente" in sys.argv:
        cliente = sys.argv[3]
        buscar_cliente(cliente)
    elif "editar" in sys.argv and "funcionario" in sys.argv:
        novo_nome = sys.argv[4]
        novo_cpf = sys.argv[5]
        novo_rg = sys.argv[6]
        nova_data_nasc = sys.argv[7]
        novo_user = sys.argv[8]
        nova_senha = sys.argv[9]
        id_funcionario = sys.argv[3]
        editar_funcionario(novo_nome, novo_cpf, novo_rg, nova_data_nasc, novo_user, nova_senha, id_funcionario)
    elif "editar" in sys.argv and "cliente" in sys.argv:
        novo_nome = sys.argv[4]
        novo_cpf = sys.argv[5]
        novo_rg = sys.argv[6]
        nova_data_nasc = sys.argv[7]
        id_cliente = sys.argv[3]
        editar_cliente(novo_nome, novo_cpf, novo_rg, nova_data_nasc, id_cliente)
    elif "editar" in sys.argv and "produto" in sys.argv:
        novo_nome = sys.argv[2]
        novo_preco = sys.argv[3]
        nova_quantidade = sys.argv[4]
        id_produto = sys.argv[1]
        editar_produto(novo_nome, novo_preco, nova_quantidade, id_produto)
    elif len(sys.argv) == 8:
        nome = sys.argv[1]
        cpf = str(sys.argv[2])  # Certifica-se de que o CPF seja tratado como string
        data_nascimento = sys.argv[3]
        rg = sys.argv[4]
        username = sys.argv[5]
        password = sys.argv[6]
        tipo = sys.argv[7]
        cadastrar_funcionario(nome, cpf, data_nascimento, rg, username, password, tipo)
    elif len(sys.argv) == 3:
        username = sys.argv[1]
        password = sys.argv[2]
        if validar_login(username, password):
            sys.exit(0)  # Login bem-sucedido
        else:
            sys.exit(1)  # Falha no login
    elif len(sys.argv) == 5:
        nome = sys.argv[1]
        cpf = str(sys.argv[2])  # Certifica-se de que o CPF seja tratado como string
        data_nascimento = sys.argv[3]
        rg = sys.argv[4]
        cadastrar_cliente(nome, cpf, data_nascimento, rg)
    elif len(sys.argv) == 4:
        nome = sys.argv[1] # Certifica-se de que o CPF seja tratado como string
        qtd_produto = sys.argv[2]
        preco = str(sys.argv[3])
        cadastrar_produto(nome, preco, qtd_produto)
    elif len(sys.argv) == 2:
        nome = sys.argv[1]
        buscar_produto(nome)
    else:
        print("Uso: python excel_utils.py <username> <password> ou python excel_utils.py <nome> <cpf> <data_nascimento> <rg> <username> <password> <tipo>")
        print(len(sys.argv))
        print(sys.argv)
        sys.exit(1)