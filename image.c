#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Esta função lê informações do arquivo de imagem (tipo, dimensões, valor máximo) e chama a função create para alocar memória e criar uma estrutura de imagem.*/
Image *getInfo(char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Erro: não foi possível abrir o arquivo.\n");
    exit(EXIT_FAILURE);
  }
  char tipo[3];
  int rows, cols, max, **pixels;
  fscanf(file, "%s", tipo);
  fscanf(file, "%d %d", &rows, &cols);
  fscanf(file, "%d", &max);
  Image *ima = create(rows, cols, tipo);
  fclose(file);
  return ima;
}

/* Esta função libera a memória alocada para uma estrutura de imagem, incluindo a matriz de pixels.
*/
void liberarImagem(Image *imagem) {
  if (imagem == NULL) {
    return; // Evitar liberar uma imagem nula
  }

  for (int i = 0; i < imagem->rows; ++i) {
    free(imagem->pixels[i]);
  }

  free(imagem->pixels);
  free(imagem);
  imagem = NULL; // Define o ponteiro para nulo para evitar acesso acidental
}

/* Esta função aloca memória para uma nova estrutura de imagem, dependendo do tipo de imagem (P2 ou P3). A matriz de pixels é alocada de acordo com o tipo de imagem.
*/
Image *create(int rows, int cols, char type[]) {
  Image *newImage = (Image *)malloc(sizeof(Image));
  if (newImage == NULL) {
    printf("Erro: falha ao alocar memória.\n");
    exit(EXIT_FAILURE);
  }
  newImage->rows = rows;
  newImage->cols = cols;
  newImage->max = 255;
  strncpy(newImage->tipo, type, sizeof(newImage->tipo));

  if (strcmp(type, "P2") == 0 || strcmp(type, "P3") == 0) {
    newImage->pixels = (int **)malloc(rows * sizeof(int *));
    if (newImage->pixels == NULL) {
      printf("Erro: falha ao alocar memória.\n");
      exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; i++) {
      int pixelSize = (strcmp(type, "P3") == 0) ? cols * 3 : cols;
      newImage->pixels[i] = (int *)malloc(pixelSize * sizeof(int));
      if (newImage->pixels[i] == NULL) {
        printf("Erro: falha ao alocar memória.\n");
        exit(EXIT_FAILURE);
      }
    }
  } else {
    printf("Erro: tipo de imagem não suportado.\n");
    exit(EXIT_FAILURE);
  }

  return newImage;
}

/* Esta função lê um arquivo PPM e cria uma estrutura de imagem correspondente, armazenando os valores dos pixels na estrutura.
*/
Image *load_from_ppm(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Erro: não foi possível abrir o arquivo %s.\n", filename);
    exit(EXIT_FAILURE);
  }

  char tipo[3];
  int rows, cols, max;
  fscanf(file, "%s", tipo);

  if (strcmp(tipo, "P3") != 0) {
    printf("Erro: O arquivo %s não é do tipo P3.\n", filename);
    exit(EXIT_FAILURE);
  }

  fscanf(file, "%d %d %d", &rows, &cols, &max);
  Image *ima = create(rows, cols, tipo);

  for (int i = 0; i < ima->rows; i++) {
    for (int j = 0; j < ima->cols * 3; j++) {
      fscanf(file, "%d", &ima->pixels[i][j]);
    }
  }

  fclose(file);
  return ima;
}

/* Esta função escreve uma estrutura de imagem em um arquivo PPM, formatando os dados corretamente.
*/
void write_to_ppm(Image *image, const char *filename) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    printf("Erro: não foi possível criar o arquivo %s.\n", filename);
    exit(EXIT_FAILURE);
  }

  fprintf(file, "%s\n", image->tipo);
  fprintf(file, "%d %d\n", image->rows, image->cols);
  fprintf(file, "%d\n", image->max);

  if (strcmp(image->tipo, "P2") == 0) {
    for (int i = 0; i < image->rows; i++) {
      for (int j = 0; j < image->cols; j++) {
        fprintf(file, "%d ", image->pixels[i][j]);
      }
      fprintf(file, "\n");
    }
  } else if (strcmp(image->tipo, "P3") == 0) {
    for (int i = 0; i < image->rows; i++) {
      for (int j = 0; j < image->cols * 3; j += 3) {
        fprintf(file, "%d %d %d ", image->pixels[i][j], image->pixels[i][j + 1], image->pixels[i][j + 2]);
      }
      fprintf(file, "\n");
    }
  } else {
    printf("Erro: tipo de imagem não suportado.\n");
    exit(EXIT_FAILURE);
  }

  fclose(file);
}

/* Esta função converte uma imagem colorida PPM (P3) em uma imagem em tons de cinza PGM (P2), usando a fórmula padrão para converter RGB para escala de cinza.
*/
void rgb_to_gray(Image *image_rgb, Image *image_gray) {
  if (strcmp(image_rgb->tipo, "P3") != 0) {
    printf("Erro: Esta função suporta apenas imagens RGB do tipo P3.\n");
    return; // Encerra a função se o tipo de imagem não for suportado
  }
  strcpy(image_gray->tipo, "P2");
  image_gray->rows = image_rgb->rows;
  image_gray->cols = image_rgb->cols;
  image_gray->max = 255;

  for (int i = 0; i < image_rgb->rows; i++) {
    for (int j = 0; j < image_rgb->cols * 3; j += 3) {
      float r = image_rgb->pixels[i][j];
      float g = image_rgb->pixels[i][j + 1];
      float b = image_rgb->pixels[i][j + 2];
      float gray_value = 0.299 * r + 0.587 * g + 0.114 * b;
      image_gray->pixels[i][j / 3] = (int)gray_value; // Converte para int
    }
  }
}
