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
		return "����";
	case ent_Sam:
		return "��";
	case ent_Eris:
		return "������";
	default:
		return "UNKNOWN!";
	}
}