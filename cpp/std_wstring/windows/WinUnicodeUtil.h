#ifndef _Windows_Unicode_Util_h_
#define _Windows_Unicode_Util_h_

#include <string>

// Convert an ANSI single-character string to an Unicode wide-character string.
// It is a helper function by wrapping MultiByteToWideChar.
std::wstring AnsiToUnicode(const std::string& ansi_str);

// Convert an Unicode wide-character string to an ANSI single-character string.
// It is a helper function by wrapping WideCharToMultiByte.
std::string UnicodeToAnsi(const std::wstring& uni_str);

#endif //_Windows_Unicode_Util_h_
