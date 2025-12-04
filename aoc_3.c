#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum_jolts = 0;

int buscar_jolts_banco(char* linea) {
    int max1 = 0;
    int max2 = 0;
    
    for (int i = 0 ; i < strlen(linea) ; i++) {

        if (linea[i] >= '0' && linea[i] <= '9') {

            int num = linea[i] - '0'; // elemento ASCII menos caracter 0
            
            if (num > max1) { 
                max2 = max1;
                max1 = num;
            } else if (num > max2) {
                max2 = num;
            }
        }
    }

    int id_banco = (max1 * 10) + max2;
    sum_jolts += id_banco;
    
    return 0;
}

int main(int argc, char *argv[]) {

    FILE *archivo = fopen(argv[1], "r");   
    if (archivo == NULL) {
        printf("Error: no se pudo abrir el archivo %s\n", argv[1]);
        return 1;
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    char linea[100000]; // guardar caracteres línea por línea

    while(fgets(linea, sizeof(linea), archivo) != NULL) { // mientras haya una línea
        buscar_jolts_banco(linea); // llega el banco
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    printf("Contraseña: %d\n", sum_jolts);
    fclose(archivo);
    return 0;
}