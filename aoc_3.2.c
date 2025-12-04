#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long sum_jolts = 0;

#define NUM_DIGITOS 12

int buscar_jolts_banco(char* linea) {

    int N = strlen(linea); // obtener longitud de línea
    if (N > 0 && linea[N-1] == '\n') {
        N--;
    }

    if (N < NUM_DIGITOS) {
        return 0;
    }

    long long id_banco = 0;
    int ini = 0;
    
    for (int k = 0; k < NUM_DIGITOS; k++) {
        
        int resto = NUM_DIGITOS - (k + 1); // si fuese 1234, seria 12-1+1=12, 12-2+1=11, 12-3+1=10, 12-4+1=9....
        int limite_busc = N - resto - 1;
        
        int max_digito = -1;
        int mejor_indice = -1;

        for (int j = ini; j <= limite_busc; j++) { // busca dígito más grande después del anterior
            
            if (linea[j] >= '0' && linea[j] <= '9') {
                int digito_actual = linea[j] - '0';
                
                if (digito_actual > max_digito) {
                    max_digito = digito_actual;
                    mejor_indice = j;
                    if (max_digito == 9) {
                        break; 
                    }
                }
            }
        }
        
        id_banco = id_banco * 10 + max_digito;
        
        ini = mejor_indice + 1;
    }

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

    printf("Contraseña: %lld\n", sum_jolts);
    fclose(archivo);
    return 0;
}