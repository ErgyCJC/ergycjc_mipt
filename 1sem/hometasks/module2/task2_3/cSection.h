#ifndef __CSECTION_HEADER__
#define __CSECTION_HEADER__

struct CSection
{
	CSection(int left_border_, int right_border_);

    int left_border;
    int right_border;

    bool operator> (CSection& obj) const;
    bool operator>= (CSection& obj) const;
};

#endif