import sys
import re

def validar_cadastro(nome, data_nasc, cpf, rg, usuario, senha, tipo):
    if not nome.isalnum():
        return "Nome invalido, use apenas caracteres alfanumericos."
    if not re.match(r"\d{2}/\d{2}/\d{4}", data_nasc):
        return "Data de nascimento invalida, use o formato dd/mm/yyyy."
    if not re.match(r"\d{3}\.\d{3}\.\d{3}-\d{2}", cpf):
        return "CPF invalido, use o formato 000.000.000-00."
    if not re.match(r"\d{2}\.\d{3}\.\d{3}-\d{1}", rg):
        return "RG invalido, use o formato 00.000.000"
