#include "Setting.hpp"

class VddReduction
{
public:
  double vdd = VDD;     // 电源供电电压
  std::map<double, int> // vdd ==> probability
      vddToProbability{
          {0.45, 532},
          {0.46, 273},
          {0.47, 183},
          {0.48, 72},
          {0.49, 49},
          {0.50, 45},
          {0.51, 39},
          {0.52, 31},
          {0.53, 27},
          {0.54, 26},
          {0.55, 7},
          {0.56, 12},
          {0.57, 11},
          {0.58, 13},
          {0.59, 9},
          {0.60, 0}};

  VddReduction();
  ~VddReduction();

  void lowBitsVddReduction(std::bitset<8> &BinaryTemp);     // 低位比特降低电压
  void showlowBitsVddReduction(std::bitset<8> &BinaryTemp); //  打印降低电压后八位二进制数组
};
