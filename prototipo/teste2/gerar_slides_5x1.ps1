function Pad {
    param($s, $w)
    return $s.PadRight($w)
}

function CriaSlide {
    param($sistema, $sistemaNome, $rodizio, $fase, $faseNome, $p1, $p2, $p3, $p4, $p5, $p6, $descricao, $observacao)

    $pasta = "slides\$sistema\rod$rodizio"
    if (-not (Test-Path $pasta)) { New-Item -ItemType Directory -Path $pasta -Force | Out-Null }

    switch ($fase) {
        1 { $nomeArq = "01_base.txt" }
        2 { $nomeArq = "02_passe.txt" }
        3 { $nomeArq = "03_levantamento.txt" }
        4 { $nomeArq = "04_corte.txt" }
        5 { $nomeArq = "05_defesa.txt" }
        6 { $nomeArq = "06_bloqueio.txt" }
    }

    $caminho = Join-Path $pasta $nomeArq

    $a = Pad $p4 9
    $b = Pad $p3 9
    $c = Pad $p2 9
    $d = Pad $p5 9
    $e = Pad $p6 9
    $f = Pad $p1 9

    $conteudo = @"
+------------------------------------------+
|     $sistemaNome - Rodizio $rodizio        |
|     Fase: $faseNome                        |
+------------------------------------------+
|                                          |
|         ========= REDE =========         |
|                                          |
|  $a $b $c |
|                                          |
|  $d $e $f |
|                                          |
+------------------------------------------+
| $descricao
|                                          |
| $observacao
+------------------------------------------+
"@

    Set-Content -Path $caminho -Value $conteudo -Encoding ASCII
}

Write-Host "Gerando slides 5x1..."

# Rodizio 1
CriaSlide "5x1" "Sistema 5x1" 1 1 "Posicao Base"        "P1(Lev)" "P2(Pon)" "P3(Cen)" "P4(Pon)" "P5(Opo)" "P6(Cen)" "Posicao inicial de cada jogador no rodizio." "Levantador na posicao 1 (saque)."
CriaSlide "5x1" "Sistema 5x1" 1 2 "Passe"               "P1(Lev)" "P2(Pon)" "P3(Cen)" "P4(Pon)" "P5(Opo)" "P6(Cen)" "Recepcao do saque adversario." "Libero entra em P6; Lev se prepara para levantar."
CriaSlide "5x1" "Sistema 5x1" 1 3 "Levantamento"        "P1(Lev)" "P2(Pon)" "P3(Cen)" "P4(Pon)" "P5(Opo)" "P6(Cen)" "Levantador faz o levantamento." "P2 e P4 atacam pelas pontas; P3 ataca no meio."
CriaSlide "5x1" "Sistema 5x1" 1 4 "Corte (Ataque)"      "P1(Lev)" "P2(Pon)" "P3(Cen)" "P4(Pon)" "P5(Opo)" "P6(Cen)" "Jogadores de ataque na abordagem." "P2 e P4 cortam; P3 faz cortada no meio."
CriaSlide "5x1" "Sistema 5x1" 1 5 "Defesa"              "P1(Lev)" "P2(Pon)" "P3(Cen)" "P4(Pon)" "P5(Opo)" "P6(Cen)" "Posicao de defesa apos ataque." "P5 e P6 cobrem fundo; P1 cobre cortada."
CriaSlide "5x1" "Sistema 5x1" 1 6 "Bloqueio"            "P1(Lev)" "P2(Pon)" "P3(Cen)" "P4(Pon)" "P5(Opo)" "P6(Cen)" "Formacao de bloqueio na rede." "P2, P3 e P4 sobem para bloquear."

