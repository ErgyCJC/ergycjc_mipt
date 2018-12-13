/*
    Задача 1_6
    Дан массив целых чисел A[0..n). Не используя других массивов,
    переставить элементы массива A в обратном порядке за O(n). n ≤ 10000.
*/

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int tmpValue = *a;
    *a = *b;
    *b = tmpValue;
}

void arrayReverse(int *values, int arraySize)
{
    int index, middleElem = (arraySize + 1 ) / 2;
    /*
        (arraySize + 1 ) / 2 - индекс элемента массива, начиная с которого, не требуется дальнейшая
        работа с массивом, т.к. первая половина массива уже поменялась местами со второй, т.е.
        массив "перевёрнут" обратную сторону.
        
        При нечётном количестве элементов массива middleElem принимает значение
        индекса центрального элемента;
        При чётном количестве элементов массива middleElem принимает значение
        индекса первого элемента второй половины массива.
    */
    for(index = 0; index < middleElem; ++index)
        swap(&values[index], &values[arraySize - index - 1]);
}

int main(int argc, char ** argv)
{
    int arraySize, index;
    scanf("%d", &arraySize);

    int *values = (int*)malloc(arraySize * sizeof(int));
    // values - название массива А из задания для осмысленности

    for(index = 0; index < arraySize; ++index)
        scanf("%d", &values[index]);

    arrayReverse(values, arraySize);

    for(index = 0; index < arraySize; ++index)
        printf("%d ", values[index]);

    free(values);
    return 0;
}