#include "Marie.h"

unsigned short Marie::hexStringToShort(const std::string& hex) const {
	unsigned short value = 0;

	for (size_t i = 0; i < hex.length(); i++) {
		value <<= 4;
		if ('a' <= hex.at(i) && hex.at(i) <= 'f') {
			value += (hex.at(i) - 'a') + 10;
		}
		else if ('0' <= hex.at(i) && hex.at(i) <= '9') {
			value += hex.at(i) - '0';
		}
	}

	return value;
}

unsigned short Marie::decStringToShort(const std::string& dec) const {
	unsigned short value = 0;

	bool isNegatve = false;
	size_t i = 0;

	if (dec.at(0) == '-') {
		isNegatve = true;
		i++;
	}

	for (; i < dec.length(); i++) {
		value *= 10;
		if ('0' <= dec.at(i) && dec.at(i) <= '9') {
			value += dec.at(i) - '0';
		}
	}

	if (isNegatve) {
		value *= -1;
	}

	return value;
}

unsigned short Marie::octStringToShort(const std::string& oct) const {
	unsigned short value = 0;

	for (size_t i = 0; i < oct.length(); i++) {
		value <<= 3;
		if ('0' <= oct.at(i) && oct.at(i) <= '7') {
			value += oct.at(i) - '0';
		}
	}

	return value;
}

Marie::Marie(const char* filename) {
    mStart = 0;
	mFilename = filename;
}

void Marie::loadFile() {
	std::ifstream infile(mFilename.c_str());
	std::string line;

	while (std::getline(infile, line))
	{
		MarieInstruction marieInstruction(line);

		if (marieInstruction.isInstruction()) {
			if (marieInstruction.getInstruction() == "org") {
				mStart = hexStringToShort(marieInstruction.getParameter());
			}
			else {
				mInstructions.push_back(line);
			}
		}
	}

	infile.close();
}

void Marie::buildSymbolTable() {
	int cellNumber = mStart;
	for (int i = 0; i < mInstructions.size(); i++) {
		std::string symbol = mInstructions[i].getSymbol();

		if (symbol != "") {
			mSymbolTable.insert(std::pair<std::string, int>(symbol, cellNumber));
		}

		cellNumber++;
	}
}

void Marie::displaySymbolTable() const {
	std::cout << "Symbol Table:\n";
	for (std::map<std::string, int>::const_iterator it = mSymbolTable.begin(); it != mSymbolTable.end(); it++) {
		std::cout << it->first << " => " << it->second << std::endl;
	}
}

void Marie::assemble() {
	int cellNumber = mStart;
	for (int i = 0; i < mInstructions.size(); i++) {
		MarieInstruction marieInstruction = mInstructions[i];
		std::string instruction = marieInstruction.getInstruction();

		if (instruction == "hex") {
			mData[cellNumber] = hexStringToShort(marieInstruction.getParameter());
		}
		if (instruction == "dec") {
			mData[cellNumber] = decStringToShort(marieInstruction.getParameter());
		}
		if (instruction == "oct") {
			mData[cellNumber] = octStringToShort(marieInstruction.getParameter());
		}
		if (instruction == "jns") {
			mData[cellNumber] = 0x0000 + mSymbolTable.find(marieInstruction.getParameter())->second;
		}
		if (instruction == "load") {
			mData[cellNumber] = 0x1000 + mSymbolTable.find(marieInstruction.getParameter())->second;
		}
		if (instruction == "store") {
			mData[cellNumber] = 0x2000 + mSymbolTable.find(marieInstruction.getParameter())->second;
		}
		if (instruction == "add") {
			mData[cellNumber] = 0x3000 + mSymbolTable.find(marieInstruction.getParameter())->second;
		}
		if (instruction == "subt") {
			mData[cellNumber] = 0x4000 + mSymbolTable.find(marieInstruction.getParameter())->second;
		}
		if (instruction == "input") {
			mData[cellNumber] = 0x5000;
		}
		if (instruction == "output") {
			mData[cellNumber] = 0x6000;
		}
		if (instruction == "halt") {
			mData[cellNumber] = 0x7000;
		}
		if (instruction == "skipcond") {
			mData[cellNumber] = 0x8000 + hexStringToShort(marieInstruction.getParameter());
		}
		if (instruction == "jump") {
			mData[cellNumber] = 0x9000 + mSymbolTable.find(marieInstruction.getParameter())->second;
		}
		if (instruction == "clear") {
			mData[cellNumber] = 0xA000;
		}
		if (instruction == "addi") {
			mData[cellNumber] = 0xB000 + mSymbolTable.find(marieInstruction.getParameter())->second;
		}
		if (instruction == "jumpi") {
			mData[cellNumber] = 0xC000 + mSymbolTable.find(marieInstruction.getParameter())->second;
		}
		if (instruction == "loadi") {
			mData[cellNumber] = 0xD000 + mSymbolTable.find(marieInstruction.getParameter())->second;
		}
		if (instruction == "storei") {
			mData[cellNumber] = 0xE000 + mSymbolTable.find(marieInstruction.getParameter())->second;
		}

		cellNumber++;
	}
}

void Marie::displayData() const {
	std::cout << "Data Table:\n";
	for (int i = 0; i < 128; i++) {
		std::cout << std::setfill('0') << std::setw(4) << std::hex << int(mData[i]) << ' ';

		if (i % 16 == 15) {
			std::cout << std::endl;
		}
	}
}

void Marie::execute() {

	short mAC = 0;
	unsigned short mPC = mStart;
	unsigned short code = 0;
	unsigned short parameter = 0;

	while (mPC < BUFFER_LENGTH) {
		code = mData[mPC] >> 12;
		parameter = mData[mPC] & 0xFFF;
		mPC++;

		if (code == 0) {
			mData[parameter] = mPC;
			mAC = parameter;
			mPC = parameter + 1;
		}
		else if (code == 1) {
			mAC = mData[parameter];
		}
		else if (code == 2) {
			mData[parameter] = mAC;
		}
		else if (code == 3) {
			mAC += mData[parameter];
		}
		else if (code == 4) {
			mAC -= mData[parameter];
		}
		else if (code == 5) {
			std::cout << "INPUT: ";
			std::cin >> mAC;
		}
		else if (code == 6) {
			std::cout << "OUTPUT: " << std::dec << mAC << std::endl;
		}
		else if (code == 7) {
			std::cout << "Program halted normally." << std::endl;
			mPC = BUFFER_LENGTH;
		}
		else if (code == 8) {
			unsigned short twobits = parameter >> 10;
			if ((twobits == 0 && mAC < 0) || (twobits == 1 && mAC == 0) || (twobits == 2 && mAC > 0)) {
				mPC++;
			}
		}
		else if (code == 9) {
			mPC = parameter;
		}
		else if (code == 10) {
			mAC = 0;
		}
		else if (code == 11) {
			mAC += mData[mData[parameter]];
		}
		else if (code == 12) {
			mPC = mData[parameter];
		}
		else if (code == 13) {
			mAC = mData[mData[parameter]];
		}
		else if (code == 14) {
			mData[mData[parameter]] = mAC;
		}
	}
}
