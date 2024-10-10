#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int r;
    int g;
    int b;
} Pixel;

void menu();
void openImage(char image_name[], int style);
void processImage(FILE *fp, int style);
void imageInfo(FILE *fp, int *coluna, int *linha, int *val);

int main() {

     int op; // Variável para armazenar a opção escolhida
    char image_name[100];
    
    printf("\n---------------- EDIT IMAGE MENU ----------------\n\n");
    printf("Enter the name of the image you want to edit: ");
    scanf("%s", image_name);

    while (1) {
        menu();

        scanf("%d", &op);

        if (op == 0) {
            printf("Finishing program.\n");
            break;
        }

        if (op < 1 || op > 3) {
            printf("Invalid option. Please try again.\n");
            continue;
        }

        openImage(image_name, op);
    }

    return 0;
}

void openImage(char image_name[], int style) {
    FILE *fp = fopen(image_name, "r");

    if (fp == NULL) {
        printf("\nError opening the file %s\n: ", image_name);
        return;
    }

    processImage(fp, style);
}

void processImage(FILE *fp, int style) {
    int coluna, linha, val;
    int r, g, b;

    imageInfo(fp, &coluna, &linha, &val);

    Pixel **matriz = (Pixel **)malloc(linha * sizeof(Pixel *));
    for (int i = 0; i < linha; i++) {
        matriz[i] = (Pixel *)malloc(coluna * sizeof(Pixel));
    }

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            fscanf(fp, "%d %d %d", &r, &g, &b);

            if (style == 1) {
       
                matriz[i][j].r = (r * 0.30) + (g * 0.59) + (b * 0.11);
                matriz[i][j].g = (r * 0.30) + (g * 0.59) + (b * 0.11);
                matriz[i][j].b = (r * 0.30) + (g * 0.59) + (b * 0.11);

            } else if (style == 2) {
        
                matriz[i][j].r = 255 - r;
                matriz[i][j].g = 255 - g;
                matriz[i][j].b = 255 - b;

            } else if (style == 3) {
 
                matriz[i][j].r = (r * 0.393) + (g * 0.769) + (b * 0.189);
                matriz[i][j].g = (r * 0.349) + (g * 0.686) + (b * 0.168);
                matriz[i][j].b = (r * 0.272) + (g * 0.534) + (b * 0.131);

                if (matriz[i][j].r > 255) matriz[i][j].r = 255;
                if (matriz[i][j].g > 255) matriz[i][j].g = 255;
                if (matriz[i][j].b > 255) matriz[i][j].b = 255;
            }
        }
    }

    fclose(fp);
    printf("Image successfully read.\n");

    FILE *fp_saida = fopen("output_image.ppm", "w");

    if (fp_saida == NULL) {
        printf("\nError opening the file\n");
        for (int i = 0; i < linha; i++) {
            free(matriz[i]);
        }
        free(matriz);
        return;
    }

    fprintf(fp_saida, "P3\n");
    fprintf(fp_saida, "%d %d\n", coluna, linha);
    fprintf(fp_saida, "%d\n", val);

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            fprintf(fp_saida, "%d %d %d ", matriz[i][j].r, matriz[i][j].g, matriz[i][j].b);
        }
        fprintf(fp_saida, "\n");
    }

    fclose(fp_saida);

    for (int i = 0; i < linha; i++) {
        free(matriz[i]);
    }
    free(matriz);

    printf("Image successfully processed and saved as output_image.ppm\n");
}

void imageInfo(FILE *fp, int *coluna, int *linha, int *val) {
    char tipoImg[3];
    fscanf(fp, "%s", tipoImg);
    fscanf(fp, "%d %d", coluna, linha);
    fscanf(fp, "%d", val);
}

void menu() {
    printf("\n------------ EDIT IMAGE MENU ------------\n\n");
    printf("\n[1] - Convert image to black and white.");
    printf("\n[2] - Convert image to X-ray.");
    printf("\n[0] - Finish the program.");
    printf("\nOption: ");
}
