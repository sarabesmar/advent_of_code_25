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

void recorta_fin_linea(char *s) {
    size_t len = strlen(s);
    while (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r')) {
        s[--len] = '\0';
    }
}

int cmp_rango(const void *a, const void *b) {
    const Rango *ra = (const Rango *)a;
    const Rango *rb = (const Rango *)b;
    if (ra->inicio < rb->inicio) return -1;
    if (ra->inicio > rb->inicio) return 1;
    if (ra->fin < rb->fin) return -1;
    if (ra->fin > rb->fin) return 1;
    return 0;
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
    int n = 0;
    
    while (fgets(linea, sizeof(linea), archivo) != NULL) { // mientras haya líneas
        recorta_fin_linea(linea);
        if (linea[0] == '\0') {  // línea vacía
            break;
        }

        long long inicio, fin; // de rango

        // si el número de elementos leídos en línea con formato INT-INT es 2, o sea, es un rango
        if (sscanf(linea, "%lld-%lld", &inicio, &fin) == 2) {
            if (inicio <= fin) {
                rangos[n].inicio = inicio;
                rangos[n].fin = fin;
            } else {
                rangos[n].inicio = fin;
                rangos[n].fin = inicio;
            }
            n++;
        }
    }

    qsort(rangos, n, sizeof(Rango), cmp_rango);

    long long total = 0;
    long long cur_ini = rangos[0].inicio;
    long long cur_fin = rangos[0].fin;

    for (int i = 1; i < n; i++) {
        long long a = rangos[i].inicio;
        long long b = rangos[i].fin;

        if (a <= cur_fin + 1) {
            // solapa o toca -> extender intervalo actual
            if (b > cur_fin) cur_fin = b;
        } else {
            // terminar intervalo actual y sumar su longitud inclusiva
            total += (cur_fin - cur_ini + 1);
            // comenzar nuevo intervalo
            cur_ini = a;
            cur_fin = b;
        }
    }

    total += (cur_fin - cur_ini + 1);

/////////////////////////////////////////////////////////////////////////////////////////////

    printf("Contraseña: %lld\n", total);
    fclose(archivo);
    return 0;
}