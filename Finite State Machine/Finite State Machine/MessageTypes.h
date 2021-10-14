#pragma once
#include <string>

enum message_type
{
	Msg_HiImHome, Msg_CookingFinished, Msg_GoToWork
};

inline std::string MsgToStr(int msg)
{
	switch (msg)
	{
	case Msg_HiImHome:
		return "HiImHome";
	case Msg_CookingFinished:
		return "CookingFinished";
	case Msg_GoToWork:
		return "GoToWork";
	default:
		return "Not recognized!";
	}
}