#pragma once
#include <string>

// in the spirit of utf8everywhere.org, these utility functions implement
// common string conversions

// std::string is always assumed to be utf-8 encoded
// std::wstring is always assumed to be utf-16 encoded
// convert to utf-16 immediately before calling the windows API

// wstring.c_str() can be used wherever a LPCWSTR is expected

std::wstring widen(std::string);

std::string narrow(std::wstring);
