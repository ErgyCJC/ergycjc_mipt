/*
    Задача 2_1
    Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1].
    Необходимо найти первую пару индексов i0 и j0, , такую что A[i0] + B[j0] = max {A[i] + B[j],
    где 0 <= i < n, 0 <= j < n, i <= j}.
    Время работы - O(n). n ≤ 100000.
*/

/*
    Сначала за один проход по массиву B будут найдены максимумы
    Потом за один проход по массиву A будет найдено i0
    Если f(n) - количество операций, выполняемых алгоритмом, то f(n) < 3*r*n,
    где r - константа, равная количеству операций, выполняемых после условного оператора
    в худшем случае для обоих проходов по массиву, т.е. f(n) = O(n)
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    int elemCount, i0 = 0, t;
    scanf("%d", &elemCount);

    int *arrayA = (int*)malloc(elemCount * sizeof(int));
    int *arrayB = (int*)malloc(elemCount * sizeof (int));
    int *jIndexes = (int*)malloc(elemCount * sizeof(int));
    // jIndexes[t] - индекс максимума в arrayB[t..size-1]

    for(t = 0; t < elemCount; ++t)
        scanf("%d", &arrayA[t]);
    for(t = 0; t < elemCount; ++t)
        scanf("%d", &arrayB[t]);

    jIndexes[elemCount - 1] = elemCount - 1;
    for(t = elemCount - 2; t >= 0; --t)
        if(arrayB[ jIndexes[t+1] ] <= arrayB[t])
            jIndexes[t] = t;
        else
            jIndexes[t] = jIndexes[t+1];

    for(t = 0; t < elemCount; ++t)
        if(arrayA[t] + arrayB[ jIndexes[t] ] > arrayA[i0] + arrayB[ jIndexes[i0] ])
            i0 = t;

    printf("%d %d", i0, jIndexes[i0]);

    free(arrayA);
    free(arrayB);
    free(jIndexes);
    return 0;
}