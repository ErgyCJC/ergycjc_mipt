#include "MSDSort.h"

// Если символа на запрашиваемой позиции char_index нет, то он принимается за '\0'
int index(std::string& line, int char_index)
{
	return line.size() > char_index ? line[char_index] : 0;
}

void MSDSort(std::vector<std::string>& lines, int left, int right, int char_index)
{
	if( right - left <= 1 ){ // Если в принимаемой на вход части массива всего одна строка
		return;
	}

	std::vector<int> count(256, 0); // count хранит количество строк с соответствующим символом на позиции char_index

	for( int i = left; i < right; ++i ){ // Подсчёт строк
		++count[ index(lines[i], char_index) + 1 ];
	}

	// Количества преобразуются в индексы первых элементов отсортированных по char_index позиции строк
	for( int i = 1; i < 256; ++i ){
		count[i] += count[i - 1];
	}

	// Буфер упорядоченных по char_index позиции строк
	std::vector<std::string> buffer(right - left);

	for( int i = left; i < right; ++i ){
		buffer[ count[ index(lines[i], char_index) ]++ ] = lines[i];
	}

	for( int i = left; i < right; ++i ){
		lines[i] = buffer[i - left];
	}

	// Рекурсивный запуск MSDSort для следующих неотсортированных блоков строк
	for( int i = 1; i < 255; ++i ){
		MSDSort(lines, left + count[i], left + count[i + 1], char_index + 1);
	}
}