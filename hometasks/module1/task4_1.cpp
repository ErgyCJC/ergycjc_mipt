#include <iostream>

/*
    Задача 4.1
    Реализовать очередь с динамическим зацикленным буфером.
    Обрабатывать команды push back и pop front.

    В первой строке количество команд n. n ≤ 1000000.
    Каждая команда задаётся как 2 целых числа: a b.

    a = 2 - pop front
    a = 3 - push back

    Если дана команда pop front, то число b - ожидаемое значение.
    Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.
*/

class Queue
{
private:
    int head;
    int tail;
    int realSize;
    int elementsCount;
    int *values;

    void addMemory() // Увеличение массива в два раза по размеру
    {
        int *newValues = new int[realSize * 2];

        for(int i = 0; i < elementsCount; ++i)
            newValues[i] = values[(head + i) % realSize];

        realSize *= 2;
        head = 0;
        tail = elementsCount - 1;
        
        delete[] values;
        values = newValues;
    }

    void bisectMemory() // Уменьшение массива в два раза по размеру
    {
        int *newValues = new int[realSize / 2];

        for(int i = 0; i < elementsCount; ++i)
            newValues[i] = values[(head + i) % realSize];

        head = 0;
        tail = elementsCount - 1;
        realSize /= 2;

        delete[] values;
        values = newValues;
    }

public:

    Queue()
    {
        head = tail = elementsCount = 0;
        realSize = 1;
        values = new int[realSize];
    }

    Queue(const Queue& obj) // По правилам должно быть, но задачей не предусмотрено
    {
        // You don't have to copy this kind of queue
    }

    ~Queue()
    {
        delete[] values;
    }

    void push_back(int key)
    {
        if(elementsCount < realSize)
            values[(tail + 1) % realSize] = key;
        else
        {
            addMemory();
            values[tail + 1] = key;
        }

        ++tail;
        ++elementsCount;
    }

    int pop_front()
    {
        if(isEmpty())
            return -1;

        int result = values[head];
        head = (head + 1) % realSize;
        --elementsCount;

        if(elementsCount * 2 == realSize)
            bisectMemory();

        return result;
    }

    bool isEmpty()
    {
        return elementsCount == 0;
    }
};

int main(int argc, char ** argv)
{
    int a, b, count;
    bool isOk = true;
    
    Queue queue;
    
    std::cin >> count;
    
    for(int i = 0; i < count; ++i)
    {
        std::cin >> a >> b;
        if(a == 3)
            queue.push_back(b);
        else if(a == 2 && queue.pop_front() != b)
            isOk = false;
    }   

    if(isOk)
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}