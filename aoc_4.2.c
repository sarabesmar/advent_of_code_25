#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILAS 150 // cantidad de lineas (NO es número de elementos por línea)
#define MAX_COLUMNAS 150 // cantidad de columnas (NO es número de elementos por columna)
#define MAX_ROLLOS 3 // máximo número de rollos que puede tener alrededor para poder sacar uno

int num_rollos = 0;
char matriz[MAX_FILAS][MAX_COLUMNAS]; // crea una matriz de char de tamaño 10000x10000

typedef struct { // estructura para guardar posiciones
    int i; // filas
    int j; // columnas
} Posicion;

int busqueda_rollos(char matriz[MAX_FILAS][MAX_COLUMNAS], int filas, int columnas) {

    // tipo de datos Posicion (estructura anterior), se crea un array que reserva un espacio en memoria de 150x150 (defines)
    // se guarda el elemento eliminado

    Posicion a_eliminar[MAX_FILAS * MAX_COLUMNAS];
    int eliminados = 0;

    for (int i = 0; i < filas; i++) { // fila por fila
        for (int j = 0; j < columnas; j++) {// columna por columna

            if (matriz[i][j] == '@') { // si el elemento es un rollo

                int vecinos = 0; // cuenta número de rollos vecinos

// esto es una burrada pero no se me ocurre de otra forma sorry

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
                    a_eliminar[eliminados].i = i;
                    a_eliminar[eliminados].j = j;
                    eliminados++; // ya no cuenta, ahora guarda posiciones
                }
            }
        }
    }
    for (int k = 0; k < eliminados; k++) { // para cambiar los que se han sacado por .
        matriz[a_eliminar[k].i][a_eliminar[k].j] = '.';
    }
    
    return eliminados;
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

    int total_eliminados = 0;
    int eliminados_en_ronda;
    int ronda = 0;
    
    while (eliminados_en_ronda > 0) { // recorre el .txt hasta que no haya cambios, cada vez habrá más puntos (rollos sacados)
        ronda++;
        eliminados_en_ronda = busqueda_rollos(matriz, filas, columnas);
        total_eliminados += eliminados_en_ronda;        
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    printf("Contraseña: %d\n", total_eliminados);
    fclose(archivo);
    return 0;
}