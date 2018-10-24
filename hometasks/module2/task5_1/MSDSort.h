#ifndef __MSDSORT_HEADER__
#define __MSDSORT_HEADER__

#include <vector>
#include <string>

void MSDSort(std::vector<std::string>& lines, int left, int right, int char_index);

int index(std::string& line, int char_index);

#endif