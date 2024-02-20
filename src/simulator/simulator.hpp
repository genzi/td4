/* simulator.hpp
 * TD4 simulator
 * COPYRIGHT: (c) 2024 Łukasz Gęsieniec.  All rights reserved.
 */
#pragma once

#include <array>
#include <map>
#include <unordered_map>
#include <string>
#include <bitset>
#include <ncurses.h>

class Simulator
{
private:
    enum class ClockSource{ Clock_1Hz, Clock_10Hz, Clock_Manual};

    std::bitset<4> RA;
    std::bitset<4> RB;
    std::bitset<4> PC;
    std::bitset<1> CF;
    std::bitset<4> IN;
    std::bitset<4> OUT;

    ClockSource clock;

    typedef void (Simulator::*MFP)(std::string);
    std::map <std::string, MFP> opcodeCallback;

    void addA(std::string im) {
        unsigned long ra = RA.to_ulong() + std::bitset<4>(im).to_ulong();
        CF = (ra > 15) ? std::bitset<1>(1) : std::bitset<1>(0);
        RA = std::bitset<4>(ra);
    }

    void movA(std::string im) {
        RA = std::bitset<4>(im);
    }

    void movAB(std::string) {
        RA = RB;
    }

    void addB(std::string im) {
        unsigned long rb = RB.to_ulong() + std::bitset<4>(im).to_ulong();
        CF = (rb > 15) ? std::bitset<1>(1) : std::bitset<1>(0);
        RB = std::bitset<4>(rb);
    }

    void movB(std::string im) {
        RB = std::bitset<4>(im);
    }

    void movBA(std::string) {
        RB = RA;
    }

    void out(std::string im) {
        OUT = std::bitset<4>(im);
    }

    void outB(std::string) {
        OUT = RB;
    }

    void inA(std::string) {
        RA = IN;
    }

    void inB(std::string) {
        RB = IN;
    }

    void jnc(std::string im) {
        if (CF.none()) {
            PC = std::bitset<4>(im);
        } else {
            PC = PC.to_ulong() + 1;
        }
    }

    void jmp(std::string im) {
        PC = std::bitset<4>(im);
    }

    void execute(std::string opcode);

public:

    Simulator(/* args */) {
        PC = 0; RA = 0; RB = 0; CF = 0; IN = 10; OUT = 0;
        clock = ClockSource::Clock_10Hz;

        opcodeCallback.insert(std::make_pair("0000", &Simulator::addA));
        opcodeCallback.insert(std::make_pair("1100", &Simulator::movA));
        opcodeCallback.insert(std::make_pair("1010", &Simulator::addB));
        opcodeCallback.insert(std::make_pair("1110", &Simulator::movB));
        opcodeCallback.insert(std::make_pair("1101", &Simulator::out));
        opcodeCallback.insert(std::make_pair("0111", &Simulator::jnc));
        opcodeCallback.insert(std::make_pair("1111", &Simulator::jmp));
        opcodeCallback.insert(std::make_pair("1000", &Simulator::movAB));
        opcodeCallback.insert(std::make_pair("0100", &Simulator::inA));
        opcodeCallback.insert(std::make_pair("0010", &Simulator::movBA));
        opcodeCallback.insert(std::make_pair("0110", &Simulator::inB));
        opcodeCallback.insert(std::make_pair("1001", &Simulator::outB));
    };
    ~Simulator() {}

    int run(const std::array<std::string, 16>& bin, const std::array<std::string, 16>& asmsrc);
};
