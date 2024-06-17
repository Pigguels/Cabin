#pragma once
#include "Data/String.h"

namespace File
{
	/*
	* Summary
	Attempts to read a file with the given name and returns the files contents
	Returns an empty string if there is no file with that name
	*/
	String ReadFile(const char* filePath);
	/*
	* Summary
	Writes the fileContents to a file that has the name of fileName,
	Creates a new file if there isn't one
	Overwrites an existing file if there is one
	*/
	bool WriteFile(const char* filePath, const char* fileContents);

	/*
	* Summary
	Reads a file in as any class
	[Note: this only works for non-dynamic classes]
	*/
	template<typename T>
	T ReadFileAsClass(const char* filePath);
	/*
	* Summary
	Writes a class to a file
	[Note: This only works for non-dynamic classes]
	*/
	template<typename T>
	bool WriteClassAsFile(const char* filePath, const T& fileContents);
}
