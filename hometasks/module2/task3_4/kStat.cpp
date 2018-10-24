#include "kStat.h"

KStat::KStat(std::vector<int>& keys):
buffer_(keys)
{
	srand( time(nullptr) ); // seed для rand()
}

int KStat::FindKValue(int k_index)
{
    first = 0;
    last = buffer_.size();

    int pivot_index;

    while( first < last ){

        pivot_index = Partition( ChoosePivot() );

        if( pivot_index == k_index ){
            return buffer_[pivot_index];

        } else if ( pivot_index > k_index ){
            last = pivot_index;

        } else if( pivot_index < k_index ){
            first = pivot_index + 1;
        }
    }

    return buffer_[pivot_index];
}

int KStat::Partition(int pivot_index)
{
    std::swap(buffer_[pivot_index], buffer_[last - 1]);

    // Проход двумя итераторами от конца массива к началу
    int largerIt = last-2; // индекс элемента, находящегося перед частью массива, точно большей pivot'а
    int checkIt = last-2; // Индекс текущего проверяемого элемента
    int pivot = buffer_[last - 1];

    for( ; checkIt >= first; --checkIt ){
        if( buffer_[checkIt] > buffer_[largerIt] ){
            std::swap(buffer_[checkIt], buffer_[largerIt]);
        }

        if( buffer_[largerIt] > pivot )
            --largerIt;
    }

    std::swap(buffer_[last - 1], buffer_[largerIt + 1]);
    return largerIt + 1;
}

int KStat::ChoosePivot()
{
    srand(time(nullptr));
    return first + rand() % (last - first);
}