#include "main.hpp"

cv::Size dsize = Size(IMAGE_WIDTH, IMAGE_HEIGHT); // 图像大小

u_int8_t BinaryTemp[8] = {0};

cv::Mat src = cv::imread(TEST_PATH, IMREAD_COLOR); // jpeg格式
// cv::Mat src = returnRawData(); // raw格式
cv::Mat dst = Mat ::zeros(dsize, CV_64FC1);
// cv::Mat dst1 = Mat ::zeros(5, 5, CV_8UC1); //测试数组

int main()
{
  // imgPreProcessing(src, dst, dsize); // 图片预处理
  // DRAM_ApproximateStorage(src,dst, dsize);
  // DRAM_CompleteApproximateStorage(src, dst, dsize);
  // SRAM_ApproximateStorage(src, dst, dsize);
  // SRAM_CompleteApproximateStorage(src, dst, dsize);
  // PSNR_ImgApproximate(src, dst, dsize);
  // PSNR_imgCompression(src, dst, dsize);
  PSNR_CompleteImgApproximate(src, dst, dsize);
  // imwrite(RESULT_SAVE_PATH +
  //             to_string(PSNR_computing(src, dst)) +
  //             "_" +
  //             to_string(K) +
  //             "_" +
  //             IMG_NAME,
  //         dst);
  // PSNR_VddReductionAndApproximate(src, dst, dsize);
  // imwrite(RESULT_SAVE_PATH + to_string(PSNR_computing(src, dst)) + "_" + to_string((VDD)) + ".jpeg", dst);
  // cv::imshow("rawImage", returnRawData());
  cv::imshow("src", src);
  cv::imshow("result", dst);
  cv::waitKey(0);
  return 0;
}
