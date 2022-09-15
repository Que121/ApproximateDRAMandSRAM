#include "vddReduction.hpp"

VddReduction::VddReduction()
{
}

VddReduction::~VddReduction()
{
}

void VddReduction::lowBitsVddReduction(std::bitset<8> &BinaryTemp)
{
  // mt19937::result_type seed = time(0); // 设置随机数种子
  // auto dice_rand = std::bind(std::uniform_int_distribution<int>(1, 10000), mt19937(seed));
  default_random_engine e;
  uniform_int_distribution<unsigned> u(0, 10000);
  for (u_int8_t i = BinaryTemp.size() - (K + 1); i > 0; i--)
  {
    fmt::print("{:d} ", (int)(u(e)));
    if ((int)(u(e)) < (vddToProbability.find(vdd)->second))
    {

      // fmt::print("{:d} ", (vddToProbability.find(vdd)->second));
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