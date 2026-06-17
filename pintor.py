import os

PASTA_ATUAL = os.path.dirname(os.path.abspath(__file__))

PASTA_RAIZ = os.path.join(PASTA_ATUAL, "quadras")

SUBSTITUICOES = {
    "[O]":"[91m[O][0m",
    "[Li]":"[94m[Li][0m",
    "[P1]":"[93m[P1][0m",
    "[LV]":"[92m[LV][0m",
    "[C2]":"[96m[C2][0m",
    "[P2]":"[93m[P2][0m",
    "[C1]":"[96m[C1][0m"
}

def substituir_em_toda_árvore(pasta_principal, dicionario_sub):
    if not os.path.exists(pasta_principal):
        print(f"Erro: A pasta '{pasta_principal}' não foi encontrada.")
        return

    print(f"Iniciando varredura na pasta: {pasta_principal}\n")
    
    contador_arquivos = 0

    # os.walk entra em todas as subpastas (4x2, 5x1, rod1, rod2...) automaticamente
    for raiz, diretorios, arquivos in os.walk(pasta_principal):
        for nome_arquivo in arquivos:
            # Alvo encontrado: arquivo .txt (como "01_base.txt", "02_Saque.txt", etc)
            if nome_arquivo.endswith('.txt'):
                caminho_completo = os.path.join(raiz, nome_arquivo)
                
                try:
                    # 1. Lê o conteúdo original
                    with open(caminho_completo, 'r', encoding='utf-8') as arquivo:
                        conteudo = arquivo.read()
                    
                    # 2. Aplica as substituições
                    conteudo_alterado = conteudo
                    alterou = False
                    for antigo, novo in dicionario_sub.items():
                        if antigo in conteudo_alterado:
                            conteudo_alterado = conteudo_alterado.replace(antigo, novo)
                            alterou = True
                    
                    # 3. Só grava no disco se realmente houve alguma mudança
                    if alterou:
                        with open(caminho_completo, 'w', encoding='utf-8') as arquivo:
                            arquivo.write(conteudo_alterado)
                        # Mostra o caminho relativo para ficar mais limpo na tela
                        caminho_relativo = os.path.relpath(caminho_completo, pasta_principal)
                        print(f"✓ Alterado: {caminho_relativo}")
                        contador_arquivos += 1
                        
                except Exception as e:
                    print(f"✗ Erro ao processar {nome_arquivo}: {e}")

    print(f"\nProntinho! O conteúdo de {contador_arquivos} arquivo(s) foi atualizado.")

if __name__ == "__main__":
    substituir_em_toda_árvore(PASTA_RAIZ, SUBSTITUICOES)