#include <stdio.h>
#include <string>
#include <locale>
#include <codecvt>
#include <iostream>

// http://en.cppreference.com/w/cpp/locale/codecvt_utf8
std::string ws2s(const std::wstring& wstr)
{
    using convert_wchar = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_wchar, wchar_t> converter;

    return converter.to_bytes(wstr);
}

std::wstring s2ws(const std::string& str)
{
    using convert_wchar = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_wchar, wchar_t> converter;

    return converter.from_bytes(str);
}


int main()
{
    // http://stackoverflow.com/questions/17641718/how-to-output-unicode-characters-in-c-c
    std::ios::sync_with_stdio(false);     // for Linux gcc.
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale(""));

    std::string str = "Hello World";
    std::string strZH = "這是中文";
    std::wstring wstr = L"這是中文";

    std::cout  << "string: "  << str   << std::endl;
    std::cout  << "string: "  << strZH << std::endl;
    std::wcout << "wstring: " << wstr  << std::endl;

    std::cout  << "convert to string: "  << ws2s(wstr)  << std::endl;
    std::wcout << "convert to wstring: " << s2ws(strZH) << std::endl;

    return 0;
}

