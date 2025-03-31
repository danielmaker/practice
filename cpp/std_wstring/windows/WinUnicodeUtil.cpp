#include "WinUnicodeUtil.h"
#include <windows.h>

#include <memory>

std::wstring AnsiToUnicode(const std::string& ansi_str)
{
    if(ansi_str.empty())
    {
        return L"";
    }

    // Allocate a buffer for the Unicode string.
    // Use of the OLE allocator is required if the resultant Unicode string will be
    // passed to another COM component and if that component will free it.
    // Otherwise you can use your own allocator.
    const ULONG cCharacters = ansi_str.length() + 1;
    auto buf = std::unique_ptr<wchar_t, decltype(&CoTaskMemFree)>(
        reinterpret_cast<wchar_t*>(CoTaskMemAlloc(cCharacters*2)), CoTaskMemFree);
    wchar_t* uni_str = buf.get();
    if (nullptr == uni_str)
	{
		//out of memory
        return L"";
	}

    // Covert to Unicode.
    if (0 == MultiByteToWideChar(CP_ACP, 0, ansi_str.c_str(), cCharacters, uni_str, cCharacters))
    {
        const auto dwError = GetLastError();
		const auto hr = HRESULT_FROM_WIN32(dwError);
        return L"";
    }

	std::wstring ret_str = uni_str;
	return ret_str;
}

std::string UnicodeToAnsi(const std::wstring& uni_str)
{
    // If input is null then just return the same.
    if (uni_str.empty())
    {
        return "";
    }

    // Determine number of bytes to be allocated for ANSI string.
    // An ANSI string can have at most 2 bytes per character (for Double Byte Character Strings.)
    const ULONG cCharacters = uni_str.length() + 1;
    const ULONG cbAnsi = cCharacters*2;

    // Use of the OLE allocator is not required because the resultant
    // ANSI string will never be passed to another COM component.
	// You can use your own allocator.
    auto buf = std::unique_ptr<char, decltype(&CoTaskMemFree)>(
        reinterpret_cast<char*>(CoTaskMemAlloc(cbAnsi)), CoTaskMemFree);
    char* ansi_str = buf.get();
	if (nullptr == ansi_str)
	{
		//error: out of memory
		return "";
	}

    // Convert to ANSI.
    if (0 == WideCharToMultiByte(CP_ACP, 0, uni_str.c_str(), cCharacters, ansi_str, cbAnsi, NULL, NULL))
    {
        const auto dwError = GetLastError();
		const auto hr = HRESULT_FROM_WIN32(dwError);
		return "";
    }

	std::string ret_str = ansi_str;
	return ret_str;
}
