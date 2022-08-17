#include "main.hpp"

int main()
{
  if (!src.empty())
  {
    cv::resize(src, dst, dsize, 0, 0, INTER_AREA); // 归一化
    cv::cvtColor(dst, dst, COLOR_RGB2GRAY);        // 灰度化
    // imshow("grey_dst", dst);

    // 读取每个像素点 逐行读取
    for (int row = 0; row < dst.rows; row++)
    {
      for (int col = 0; col < dst.cols; col++)
      {
        int v = dst.at<uchar>(row, col);
        // fmt::print("{} ", v);
        std::bitset<8> BinaryTemp(v); // 八位二进制转换

#if DEBUG_BITS
        printf("\033[32m"
               "未翻转--> ");
        ShowBinaryTemp(BinaryTemp);
#endif

        ApproximateBinaryTemp(BinaryTemp, K); // 近似操作
        dram.StorageBits(BinaryTemp);

        
#if DEBUG_BITS
        printf("\033[31m"
               "已翻转--> ");
        ShowBinaryTemp(BinaryTemp);
#endif

        DecodeFlipBits(BinaryTemp); // 解码

#if DEBUG_BITS
        printf("\033[30m"
               "已解码--> ");
        ShowBinaryTemp(BinaryTemp);
#endif

#if DEBUG_METRICATION
        printf("%d ", dst.at<uchar>(row, col));
        printf("%d \n", (int)(BinaryTemp.to_ulong()));
#endif
        dst.at<uchar>(row, col) = (int)(BinaryTemp.to_ulong());
      }
    }
    // dram.ShowStorageBits();
    // dram.ShowGroupsBits();
    dram.WriteExcelBits((string)(EXCEL_NAME));
    fmt::print("高位比特数：{:d} 总比特数：{:d} 高位比特占比：{:f}", dram.CountHighBits(), dram.GetAllBits(), dram.GetHighBitsPercentage());
    
    namedWindow("dst", WINDOW_AUTOSIZE);
    imshow("dst", dst);
    imwrite(TEST_SAVE_PATH, dst);
    waitKey(0);
  }

  return 0;
}
