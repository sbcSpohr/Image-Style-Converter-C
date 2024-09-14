#include <stdio.h>
#include <stdlib.h>

void menu();
void open_image(char image_name[], int style);
void image_info(FILE *fp, int *coluna, int *linha, int *val);
void process_image(FILE *fp, int style);

int main() {
    int op;
    char image_name[100];

    printf("\n---------------- EDIT IMAGE MENU ----------------\n\n");
    printf("Enter the name of the image you want to edit: ");
    scanf("%s", image_name);

    do {
        menu();
        scanf("%d", &op);

        switch (op)
        {
        case 1:
        case 2:
            open_image(image_name, op);
            break;
        default:
            break;
        }

    } while (op != 0);

    printf("\nProgram closed.");

    return 0;
}

void menu() {
    printf("\n------------ EDIT IMAGE MENU ------------\n\n");
    printf("\n[1] - Convert image to black and white.");
    printf("\n[2] - Convert image to X-ray.");
    printf("\n[0] - Finish the program.");
    printf("\nOption: ");
}

void open_image(char image_name[], int style) {
    FILE *fp = fopen(image_name, "r");

    if (fp == NULL) {
        printf("Error opening the image %s\n", image_name);
        return;
    }

    process_image(fp, style);
}

void image_info(FILE *fp, int *coluna, int *linha, int *val) {
    char tipoImg[3];

    fscanf(fp, "%s", tipoImg);
    printf("\nPPM type: %s\n", tipoImg);

    fscanf(fp, "%d %d", coluna, linha);
    printf("\nImage size: %d x %d", *coluna, *linha);

    fscanf(fp, "%d", val);
    printf("\nMaximum pixel value: %d\n", *val);
}

void process_image(FILE *fp, int style) {
    int coluna, linha, val;
    int r, g, b;

    image_info(fp, &coluna, &linha, &val);

    int **matriz = (int **)malloc(linha * sizeof(int *));
    for (int i = 0; i < linha; i++) {
        matriz[i] = (int *)malloc(coluna * sizeof(int));
    }

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            fscanf(fp, "%d %d %d", &r, &g, &b);

            if (style == 1) {
                matriz[i][j] = (int)((r * 0.30) + (g * 0.59) + (b * 0.11));
            }
            else if (style == 2) {
                matriz[i][j] = 255 - (int)((r * 0.30) + (g * 0.59) + (b * 0.11));
            }
        }
    }

    fclose(fp);
    printf("\nImage successfully read.");

    FILE *fp_saida = fopen("output_image.ppm", "w");
    if (fp_saida == NULL) {
        printf("Error opening the file for writing.\n");
        for (int i = 0; i < linha; i++) {
            free(matriz[i]);
        }
        free(matriz);
        return;
    }

    if (style == 1) {
        fprintf(fp_saida, "P2\n");
        fprintf(fp_saida, "%d %d\n", coluna, linha);
        fprintf(fp_saida, "255\n");

        for (int i = 0; i < linha; i++) {
            for (int j = 0; j < coluna; j++) {
                fprintf(fp_saida, "%d ", matriz[i][j]);
            }
            fprintf(fp_saida, "\n");
        }
    }
    else if (style == 2) {
        fprintf(fp_saida, "P3\n");
        fprintf(fp_saida, "%d %d\n", coluna, linha);
        fprintf(fp_saida, "255\n");

        for (int i = 0; i < linha; i++) {
            for (int j = 0; j < coluna; j++) {
                int gray = matriz[i][j];
                fprintf(fp_saida, "%d %d %d ", gray, gray, gray); // RGB iguais para preto e branco
            }
            fprintf(fp_saida, "\n");
        }
    }

    fclose(fp_saida);

    for (int i = 0; i < linha; i++) {
        free(matriz[i]);
    }
    free(matriz);

    printf("Image saved.");
}
