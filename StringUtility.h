#pragma once
#include <string>

//文字コードユーティリティ
namespace StringUtility
{
	//stringをwstringに変換すること
	std::wstring ConvertString(const std::string& str);

	//wstringをstringに変換する
	std::string ConvertString(const std::wstring& str);
};