/*
    Задача 6_1

    Вовочка ест фрукты из бабушкиной корзины.
    В корзине лежат фрукты разной массы.
    Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм.
    За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно,
    откусывает от каждого половину и кладет огрызки обратно в корзину.
    Если фрукт весит нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.

    Определить за сколько подходов Вовочка съест все фрукты в корзине.
    Вначале вводится n - количество фруктов и n строк с массами фруктов. n ≤ 50000.
    Затем K - "грузоподъемность". K ≤ 1000.
    
    Вывод: Неотрицательное число - количество подходов к корзине.
*/

#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

class Heap
{
public:
    Heap(): buffer_size(1), size(0)
    {
        buffer = new int[buffer_size];
    }

    ~Heap()
    {
        delete[] buffer;
    }

    void add(int key){
        if(size == buffer_size)
        {
            int *tmp_buffer = new int[buffer_size * 2];
            
            for(int i = 0; i < size; ++i)
                tmp_buffer[i] = buffer[i];

            buffer_size *= 2;
            delete[] buffer;
            buffer = tmp_buffer;
        }

        buffer[size] = key;
        ++size;
        siftUp(size - 1);
    }

    void SpAdd(int key){
        if(size == buffer_size)
        {
            int *tmp_buffer = new int[buffer_size * 2];
            
            for(int i = 0; i < size; ++i)
                tmp_buffer[i] = buffer[i];

            buffer_size *= 2;
            delete[] buffer;
            buffer = tmp_buffer;
        }

        buffer[size] = key;
        ++size;
    }

    int extractTop()
    {
        int result = buffer[0];
        buffer[0] = buffer[size - 1];
        --size;

        if(size * 2 == buffer_size)
        {
            int *tmp_buffer = new int[size];
            
            for(int i = 0; i < size; ++i)
                tmp_buffer[i] = buffer[i];

            buffer_size = size;
            delete[] buffer;
            buffer = tmp_buffer;
        }
        
        siftDown(0);
        return result;
    }

    int SpExtractTop()
    {
        int result = buffer[0];
        buffer[0] = buffer[size - 1];
        --size;

        if(size * 2 == buffer_size)
        {
            int *tmp_buffer = new int[size];
            
            for(int i = 0; i < size; ++i)
                tmp_buffer[i] = buffer[i];

            buffer_size = size;
            delete[] buffer;
            buffer = tmp_buffer;
        }
        return result;
    }

    int getTop()
    {
        return buffer[0];
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void print()
    {
        for(int i =0 ; i < size; ++i)
        cout << buffer[i] << " ";
        cout << endl;
    }

private:
    int *buffer;
    int buffer_size;
    int size;

    void siftUp(int index)
    {
        while(index != 0 && buffer[index] > buffer[(index - 1)/2])
        {
            int tmp_value = buffer[index];
            buffer[index] = buffer[(index - 1) / 2];
            buffer[(index - 1) / 2] = tmp_value;

            index = (index - 1) / 2;
        }
    }

    void siftDown(int index)
    {
        while(index < size)
        {
            int largest = index;
            if(index * 2 + 1 < size && buffer[index * 2 + 1] > buffer[largest])
                largest = index * 2 + 1;
            if(index * 2 + 2 < size && buffer[index * 2 + 2] > buffer[largest])
                largest = index * 2 + 2;

            if(largest != index)
                std::swap(buffer[index], buffer[largest]);
            else
                return;

            index = largest;
        }
    }
};

int main(){
    int count, max_weight, tmp_weight, steps = 0;

    Heap heap;
    Heap tmp;

    cin >> count;
    for(int i = 0; i < count; ++i)
    {
        cin >> tmp_weight;
        heap.add(tmp_weight);
    }
    cin >> max_weight;

    while(!heap.isEmpty()){
        tmp_weight = 0;

        while(!heap.isEmpty() && tmp_weight + heap.getTop() <= max_weight)
        {
            tmp_weight += heap.getTop();
            tmp.SpAdd(heap.extractTop() / 2);
        }

        while(!tmp.isEmpty())
        {
            int tmp_weight = tmp.SpExtractTop();
            if(tmp_weight != 0)
                heap.add(tmp_weight);
        }
        steps++;
    }

    cout << steps;
    return 0;
}