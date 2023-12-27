/* td4.hpp
 * COPYRIGHT: (c) 2024 Łukasz Gęsieniec.  All rights reserved.
 */

#pragma once

using namespace std;

#include <array>
#include <string>


class Td4 {
    public:
    enum class Status{ Ok, Nok};

    Status assemble(array<string, 16> in, array<string, 16> &out);

};
