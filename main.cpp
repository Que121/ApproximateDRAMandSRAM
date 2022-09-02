#include "main.hpp"

cv::Size dsize = Size(IMAGE_WIDTH, IMAGE_HEIGHT); // 图像大小

u_int8_t BinaryTemp[8] = {0};

// cv::Mat src = cv::imread(TEST_PATH, IMREAD_COLOR); // jpeg格式
cv::Mat src = returnRawData(); // raw格式
cv::Mat dst = Mat ::zeros(dsize, CV_64FC1);
// cv::Mat dst1 = Mat ::zeros(5, 5, CV_8UC1); //测试数组

int main()
{
  // DRAM_ApproximateStorage();
  // SRAM_ApproximateStorage();
  PSNR_imgApproximate(src, dst, dsize);
  // PSNR_imgCompression(src, dst, dsize);
  // cv::imshow("rawImage", returnRawData());
  cv::imshow("src", src);
  cv::imshow("result", dst);
  cv::waitKey();
  return 0;
}
