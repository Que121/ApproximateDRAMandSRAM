#include "Setting.hpp"

class VddReduction
{
public:
  double vdd = VDD;       // 电源供电电压
  u_int32_t countGap = 0; // 翻转间隔
  std::map<double, int>   // vdd ==> probability
      vddToProbabilityGap{
          {0.45, (double)(1) / (0.0532)},
          {0.46, (double)(1) / (0.0273)},
          {0.47, (double)(1) / (0.0183)},
          {0.48, (double)(1) / (0.0072)},
          {0.49, (double)(1) / (0.0049)},
          {0.50, (double)(1) / (0.0045)},
          {0.51, (double)(1) / (0.0039)},
          {0.52, (double)(1) / (0.0031)}, 
          {0.53, (double)(1) / (0.0027)},
          {0.54, (double)(1) / (0.0026)},
          {0.55, (double)(1) / (0.0007)},
          {0.56, (double)(1) / (0.0012)},
          {0.57, (double)(1) / (0.0011)},
          {0.58, (double)(1) / (0.0013)},
          {0.59, (double)(1) / (0.0009)},
          {0.60, 0}};

  VddReduction();
  ~VddReduction();

  void lowBitsVddReduction(std::bitset<8> &BinaryTemp);     // 低位比特降低电压
  void showlowBitsVddReduction(std::bitset<8> &BinaryTemp); //  打印降低电压后八位二进制数组
};
