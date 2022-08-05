#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <iostream>
#include <string>
#include <fmt/core.h>
#include <fmt/format.h>
#include <bitset>

using namespace cv;
using namespace std;

#define TEST_PATH "/home/quinton/Desktop/ApproximateDRAMandSRAM/test.jpeg"                // 测试路径
#define TEST_SAVE_PATH "/home/quinton/Desktop/ApproximateDRAMandSRAM/test_processed.jpeg" // 测试保存路径

// DRAM模型
class DRAM
{
private:
  u_int32_t FlipCount;

public:
  DRAM(/* args */);
  ~DRAM();
};

DRAM::DRAM(/* args */)
{
}

DRAM::~DRAM()
{
}

// SRAM模型
class SRAM
{
private:
  /* data */
public:
  SRAM(/* args */);
  ~SRAM();
};

SRAM::SRAM(/* args */)
{
}

SRAM::~SRAM()
{
}
