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

eGameTag Unility::GetGameTag(string tag)
{
	if(tag == "-1")
	{
		return eGameTag::eEmpty;
	}
	//world tag
	if(tag == "u1_1")		//underground of world 1_1
	{
		return eGameTag::eToUnderground1_1;
	}
	if(tag == "m1_1")
	{
		return eGameTag::eToMiddleOnGround1_1;
	}

	//item tag
	if(tag == "mushroom")
	{
		return eGameTag::eStoreMushroom;
	}

	if(tag == "coin")
	{
		return eGameTag::eStoreCoin;
	}

	if(tag == "1up")
	{
		return eGameTag::eStore1Up;
	}

	if(tag == "star")
	{
		return eGameTag::eStoreStar;
	}

	//no tag
	return eGameTag::eEmpty;
}

eWorldID Unility::GetWorldIDFromTag(eGameTag tag)
{
	if(tag == eGameTag::eToUnderground1_1)
	{
		return eWorldID::eUnderground1_1;
	}

	if(tag == eGameTag::eToMiddleOnGround1_1)
	{
		return eWorldID::e1_1;
	}
}

bool Unility::IsInSameMap(eWorldID world1, eWorldID world2)
{
	if(world1 == eWorldID::e1_1 && world2 == eWorldID::eUnderground1_1 || 
		world1 == eWorldID::eUnderground1_1 && world2 == eWorldID::e1_1 )
	{
		return true;
	}

	return false;
}

string Unility::IntToFixedLengthString(int value, int digits) {
    int uvalue = value;
    if (value < 0) {
        uvalue = -uvalue;
    }
    string result;
    while (digits-- > 0) {
        result += ('0' + uvalue % 10);
        uvalue /= 10;
    }
    if (value < 0) {
        result += '-';
    }
    reverse(result.begin(), result.end());
    return result;
}