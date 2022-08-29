#include "Setting.hpp"

int around(double a);

// DCT变换
class _DCT
{
public:
  double alpha, beta;                                                       // C(k)  C(l)
  u_int32_t m = 0, n = 0, k = 0, l = 0;                                     // DCT公式中系数
  cv::Mat DCT_output = cv::Mat ::zeros(IMAGE_WIDTH, IMAGE_HEIGH, CV_64FC1); // DCT输出图像

  _DCT();
  ~_DCT();
  void DCT_transform(cv::Mat &_DCT_input); // DCT变换
  cv::Mat DCT_returnImg();                // 返回DCT变换后的图片
};

// 反DCT变换
class _IDCT
{
public:
  double alpha, beta;                                                        // C(k)  C(l)
  u_int32_t m = 0, n = 0, k = 0, l = 0;                                      // IDCT公式中系数
  cv::Mat IDCT_output = cv::Mat ::zeros(IMAGE_WIDTH, IMAGE_HEIGH, CV_64FC1); // IDCT输出图像

  _IDCT();
  ~_IDCT();
  void IDCT_transform(cv::Mat &_IDCT_input); // 反DCT变换
  cv::Mat IDCT_returnImg();                 // 返回反DCT变换后的图片
};

//量化

//反量化
