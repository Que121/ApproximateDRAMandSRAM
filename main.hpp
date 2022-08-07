#include "Setting.hpp"
#include "DRAMandSRAM.hpp"

using namespace cv;
using namespace std;

// #define DEBUG_BITS 1 // 开启调试模式
// #define DEBUG_METRICATION 1

#define TEST_PATH "/home/quinton/Desktop/ApproximateDRAMandSRAM/test.jpeg"                // 测试路径
#define TEST_SAVE_PATH "/home/quinton/Desktop/ApproximateDRAMandSRAM/test_processed.jpeg" // 测试保存路径

DRAM dram;

u_int8_t BinaryTemp[8] = {0};
u_int8_t K = 3; // 分隔点

Size dsize = Size(512, 512);

cv::Mat src = cv::imread(TEST_PATH, IMREAD_COLOR);
cv::Mat dst = Mat ::zeros(dsize, CV_64FC1);
// cv::Mat dst1 = Mat ::zeros(5, 5, CV_8UC1); //测试数组

// 打印八位二进制数组 bitset里数字越大位数越高
void ShowBinaryTemp(std::bitset<8> &BinaryTemp)
{
  for (int8_t i = BinaryTemp.size() - 1; i > -1; i--)
  {
    fmt::print("{:x} ", BinaryTemp[i]);
  }
  fmt::print("\n");
}

// 计算高位里1的个数
u_int8_t CountHighBits(std::bitset<8> &BinaryTemp)
{
  u_int8_t count = 0;
  for (u_int8_t i = BinaryTemp.size() - 1; i > BinaryTemp.size() - (K + 1); i--)
  {
    if (BinaryTemp.test(i))
    {
      count++;
    }
  }
  return count;
}

// 遍历返回第一个1
u_int8_t TraverseLowBits(std::bitset<8> &BinaryTemp)
{
  for (u_int8_t i = BinaryTemp.size() - (K + 1); i > 0; i--)
  {
    if (BinaryTemp.test(i))
    {
      return i;
      break;
    }
  }
  return 0;
}

// 编码 翻转比特 标志位置0
void EncodeFlipBits(std::bitset<8> &BinaryTemp)
{
  if (CountHighBits(BinaryTemp) > (K / 2))
  {
    // printf("%d \n", (K / 2));
    // printf("%d \n", CountHighBits(BinaryTemp));
    for (u_int8_t i = BinaryTemp.size() - 1; i > BinaryTemp.size() - (K + 1); i--)
    {
      BinaryTemp.flip(i);
      // (BinaryTemp[i] == 1) ? BinaryTemp[i] = 0 : BinaryTemp[i] = 1;
    }
    BinaryTemp[0] = 0;
    return;
  }
  BinaryTemp[0] = 1;
}

// 补偿截断
void TruncatedFlipBits(std::bitset<8> &BinaryTemp)
{
  if (TraverseLowBits(BinaryTemp))
  {
    for (u_int8_t i = TraverseLowBits(BinaryTemp) - 1; i > 0; i--)
    {
      BinaryTemp.reset(i);
    }
  }
}

// 解码 标志位不变
void DecodeFlipBits(std::bitset<8> &BinaryTemp)
{
  if (BinaryTemp[0] == 0)
  {
    for (u_int8_t i = BinaryTemp.size() - 1; i > BinaryTemp.size() - (K + 1); i--)
    {
      BinaryTemp.flip(i);
    }
  }
}

// 近似操作八位二进制
void ApproximateBinaryTemp(std::bitset<8> &BinaryTemp, u_int8_t K)
{
  EncodeFlipBits(BinaryTemp);
  TruncatedFlipBits(BinaryTemp);
}