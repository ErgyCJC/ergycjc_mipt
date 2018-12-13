// Задача 4.1
// Contest link: https://contest.yandex.ru/contest/10866/problems/4_1/
//
// Дано невзвешенное дерево. Расстоянием между двумя вершинами будем называть количество ребер в пути,
// соединяющем эти две вершины. Для каждой вершины определите расстояние до самой удаленной от нее вершины.
//
// В первой строке записано количество вершин n <= 10000. Затем следует n - 1 строка, описывающая ребра дерева.
// Каждое ребро - это два различных целых числа - индексы вершин в диапазоне [0, n-1].
// Индекс корня – 0. В каждом ребре родительской вершиной является та, чей номер меньше.
//
// Выход должен содержать n строк. В i-ой строке выводится расстояние от i-ой вершины до самой удаленной от нее.

#include <vector>
#include <iostream>
#include <stack>
#include <cmath>
#include <cstdlib>

class Graph
{
public:
	Graph( int count );

	// Добавление ребра между двумя вершинами
	void add( int index1, int index2 );

	// Конечно, нежелательно выводить данные методом класса
	// Но очень хочется, поэтому передаётся объект потока вывода
	void putOutDistances( std::ostream& out_stream );

private:
	// Матрица смежности
	std::vector< std::vector<int> > connections;

	std::vector<int> heights; // Глубина поддеревьев с заданой вершиной
	std::vector<int> rootWays; // Путь через корень поддерева
	std::vector<int> parents; // Индексы родительских вершин

	void setHeights( int index ); // Просчитать глубины поддеревьев

	void setRootWays( int index ); // Просчитать пути через корни поддеревьев
};

//========================//========================//========================//========================//

Graph::Graph( int count )
{
	connections.resize( count );
	
	heights.resize( count, 0 );
	rootWays.resize( count, 0 );
	parents.resize( count, -1 );
}

void Graph::add( int index1, int index2 )
{
	// Создание ребра
	connections[index1].push_back( index2 );
	connections[index2].push_back( index1 );

	// Добавление информации о родителе
	parents[index2] = index1;	
}

void Graph::putOutDistances( std::ostream& out_stream )
{
	setHeights( 0 ); // Начинаем обход с корня дерева
	setRootWays( 0 ); // Начинаем обход с корня дерева

	// Выводим максимальные расстояния
	for( int i = 0; i < connections.size(); ++i ){
		out_stream << std::max( rootWays[i], heights[i] ) << "\n";
	}
}

void Graph::setHeights( int index )
{
	// DFS
	for( int i = 0; i < connections[index].size(); ++i ){
		if( connections[index][i] != parents[index] ){  // Не закольцовываемся на родительскую вершину
			setHeights( connections[index][i] );

			if( heights[ connections[index][i] ] + 1 > heights[index] ){
				heights[index] = heights[ connections[index][i] ] + 1;
			}
		}
	}
}

void Graph::setRootWays( int index )
{
	// Информация о двух наиболее глубоких поддеревьях
	int maxSubHeight1 = -1, maxSubIndex1;
    int maxSubHeight2 = -1, maxSubIndex2;

	// Поиск двух наиболле глубоких поддерева
    for( int i = 0; i < connections[index].size(); ++i ){
		int current_index = connections[index][i];

        if( current_index != parents[index] ){ // Не закольцовываемся на родительскую вершину
			if( maxSubHeight1 <= heights[current_index] + 1 ){
				maxSubIndex2 = maxSubIndex1;
				maxSubHeight2 = maxSubHeight1;
				
				maxSubIndex1 = current_index;
				maxSubHeight1 = heights[current_index] + 1;
			}
			else if( maxSubHeight2 <= heights[current_index] + 1 ){
				maxSubHeight2 = heights[current_index] + 1;
				maxSubIndex2 = current_index;
			}
		}
    }

	// DFS
    for( int i = 0; i < connections[index].size(); ++i ){
		int next_index = connections[index][i];

		if( next_index != parents[index] ){  // Не закольцовываемся на родительскую вершину
			if (next_index == maxSubIndex1) {
				rootWays[next_index] = std::max(rootWays[index], maxSubHeight2) + 1;
			} else {
				rootWays[next_index] = std::max(rootWays[index], maxSubHeight1) + 1;
			}

			setRootWays( next_index );
		}
    }
}

//========================//========================//========================//========================//

int main( int argc, char** argv )
{
	int count, index1, index2;
	std::cin >> count;

	Graph tree( count );
	for( int i = 0; i < count - 1; ++i ){
		std::cin >> index1 >> index2;
		tree.add( index1, index2 );
	}

	tree.putOutDistances( std::cout );
	return 0;
}