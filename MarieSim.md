# MarieSim Cheat Sheet

Each instruction in MarieSim is comprised of 16 bits.

- First 4 bits: Instruction Code
- Last 12 bits: Parameter to that instruction (if any)

## Registers

Marie utilizes multiple registers, but there are two that I feel are more important than the others.

### AC

AC is your one and only variable that you can use in MarieSim. Most instructions use this register in an explicit way to help you to solve a problem. The one exception to this rule is `jns` which uses the AC register to modify the PC register to create subroutines. All instructions except for `jump`, `jumpi`, and `halt` will use the AC register.

### PC

PC is your program counter. It keeps track of where you are in the program. The typical behavior of this register will be to increment by 1 after each instruction. There are a few instructions which will modify the PC register to help you to jump to other parts of your program. Those instructions are `jump`, `jumpi`, and `jns`.

## Comments and Documentation

Documentation for MarieSim uses the single forward slash '/' mark. Out of habit and consistency with other programming languages, this document uses '//' for a comment. Everything after a '/' is ignored until the end of the line.

## Syntax of a Line of MarieSim

Each line of MarieSim program is comprised of (at most) three parts. Each part has an explicit order. Blank lines are skipped over in MarieSim.

1. The first part is a label. The label for a line is optional. If used, it must be followed by a comma.
2. The second is the instruction.
3. The third is the parameter to the instruction if necessary. Not all instructions use a parameter.

### Example Lines

This is not a complete program of MarieSim. This highlights different types of lines and their parts.

    halt            // This line is only an instruction.
    stop, halt      // The instruction is "halt". The label is "stop". There must be a comma after the label.
    jump stop       // The instruction is "jump". The parameter is "stop". There is no label.
    printx, load x  // The label is "printx", the instruction is "load", the parameter is "x"

## MarieSim Instructions

| Mnemonic      | Hexcode       | Description  |
| --- |:---:| --- |
| jns X | 0 | See below. |
| load X | 1 | Load the value at address X into AC. AC <- value at address X. |
| store X | 2 | Store the value in AC into address X. Address X <- AC. |
| add X | 3 | Add the value at address X into AC. AC <- AC + X |
| subt X | 4 | Subtract from AC the value at address X. AC <- AC - X |
| input | 5 | Read from INPUT a value from the keyboard into AC. |
| output | 6 | Output the value of AC to the OUTPUT panel. |
| halt | 7 | Stop the program. |
| skipcond X | 8 | See below. |
| jump X | 9 | Load the value of X into PC. |
| clear | A | Put all zeros into AC. |
| addi X | B | Add the value at the address stored in the address of X to AC. |
| jumpi X | C | Load the value at address X to PC. |
| loadi X | D | Load the value at the address stored in the address of X to AC. |
| storei X | E | Store the value in AC to the address of the value stored in X.|

### Understanding `halt`

All programs in MarieSim need an explicit command to halt the program. This is the shortest program that you can write in MarieSim.

    halt
    
This program doesn't do anything. While you can have multiple `halt` commands in a single MarieSim program, it's customary to have one `halt`.

### Understanding `input` and `output`

`input` and `output` are your core keyboard input and screen output tools. Input transfers keyboard to AC and output transfers AC to the screen.

#### Example

This example inputs a number and immediately echos that number, then stops.

    input
    output
    halt

### Understanding `add` and `subt`

`add` and `subt` will take the value at a particular location in memory and adds them to AC (`add`) or subtracts them from AC (`subt`). This sample code will add the value stored at location `two` to whatever the user inputs. As you can see from this program, we typically initialize our memory locations after the program.

    input
    add two
    output
    halt
    two, dec 2

This code does the same thing, but subtracts from input whatever value is stored at location `two`.

    input
    subt two
    output
    halt
    two, dec 2

### Understanding `load` and `store`

`load` will load a value at a location into AC. `store` will move whatever is in AC to a memory location. This sample program will take a number, store it into location `first`, take a second number and store it into location `section`, take a third number and immediately output that number, then load the number in second and output, then load the number in first and then output it.

    input
    store first
    input
    store second
    input
    output
    load second
    output
    load first
    output
    halt
    first, dec 0
    second, dec 0

