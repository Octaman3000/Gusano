#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Para usar sleep()
#include <string.h>

#define TIEMPO_TOTAL 600  // 10 minutos = 600 segundos

// Función para obtener el tiempo restante desde el archivo
int get_remaining_time() {
    FILE *file = fopen("time_counter.txt", "r");
    int remaining_time = TIEMPO_TOTAL;

    // Si el archivo existe, leer el tiempo restante desde el archivo
    if (file) {
        fscanf(file, "%d", &remaining_time);
        fclose(file);
    }

    return remaining_time;
}

// Función para guardar el tiempo restante en el archivo
void save_remaining_time(int remaining_time) {
    FILE *file = fopen("time_counter.txt", "w");
    if (file) {
        fprintf(file, "%d", remaining_time);
        fclose(file);
    }
}

// Función que maneja la replicación del gusano
void replicate() {
    int remaining_time = get_remaining_time();

    // Al replicarse, el gusano hijo recibe el tiempo restante
    printf("Replicando gusano con tiempo restante: %d segundos.\n", remaining_time);

    // Guardar el tiempo restante para el gusano hijo
    save_remaining_time(remaining_time);
}

// Función principal donde ocurre la ejecución del gusano
int main() {
    int remaining_time = get_remaining_time();

    // El gusano madre cuenta los segundos hasta que se replique
    while (remaining_time > 0) {
        printf("Tiempo restante: %d segundos.\n", remaining_time);
        sleep(1);  // Esperar 1 segundo
        remaining_time--;  // Decrementar el tiempo
        save_remaining_time(remaining_time);  // Guardar el tiempo restante

        // Si el tiempo se agotó, replicarse
        if (remaining_time <= 0) {
            printf("Tiempo agotado. Replicándose...\n");
            replicate();  // Crear un hijo
            break;  // El gusano madre deja de ejecutar después de la replicación
        }
    }

    return 0;
}