// Задача A

// Contest link: https://contest.yandex.ru/contest/12173/problems/A

// Требуется отыскать самый короткий маршрут между городами. Из города может выходить дорога, которая возвращается в этот же город.
// Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
// N <= 10000, M <= 250000.
// Длина каждой дороги <= 10000.

// Первая строка содержит число N – количество городов.
// Вторая строка содержит число M - количество дорог.
// Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
// Все указанные дороги двусторонние. Между любыми двумя городами может быть больше одной дороги.
// Последняя строка содержит маршрут (откуда и куда нужно доехать).
// Вывести длину самого короткого маршрута.

#include <vector>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <utility>

//============================//============================//============================//

template <class T>
class BinHeap {
public:
    BinHeap();

    ~BinHeap();

    BinHeap(const BinHeap& heap_obj);

    BinHeap& operator=(const BinHeap& heap_obj);

    void Add(T key);

    T PopTop();

    T& GetTop();

    bool Empty() const;

private:
    T *buffer;
    int buffer_size;
    int size;

    void SiftUp(int index);

    void SiftDown(int index);
};

template <class T>
BinHeap<T>::BinHeap() : buffer_size(1), size(0) {
    buffer = new T[buffer_size];
}

template <class T>
BinHeap<T>::~BinHeap() {
    delete[] buffer;
}

template <class T>
BinHeap<T>::BinHeap(const BinHeap& heap_obj) {
    size = heap_obj.size;
    buffer_size = heap_obj.buffer_size;

    buffer = new T[buffer_size];
    for (int i = 0; i < size; ++i) {
        buffer[i] = heap_obj.buffer[i];
    }
}

template <class T>
BinHeap<T>& BinHeap<T>::operator=(const BinHeap& heap_obj) {
    size = heap_obj.size;
    buffer_size = heap_obj.buffer_size;

    buffer = new T[buffer_size];
    for (int i = 0; i < size; ++i) {
        buffer[i] = heap_obj.buffer[i];
    }

    return *this;
}

template <class T>
void BinHeap<T>::Add(T key){
    if (size == buffer_size) {
        T *tmp_buffer = new T[buffer_size * 2];
        
        for (int i = 0; i < size; ++i) {
            tmp_buffer[i] = buffer[i];
        }

        buffer_size *= 2;
        delete[] buffer;
        buffer = tmp_buffer;
    }

    buffer[size] = key;
    ++size;
    SiftUp(size - 1);
}

template <class T>
T BinHeap<T>::PopTop() {
    T result = buffer[0];
    buffer[0] = buffer[size - 1];
    --size;

    if (size * 2 == buffer_size) {
        T *tmp_buffer = new T[size];
        
        for (int i = 0; i < size; ++i) {
            tmp_buffer[i] = buffer[i];
        }

        buffer_size = size;
        delete[] buffer;
        buffer = tmp_buffer;
    }
    
    SiftDown(0);
    return result;
}

template <class T>
T& BinHeap<T>::GetTop() {
    return buffer[0];
}

template <class T>
bool BinHeap<T>::Empty() const {
    return size == 0;
}

template <class T>
void BinHeap<T>::SiftUp(int index) {
    while (index != 0 && buffer[index] > buffer[(index - 1) / 2]) {
        std::swap(buffer[index], buffer[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

template <class T>
void BinHeap<T>::SiftDown(int index) {
    while (index < size) {
        int largest = index;

        if (index * 2 + 1 < size && buffer[index * 2 + 1] > buffer[largest]) {
            largest = index * 2 + 1;
        }
        if (index * 2 + 2 < size && buffer[index * 2 + 2] > buffer[largest]) {
            largest = index * 2 + 2;
        }

        if (largest != index) {
            std::swap(buffer[index], buffer[largest]);
        }
        else {
            break;
        }

        index = largest;
    }
}

//============================//============================//============================//

class ListGraph {
public:
    ListGraph(int _v_count);

    void Add(int from_v, int to_v, int weight);

    int MinRouteLength(int from_v, int to_v);

    int Size() const;

    void GetConnections(int v, std::vector<std::pair<int, int>>& result);

private:
    std::vector< std::vector< std::pair<int, int> > > edges;
};

ListGraph::ListGraph(int _v_count) {
    edges.resize(_v_count);
}

void ListGraph::GetConnections(int v, std::vector<std::pair<int, int>>& result) {
    result = edges[v];
}

void ListGraph::Add(int from_v, int to_v, int weight) {
    edges[from_v].push_back(std::make_pair(to_v, weight));
}

int ListGraph::MinRouteLength(int from_v, int to_v) {
    // Dijkstra's algorithm on binary heap
    // Here pairs usage (first, second): first - destination vertex, second - edge weight

    std::vector<int> distance(Size(), INT_MAX);
    distance[from_v] = 0;
        
    BinHeap<std::pair<int, int>> heap;
    heap.Add(std::make_pair(from_v, distance[from_v]));
    
    while (!heap.Empty()) {
        std::pair<int, int> current_e = heap.PopTop();

        if (current_e.second > distance[current_e.first]) {
            continue;
        }

        std::vector< std::pair<int, int> > incident_edges;
        GetConnections(current_e.first, incident_edges);
        
        for (auto e : incident_edges) {
            int v = current_e.first, next_v = e.first, next_weight = e.second;
            
            if (distance[v] + next_weight < distance[next_v]) {
                distance[next_v] = distance[v] + next_weight;
                heap.Add(std::make_pair(next_v, distance[next_v]));
            }
        }
    }

    return distance[to_v];
}

int ListGraph::Size() const{
    return static_cast<int>(edges.size());
}

//============================//============================//============================//

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);

    int vertices_count, edges_count, from_v, to_v, weight;
    std::cin >> vertices_count >> edges_count;

    ListGraph graph(vertices_count);

    for (int i = 0; i < edges_count; ++i) {
        std::cin >> from_v >> to_v >> weight;
        graph.Add(from_v, to_v, weight);
        graph.Add(to_v, from_v, weight);
    }

    std::cin >> from_v >> to_v;
    std::cout << graph.MinRouteLength(from_v, to_v) << std::endl;

    return 0;
}