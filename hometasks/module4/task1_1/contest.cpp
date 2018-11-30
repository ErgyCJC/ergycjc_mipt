// Задача 1.1
// Contest link: https://contest.yandex.ru/contest/6512/problems/1/
//
// Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
// Хранимые строки непустые и состоят из строчных латинских букв. Хеш-функция строки должна быть реализована с помощью
// вычисления значения многочлена методом Горнера. Начальный размер таблицы должен быть равным 8-ми.
// Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
// Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки
// принадлежности данной строки множеству. 1_1. Для разрешения коллизий используйте квадратичное пробирование.
// i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
//
// Каждая строка входных данных задает одну операцию над множеством.
// Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.
// Тип операции – один из трех символов:
// 	+ означает добавление данной строки в множество;
// 	- означает удаление строки из множества;
// 	? означает проверку принадлежности данной строки множеству.
// При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве.
// При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
//
// Программа должна вывести для каждой операции одну из двух строк OK или FAIL,
// в зависимости от того, встречается ли данное слово в нашем множестве.

#include <iostream>
#include <string>
#include <vector>

// Структура, для хранения ключа в хеш-таблице и индикатора его "удалённости" из неё
struct Node
{
    std::string line;
    bool deleted;

    Node( std::string line_, bool deleted_ ): line( line_ ), deleted( deleted_ ) {}
};

// Хеш-таблица для std::string
class HashTable
{
public:
	HashTable( int size_ = 8 )
	{
		size = size_;
		elements_count = 0;
		table = new std::vector< Node* >( size, nullptr );
	}

	~HashTable()
	{
		for( int i = 0; i < table->size(); i++ ){
			if( table->at(i) != nullptr ){ // Удаление всех непустых нод
				delete table->at(i);
			}
		}

		delete table; // Удаление самой "таблицы"
	}

	bool Push( std::string& line )
	{
		if( isLoadFactorCritical() ){ // Увеличиваем размер в 2 раза, если заполненность таблицы больше 3/4
			RebuildTable();
		}

		int index = Hash( line, size );
		int attempt = 0;
		int	insert_index = -1;

		// Перебираем позиции в таблице, пока не будет найдена пустая нода или не будут пройдены все ноды в таблице
		while( table->at(index) != nullptr && attempt < size ){
			
			// Уже существует ключ line, который не удалён
			if( table->at(index)->line == line && !table->at(index)->deleted ){
				return false;
			}

			// Найдена подходящая нода с пометкой deleted, запоминаем её в insert_index
			// Если потом не будет найдено дубликата ключа line, то вставка будет по insert_index
			if( table->at(index)->deleted && insert_index == -1){
				insert_index = index;
			}

			++attempt;
			index = ( index + attempt ) % size; // Квадратичная проба
		}

		// Если была найдена пустая нода, но не найден идущих перед ней deleted-нод
		if( insert_index != -1 ){
			table->at(insert_index)->line = line;
			table->at(insert_index)->deleted = false;
		}
		// Была найдена подходящая deleted-нода и не найдено дубликатов ключа line
		else
		{
			table->at(index) = new Node( line, false );
		}

		elements_count++;
		return true;
	}

	bool Remove( std::string& line )
	{
		int attempt = 0;
		int index = Hash( line, size );

		while( table->at(index) != nullptr && attempt < size ){
			
			if( table->at(index)->line == line && !table->at(index)->deleted ){
				table->at(index)->deleted = true;
				--elements_count;
				return true;
			}

			++attempt;
			index = ( index + attempt ) % size;
		}

		return false;
	}

	bool Find( std::string& line )
	{
		int attempt = 0;
		int index = Hash( line, size );

		while( table->at(index) != nullptr && attempt < size ){

			if( table->at(index)->line == line && !table->at(index)->deleted ){
				return true;
			}

			++attempt;
			index = ( index + attempt ) % size;
		}

		return false;
	}

private:
	std::vector< Node* >* table;
	int size;
	int elements_count;

	// ЗАполнена ли таблица больше, чем на 3/4
	bool isLoadFactorCritical()
	{
		return 4 * elements_count >= 3 * size;
	}

	int Hash( std::string& line, int m )
	{
		int hash = 0;

		for( int i = 0; i < line.size(); ++i ){
			hash = ( hash * 13 +  line[i] * 257 ) % m;
		}

		return hash;
	}
	
	// Создаётся новая таблица, в неё вставляются все существующие не-deleted ключи
	// Старая таблица удаляется
	// Новая запоминается в table
	void RebuildTable()
	{
		elements_count = 0;
		int old_size = size;
		size *= 2;

		std::vector< Node* >* old_table = table;
		table = new std::vector< Node* >( size, nullptr );

		for( int i = 0; i < old_size; ++i ){
			if( old_table->at(i) != nullptr && !old_table->at(i)->deleted ){
				Push( old_table->at(i)->line );
				delete old_table->at(i);
			}
			else if( old_table->at(i) != nullptr ){
				delete old_table->at(i);
			}
		}

		delete old_table;
	}
};

//====================//====================//====================//====================//

int main( int argc, char** argv ) 
{
	HashTable set;
	char command;
	std::string line;

	while( std::cin >> command)
	{
		std::cin >> line;
		
		if( command == '+' ){
			std::cout << ( set.Push( line ) ? "OK" : "FAIL" ) << "\n";
		}
		else if( command == '-' ){
			std::cout << ( set.Remove( line ) ? "OK" : "FAIL" ) << "\n";
		}
		else if( command == '?' ){
			std::cout << ( set.Find( line ) ? "OK" : "FAIL" ) << "\n";
		}
	}

	return 0;
}