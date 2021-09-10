#pragma once

#include <iostream>

using namespace std;

int maxElement(int* arr, int n){
    int a = -999999999;
    for (int i = 0; i < n; i++){
        if (arr[i] > a){
            a = arr[i];
        }
    }
    return a;
}

int minElement(int* arr, int n){
    int a = 999999999;
    for (int i = 0; i < n; i++){
        if (arr[i] < a){
            a = arr[i];
        }
    }
    return a;
}

void printArr(int *arr, int n){
    for (int i = 0 ; i < n; i++){
        cout << i << ": " << arr[i] << "\n";
    }
    cout << endl;
}

// funciona con los negativos, no es el algoritmo principal
void countingSortModified(int *arr, int n){
    int max = maxElement(arr, n);
    int min = minElement(arr, n);
    int range = max - min + 1;

    int *output = new int[n];
    int *count = new int[range];

    // Se llena el count y el output de espacios
    for (int i = 0; i < range; i++){
        count[i] = 0;
    }
    for (int i = 0; i < n; i++){
        output[i] = 0;
    }

    // Se escribe cuantos elementos del indice i existen en el array u se guarda la cantidad en count
    for (int i = 0; i < n; i++) {
        count[arr[i] - min]++;
    }

    // Se agrega la cuenta que hay en el indice anterior hasta le final
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    // Se compara el array con el count y se escriben los elementos en el indice indicado de output
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// algortimo principal
void countingSort(int *arr, int n) {
    int max = maxElement(arr, n);
    int *count = new int[max + 1];
    int *output = new int[n];

    for (int i = 0; i < max + 1; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        ++count[arr[i]];
    }


    for (int i = 1; i <= max; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = 0; i < n; ++i) {
        output[count[arr[i]] - 1] = arr[i];
        --count[arr[i]];
    }

    for (int i = 0; i < n; ++i){
        arr[i] = output[i];
    }
}
