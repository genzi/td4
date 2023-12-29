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
    enum class Status{ Ok, Nok, AsmErr};

    Status assemble(array<string, 16> in, array<string, 16> &out);

    private:
                                                        // bit0     bit7
    map<string, string> instructionToOpcode = {{"ADD A, ",  "XXXX0000"},
                                               {"MOV A, B", "00001000"},
                                               {"IN A",     "00000100"},
                                               {"MOV A, ",  "XXXX1100"},
                                               {"MOV B, A", "00000010"},
                                               {"ADD B, ",  "XXXX1010"},
                                               {"IN B",     "00000110"},
                                               {"MOV B, ",  "XXXX1110"},
                                               {"OUT B",    "00001001"},
                                               {"OUT ",     "XXXX1101"},
                                               {"JNC ",     "XXXX0111"},
                                               {"JMP ",     "XXXX1111"}};

    string getOpcode(string instruction);


};
