#include "td4.hpp"
#include <regex>


Td4::Status Td4::assemble(std::array<std::string, 16> in, std::array<std::string, 16> &out) {
    Status status = Status::Ok;
    for (unsigned int i = 0; i < in.size(); i++) {
        if(in[i] == "") break;
        out[i] = getOpcode(in[i]);
        if(out[i] == "") status = Status::AsmErr;
    }
    return status;
}

string Td4::getOpcode(string instruction) {
    string rawInstruction = std::regex_replace( instruction,
                                                       regex("[01]"),
                                                       "");
    string immediate = std::regex_replace( instruction,
                                                       regex("[^01]"),
                                                       "");
    string opcode = instructionToOpcode[rawInstruction];

    if(immediate != "") {
        reverse(immediate.begin(), immediate.end());
        opcode = regex_replace(opcode,
                               regex("XXXX"),
                               immediate);
    }

    return opcode;
}