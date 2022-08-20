#include "main.hpp"

int main()
{
  // DRAM_ApproximateStorage();
  // SRAM_ApproximateStorage();
  cv::imshow("rawImage", returnRawData());
  cv::waitKey();
  return 0;
}
