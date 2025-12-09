#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

// si ID en rango fresco, si no podrido
// devolver número de frescos (cantidad)

#define MAX_RANGOS 200// máximo de rangos a leer

typedef struct { // estructura para guardar rango
    long long inicio;
    long long fin;
} Rango;

int rango(long long numero, Rango rangos[], int num_rangos) { // función para comprobar si ID pertenece a algún rango
    for (int i = 0; i < num_rangos; i++) { // recorre todos los rangos

        if (numero >= rangos[i].inicio && numero <= rangos[i].fin) {
            return 1; // rango
        }
    }
    return 0; // no rango
}

void fin_linea(char *s) { // elimina \n del final
    size_t len = strlen(s);
    while (len > 0 && s[len-1] == '\n') {
        s[--len] = '\0';
    }
}

int main(int argc, char *argv[]) {

    FILE *archivo = fopen(argv[1], "r");   
    if (archivo == NULL) {
        printf("Error: no se pudo abrir el archivo %s\n", argv[1]);
        return 1;
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    char linea[150]; // espacio máximo reservado para elementos en cada línea
    Rango rangos[MAX_RANGOS]; // 'variable' tipo Rango que guarda hasta MAX_RANGOS
    int num_rangos = 0; // número de rangos intentados
    long long linea_vacia = 0; // para comprobar si se ha llegado a la línea vacía para empezar con los ID
    
    while (fgets(linea, sizeof(linea), archivo) != NULL) { // mientras haya líneas

        fin_linea(linea);
        if (linea[0] == '\0') {  // línea vacía
            break;
        }

        long long inicio, fin; // de rango

        // si el número de elementos leídos en línea con formato INT-INT es 2, o sea, es un rango
        if (sscanf(linea, "%lld-%lld", &inicio, &fin) == 2) { 
            rangos[num_rangos].inicio = inicio; // inicio de struct es inicio definido en main
            rangos[num_rangos].fin = fin; // fin de struct es fin definido en main
            num_rangos++; // aumenta el número de rangos del fichero txt
        }
    }

    long long numero;
    int ing = 0; // número de ingredientes frescos

    // fscanf(archivo, formato, &variable)
    // devuelve el número de elementos leídos exitosamente
    while (fscanf(archivo, "%lld", &numero) == 1) { // mientras lea 1 elemento (entero)
                                                      // va elemento por elemento (o número por número)
        if (rango(numero, rangos, num_rangos)) { // si pertenece al rango (return 1)
            ing++;
        }
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    printf("Contraseña: %d\n", ing);
    fclose(archivo);
    return 0;
}