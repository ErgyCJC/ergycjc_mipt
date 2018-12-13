#include "stringInsertSort.h"

// is line1 smaller than line2 ?
bool  StringInsertionSort::compare(std::string& line1, std::string& line2)
{
    for( int i = 0; i < line1.size() && i < line2.size(); ++i ){
        if( (int)line1[i] < (int)line2[i] ){
            return true;
        } else if( (int)line1[i] > (int)line2[i] ){
            return false;
        }
    }

    if( line1.size() < line2.size() ){
        return true;
    } else{
        return false;
    }
}

void StringInsertionSort::Sort(std::vector<std::string>& lines)
{
    for( int i = 1; i < lines.size(); ++i ){
        int index = i;
        while( index > 0 && compare( lines[index], lines[index - 1] )){
            std::swap( lines[index], lines[index - 1] );
            --index;
        }
    }
}