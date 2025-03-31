#include <stdio.h>
#include <string>
#include <locale>
#include <codecvt>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include "WinUnicodeUtil.h"
#endif

// http://en.cppreference.com/w/cpp/language/string_literal
// http://en.cppreference.com/w/cpp/locale/codecvt_utf8
std::string ws2s(const std::wstring& wstr)
{
    try
    {
        using convert_wchar = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_wchar, wchar_t> converter;
        return converter.to_bytes(wstr);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return {};
}

std::wstring s2ws(const std::string& str)
{
    try
    {
        using convert_wchar = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_wchar, wchar_t> converter;
        return converter.from_bytes(str);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return {};
}

template<typename T>
std::string toUtf8(const T& str)
{
    try
    {
        using convert_type = std::codecvt_utf8<typename T::value_type>;
        std::wstring_convert<convert_type, typename T::value_type> converter;
        return converter.to_bytes(str);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return {};
}

int main()
{
#if defined(_WIN32) || defined(_WIN64)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    // http://stackoverflow.com/questions/17641718/how-to-output-unicode-characters-in-c-c
    std::ios::sync_with_stdio(false);     // for Linux gcc.
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale(""));

    // https://en.cppreference.com/w/cpp/language/string_literal
    std::string str = "Hello World";
    std::string strZH = "這是中文";
    std::string strRaw = R"(This is a "raw" string)";
    std::wstring wstr = L"這是中文";

    std::u8string strUtf8 = u8"這是中文";
    std::u16string strUtf16 = u"這是中文";
    std::u32string strUft32 = U"這是中文";

    std::cout  << "string: "  << str   << std::endl;
    std::cout  << "string: "  << strZH << std::endl;
    std::cout  << "raw string: "  << strRaw << std::endl;
    std::wcout << "wstring: " << wstr  << std::endl;

    std::cout  << "convert to string: "  << ws2s(wstr)  << std::endl;
    std::wcout << "convert to wstring: " << s2ws(strZH) << std::endl;

    std::cout  << "string-utf8: "  << std::string(strUtf8.begin(), strUtf8.end())  << std::endl;
    std::cout  << "string-utf16 to utf8: " << toUtf8(strUtf16) << std::endl;
    std::cout  << "string-utf32 to utf8: " << toUtf8(strUft32) << std::endl;

#if defined(_WIN32) || defined(_WIN64)
    std::cout  << "UnicodeToAnsi: " << UnicodeToAnsi(wstr.c_str())  << std::endl;
    std::wcout << "AnsiToUnicode: " << AnsiToUnicode(strZH.c_str()) << std::endl;
#endif

    return 0;
}
