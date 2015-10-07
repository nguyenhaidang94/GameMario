#include "Unility.h"


Unility::Unility(void)
{
}


Unility::~Unility(void)
{
}

vector<string> Unility::Split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

eCollisionDirection Unility::GetOppositeDirection(eCollisionDirection direction)
{
	switch (direction)
	{
	case eNone:
		return eNone;
	case eTop:
		return eBottom;
	case eBottom:
		return eTop;
	case eLeft:
		return eRight;
	case eRight:
		return eLeft;
	default:
		return eNone;
	}
}