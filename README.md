# abstract_vm
AbstractVM is a machine that uses a stack to compute simple arithmetic expressions. <br />
These arithmetic expressions are provided to the machine as basic assembly programs

As for any assembly language, the language of AbstractVM is composed of a series of
instructions, with one instruction per line. However, AbstractVM’s assembly language
has a limited type system, which is a major difference from other real world assembly
languages.

Comments: Comments start with a ’;’ and finish with a newline. <br />
A comment can be either at the start of a line, or after an instruction.

push v: Pushes the value v at the top of the stack. The value v has one of the following form:

	int8(n) : Creates an 8-bit integer with value n.
	int16(n) : Creates a 16-bit integer with value n.
	int32(n) : Creates a 32-bit integer with value n.
	float(z) : Creates a float with value z.
	double(z) : Creates a double with value z.

pop: Unstacks the value from the top of the stack. If the stack is empty, <br />
produce an error.

dump: Displays each value of the stack, from the most recent one to the oldest one <br />
without changing the stack. Each value is separated from the next one by a newline.

assert v: Asserts that the value at the top of the stack is equal to the one passed as parameter <br />
for this instruction. If it is not the case, the program execution produce an error. <br />
The value v has the same form that those passed as parameters to the instruction push.

add: Unstacks the first two values on the stack, adds them together and stacks the <br />
result. If the number of values on the stack is strictly inferior to 2, the program <br />
execution produce an error.

sub: Unstacks the first two values on the stack, subtracts them, then stacks the <br />
result. If the number of values on the stack is strictly inferior to 2, the program <br />
execution produce an error.

mul: Unstacks the first two values on the stack, multiplies them, then stacks the <br />
result. If the number of values on the stack is strictly inferior to 2, the program <br />
execution produce an error.

div: Unstacks the first two values on the stack, divides them, then stacks the result. <br />
If the number of values on the stack is strictly inferior to 2 or the divisor is equal to 0, <br />
the program execution produce an error.

mod: Unstacks the first two values on the stack, calculates the modulus, then <br />
stacks the result. If the number of values on the stack is strictly inferior to 2 or <br />
the divisor is equal to 0, the program execution produce an error.

print: Asserts that the value at the top of the stack is an 8-bit integer. (If not, <br />
see the instruction assert), then interprets it as an ASCII value and displays the <br />
corresponding character on the standard output.

println: Displays 8-bit integers row as line, starting from the top of the stack <br />
till the other data type or the end of the stack.

pow: Unstacks the first two values on the stack, then stack base raised to the power exponent. <br />
If the number of values on the stack is strictly inferior to 2, the program <br />
execution produce an error.

log2: Unstacks the first two values on the stack, then stack the binary (base-2) logarithm of x. <br />
If the stack is empty, the program execution produce an error.

range: Displays the type of the first element on the stack and it's min/max range. <br />
If the stack is empty, the program execution produce an error.

cout: switch for result buffer output. (if doesn't active, output will be done after program execution)

exit: Terminate the execution of the current program. If this instruction does not <br />
appears while all others instruction has been processed, the execution produce an error.
