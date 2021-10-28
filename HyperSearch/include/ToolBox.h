#pragma once
#include <regex>
#include <string>

using namespace std;

namespace ToolBox
{

	//字符串裁剪
	inline std::string CutString(const std::string& Str, const char* Start, const char* End)
	{
		if (Start)
		{
			int StartPos = Str.find(Start);
			if (StartPos != Str.npos)
			{
				return CutString(Str.substr(strlen(Start)), nullptr, End);
			}
		}
		else if (End)
		{
			int EndPos = Str.find(End);
			if (EndPos != Str.npos)
			{
				return Str.substr(0, EndPos);
			}
		}
		return Str;
	}

}