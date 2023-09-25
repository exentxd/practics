#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Main function to do heap sort
void heapSort(int arr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);

        // Heapify root element to get highest element at root again
        heapify(arr, i, 0);
    }
}

void restart();
void error();

void hsort() {
    FILE* nosort;
    FILE* sort;
    int n;
    int i = 0;
    int* arr;
    label:
    system("cls");
    printf("||=============================||\n");
    printf("  Введите размер массива:");
    scanf("%d", &n);
    if (n <= 0) goto label;
    srand(time(0));
    if ((nosort = fopen("nosort.txt", "w")) == NULL) error();
    arr = (int*)malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
    for (i = 0; i < n; i++) {
        fprintf(nosort, "%d  ", arr[i]);
    }
    fclose(nosort);

    clock_t st = clock();
    heapSort(arr, n);
    clock_t end = clock();

    float sec = float(end) - float(st);
    float milsec = sec / 1000;
    if ((sort = fopen("sort.txt", "w")) == NULL) error();
    for (i = 0; i < n; i++) {
        fprintf(sort, "%d  ", arr[i]);
    }
    fclose(sort);
    free(arr);
    system("cls");
    printf("||=============================||\n");
    printf("|| Массив успешно отсортирован ||\n");
    printf("||     за %5.3f секунд         ||\n", milsec);
    printf("||     1. Сортировать заново   ||\n");
    printf("||     2. Выход                ||\n");
    printf("||=============================||\n");
    restart();
}

void error() {
    system("cls");
    printf("||=============================||\n");
    printf("||                             ||\n");
    printf("||            Error!           ||\n");
    printf("||   Не удалось открыть файл   ||\n");
    printf("||                             ||\n");
    printf("||=============================||\n");
    _Exit(0);
}

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    printf("||=============================||\n");
    printf("||           HeapSort          ||\n");
    printf("||                             ||\n");
    printf("||     1. Начать сортировку    ||\n");
    printf("||     2. Выход                ||\n");
    printf("||=============================||\n");
    label1:
    while (!_kbhit());
    switch (_getch()) {
    case 49: hsort();
        break;
    case 50: _Exit(0);
        break;
    default:
        goto label1;
    }
    return 0;
}

void restart() {
label2:
    while (!_kbhit());
    switch (_getch()) {
    case 49: hsort();
        break;
    case 50: _Exit(0);
        break;
    default:
        goto label2;
    }
}