# Rodizio 2
CriaSlide "5x1" "Sistema 5x1" 2 1 "Posicao Base"        "P1(Cen)" "P2(Lev)" "P3(Pon)" "P4(Cen)" "P5(Pon)" "P6(Opo)" "Posicao inicial do rodizio 2." "Levantador agora na posicao 2."
CriaSlide "5x1" "Sistema 5x1" 2 2 "Passe"               "P1(Cen)" "P2(Lev)" "P3(Pon)" "P4(Cen)" "P5(Pon)" "P6(Opo)" "Recepcao do saque." "Libero cobre P6; Lev se desloca para area de levantamento."
CriaSlide "5x1" "Sistema 5x1" 2 3 "Levantamento"        "P1(Cen)" "P2(Lev)" "P3(Pon)" "P4(Cen)" "P5(Pon)" "P6(Opo)" "Levantador na rede." "P3 e P5 atacam pelas pontas; P4 ataca no meio."
CriaSlide "5x1" "Sistema 5x1" 2 4 "Corte (Ataque)"      "P1(Cen)" "P2(Lev)" "P3(Pon)" "P4(Cen)" "P5(Pon)" "P6(Opo)" "Ataque pelo meio e pontas." "P3, P4 e P5 sao opcoes de cortada."
CriaSlide "5x1" "Sistema 5x1" 2 5 "Defesa"              "P1(Cen)" "P2(Lev)" "P3(Pon)" "P4(Cen)" "P5(Pon)" "P6(Opo)" "Defesa pos-ataque." "P1 e P6 protegem fundo; Lev cobre rede."
CriaSlide "5x1" "Sistema 5x1" 2 6 "Bloqueio"            "P1(Cen)" "P2(Lev)" "P3(Pon)" "P4(Cen)" "P5(Pon)" "P6(Opo)" "Bloqueio triplo na rede." "P2, P3 e P4 saltam para bloquear."

# Rodizio 3
CriaSlide "5x1" "Sistema 5x1" 3 1 "Posicao Base"        "P1(Opo)" "P2(Cen)" "P3(Lev)" "P4(Pon)" "P5(Cen)" "P6(Pon)" "Posicao inicial do rodizio 3." "Levantador na posicao 3 (meio da rede)."
CriaSlide "5x1" "Sistema 5x1" 3 2 "Passe"               "P1(Opo)" "P2(Cen)" "P3(Lev)" "P4(Pon)" "P5(Cen)" "P6(Pon)" "Recepcao do saque." "Lev se prepara para saida de rede."
CriaSlide "5x1" "Sistema 5x1" 3 3 "Levantamento"        "P1(Opo)" "P2(Cen)" "P3(Lev)" "P4(Pon)" "P5(Cen)" "P6(Pon)" "Levantador na rede." "P2 e P4 atacam; P1 faz cortada de fundo."
CriaSlide "5x1" "Sistema 5x1" 3 4 "Corte (Ataque)"      "P1(Opo)" "P2(Cen)" "P3(Lev)" "P4(Pon)" "P5(Cen)" "P6(Pon)" "Opcoes de ataque." "Ataque pelos 3 jogadores da frente."
CriaSlide "5x1" "Sistema 5x1" 3 5 "Defesa"              "P1(Opo)" "P2(Cen)" "P3(Lev)" "P4(Pon)" "P5(Cen)" "P6(Pon)" "Defesa pos-ataque." "Linha de defesa em W."
CriaSlide "5x1" "Sistema 5x1" 3 6 "Bloqueio"            "P1(Opo)" "P2(Cen)" "P3(Lev)" "P4(Pon)" "P5(Cen)" "P6(Pon)" "Bloqueio com 2 ou 3 jogadores." "P2, P3 e P4 formam o bloqueio."

# Rodizio 4
CriaSlide "5x1" "Sistema 5x1" 4 1 "Posicao Base"        "P1(Pon)" "P2(Opo)" "P3(Cen)" "P4(Lev)" "P5(Pon)" "P6(Cen)" "Posicao inicial do rodizio 4." "Levantador na posicao 4 (entrada de rede)."
CriaSlide "5x1" "Sistema 5x1" 4 2 "Passe"               "P1(Pon)" "P2(Opo)" "P3(Cen)" "P4(Lev)" "P5(Pon)" "P6(Cen)" "Recepcao do saque." "Lev se prepara para levantar da entrada."
CriaSlide "5x1" "Sistema 5x1" 4 3 "Levantamento"        "P1(Pon)" "P2(Opo)" "P3(Cen)" "P4(Lev)" "P5(Pon)" "P6(Cen)" "Levantador na entrada da rede." "Distribui bolas para P2, P3 e P6."
CriaSlide "5x1" "Sistema 5x1" 4 4 "Corte (Ataque)"      "P1(Pon)" "P2(Opo)" "P3(Cen)" "P4(Lev)" "P5(Pon)" "P6(Cen)" "Opcoes de cortada." "P2 (oposto) ataca forte; P3 corta no meio."
CriaSlide "5x1" "Sistema 5x1" 4 5 "Defesa"              "P1(Pon)" "P2(Opo)" "P3(Cen)" "P4(Lev)" "P5(Pon)" "P6(Cen)" "Defesa pos-ataque." "Cobertura de bloqueio com P1 e P5."
CriaSlide "5x1" "Sistema 5x1" 4 6 "Bloqueio"            "P1(Pon)" "P2(Opo)" "P3(Cen)" "P4(Lev)" "P5(Pon)" "P6(Cen)" "Bloqueio na rede." "P2, P3 e P4 bloqueiam juntos."

