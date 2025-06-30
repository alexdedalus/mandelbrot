#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    // Definição dos limites do plano complexo
    double x_min = -2.0, x_max = 1.0;
    double y_min = -1.5, y_max = 1.5;

    // Resolução da imagem
    int pixel_x = 1024, pixel_y = 1024;

    // Número máximo de iterações
    int max_iter = 255;

    // Abre arquivo para salvar imagem em formato PGM (Portable GrayMap)
    FILE *f = fopen("mandelbrot.pgm", "w");
    if (!f) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return 1;
    }

    // Escreve o cabeçalho do PGM
    fprintf(f, "P2\n%d %d\n%d\n", pixel_x, pixel_y, max_iter);

    // Loop de pixels
    for (int i = 0; i < pixel_y; i++) {
        for (int j = 0; j < pixel_x; j++) {
            // Mapeia coordenadas do pixel para o plano complexo
            double real = x_min + (x_max - x_min) * j / pixel_x;
            double imag = y_min + (y_max - y_min) * i / pixel_y;

            double z_real = real;
            double z_imag = imag;

            int iteration = 0;
            while ((z_real * z_real + z_imag * z_imag <= 4.0) && (iteration < max_iter)) {
                double temp = z_real * z_real - z_imag * z_imag + real;
                z_imag = 2 * z_real * z_imag + imag;
                z_real = temp;
                iteration++;
            }

            // Salva o número de iterações (valor de intensidade) no arquivo
            fprintf(f, "%d ", iteration);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Imagem Mandelbrot salva como 'mandelbrot.pgm'\n");

    return 0;
}
