#include "cHeapSort.h"
#include <cstdlib>

CHeapSort::CHeapSort(std::vector<CSection>& keys):
buffer_(keys)
{
    heap_size_ = buffer_.size();
}

void CHeapSort::SiftUp(int index)
{
    while( buffer_[index] > buffer_[(index - 1) / 2] ){
        std::swap(buffer_[index], buffer_[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void CHeapSort::SiftDown(int index)
{
    while( index * 2 + 1 < heap_size_ ){

        int left_child = index * 2 + 1;
        int right_child = index * 2 + 2;
        int largest = left_child;

        if( right_child < heap_size_ && buffer_[right_child] > buffer_[left_child] )
            largest = right_child;

        if( buffer_[index] >= buffer_[largest] )
            break;

        std::swap(buffer_[index], buffer_[largest]);

        index = largest;
    }
}

void CHeapSort::Sort()
{
    heap_size_ = buffer_.size();

    Build(); // Создание кучи

    while( heap_size_ > 0 ){ // Выбор максимального элемента кучи и его перемещение в начало отсортированной части массива
        --heap_size_;
        std::swap(buffer_[0], buffer_[heap_size_]);
        SiftDown(0);
    }
}

void CHeapSort::Build() // Создание кучи на переданном сортировке массиве
{
    for( int index = heap_size_ / 2 - 1; index >= 0; --index ){
        SiftDown(index);
    }
}