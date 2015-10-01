#pragma once
#include <vector>
#include <string.h>
#include <sstream>
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
};

