#include "vddReduction.hpp"

VddReduction::VddReduction()
{
}

VddReduction::~VddReduction()
{
}

void VddReduction::lowBitsVddReduction(std::bitset<8> &BinaryTemp)
{
  static default_random_engine e(time(0));
  static uniform_int_distribution<unsigned> u(1, (BinaryTemp.size() - (K + 1)));
  for (u_int8_t i = BinaryTemp.size() - (K + 1); i > 0; i--)
  {
    if ((vddToProbabilityGap.find(vdd)->second) != 0)
    {
      countGap++;
      if (countGap == (vddToProbabilityGap.find(vdd)->second))
      {
        fmt::print("{:d} \n", countGap);
        BinaryTemp.flip(u(e));
        countGap = 0;
      }
    }
  }
}

void VddReduction::showlowBitsVddReduction(std::bitset<8> &BinaryTemp)
{
  for (int8_t i = BinaryTemp.size() - 1; i > -1; i--)
  {
    fmt::print("{:x} ", BinaryTemp[i]);
  }
  fmt::print("\n");
}