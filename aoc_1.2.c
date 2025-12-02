#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i = 50;
int cont0 = 0;

int rotacion(char letra, int numero) {

    if (letra == 'R') { // si gira a la derecha
        
        // contar cuántas veces pasa por 0 durante la rotación
        for (int paso = 0; paso < numero; paso++) {
            i = (i + 1) % 100;
            if (i == 0) {
                cont0++;
            }
        }

    } else { // si gira a la izquierda
        
        // contar cuántas veces pasa por 0 durante la rotación
        for (int paso = 0; paso < numero; paso++) {
            i = i - 1;
            if (i < 0) {
                i = 99;
            }
            if (i == 0) {
                cont0++;
            }
        }
    }
    
    return 0;
}



int main(int argc, char *argv[]) {
    
    FILE *archivo = fopen(argv[1], "r"); // declaración puntero a FILE (tipo de C para manejar archivos)
                                         // archivo es el nombre de la variable, r es modo lectura (read)

    if(archivo == NULL) {
        printf("Error: no se pudo abrir el archivo %s\n", argv[1]);
        return 1;
    }
    
    char letra;
    int numero;
    char linea[100]; // número de elementos por línea

    // fgets(buffer(para guardar línea leída), tamaño(cuantos caracteres puede leer), archivo)
    while(fgets(linea, sizeof(linea), archivo) != NULL) { // mientras haya una línea
        
        if(sscanf(linea, " %c%d", &letra, &numero) == 2) { // sscanf por que lee de un string, no del teclado
            rotacion(letra, numero);
        }
    
    }
    
    printf("Contraseña: %d\n", cont0);
    fclose(archivo);
    return 0;
}