# Rodizio 5
CriaSlide "5x1" "Sistema 5x1" 5 1 "Posicao Base"        "P1(Cen)" "P2(Pon)" "P3(Opo)" "P4(Cen)" "P5(Lev)" "P6(Pon)" "Posicao inicial do rodizio 5." "Levantador na posicao 5 (fundo-esquerda)."
CriaSlide "5x1" "Sistema 5x1" 5 2 "Passe"               "P1(Cen)" "P2(Pon)" "P3(Opo)" "P4(Cen)" "P5(Lev)" "P6(Pon)" "Recepcao do saque." "Lev corre para entrada de rede; recepcao em 3."
CriaSlide "5x1" "Sistema 5x1" 5 3 "Levantamento"        "P1(Cen)" "P2(Pon)" "P3(Opo)" "P4(Cen)" "P5(Lev)" "P6(Pon)" "Levantador na entrada de rede." "Lev chega correndo; distribui bolas."
CriaSlide "5x1" "Sistema 5x1" 5 4 "Corte (Ataque)"      "P1(Cen)" "P2(Pon)" "P3(Opo)" "P4(Cen)" "P5(Lev)" "P6(Pon)" "Ataque organizado." "P2 e P6 pelas pontas; P3 de fundo."
CriaSlide "5x1" "Sistema 5x1" 5 5 "Defesa"              "P1(Cen)" "P2(Pon)" "P3(Opo)" "P4(Cen)" "P5(Lev)" "P6(Pon)" "Defesa em semi-circulo." "P1 e P4 sao Centrais de bloqueio."
CriaSlide "5x1" "Sistema 5x1" 5 6 "Bloqueio"            "P1(Cen)" "P2(Pon)" "P3(Opo)" "P4(Cen)" "P5(Lev)" "P6(Pon)" "Bloqueio no ataque adversario." "P2 e P3 bloqueiam; P4 apoia."

# Rodizio 6
CriaSlide "5x1" "Sistema 5x1" 6 1 "Posicao Base"        "P1(Pon)" "P2(Cen)" "P3(Pon)" "P4(Opo)" "P5(Cen)" "P6(Lev)" "Posicao inicial do rodizio 6." "Levantador na posicao 6 (fundo-meio)."
CriaSlide "5x1" "Sistema 5x1" 6 2 "Passe"               "P1(Pon)" "P2(Cen)" "P3(Pon)" "P4(Opo)" "P5(Cen)" "P6(Lev)" "Recepcao do saque." "Lev corre para entrada; recepcao protegida."
CriaSlide "5x1" "Sistema 5x1" 6 3 "Levantamento"        "P1(Pon)" "P2(Cen)" "P3(Pon)" "P4(Opo)" "P5(Cen)" "P6(Lev)" "Levantador chega na entrada." "P2 e P3 como opcoes principais."
CriaSlide "5x1" "Sistema 5x1" 6 4 "Corte (Ataque)"      "P1(Pon)" "P2(Cen)" "P3(Pon)" "P4(Opo)" "P5(Cen)" "P6(Lev)" "Sequencia de ataque." "P3 e P1 atacam; P4 auxilia no meio."
CriaSlide "5x1" "Sistema 5x1" 6 5 "Defesa"              "P1(Pon)" "P2(Cen)" "P3(Pon)" "P4(Opo)" "P5(Cen)" "P6(Lev)" "Defesa organizada." "Cobertura de bloqueio e fundo."
CriaSlide "5x1" "Sistema 5x1" 6 6 "Bloqueio"            "P1(Pon)" "P2(Cen)" "P3(Pon)" "P4(Opo)" "P5(Cen)" "P6(Lev)" "Bloqueio triplo." "P2, P3 e P4 bloqueiam ataque adversario."

Write-Host "Total: 36 slides 5x1 gerados com sucesso!"
