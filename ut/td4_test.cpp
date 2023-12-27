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
