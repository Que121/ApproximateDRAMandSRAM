#include "outputQualityEvaluate.hpp"

int around(double a)
{
  if (a >= 0)
  {
    return int(a + 0.5);
  }
  else
  {
    return int(a - 0.5);
  }
}

u_int32_t QuantizationTable[8][8] = {{16, 11, 10, 16, 24, 40, 51, 61}, //标准亮度量化表
                                     {12, 12, 14, 19, 26, 58, 60, 55},
                                     {14, 13, 16, 24, 40, 57, 69, 56},
                                     {14, 17, 22, 29, 51, 87, 80, 62},
                                     {18, 22, 37, 56, 68, 109, 103, 77},
                                     {24, 35, 55, 64, 81, 104, 113, 92},
                                     {49, 64, 78, 87, 103, 121, 120, 101},
                                     {72, 92, 95, 98, 112, 100, 103, 99}};

_DCT ::_DCT()
{
}

_DCT ::~_DCT()
{
}

void _DCT::DCT_transform(cv::Mat &DCT_transform)
{
  for (u_int32_t k = 0; k < DCT_transform.rows; k++)
  {
    for (u_int32_t l = 0; l < DCT_transform.cols; l++)
    {
      if (k == 0)
      {
        alpha = sqrt(1.0 / DCT_transform.rows);
      }
      else
      {
        alpha = sqrt(2.0 / DCT_transform.rows);
      }
      if (l == 0)
      {
        beta = sqrt(1.0 / DCT_transform.cols);
      }
      else
      {
        beta = sqrt(2.0 / DCT_transform.cols);
      }
      double temp = 0.0;
      for (u_int32_t m = 0; m < DCT_transform.rows; m++)
      {
        for (u_int32_t n = 0; n < DCT_transform.cols; n++)
        {

          //每个像素对应的tmp值即累加式计算完毕
          temp += DCT_transform.at<double>(m, n) *
                  cos((2 * m + 1) * k * PI / (2.0 * DCT_transform.rows)) *
                  cos((2 * n + 1) * l * PI / (2.0 * DCT_transform.cols));
        }
      }
      DCT_transform.at<double>(k, l) = alpha * beta * temp;
      DCT_output.at<double>(k, l) = alpha * beta * temp;
    }
  }
}

cv::Mat _DCT::DCT_returnImg()
{
  cv::imshow("DCT_output", DCT_output);
  return DCT_output;
}

_IDCT::_IDCT(/* args */)
{
}

_IDCT::~_IDCT()
{
}

void _IDCT::IDCT_transform(cv::Mat &IDCT_transform)
{
  for (u_int32_t k = 0; k < IDCT_transform.rows; k++)
  {
    for (u_int32_t l = 0; l < IDCT_transform.cols; l++)
    {
      double temp = 0.0;
      for (u_int32_t m = 0; m < IDCT_transform.rows; m++)
      {
        for (u_int32_t n = 0; n < IDCT_transform.cols; n++)
        {
          if (k == 0)
          {
            alpha = 1.0 / sqrt(IDCT_transform.rows);
          }
          else
          {
            alpha = sqrt(2.0 / IDCT_transform.rows);
          }
          if (l == 0)
          {
            beta = 1.0 / sqrt(IDCT_transform.cols);
          }
          else
          {
            beta = sqrt(2.0 / IDCT_transform.cols);
          }
          //每个像素对应的tmp值即累加式计算完毕
          temp += alpha * beta * IDCT_transform.at<double>(m, n) *
                  cos(PI * (2 * m + 1) * m / (2 * IDCT_transform.rows)) *
                  cos(PI * (2 * n + 1) * n / (2 * IDCT_transform.cols));
        }
      }
      IDCT_transform.at<double>(k, l) = alpha * beta * temp;
      IDCT_output.at<double>(k, l) = alpha * beta * temp;
    }
  }
}

cv::Mat _IDCT::IDCT_returnImg()
{
  cv::imshow("IDCT_output", IDCT_output);
  return IDCT_output;
}
