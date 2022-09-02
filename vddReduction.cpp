#include "vddReduction.hpp"

VddReduction::VddReduction()
{
}

VddReduction::~VddReduction()
{
}

void VddReduction::lowBitsVddReduction(std::bitset<8> &BinaryTemp)
{
  for (u_int8_t i = BinaryTemp.size() - (K + 1); i > 0; i--)
  {
    srand(time(0)); // 设置随机数种子
    if ((rand() % (10000 - 1)) < (vddToProbability.find(vdd)->second))
    {
      // fmt::print("1111111111111111111111111111111");
      BinaryTemp.flip(i);
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