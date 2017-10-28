# MarieSim

## To Compile

To compile the code, use this line. All of the source code is written in C++ and found in the `src` folder. This will produce an `a.out` file.

    g++ src/*.cpp

## To Execute

There are a few `mas` files that can be used to test the application in the `sample_code` folder. Try it out with the `echo.mas` file.

    ./a.out sample_code/echo.mas

The code will then display the following:

    - The symbol table.
    - The first 128 instructions. 
    - The program execution.

If you need more than 128 instructions, you'll have to tweak the source code. 128 instructions is enough for most student programs. Here's an example of what runs when you execute `echo.mas`.

    $ ./a.out sample_code/echo.mas 
    Symbol Table:
    Data Table:
    5000 6000 7000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 
    0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 
    0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 
    0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 
    0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 
    0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 
    0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 
    0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 
    INPUT: 42
    OUTPUT: 42
    Program halted normally.

## Known Bugs

None!
