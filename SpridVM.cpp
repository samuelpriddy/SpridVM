#include <iostream>
#include <vector>

using namespace std;

enum OPCODES {
	OP_PRT = 0b000, //Print the value in a given register
	OP_LD = 0b001, //Load a given value into a register
	OP_ADD = 0b010, //Add the values in two given registers
	OP_SUB = 0b011, //Subtract the values in two given registers
	OP_STP = 0b100, //Stop the VM
};

enum REGISTERS {
	R_R0, 
	R_R1, 
	R_R2, 
	R_R3,
	R_R4,
	R_R5,
	R_R6,
	R_R7,
	R_PC, //Register for program counter
	R_MS, //Register for machine state; 1=On 0=Off
};

class SpridVM {
	uint8_t memory[0x1000];//Allocate 4096 bytes for memory
	uint8_t regs[0x10]; //Allocate 9 bytes for registers

	public:
		SpridVM() {
			regs[R_MS] = 1;
		};

		int execute(uint16_t inst) {
			uint8_t opcode = findOpcode(inst);

			if (!regs[R_MS]) { return 0; }
			else if (opcode == OP_PRT) {printOp(inst);}
			else if (opcode == OP_LD) {loadOp(inst);}
		}

	private:
		int printOp(uint16_t inst) {
			uint8_t reg = (inst >> 10) & 0b111;
			cout << regs[reg];
			return 0;
		}

		int loadOp(uint16_t inst) {
			uint8_t reg = (inst >> 10) & 0b111;
			uint8_t val = inst & 0b11111111;
			regs[reg] = val;
			return 0;
		}

		//Returns the opcode of the given instruction
		uint8_t findOpcode(uint16_t inst) {return (inst >> 13) & 0b111;} 
};

int main() {
	uint16_t instructions[] = { 0b0010000000000010, 0b0000000000000000 };

	SpridVM vm;
	for (int i = 0; i < sizeof(instructions); i++) {
		vm.execute(instructions[i]);
	}
};