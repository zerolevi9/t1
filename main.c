#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

int main() {
  char escolha;
  char refNome_entrada[100];
  char refNome_saida[100];
  char *nomePPMentrada = refNome_entrada;
  char *nomePPMsaida = refNome_saida;
  Image *ima;

  while (escolha != 's') {
    printf("\n Escolha uma opção: \n");
    printf("(a) Converter uma imagem\n");
    printf("(b) Sair\n");
    scanf(" %c", &escolha);

    switch (escolha) {
      case 'b': 
          break;

      case 'a':
          printf(" \nConverter uma imagem PPM em PGM\n");
          printf("Caminho default? s ou n\n");
          scanf(" %c", &escolha);
          if (escolha == 's') {
            ima = getInfo("a.ppm");
            nomePPMentrada = "a.ppm";
          } else if (escolha == 'n') {
            printf("\nQual o nome do arquivo?\n");
            scanf("%s", refNome_entrada);
            ima = getInfo(refNome_entrada);
          } else {
            printf("Opção inválida. Tente novamente.\n");
            break;
          }
          Image *new = create(ima->rows, ima->cols, "P2");
          Image *old = create(ima->rows, ima->cols, ima->tipo);
          old = load_from_ppm(nomePPMentrada);
          rgb_to_gray(old, new);
          printf("Irá nomear o arquivo? s ou n\n");
          scanf(" %c", &escolha);
          if (escolha == 's') {
            printf("Nome do arquivo?\n");
            scanf("%s", refNome_saida);
            write_to_ppm(new, refNome_saida);
          } 
          else if (escolha == 'n') {
            printf("Você escolheu o nome padrão, o arquivo ficou salvo como default.ppm\n");
            write_to_ppm(new, "default.ppm");
          } 
          else {
            printf("erro, tente novamente\n");
          }         
          liberarImagem(new);
          liberarImagem(old);
          liberarImagem(ima);
          printf("\nImagem foi gerada com sucesso!\n");
          escolha = 'n';
          break;

      default:
          printf("Opção inválida. Tente novamente.\n");
          break;
    }
  }
  printf("Programa encerrado\n");
  return 0;
}
