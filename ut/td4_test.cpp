#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

#include "td4/td4.hpp"


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
  array<string, 16> in{"IN A"};
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
