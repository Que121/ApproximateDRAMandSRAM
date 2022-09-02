#include "Setting.hpp"

// 计算PSNR
double PSNR_computing(cv::Mat &dst1, cv::Mat &dst2);

// Ｍat转换为CV_32FC1
void imgTo32FC1(cv::Mat &dst);

// Mat转换为CV_8UC1
void imgTo8UC1(cv::Mat &dst);

// DCT变换
void DCT_transform(cv::Mat &dst);

// 反DCT变换
void IDCT_transform(cv::Mat &dst);

// 图像四舍五入
void imgRound(cv::Mat &dst,const int &bits);

//量化
class ImgQuantization
{
public:
  u_int8_t imgQuantizationRows = 8;
  u_int8_t imgQuantizationCols = 8;

  ImgQuantization();
  ~ImgQuantization();

  void ImgQuantify(cv::Mat &dst);
};

//反量化
class ImgDequantization
{
public:
  u_int8_t imgDequantizationRows = 8;
  u_int8_t imgDequantizationCols = 8;

  ImgDequantization();
  ~ImgDequantization();

  void ImgDequantify(cv::Mat &dst);
};

// 图像分块和合并
class ImgChunkandMerge
{
public:
  u_int8_t imgChunkRows = 8;
  u_int8_t imgChunkCols = 8;
  std::vector<cv::Mat> ImgChunk; // 存储8*8小块
  cv::Mat roiImg = Mat ::zeros(imgChunkRows,
                               imgChunkCols, CV_64FC1);
  cv::Mat cutImg = Mat ::zeros(imgChunkRows,
                               imgChunkCols, CV_64FC1);

  ImgChunkandMerge();
  ~ImgChunkandMerge();

  void imgChunking(cv::Mat &dst); // 图像分块
  void imgMerging(cv::Mat &dst);  // 图像合并
  void showImgChunk();            // 显示分块图像
};
