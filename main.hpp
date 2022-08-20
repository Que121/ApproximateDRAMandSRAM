#include "Setting.hpp"
#include "DRAMandSRAM.hpp"

using namespace cv;
using namespace std;

DRAM dram;
SRAM sram;

cv::Size dsize = Size(IMAGE_WIDTH, IMAGE_HEIGH); // 图像大小

u_int8_t BinaryTemp[8] = {0};
u_int8_t K = 3; // 分隔点

cv::Mat src = cv::imread(TEST_PATH, IMREAD_COLOR);
cv::Mat dst = Mat ::zeros(dsize, CV_64FC1);
// cv::Mat dst1 = Mat ::zeros(5, 5, CV_8UC1); //测试数组

// 打开raw格式图片
void openRawData()
{
  std::ifstream fin;
  fin.open(RAW_IMAGE_PATH, std::ios::binary); // binary读取模式
  if (!fin)
  {
    std::cerr << "open failed: " << RAW_IMAGE_PATH << std::endl;
  }
  fin.seekg(0, fin.end);    // seek函数会把标记移动到输入流的结尾
  int length = fin.tellg(); // tell会告知整个输入流（从开头到标记）的字节数量
  fin.seekg(0, fin.beg);    // 移动到流的开始位置
  char *buffer = new char[length];
  fin.read(buffer, length); // read函数读取（拷贝）流中的length各字节到buffer
  cv::Mat rawImage(cv::Size(IMAGE_WIDTH, IMAGE_HEIGH), CV_8UC1, buffer);
  cv::imshow("rawImage", rawImage);
  cv::waitKey();
}

// 返回raw格式照片
cv::Mat returnRawData()
{
  std::ifstream fin;
  fin.open(RAW_IMAGE_PATH, std::ios::binary); // binary读取模式
  if (!fin)
  {
    std::cerr << "open failed: " << RAW_IMAGE_PATH << std::endl;
  }
  fin.seekg(0, fin.end);
  int length = fin.tellg();
  fin.seekg(0, fin.beg);
  char *buffer = new char[length];
  fin.read(buffer, length);
  cv::Mat rawImage(cv::Size(IMAGE_WIDTH, IMAGE_HEIGH), CV_8UC1, buffer);
  return rawImage;
}

// 打印八位二进制数组 bitset里数字越大位数越高
void ShowBinaryTemp(std::bitset<8> &BinaryTemp)
{
  for (int8_t i = BinaryTemp.size() - 1; i > -1; i--)
  {
    fmt::print("{:x} ", BinaryTemp[i]);
  }
  fmt::print("\n");
}

// 计算高位里1的个数
u_int8_t CountHighBits(std::bitset<8> &BinaryTemp)
{
  u_int8_t count = 0;
  for (u_int8_t i = BinaryTemp.size() - 1; i > BinaryTemp.size() - (K + 1); i--)
  {
    if (BinaryTemp.test(i))
    {
      count++;
    }
  }
  return count;
}

// 遍历返回第一个1
u_int8_t TraverseLowBits(std::bitset<8> &BinaryTemp)
{
  for (u_int8_t i = BinaryTemp.size() - (K + 1); i > 0; i--)
  {
    if (BinaryTemp.test(i))
    {
      return i;
      break;
    }
  }
  return 0;
}

// 编码 翻转比特 标志位置0
void EncodeFlipBits(std::bitset<8> &BinaryTemp)
{
  if (CountHighBits(BinaryTemp) > (K / 2))
  {
    // printf("%d \n", (K / 2));
    // printf("%d \n", CountHighBits(BinaryTemp));
    for (u_int8_t i = BinaryTemp.size() - 1; i > BinaryTemp.size() - (K + 1); i--)
    {
      BinaryTemp.flip(i);
      // (BinaryTemp[i] == 1) ? BinaryTemp[i] = 0 : BinaryTemp[i] = 1;
    }
    BinaryTemp[0] = 0;
    return;
  }
  BinaryTemp[0] = 1;
}

// 补偿截断
void TruncatedFlipBits(std::bitset<8> &BinaryTemp)
{
  if (TraverseLowBits(BinaryTemp))
  {
    for (u_int8_t i = TraverseLowBits(BinaryTemp) - 1; i > 0; i--)
    {
      BinaryTemp.reset(i);
    }
  }
}

// 解码 标志位不变
void DecodeFlipBits(std::bitset<8> &BinaryTemp)
{
  if (BinaryTemp[0] == 0)
  {
    for (u_int8_t i = BinaryTemp.size() - 1; i > BinaryTemp.size() - (K + 1); i--)
    {
      BinaryTemp.flip(i);
    }
  }
}

// 近似操作八位二进制
void ApproximateBinaryTemp(std::bitset<8> &BinaryTemp, u_int8_t K)
{
  EncodeFlipBits(BinaryTemp);
  TruncatedFlipBits(BinaryTemp);
}

