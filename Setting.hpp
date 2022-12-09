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
#include <map>
#include <time.h>
#include <unistd.h>
#include <random>

// #define DEBUG_BITS 1 // 开启调试模式
// #define DEBUG_METRICATION 1

#define K 1                                                                         // 近似阈值
#define TEST_PATH "/home/quinton/Desktop/ApproximateDRAMandSRAM/img/src19.jpg"      // 测试路径
#define TEST_SAVE_PATH "/home/quinton/Desktop/ApproximateDRAMandSRAM/img/dst19.jpg" // 测试保存路径
#define RESULT_SAVE_PATH "/home/quinton/Desktop/ApproximateDRAMandSRAM/result_img/" // 结果保存路径
#define EXCEL_NAME "/home/quinton/Desktop/ApproximateDRAMandSRAM/DRAM_Bits.csv"     // excel导出路径
#define RAW_IMAGE_PATH "/home/quinton/Desktop/ApproximateDRAMandSRAM/lena512.raw"   // raw格式图片路径
#define IMG_NAME "19.jpg"                                                           // 保存的dst名字
#define BITS_8 8                                                                    // 定义使用的bit位数
#define KB_TO_BYTE 1024                                                             // 1KB=1024Byte
#define IMAGE_WIDTH 512                                                             // 输入图像宽
#define IMAGE_HEIGHT 512                                                            // 输入图像高
#define PI 3.1415926                                                                // 近似圆周率(DCT使用)
#define ROUNDPOINT 0                                                                // 量化四舍五入保留的小数位
#define VDD 0.60                                                                    // 电源供电电压
#define SRAM64 storageSizekb_64                                                     // SRAM64kb mod
#define SRAM128 storageSizekb_128                                                   // SRAM128kb mod
using namespace cv;
using namespace std;