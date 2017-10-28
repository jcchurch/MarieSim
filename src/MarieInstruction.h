#pragma once
#include <algorithm>
#include <string>

class MarieInstruction
{
private:
	std::string mSymbol;
	std::string mInstruction;
	std::string mParameter;
	bool mIsInstruction;

	size_t skipSpaces(const std::string & line, size_t) const;
	size_t parseSymbol(const std::string&);
	size_t parseInstruction(const std::string&, size_t);
	size_t parseParameter(const std::string&, size_t);

public:
	MarieInstruction(const std::string& line);

	inline bool isInstruction() const {
		return mIsInstruction;
	}

	inline std::string getSymbol() const {
		return mSymbol;
	}

	inline std::string getInstruction() const {
		return mInstruction;
	}

	std::string getParameter() const {
		return mParameter;
	}
};

