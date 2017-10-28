#include <iostream>
#include "Marie.h"

int main(int argc, char* argv[]) {

    if (argc == 1) {
        std::cout << "Usage: " << argv[0] << " [filename]" << std::endl;
    }
    else {
        Marie file(argv[1]);

        file.loadFile();
        file.buildSymbolTable();
        // file.displaySymbolTable();
        file.assemble();
        file.displayData();
        file.execute();
    }

	return 0;
}
