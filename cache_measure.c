#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MIN_ELEMENT 256  // Since int is 4 byte, so the minimum number of element is 256
#define SIZE_ORDER 17  // Array size is from 1KB to 64MB
#define INIT_STRIDE 8
#define AVERAGE 10
unsigned int numOperation = 1 << 25;

int MeasureTime(int n, int s);
int CalculateOneRound(int n, int s);

int CalculateOneRound(int n, int s) {
    int i;
    unsigned long long interval;
    LARGE_INTEGER frequency, begin, end;
    int *arr = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++) {
        arr[i] = 0;
    }
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&begin);
    for (i = 0; i < numOperation; i++) {
        arr[(i * s) & (n - 1)] += 1;
    }
    QueryPerformanceCounter(&end);
    interval = (end.QuadPart - begin.QuadPart) * 1000000 / frequency.QuadPart;
    free(arr);
    return (int)interval;
}

int MeasureTime(int n, int s) {
    int i, cur = 0, total = 0;
    for (i = 0; i < AVERAGE; i++) {
        cur = CalculateOneRound(n, s);
        total += cur / 10;
    }
    return total;
}

int main() {
    int i, cost, j;
    FILE *fp1 = fopen("Data.txt", "w");
    for (j = 0; j < 5; j++) {
        int stride = INIT_STRIDE << j;
        for (i = 0; i < SIZE_ORDER; i++) {
            int arraySize = MIN_ELEMENT * (1 << i);
            cost = MeasureTime(arraySize, stride);
            fprintf(fp1, "%d,%d,%d\n", i, stride, cost);
        }
    }
    fclose(fp1);
    printf("Successfully ouput the data!\n");
    return 0;
}
