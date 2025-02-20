#include "clrpp/Caller.hpp"
#include "gtest/gtest.h"

TEST(clrpp, Dummy)
{
  clr::Caller("test");
  EXPECT_EQ(true, true);
}
