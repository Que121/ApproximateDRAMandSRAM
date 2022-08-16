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
#define EXCEL_NAME "DRAM_Bits.csv"                                                        // excel导出路径