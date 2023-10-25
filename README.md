# Manipulação de Imagens no Formato PPM - README
Este projeto implementa um Tipo Abstrato de Dados (TAD) em linguagem C para a leitura, gravação e manipulação de imagens no formato PPM (Portable Pix Map). Além disso, o programa realiza a conversão de imagens coloridas em imagens em tons de cinza. Abaixo estão as instruções para executar o programa e algumas decisões de implementação tomadas durante o desenvolvimento.


## Passo-a-passo para Executar o Programa

**Compilação:**
Para compilar o programa, você pode usar o arquivo Makefile fornecido. Basta abrir o terminal e navegar até o diretório do projeto e executar o seguinte comando:


**Menu de Opções:**
Após executar o programa, você será apresentado a um menu de opções interativo no qual pode escolher entre as seguintes operações:

Carregar Imagem: Permite carregar uma imagem do formato PPM.
Converter para Tons de Cinza: Converte a imagem carregada para tons de cinza.
Gravar Imagem: Grava a imagem atual em um arquivo PPM.
Sair: Encerra o programa.

## Principais Decisões de Implementação

**Estrutura de Dados:**
Foi utilizada uma estrutura Image para representar as informações da imagem. Esta estrutura contém o tipo da imagem (P2 para tons de cinza ou P3 para colorida), largura, altura e uma matriz de pixels.

## Leitura e Escrita de Imagens:

A leitura de imagens PPM foi implementada na função "load_from_ppm" usando as funções de manipulação de arquivos em C.
A escrita de imagens PPM foi implementada na função "write_to_ppm" usando as mesmas funções de manipulação de arquivos.

## Conversão para Tons de Cinza:

A conversão de imagens coloridas para tons de cinza foi realizada conforme a fórmula fornecida no enunciado do trabalho: Igray(y, x) = 0.299 * IRGB(y, x, R) + 0.587 * IRGB(y, x, G) + 0.114 * IRGB(y, x, B).

## Gerenciamento de Memória:

Foi feito o gerenciamento adequado de memória para evitar vazamentos, garantindo que a memória alocada dinamicamente seja liberada corretamente.

## Menu Interativo:

O programa apresenta um menu interativo para permitir que o usuário escolha facilmente as operações desejadas.


Este é um guia básico para entender como executar o programa e as principais decisões de implementação. Sinta-se à vontade para explorar o código-fonte para obter uma compreensão mais detalhada da implementação.

_Levi Monteiro e Gabriel Lacerda_