// DRAM近似存储
void DRAM_ApproximateStorage()
{
  if (!src.empty())
  {
    cv::resize(src, dst, dsize, 0, 0, INTER_AREA); // 归一化
    cv::cvtColor(dst, dst, COLOR_RGB2GRAY);        // 灰度化
    for (int row = 0; row < dst.rows; row++)
    {
      for (int col = 0; col < dst.cols; col++)
      {
        int v = dst.at<uchar>(row, col);
        std::bitset<8> BinaryTemp(v);         // 八位二进制转换
        ApproximateBinaryTemp(BinaryTemp, K); // 近似操作
        dram.StorageBits(BinaryTemp);
        DecodeFlipBits(BinaryTemp); // 解码
        dst.at<uchar>(row, col) = (int)(BinaryTemp.to_ulong());
      }
    }
    // dram.ShowStorageBits();
    // dram.ShowGroupsBits();
    // dram.WriteExcelBits((string)(EXCEL_NAME));
    // fmt::print("DRAM高位比特数：{:d} DRAM总比特数：{:d} DRAM高位比特占比：{:f}",
    //            dram.CountHighBits(), dram.GetAllBits(), dram.GetHighBitsPercentage());
    namedWindow("dst", WINDOW_AUTOSIZE);
    imshow("dst", dst);
    imwrite(TEST_SAVE_PATH, dst);
    waitKey(0);
  }
}

// SRAM近似存储
void SRAM_ApproximateStorage()
{
  u_int32_t StorageLoopTimes = ceil((double)(IMAGE_WIDTH * IMAGE_WIDTH) / (double)(sram.SRAM_storageSizeByte)); // 存储次数
  u_int32_t storageSizeFmod = (IMAGE_WIDTH * IMAGE_WIDTH) % (sram.SRAM_storageSizeByte);
  // fmt::print("{:d} {:d}", StorageLoopTimes, storageSizeFmod); //right
  if (!src.empty())
  {
    cv::resize(src, dst, dsize, 0, 0, INTER_AREA); // 归一化
    cv::cvtColor(dst, dst, COLOR_RGB2GRAY);        // 灰度化
    for (int row = 0; row < dst.rows; row++)
    {
      for (int col = 0; col < dst.cols; col++)
      {
        int v = dst.at<uchar>(row, col);
        std::bitset<8> BinaryTemp(v);         // 八位二进制转换
        ApproximateBinaryTemp(BinaryTemp, K); // 近似操作

        if (sram.StorageLoopTimes_flag < StorageLoopTimes) // 非最后一次循环情况
        {
          // fmt::print("{:d}", storageSizeFmod); // 正常
          if (sram.SRAM_Bits.size() < sram.SRAM_storageSizeByte)
          {
            // fmt::print("{:d}", storageSizeFmod); // 正常
            sram.StorageBits(BinaryTemp, sram.SRAM_storageSizeByte);
            sram.CalculateFlipBits(StorageLoopTimes, sram.SRAM_storageSizeByte);
          }
        }
        else if (sram.StorageLoopTimes_flag == StorageLoopTimes) //最后一次循环
        {
          if (storageSizeFmod == 0)
          {
            if (sram.SRAM_Bits.size() < sram.SRAM_storageSizeByte)
            {
              sram.StorageBits(BinaryTemp, sram.SRAM_storageSizeByte);
              sram.CalculateFlipBits(StorageLoopTimes, sram.SRAM_storageSizeByte);
            }
          }
          else
          {
            if (sram.SRAM_Bits.size() < storageSizeFmod)
            {
              sram.StorageBits(BinaryTemp, storageSizeFmod);
              sram.CalculateFlipBits(StorageLoopTimes, storageSizeFmod);
            }
          }
        }

        DecodeFlipBits(BinaryTemp); // 解码
        dst.at<uchar>(row, col) = (int)(BinaryTemp.to_ulong());
      }
    }
    namedWindow("dst", WINDOW_AUTOSIZE);
    imshow("dst", dst);
    imwrite(TEST_SAVE_PATH, dst);
    waitKey(0);
  }
}

// 近似存储测试
void ApproximateStorageDebug()
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
                                              // dram.StorageBits(BinaryTemp);
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
    // dram.WriteExcelBits((string)(EXCEL_NAME));
    // fmt::print("DRAM高位比特数：{:d} DRAM总比特数：{:d} DRAM高位比特占比：{:f}",
    //            dram.CountHighBits(), dram.GetAllBits(), dram.GetHighBitsPercentage());
    namedWindow("dst", WINDOW_AUTOSIZE);
    imshow("dst", dst);
    imwrite(TEST_SAVE_PATH, dst);
    waitKey(0);
  }
}
