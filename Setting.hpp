#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <string>
#include <fmt/core.h>
#include <fmt/format.h>
#include <bitset>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <streambuf>
#include <memory>
#include <cmath>
#include <sstream>
#include <iomanip>

// s#define DEBUG_BITS 1 // 开启调试模式
// #define DEBUG_METRICATION 1

#define K 4                                                                       //近似阈值
#define TEST_PATH "/home/quinton/Desktop/ApproximateDRAMandSRAM/src.jpeg"         // 测试路径
#define TEST_SAVE_PATH "/home/quinton/Desktop/ApproximateDRAMandSRAM/dst.jpeg"    // 测试保存路径
#define EXCEL_NAME "/home/quinton/Desktop/ApproximateDRAMandSRAM/DRAM_Bits.csv"   // excel导出路径
#define RAW_IMAGE_PATH "/home/quinton/Desktop/ApproximateDRAMandSRAM/lena512.raw" // raw格式图片路径
#define BITS_8 8                                                                  // 定义使用的bit位数
#define KB_TO_BYTE 1024                                                           // 1KB=1024Byte
#define IMAGE_WIDTH 512                                                           // 输入图像宽
#define IMAGE_HEIGHT 512                                                          // 输入图像高
#define PI 3.1415926                                                              // 近似圆周率(DCT使用)
#define ROUNDPOINT 0                                                              // 量化四舍五入保留的小数位

using namespace cv;
using namespace std;