/* td4.hpp
 * COPYRIGHT: (c) 2024 Łukasz Gęsieniec.  All rights reserved.
 */

#pragma once

#include <array>
#include <string>
#include <map>

using namespace std;


class Td4 {
    public:
    enum class Status{ Ok, Nok, AsmErr, DisasmErr};

    Status assemble(array<string, 16> in, array<string, 16> &out);
    Status disassemble(array<string, 16> in, array<string, 16> &out);

    private:
                                                        // bit0     bit7
    map<string, string> instructionToOpcodeWithIm = {{"ADD A, ",  "XXXX0000"},
                                                     {"MOV A, ",  "XXXX1100"},
                                                     {"ADD B, ",  "XXXX1010"},
                                                     {"MOV B, ",  "XXXX1110"},
                                                     {"OUT ",     "XXXX1101"},
                                                     {"JNC ",     "XXXX0111"},
                                                     {"JMP ",     "XXXX1111"}};

    map<string, string> instructionToOpcodeWithoutIm = {{"MOV A, B", "00001000"},
                                                        {"IN A",     "00000100"},
                                                        {"MOV B, A", "00000010"},
                                                        {"IN B",     "00000110"},
                                                        {"OUT B",    "00001001"}};

                                                     // bit4 bit7
    map<string, string> opcodeToinstructionWithIm = {{"0000", "ADD A, "},
                                                     {"1100", "MOV A, "},
                                                     {"1010", "ADD B, "},
                                                     {"1110", "MOV B, "},
                                                     {"1101", "OUT "},
                                                     {"0111", "JNC "},
                                                     {"1111", "JMP "}};

    map<string, string> opcodeToinstructionWithoutIm = {{"1000", "MOV A, B"},
                                                        {"0100", "IN A"},
                                                        {"0010", "MOV B, A"},
                                                        {"0110", "IN B"},
                                                        {"1001", "OUT B"}};

    string getOpcode(string instruction);
    string getInstruction(string opcode);

};
