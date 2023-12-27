#include "td4.hpp"

Td4::Status Td4::assemble(array<string, 16> in, array<string, 16> &out) {

    out[0] = "00000100";

    return Status::Ok;
}
