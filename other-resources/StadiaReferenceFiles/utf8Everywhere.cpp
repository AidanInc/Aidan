#include "utf8Everywhere.h"
#include <locale>
#include <codecvt>

std::wstring widen(std::string utf8) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring utf16 = converter.from_bytes(utf8);
    return utf16;
}

std::string narrow(std::wstring utf16) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string utf8 = converter.to_bytes(utf16);
    return utf8;
}