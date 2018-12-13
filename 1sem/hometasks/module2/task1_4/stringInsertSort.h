#include <vector>
#include <string>
#include <cstdlib>

class StringInsertionSort
{
public:
    void Sort(std::vector<std::string>& lines); // Сортировка вставками, принимающая ссылку на вектор строк

private:
    bool compare(std::string& line1, std::string& line2); // Функция сравнения строк по лексико-графическому закону
};