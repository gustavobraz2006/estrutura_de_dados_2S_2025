#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 1000
int main() {
int array[ARRAY_SIZE];
srand(time(NULL)); // Inicializa o gerador de números aleatórios
for (int i = 0; i < ARRAY_SIZE; i++) array[i] = rand(); // Preenchendo o vetor
for (int i = 0; i < 10; i++) printf("%d ", array[i]);

return 0;
}
