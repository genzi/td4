#include "td4/td4.hpp"

#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

//using namespace std;


TEST_GROUP(Td4TestGroup)
{
   void setup()
   {
      // Init stuff
   }

   void teardown()
   {
      mock().checkExpectations();
      mock().clear();
   }
};

TEST(Td4TestGroup, CreateTd4Object)
{
   Td4 cpu;
   (void)cpu;
}

TEST(Td4TestGroup, Td4AsmCall)
{
  array<string, 16> in{"ADD A, 0001"};
  array<string, 16> out;
  Td4 td4asm;

  Td4::Status status = td4asm.assemble(in, out);

  CHECK_TRUE(Td4::Status::Ok == status);
}

TEST(Td4TestGroup, Td4AsmCheckOut)
{
  array<string, 16> in{"IN A"};
  array<string, 16> out;
  Td4 td4asm;

  Td4::Status status = td4asm.assemble(in, out);

  CHECK_TRUE(Td4::Status::Ok == status);
  STRCMP_EQUAL((char *)"00000100", out[0].c_str());
}

TEST(Td4TestGroup, Td4AsmCheckOutTwoInstructions)
{
  array<string, 16> in{"IN A", "OUT B"};
  array<string, 16> out;
  Td4 td4asm;

  Td4::Status status = td4asm.assemble(in, out);

  CHECK_TRUE(Td4::Status::Ok == status);
  STRCMP_EQUAL((char *)"00000100", out[0].c_str());
  STRCMP_EQUAL((char *)"00001001", out[1].c_str());
}

TEST(Td4TestGroup, Td4AsmBadInstruction)
{
  array<string, 16> in{"BAD INSTR"};
  array<string, 16> out;
  Td4 td4asm;

  Td4::Status status = td4asm.assemble(in, out);

  CHECK_TRUE(Td4::Status::AsmErr == status);
}

TEST(Td4TestGroup, Td4AsmCheckOutAllInstructions)
{
  array<string, 16> in = {"ADD A, 0001",  //"10000000"},
                          "MOV A, B",     //"00001000"},
                          "IN A",         //"00000100"},
                          "MOV A, 0010",  //"01001100"},
                          "MOV B, A",     //"00000010"},
                          "ADD B, 0100",  //"00101010"},
                          "IN B",         //"00000110"},
                          "MOV B, 1000",  //"00011110"},
                          "OUT B",        //"00001001"},
                          "OUT 0011",     //"11001101"},
                          "JNC 1110",     //"01110111"},
                          "JMP 1111"};    //"11111111"}};
  array<string, 16> out;
  Td4 td4asm;

  Td4::Status status = td4asm.assemble(in, out);

  CHECK_TRUE(Td4::Status::Ok == status);
  STRCMP_EQUAL((char *)"10000000", out[0].c_str());
  STRCMP_EQUAL((char *)"00001000", out[1].c_str());
  STRCMP_EQUAL((char *)"00000100", out[2].c_str());
  STRCMP_EQUAL((char *)"01001100", out[3].c_str());
  STRCMP_EQUAL((char *)"00000010", out[4].c_str());
  STRCMP_EQUAL((char *)"00101010", out[5].c_str());
  STRCMP_EQUAL((char *)"00000110", out[6].c_str());
  STRCMP_EQUAL((char *)"00011110", out[7].c_str());
  STRCMP_EQUAL((char *)"00001001", out[8].c_str());
  STRCMP_EQUAL((char *)"11001101", out[9].c_str());
  STRCMP_EQUAL((char *)"01110111", out[10].c_str());
  STRCMP_EQUAL((char *)"11111111", out[11].c_str());
}

TEST(Td4TestGroup, Td4DisasmCall)
{
  array<string, 16> in{"11111111"};
  array<string, 16> out;
  Td4 td4disasm;

  Td4::Status status = td4disasm.disassemble(in, out);

  CHECK_TRUE(Td4::Status::Ok == status);
}

TEST(Td4TestGroup, Td4DisasmCheckOut)
{
  array<string, 16> in{"00000100"};
  array<string, 16> out;
  Td4 td4disasm;

  Td4::Status status = td4disasm.disassemble(in, out);

  CHECK_TRUE(Td4::Status::Ok == status);
  STRCMP_EQUAL((char *)"IN A", out[0].c_str());
}

TEST(Td4TestGroup, Td4DisasmCheckOutTwoOpcodes)
{
  array<string, 16> in{"00000100", "00001001"};
  array<string, 16> out;
  Td4 td4disasm;

  Td4::Status status = td4disasm.disassemble(in, out);

  CHECK_TRUE(Td4::Status::Ok == status);
  STRCMP_EQUAL((char *)"IN A", out[0].c_str());
  STRCMP_EQUAL((char *)"OUT B", out[1].c_str());
}

TEST(Td4TestGroup, Td4DisasmWithImmediateCheckOut)
{
  array<string, 16> in{"10000000"};
  array<string, 16> out;
  Td4 td4disasm;

  Td4::Status status = td4disasm.disassemble(in, out);

  CHECK_TRUE(Td4::Status::Ok == status);
  STRCMP_EQUAL((char *)"ADD A, 0001", out[0].c_str());
}

TEST(Td4TestGroup, Td4DisasmCheckOutAllInstructions)
{
  array<string, 16> in = {"10000000",
                          "00001000",
                          "00000100",
                          "01001100",
                          "00000010",
                          "00101010",
                          "00000110",
                          "00011110",
                          "00001001",
                          "11001101",
                          "01110111",
                          "11111111"};
  array<string, 16> out;
  Td4 td4asm;

  Td4::Status status = td4asm.disassemble(in, out);

  CHECK_TRUE(Td4::Status::Ok == status);
  STRCMP_EQUAL((char *)"ADD A, 0001", out[0].c_str());
  STRCMP_EQUAL((char *)"MOV A, B",    out[1].c_str());
  STRCMP_EQUAL((char *)"IN A",        out[2].c_str());
  STRCMP_EQUAL((char *)"MOV A, 0010", out[3].c_str());
  STRCMP_EQUAL((char *)"MOV B, A",    out[4].c_str());
  STRCMP_EQUAL((char *)"ADD B, 0100", out[5].c_str());
  STRCMP_EQUAL((char *)"IN B",        out[6].c_str());
  STRCMP_EQUAL((char *)"MOV B, 1000", out[7].c_str());
  STRCMP_EQUAL((char *)"OUT B",       out[8].c_str());
  STRCMP_EQUAL((char *)"OUT 0011",    out[9].c_str());
  STRCMP_EQUAL((char *)"JNC 1110",    out[10].c_str());
  STRCMP_EQUAL((char *)"JMP 1111",    out[11].c_str());
}
