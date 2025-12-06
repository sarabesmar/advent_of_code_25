#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILAS 10000 // cantidad de lineas (NO es número de elementos por línea)
#define MAX_COLUMNAS 10000 // cantidad de columnas (NO es número de elementos por columna)
#define MAX_ROLLOS 3 // máximo número de rollos que puede tener alrededor para poder sacar uno

int num_rollos = 0;
char matriz[MAX_FILAS][MAX_COLUMNAS]; // crea una matriz de char de tamaño 10000x10000

int busqueda_rollos(char matriz[MAX_FILAS][MAX_COLUMNAS], int filas, int columnas) {

    for (int i = 0; i < filas; i++) { // fila por fila
        for (int j = 0; j < columnas; j++) {// columna por columna

            if (matriz[i][j] == '@') { // si el elemento es un rollo

                int vecinos = 0; // cuenta número de rollos vecinos

// esto es una burrada pero no se me ocurre de otra forma sorry

/*
                // Arriba-Izquierda
                if () {
                    vecinos++;
                }
                // Arriba-Derecha
                if () {
                    vecinos++;
                }
                // Abajo-Izquierda
                if () {
                    vecinos++;
                }
                // Abajo-Derecha
                if () {
                    vecinos++;
                }

*/

                if (j > 0 && matriz[i][j-1] == '@') { // elemento izquierda
                    vecinos++;
                }
                if (j < columnas-1 && matriz[i][j+1] == '@') { // elemento derecha
                    vecinos++;
                }
                if (i < filas-1 && matriz[i+1][j] == '@') { // elemento abajo
                    vecinos++;
                }
                if (i > 0 && matriz[i-1][j] == '@') { // elemento arriba
                    vecinos++;
                } 
                
                if (i < filas-1 && j > 0 && matriz[i+1][j-1] == '@') { // elemento abajo izq
                    vecinos++;
                }
                if (i < filas-1 && j < columnas-1 && matriz[i+1][j+1] == '@') { // elemento abajo der
                    vecinos++;
                }
                if (i > 0 && j < columnas-1 && matriz[i-1][j+1] == '@') { // elemento arriba der
                    vecinos++;
                }
                if (i > 0 && j > 0 && matriz[i-1][j-1] == '@') { // elemento arriba izq
                    vecinos++;
                }

                if (vecinos <= MAX_ROLLOS) {
                    num_rollos++; // si hay más de 3 aumenta el número de rollos que no se pueden sacar
                }
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {

    FILE *archivo = fopen(argv[1], "r");   
    if (archivo == NULL) {
        printf("Error: no se pudo abrir el archivo %s\n", argv[1]);
        return 1;
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    int filas = 0; // número de filas leídas
    int columnas = 0; // número de columnas leídas

    while(filas < MAX_FILAS) {

        // fgets(char *str, int n, FILE *stream) -> puntero a buffer donde se guarda línea leída
        //                                          tamaño máximo de carateres a leer
        //                                          puntero al archivo desde donde leer
        // devuelve puntero a la cadena leída

        if (fgets(matriz[filas], MAX_COLUMNAS, archivo) == NULL) { // en la matriz se guardan las filas que vaya leyendo
                                                                   // el número máximo elementos es la cantidad de columnas
            break; // cuando no queden más líneas sale del bucle
        }

        // strcspn(const char *str1, const char *str2); -> busca en str1
        //                                                 str2 qeu contiene los caracteres a buscar en str1 
        // en nuestro caso busca en la matriz los \n

        int pos = strcspn(matriz[filas], "\n"); // encuentra posición del \n
        matriz[filas][pos] = '\0'; // convierte \n en \0 (fin de fila)

        if (filas == 0) { // en la primera fila guarda la longitud de esta para tener la cantidad de columnas
            columnas = strlen(matriz[filas]);
        }

        filas ++; // aumenta número de filas y sigue con el bucle
    }

    busqueda_rollos(matriz, filas, columnas);

/////////////////////////////////////////////////////////////////////////////////////////////

    printf("Contraseña: %d\n", num_rollos);
    fclose(archivo);
    return 0;
}