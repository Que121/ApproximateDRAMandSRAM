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
  void ShowStorageBits();                           // 打印DRAM存储的比特
  void WriteExcelBits(const cv::String &excelName); // 写入excel表格
  void ShowGroupsBits();                            // 打印数据组数
  u_int32_t CountHighBits();                        // 计算DRAM中高位比特数
  u_int32_t GetAllBits();                           // 比特总数
  double GetHighBitsAverage();                      // 计算单个像素平均含有的高位比特数
  double GetHighBitsPercentage();                   // 高位比特占比
};

// SRAM模型
class SRAM
{
public:
  static const u_int32_t storageSizekb_64 = 64;          // 64kb
  static const u_int32_t storageSizekb_128 = 128;        // 128kb
  static const u_int32_t storageSizekb_256 = 256;        // 256kb
  u_int8_t SRAM_HighBits = 0;                            // SRAM高位比特数
  u_int32_t SRAM_storageSizeByte = SRAM128 * KB_TO_BYTE; // SRAM储存的Byte数
  u_int32_t SRAM_FlipTimes = 0;                          // 翻转次数
  u_int32_t allFilpTimes = 0;                            // 总翻转次数
  u_int32_t StorageLoopTimes_flag = 1;                   // 存储循环标志
  vector<vector<u_int8_t>> SRAM_Bits;                    // 储存在SRAM的比特
  vector<vector<u_int8_t>> SRAM_LastBits;                // 上一次储存在SRAM的比特

  SRAM();
  ~SRAM();
  void ShowStorageBits();                                                              // 打印SRAM存储的比特
  void StorageBits(std::bitset<8> &BinaryTemp, u_int32_t storageSizecount);            // SRSM比特
  double CalculateFlipProbability();                                                   // 计算单次翻转概率
  double CalculateAllFlipProbability();                                                // 计算总翻转概率
  u_int32_t CalculateFlipBits(std::bitset<8> &BinaryTemp, u_int32_t storageSizecount); // 计算翻转比特数(弃用)
  u_int32_t ShowGroupsBits();                                                          // 打印数据组数
  u_int32_t GetAllBits();                                                              // 比特总数
  void CalculateFlipBits(u_int32_t &StorageLoopTimes, u_int32_t &storageBitsFlag);     // 计算翻转概率无返回值
};
