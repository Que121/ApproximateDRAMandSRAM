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

// s#define DEBUG_BITS 1 // 开启调试模式
// #define DEBUG_METRICATION 1

#define TEST_PATH "/home/quinton/Desktop/ApproximateDRAMandSRAM/test.jpeg"                // 测试路径
#define TEST_SAVE_PATH "/home/quinton/Desktop/ApproximateDRAMandSRAM/test_processed.jpeg" // 测试保存路径
#define EXCEL_NAME "/home/quinton/Desktop/ApproximateDRAMandSRAM/DRAM_Bits.csv"           // excel导出路径
#define BITS_8 8                                                                          // 定义使用的bit位数
#define KB_TO_BYTE 1024                                                                   // 1KB=1024Byte
#define IMAGE_WIDTH 512                                                                   // 输入图像宽
#define IMAGE_HEIGH 512                                                                   // 输入图像高