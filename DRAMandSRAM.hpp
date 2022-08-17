#include "Setting.hpp"
using namespace cv;
using namespace std;

// DRAM模型
class DRAM
{
public:
  u_int32_t DRAM_HighBits = 0;        // DRAM高位比特数
  vector<vector<u_int8_t>> DRAM_Bits; // 储存在DRAM的比特
  u_int32_t CountBinaryTemp = 0;      // 统计比特组数

  DRAM();
  ~DRAM();
  void StorageBits(std::bitset<8> &BinaryTemp);     // DRAM存储比特
  void ShowStorageBits();                           // 打印DRAM存储的比特和总比特数
  void WriteExcelBits(const cv::String &excelName); // 写入excel表格
  void ShowGroupsBits();                            // 打印数据组数
  u_int32_t CountHighBits();                        // 计算DRAM中高位比特数
  u_int32_t GetAllBits();                           // 比特总数
  double GetHighBitsPercentage();                   // 高位比特占比
};

// SRAM模型
class SRAM
{
public:
  static const u_int32_t storageSizekb_64 = 64;                         // 64kb
  static const u_int32_t storageSizekb_128 = 128;                       // 128kb
  static const u_int32_t storageSizekb_256 = 256;                       // 256kb
  u_int32_t SRAM_HighBits = 0;                                          // SRAM高位比特数
  u_int32_t SRAM_Bits[storageSizekb_64 * KB_TO_BYTE][BITS_8] = {0};     // 储存在SRAM的比特
  u_int32_t SRAM_LastBits[storageSizekb_64 * KB_TO_BYTE][BITS_8] = {0}; // 上一次储存在SRAM的比特

  SRAM(/* args */);
  ~SRAM();
  void StorageBits(std::bitset<8> &BinaryTemp); // SRSM存储比特
  void ShowStorageBits();                       // 打印SRAM存储的比特和总比特数
  void CalculateFlipProbability();              // 计算翻转概率
};