### Understanding `clear`

`clear` is a quick way to write 0 to the AC register. That's all it does. This sample program displays 0 no matter what you type.

    input
    clear
    output
    halt

### Understanding `jump`

`jump` will jump to another line of code by changing the PC register to the value of a location (not the value at that location). This is useful for creating loops and if statements. See the next example.

### Understanding `skipcond`

`skipcode` uses the first two bits of the parameter and performs one of the following actions. It's named `skipcond` because it will skip the next instruction given a condition. This wording is confusing to me, so I've rewritten each instruction using a "run next if" description.

| Bits | Original Description | My Description | Example |
| --- | --- | --- | --- |
| 00 | Skip next instruction if AC is negative. | Run next instruction if AC >= 0. | skipcond 000 |
| 01 | Skip next instruction if AC is 0. | Run next instruction if AC != 0. | skipcond 400 |
| 10 | Skip next instruction if AC is positive. | Run next instruction if AC <= 0. | skipcond 800 |

#### Example

In this example, x is set to decimal 15 and y is set to decimal 20. This program prints out the larger of the two values.

    load y          // AC = y
    subt x          // AC = y - x
    skipcond 800    // If AC <= 0, then
    jump printx     //    jump to print x because x >= y
    load y          // AC = y (because x < y)
    output          // output y
    jump stop       // stop
    printx, load x  // AC = x (because x >= y)
    output          // output x
    stop, halt      // stop
    x, dec 15
    y, dec 20

### Understanding `jumpi`, `storei`, and `loadi`.

These instructions are known as the "indirect" instructions. These instructions don't work directly with an address, but instead work with an address store at a passed address.

- `jumpi` will jump the PC register to an address stored in the passed memory address.
- `loadi` will load value into AC found in the address taken in the passed memory address.
- `storei` will store the value of AC into a memory address stored in the passed memory address.

### Understanding `jns`

`jns` will do three things: it will store the value in PC into address X, load X into AC, then it will perform a jump to address X+1.

`jns` is used to create subroutines in your code (subroutines are similar functions) using an address parameter X. The idea is that location X+1 will be the start of a subroutine and that location X will be open space for storing the current PC value. At the end of the subroutine will be a call to `jumpi` and the name of your subroutine. `jumpi` is the jump indirect instruction, which jumps to the value stored at an address. The value stored at the address of your subroutine is your original PC value, thus sending your to the line immediately after the original `jns` call.

**WARNING** Because `jns` uses the AC register, be warned that whatever you put into AC before `jns` executes will be changed after `jns` executes.

#### Example

This example creates a subroutine called `doubleprint` with one parameter named `x`. The parameter `x` is loaded into AC, doubled, then printed, then returns control to the instruction after the caller. This code prints the double of 10, 15, and 20 (thus it prints 20, 30, 40).

    load ten
    store x
    jns doubleprint   // call doubleprint with 10
    load fifteen
    store x
    jns doubleprint   // call doubleprint with 15
    load twenty
    store x
    jns doubleprint   // call doubleprint with 20
    halt

    // DoublePrint subroutine
    doubleprint, hex 0  // Place for storing the location of instruction after jns call
    load x              // Start of procedure
    add x
    output
    jumpi doubleprint   // Jump to the address stored in the address doubleprint

    ten, dec 10
    fifteen, dec 15
    twenty, dec 20
    x, dec 0

## Assembler Directives

These are not instructions for the MarieSim environment. These are assembly directives, which means they are executed at the time of assembly (not while the program is being run).

| Mnemonic | Description |
| --- | --- |
| org X | Sets the starting instruction. If unused, first instruction is 000. |
| dec X | Converts decimal value X into hexadecimal and puts it into  memory. |
| oct X | Converts octal value X into hexadecimal and puts it into memory. |
| hex X | Puts hexidecimal value X into memory. |
