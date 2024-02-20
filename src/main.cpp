#include "td4/td4.hpp"
#include "simulator/simulator.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>


bool check_cli_args(const std::vector<std::string>& args) {
    return !((args.size() < 3 || args[1] == "-h") ||
             (args.size() >= 3 && (args[1] != "-d" && args[1] != "-a" && args[1] != "-s")));
}

void print_usage(const std::string& program_name) {
    std::cerr << "Usage: " << endl
              << "  " << program_name << " -d <file>" << std::endl
              << "  " << program_name << " -a <file>" << std::endl
              << "  " << program_name << " -h" << std::endl;
}

int check_input_file(const std::string& file_path) {
    if (!std::filesystem::exists(file_path)) {
        std::cerr << "File " << file_path << " does not exist." << std::endl;
        return 2;
    }
    if (!std::filesystem::is_regular_file(file_path)) {
        std::cerr << "File " << file_path << " is not a regular file." << std::endl;
        return 3;
    }
    if (std::filesystem::is_directory(file_path)) {
        std::cerr << "File " << file_path << " is a directory." << std::endl;
        return 1;
    }
    return 0;
}

int simulate(const array<string, 16>& bin, const array<string, 16>& asmsrc) {

    Simulator simulator;
    simulator.run(bin, asmsrc);

    return 0;
}

int main(int argc, char *argv[]) {

    std::vector<std::string> args(argv, argv+argc);

    if (!check_cli_args(args)) {
        print_usage(args[0]);
        return 1;
    }
    if (args[1] == "-h") {
        print_usage(args[0]);
        return 0;
    }

    if (check_input_file(args[2]) != 0) {
        return 2;
    }

    // open text file from command line arguments and read it line by line
    std::ifstream file(argv[2]);
    std::string line;
    array<string, 16> source;
    for (int i = 0; std::getline(file, line); i++) {
        source[i] = line;
    }
    array<string, 16> out;
    Td4 td4;
    Td4::Status status;
    std::string action;
    if (args[1] == "-a") {
        status = td4.assemble(source, out);
        action = "Assembly";
    } else if (args[1] == "-d") {
        status = td4.disassemble(source, out);
        action = "Disassembly";
    } else if (args[1] == "-s") {
        status = td4.disassemble(source, out);
        if (status == Td4::Status::Ok)
            return simulate(source, out);
        action = "Simulation disassembly";
    } else {
        status = Td4::Status::Nok;
        action = "Unknown action";
    }
    file.close();

    if (status == Td4::Status::Ok) {
        std::cout << action << " succeeded." << std::endl;
        size_t dot_pos = args[2].find_last_of(".");
        std::string out_file_name = args[2].substr(0, dot_pos) + (args[1] == "-a" ? ".out" : ".a");
        std::cout << "Writing output to " << out_file_name << std::endl;
        std::ofstream outfile(out_file_name);
        for (const auto& line : out) {
            outfile << line << std::endl;
        }
        outfile.close();
    } else {
        std::cout << action << " failed." << std::endl;
    }

    return 0;
}
