#pragma once
#include <vector>
#include <string.h>
#include <sstream>
#include "GlobalVariables.h"
using namespace std;

static class Unility
{
public:
	Unility(void);
	~Unility(void);
	/// <summary>
    /// Split a string with delim charater
    /// </summary>
    /// <param name="s">string need to be splited</param>
	/// <param name="s">Character to split the string</param>
    /// <returns></returns>
	static vector<string> Split(const string &s, char delim);

	//Get opposite collision direction of given direction
	static eCollisionDirection GetOppositeDirection(eCollisionDirection direction);

	//Get enum eGameTag from tag generate by map editor
	static eGameTag GetGameTag(string tag);

	//Get enum eWorldID from eGameTag
	static eWorldID GetWorldIDFromTag(eGameTag tag);

	//Check if 2 worldID in same map
	static bool IsInSameMap(eWorldID world1, eWorldID world2);
};

