#include "simulator.hpp"
#include <cstring>
#include <algorithm>


void Simulator::execute(std::string opcode) {
    MFP fp = opcodeCallback[opcode.substr(4, 4)];
    std::string im = opcode.substr(0, 4);
    std::reverse(im.begin(), im.end());
    (this->*fp)(im);
    if (fp != &Simulator::addA && fp != &Simulator::addB) {
        CF = std::bitset<1>(0);
    }
    if (fp != &Simulator::jnc && fp != &Simulator::jmp) {
        PC = PC.to_ulong() + 1;
    }
}

int Simulator::run(const std::array<std::string, 16>& bin, const std::array<std::string, 16>& asmsrc) {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    WINDOW *regs_win = newwin(6, 21, 1, 1);
    WINDOW *ports_win = newwin(4, 21, 7, 1);
    WINDOW *clock_win = newwin(5, 21, 11, 1);
    WINDOW *keys_win = newwin(6, 21, 16, 1);
    WINDOW *program_win = newwin(18, 30, 1, 23);
    refresh();

    box(regs_win, 0, 0);
    box(ports_win, 0, 0);
    box(clock_win, 0, 0);
    box(keys_win, 0, 0);
    box(program_win, 0, 0);

    mvwprintw(regs_win, 0, 1, "Registers");
    mvwprintw(regs_win, 1, 1, "A:	0000");
    mvwprintw(regs_win, 2, 1, "B:	0000");
    mvwprintw(regs_win, 3, 1, "CF:	0   ");
    mvwprintw(regs_win, 4, 1, "PC:	0000");

    mvwprintw(ports_win, 0, 1, "Ports");
    mvwprintw(ports_win, 1, 1, "IN:	0000");
    mvwprintw(ports_win, 2, 1, "OUT:	0000");

    mvwprintw(clock_win, 0, 1, "Clock");
    mvwprintw(clock_win, 1, 1, "  1 Hz");
    mvwprintw(clock_win, 2, 1, "> 10 Hz");
    mvwprintw(clock_win, 3, 1, "  Manual");

    mvwprintw(keys_win, 0, 1, "Keys");
    mvwprintw(keys_win, 1, 1, "IN port: 1, 2, 3, 4");
    mvwprintw(keys_win, 2, 1, "Clock: z, x, c");
    mvwprintw(keys_win, 3, 1, "Reset: r");
    mvwprintw(keys_win, 4, 1, "Quit: q");

    mvwprintw(program_win, 0, 1, "Program");
    for(std::size_t i = 0; i < asmsrc.size(); i++) {
        mvwprintw(program_win, i+1, 3, "%s: %s", std::bitset<4>(i).to_string().c_str(), asmsrc[i].c_str());
    }

    wrefresh(regs_win);
    wrefresh(ports_win);
    wrefresh(clock_win);
    wrefresh(keys_win);
    wrefresh(program_win);

    if (clock == ClockSource::Clock_1Hz)
        timeout(1000);
    else if (clock == ClockSource::Clock_10Hz)
        timeout(100);
    else //ClockSource::Clock_Manual
        timeout(-1);

    int c;
    while((c = getch()) != 'q') {

        switch (c)
        {
        case 'z':
            clock = ClockSource::Clock_1Hz;
            timeout(1000);
            mvwprintw(clock_win, 1, 1, ">");
            mvwprintw(clock_win, 2, 1, " ");
            mvwprintw(clock_win, 3, 1, " ");
            wrefresh(clock_win);
            break;
        case 'x':
            clock = ClockSource::Clock_10Hz;
            timeout(100);
            mvwprintw(clock_win, 1, 1, " ");
            mvwprintw(clock_win, 2, 1, ">");
            mvwprintw(clock_win, 3, 1, " ");
            wrefresh(clock_win);
            break;
        case 'c':
            clock = ClockSource::Clock_Manual;
            timeout(-1);
            mvwprintw(clock_win, 1, 1, " ");
            mvwprintw(clock_win, 2, 1, " ");
            mvwprintw(clock_win, 3, 1, ">");
            wrefresh(clock_win);
        case -1:
            mvwprintw(program_win, PC.to_ulong()+1, 1, " ");

            execute(bin[PC.to_ulong()]);
            mvwprintw(regs_win, 1, 1, "A:	%s", RA.to_string().c_str());
            mvwprintw(regs_win, 2, 1, "B:	%s", RB.to_string().c_str());
            mvwprintw(regs_win, 3, 1, "CF:	%s", CF.to_string().c_str());
            mvwprintw(regs_win, 4, 1, "PC:	%s", PC.to_string().c_str());
            wrefresh(regs_win);

            mvwprintw(ports_win, 1, 1, "IN:	%s", IN.to_string().c_str());
            mvwprintw(ports_win, 2, 1, "OUT:	%s", OUT.to_string().c_str());
            wrefresh(ports_win);

            mvwprintw(program_win, PC.to_ulong()+1, 1, ">");
            wrefresh(program_win);
            break;
        case '1':
        case '2':
        case '3':
        case '4':
            if(c == '1') IN[3] = !IN[3]; else
            if(c == '2') IN[2] = !IN[2]; else
            if(c == '3') IN[1] = !IN[1]; else
            if(c == '4') IN[0] = !IN[0];
            mvwprintw(ports_win, 1, 1, "IN:	%s", IN.to_string().c_str());
            wrefresh(ports_win);
            break;
        case 'r':
            PC = 0; RA = 0; RB = 0; CF = 0; OUT = 0;
            refresh();
            break;
        default:
            break;
        }
    }

    endwin();

    return 0;
}
