#include <stdio.h>
#include <time.h>
int main() {
clock_t start_time, end_time;
double cpu_time_used;
start_time = clock(); // Captura o tempo de início
// Seu código ou trecho de código a ser medido
end_time = clock(); // Captura o tempo de término
cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
printf("Tempo de CPU usado: %f segundos\n", cpu_time_used);
}
