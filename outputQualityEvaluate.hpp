#include "Setting.hpp"

int around(double a);

// DCT变换
class DCT
{
public:
  double alpha, beta;                                                      // C(k)  C(l)
  u_int32_t m = 0, n = 0, k = 0, l = 0;                                    // DCT公式中系数
  cv::Mat DCT_input = cv::Mat ::zeros(IMAGE_WIDTH, IMAGE_HEIGH, CV_64FC1); // DCT输入图像

  DCT(/* args */);
  ~DCT();
  void DCT_transform(cv::Mat &DCT_input);
};

void IDCT(cv::Mat &img);