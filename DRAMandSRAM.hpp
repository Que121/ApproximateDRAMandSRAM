#include "Setting.hpp"
using namespace cv;
using namespace std;

// DRAM模型
class DRAM
{
public:
  u_int32_t DRAM_HighBits = 0;        // 高位比特数
  vector<vector<u_int8_t>> DRAM_Bits; // 储存在DRAM的比特
  u_int32_t CountBinaryTemp = 0;      // 统计比特组数

  DRAM();
  ~DRAM();
  void StorageBits(std::bitset<8> &BinaryTemp);                 // DRAM存储比特
  void ShowStorageBits();                                       // 打印存储的比特和总比特数
  u_int32_t CountHighBits(vector<vector<u_int8_t>> &DRAM_Bits); // 计算DRAM中高位比特数
};

// SRAM模型
class SRAM
{
private:
  /* data */
public:
  SRAM(/* args */);
  ~SRAM();
};