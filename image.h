#ifndef IMAGE_H
#define IMAGE_H

typedef struct imagem{
  char tipo[3]; 
  int rows;     
  int cols;     
  int max;
  int **pixels;
}Image;

Image *getInfo(char *filename); //Le informações de uma imagem a partir de um arquivo com o nome filename e retorna uma estrutura Image preenchida com essas informações.
void liberarImagem(Image *imagem); // Esta função é responsável por liberar a memória alocada dinamicamente para uma estrutura
Image *create(int rows, int cols, char type[]); // Esta função cria uma nova estrutura
Image *load_from_ppm(const char *filename); // Esta função carrega uma imagem do formato PPM a partir de um arquivo com o nome
void write_to_ppm(Image *image, const char *filename); // Esta função grava uma estrutura
void rgb_to_gray(Image *image_rgb, Image *image_gray); // Esta função converte uma imagem colorida RGB 
#endif
