#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include "MarieInstruction.h"

class Marie
{
private:
	const static int BUFFER_LENGTH = 4096;
	unsigned short mStart;

	std::string mFilename;
	unsigned short mData[BUFFER_LENGTH];

	std::vector<MarieInstruction> mInstructions;
	std::map<std::string, int> mSymbolTable;

	unsigned short hexStringToShort(const std::string&) const;
	unsigned short decStringToShort(const std::string&) const;
	unsigned short octStringToShort(const std::string&) const;

public:
	
	Marie(const char*);

	void loadFile();
	void buildSymbolTable();
	void displaySymbolTable() const;

	void assemble();
	void displayData() const;
	void execute();
};

