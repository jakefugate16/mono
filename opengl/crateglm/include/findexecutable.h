#ifndef __FIND_EXECUTABLE_H
#define __FIND_EXECUTABLE_H

#ifdef __WIN64__
#include <windows.h>
#endif

#include <algorithm>
#include <filesystem>
#include <string>
#include <iostream>

namespace getexecutable
{

	std::string convertWindowstoPosixSep(const std::string& windowsPath)
	{
		std::string posixPath { windowsPath };
		std::replace(posixPath.begin(), posixPath.end(), '\\', '/');
		return posixPath;
	}

	std::filesystem::path getExecutablePath()
	{
	#if defined(__WIN64__)
		char exePath[MAX_PATH];
		GetModuleFileName(NULL, exePath, MAX_PATH);

	#elif defined(__linux__)
		std::string{ std::filesystem::canonical("proc/self/exe").string() };

	#else
		char exePath[1] = "";
	#endif
		std::string exePath_str { exePath };

	#if defined(__MINGW64__) && defined(__WIN64__)
		exePath_str = convertWindowstoPosixSep(exePath_str);
	#endif
		return std::filesystem::path(exePath_str);
	}

	std::filesystem::path getExecutableDirectory()
	{
		std::filesystem::path exepath{ getExecutablePath() };
		return std::filesystem::path(exepath).parent_path();
	}
}
#endif
