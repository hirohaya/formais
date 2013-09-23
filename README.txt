Lucas Hiroshi Hayashida - nUSP 7557630 
Renan Fichberg - nUSP 7991131
MAC0239 - Métodos Formais em Programação
Primeiro EP - Sudoku
2013/2.

Repositório para o EP1 de Métodos Formais em Programação pelo IME-USP, ministrada pelo professor Marcelo Finger.
        

RELATÓRIO:

A lógica do EP é muito simples:

Primeiramente, consideramos um Sudoku de tamanho 9x9 sem uma configuração inicial, isto é, 
um sudoku vazio. As regras do Sudoku então serão as cláusulas iniciais que o programa irá construir:

I) Cada célula pode ter apenas um número. Então uma celula tera ou o valor 1, ou o valor 2, ou ... 
ou o valor 9.

II) Se uma celula C já possui um numero n, com n pertencente a [1, 9], então C não pode ter nenhum dos 
outros 8 possíveis numero do intervalo [1, 9]

As regras I e II estão escritas na função "cells".

III) Uma linha pode ter qualquer um dos numeros de [1, 9] em qualquer uma de suas 9 casas.

IV) Se uma linha já possui um dos 9 numeros de [1, 9] em uma celula, entao nas outras 8 celulas este numero
não pode estar presente.

As regras III e IV estão escritas nas função "rows", sendo que as funções "columns" e "boxes" possuem um 
raciocininio análogo (porém, a função boxes foi divida em partes, onde cada um dos 9 blocos do Sudoku
tem 2 blocos de loop responsáveis pelas suas regras).
Por fim, a função "unempty_cells" trata do Sudoku desejado, isto é, com a sua configuração incial já
decidida.
A função converter é responsavél por deixar as variáveis no formato necessário para o arquivo de entrada SAT.

Nota: O programa foi feito para Sudokus de 9x9, e apenas 9x9. Tentar com Sudokus de qualquer tamanho 
diferente deste não irá funcionar.

Nota2: O programa deverá preparar uma saída (com o nome que o usuario escolher) já pronta para o zChaff.
