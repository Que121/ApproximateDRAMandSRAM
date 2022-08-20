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

DCT ::DCT()
{
}

DCT ::~DCT()
{
}

/*
void DCT_transform(cv::Mat &DCT_transform)
{
  for (u_int32_t k = 0; k < DCT_transform.rows; k++)
  {
    for (u_int32_t l = 0; l < DCT_transform.cols; l++)
    {
      if (k == 0)
      {
        alpha = sqrt(1.0 / NUM);
      }
      else
      {
        alpha = sqrt(2.0 / NUM);
      }
      if (l == 0)
      {
        beta = sqrt(1.0 / NUM);
      }
      else
      {
        beta = sqrt(2.0 / NUM);
      }
      double temp = 0.0;
      for (u_int32_t m = 0; m < DCT_transform.rows; m++)
      {
        for (u_int32_t n = 0; n < DCT_transform.cols; n++)
        {

          temp += data[m][n] * cos((2 * m + 1) * k * PI / (2.0 * NUM)) * cos((2 * n + 1) * l * PI / (2.0 * NUM));
        }
      }
      output[k][l] = around(alpha * beta * temp);
    }
  }
  memset(data, 0, sizeof(int) * NUM * NUM);
  memcpy(data, output, sizeof(int) * NUM * NUM);
}
*/