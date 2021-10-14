#pragma once
#include <string>

enum
{
	ent_Jeff, ent_Sam, ent_Eris
};

inline std::string GetNameOfEntity(int n)
{
	switch (n)
	{
	case ent_Jeff:
		return "제프";
	case ent_Sam:
		return "샘";
	case ent_Eris:
		return "에리스";
	default:
		return "UNKNOWN!";
	}
}