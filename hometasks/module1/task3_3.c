/*
    Задача 3_3 
    Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.
    A[0..n-1] и B[0..m-1]. n » m. Найдите их пересечение.
    Требуемое время работы: O(m * log k), где k - позиция элементта B[m-1] в массиве A.
    В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска
    элемента B[i-1].
    n, k ≤ 10000.
*/

#include <stdlib.h>
#include <stdio.h>

int search(int* array, int left, int size, int key)
{
    int addition = 1;
    int right = left;
    
    while(right + addition < size && array[right] <= key)
    {
        left = right;
        right += addition;
        addition *= 2;
    }

    if(right + addition >= size && array[right] <= key)
    {
        left = right;
        right = size - 1;
    }

    if(right - left <= 1)
    {
        if(array[left] == key)
            return left;
        else if(array[right] == key)
            return right;
        else
            return -1;
    }
    else
        return search(array, left, right + 1, key);
}


int main(int argc, char ** argv)
{
    int n, m, t, lowerBorder = 0, index, value;
    scanf("%d %d", &n, &m);

    int *arrayA = (int*)malloc(n * sizeof(int));

    for(t = 0; t < n; ++t)
        scanf("%d", &arrayA[t]);
    
    for(t = 0; t < m; ++t)
    {
        scanf("%d", &value);
        index = search(arrayA, lowerBorder, n, value);

        if(index != -1)
        {
            printf("%d ", value);
            lowerBorder = index + 1;
        }
    }

    free(arrayA);
    return 0;
}