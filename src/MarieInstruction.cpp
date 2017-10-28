#include "MarieInstruction.h"

MarieInstruction::MarieInstruction(const std::string& line)
{
	std::string lineLower = line;
	std::transform(lineLower.begin(), lineLower.end(), lineLower.begin(), ::tolower);

	mIsInstruction = false;
	size_t start = parseSymbol(lineLower);
	start = parseInstruction(lineLower, start);
	start = parseParameter(lineLower, start);
}

size_t MarieInstruction::skipSpaces(const std::string& line, size_t start) const {
	size_t i = start;
	while (i < line.length() && line.at(i) == ' ') {
		i++;
	}
	return i;
}

size_t MarieInstruction::parseSymbol(const std::string& line) {
	std::string symbol = "";

	size_t start = skipSpaces(line, 0);

	size_t i = start;
	while (i < line.length() && line.at(i) != ',' && line.at(i) != '/') {
		if (line.at(i) != ' ') {
			symbol += line.at(i);
		}
		i++;
	}

	if (i >= line.length() || line.at(i) != ',') {
		mSymbol = "";
		return start;
	}

	mSymbol = symbol;
	return i+1;
}

size_t MarieInstruction::parseInstruction(const std::string& line, size_t start) {
	std::string instruction = "";

	size_t i = skipSpaces(line, start);
	while (i < line.length() && 'a' <= line.at(i) && line.at(i) <= 'z') {
		instruction += line.at(i);
		i++;
	}

	if (instruction.length() == 0) {
		return start;
	}

	mIsInstruction = true;
	mInstruction = instruction;
	return i;
}

size_t MarieInstruction::parseParameter(const std::string& line, size_t start) {
	std::string parameter = "";

	size_t i = skipSpaces(line, start);
	while (i < line.length() && ('a' <= line.at(i) && line.at(i) <= 'z' || '0' <= line.at(i) && line.at(i) <= '9' || '-' == line.at(i))) {
		parameter += line.at(i);
		i++;
	}

	if (parameter.length() == 0) {
		return start;
	}

	mParameter = parameter;
	return i;
}