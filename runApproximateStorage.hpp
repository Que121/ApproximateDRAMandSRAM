#include "Setting.hpp"
#include "DRAMandSRAM.hpp"
#include "outputQualityEvaluate.hpp"

// 图像预处理
void imgPreProcessing(cv::Mat &src, cv::Mat &dst, cv::Size dsize);

// 图片预处理(raw格式使用)
void RAW_imgPreProcessing(cv::Mat &src, cv::Mat &dst, cv::Size dsize);

// 打开raw格式图片
void openRawData();

// 返回raw格式照片
cv::Mat returnRawData();

// 打印八位二进制数组 bitset里数字越大位数越高
void ShowBinaryTemp(std::bitset<8> &BinaryTemp);

// 计算高位里1的个数
u_int8_t CountHighBits(std::bitset<8> &BinaryTemp);

// 遍历返回第一个1
u_int8_t TraverseLowBits(std::bitset<8> &BinaryTemp);

// 编码 翻转比特 标志位置0
void EncodeFlipBits(std::bitset<8> &BinaryTemp);

// 补偿截断
void TruncatedFlipBits(std::bitset<8> &BinaryTemp);

// 解码 标志位不变
void DecodeFlipBits(std::bitset<8> &BinaryTemp);

// 近似操作八位二进制
void ApproximateBinaryTemp(std::bitset<8> &BinaryTemp);

// DRAM近似存储
void DRAM_ApproximateStorage(cv::Mat &src, cv::Mat &dst, cv::Size dsize);

// SRAM近似存储
void SRAM_ApproximateStorage(cv::Mat &src, cv::Mat &dst, cv::Size dsize);

// 近似存储测试
void ApproximateStorageDebug(cv::Mat &src, cv::Mat &dst, cv::Size dsize);

// 图片分块dct、量化、反量化、idct
void ImgCompression(cv::Mat &dst);

// 近似图和原图计算PSNR
void PSNR_imgApproximate(cv::Mat &src, cv::Mat &dst, cv::Size &dsize);
