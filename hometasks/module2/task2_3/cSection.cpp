#include "cSection.h"

CSection::CSection(int left_border_, int right_border_):
	left_border(left_border_), right_border(right_border_) {}

bool CSection::operator>(CSection& obj) const
{
    return left_border > obj.left_border;
}

bool CSection::operator>=(CSection& obj) const
{
    return left_border >= obj.left_border;
}