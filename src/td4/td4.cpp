#include "td4.hpp"
#include <regex>


Td4::Status Td4::assemble(array<string, 16> in, array<string, 16> &out) {
    Status status = Status::Ok;
    for (unsigned int i = 0; i < in.size(); i++) {
        if(in[i] == "") break;
        out[i] = getOpcode(in[i]);
        if(out[i] == "") status = Status::AsmErr;
    }
    return status;
}

Td4::Status Td4::disassemble(array<string, 16> in, array<string, 16> &out) {
    Status status = Status::Ok;
    for (unsigned int i = 0; i < in.size(); i++) {
        if(in[i] == "") break;
        out[i] = getInstruction(in[i]);
        if(out[i] == "") status = Status::DisasmErr;
    }
    return status;
}

string Td4::getOpcode(string instruction) {
    string rawInstruction = regex_replace( instruction,
                                           regex("[01]"),
                                           "");
    string immediate = regex_replace( instruction,
                                      regex("[^01]"),
                                      "");
    string opcode = instructionToOpcodeWithoutIm[rawInstruction];

    if("" == opcode) {
        opcode = instructionToOpcodeWithIm[rawInstruction];
        if("" == opcode) return "";
        reverse(immediate.begin(), immediate.end());
        opcode = regex_replace(opcode,
                               regex("XXXX"),
                               immediate);
    }

    return opcode;
}

string Td4::getInstruction(string opcode) {
    string instruction = opcodeToinstructionWithoutIm[opcode.substr(4, 4)];

    if("" == instruction) {
        instruction = opcodeToinstructionWithIm[opcode.substr(4, 4)];
        if("" == instruction) return "";
        string temp = opcode.substr(0, 4);
        reverse(temp.begin(), temp.end());
        instruction += temp;
    }

    return instruction;
}
