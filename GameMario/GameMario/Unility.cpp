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
	if(tag == "h1_1")		//hidden map of world 1_1
	{
		return eGameTag::eToHidden1_1;
	}
	if(tag == "m1_1")	//middle of ground of world 1_1
	{
		return eGameTag::eToMiddleOnGround1_1;
	}
	if(tag == "1_2")		//to main map of world 1_2
	{
		return eGameTag::eTo1_2;
	}
	if(tag == "h1_2")	//hidden map of world 1_2
	{
		return eGameTag::eToHidden1_2;
	}
	if(tag == "r1_2")	//right map of world 1_2
	{
		return eGameTag::eToRight1_2;
	}
	if(tag == "m1_2")	//middle of main map  of world 1_2
	{
		return eGameTag::eToMiddle1_2;
	}

	//no tag
	return eGameTag::eEmpty;
}

eWorldID Unility::GetWorldIDFromTag(eGameTag tag)
{
	if(tag == eGameTag::eToHidden1_1)
	{
		return eWorldID::eHidden1_1;
	}

	if(tag == eGameTag::eToMiddleOnGround1_1)
	{
		return eWorldID::e1_1;
	}

	if(tag == eGameTag::eTo1_2 || tag == eGameTag::eToMiddle1_2)
	{
		return eWorldID::e1_2;
	}

	if(tag == eGameTag::eToHidden1_2)
	{
		return eWorldID::eHidden1_2;
	}

	if(tag == eGameTag::eToRight1_2)
	{
		return eWorldID::eRight1_2;
	}
}

bool Unility::IsInSameMap(eWorldID world1, eWorldID world2)
{
	if(world1 == eWorldID::e1_1 && world2 == eWorldID::eHidden1_1 || 
		world1 == eWorldID::eHidden1_1 && world2 == eWorldID::e1_1 )
	{
		return true;
	}

	if(world1 == eWorldID::e1_2 && world2 == eWorldID::eHidden1_2 || 
		world1 == eWorldID::eHidden1_2 && world2 == eWorldID::e1_2 ||
		world1 == eWorldID::e1_2 && world2 == eWorldID::eLeft1_2 ||
		world1 == eWorldID::eLeft1_2 && world2 == eWorldID::e1_2 ||
		world1 == eWorldID::e1_2 && world2 == eWorldID::eRight1_2 ||
		world1 == eWorldID::eRight1_2 && world2 == eWorldID::e1_2)
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