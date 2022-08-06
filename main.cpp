#include "main.hpp"

u_int8_t BinaryTemp[8] = {0};
u_int8_t K = 3; // 分隔点

Size dsize = Size(512, 512);

cv::Mat src = cv::imread(TEST_PATH, IMREAD_COLOR);
cv::Mat dst = Mat ::zeros(dsize, CV_64FC1);
// cv::Mat dst1 = Mat ::zeros(5, 5, CV_8UC1); //测试数组

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

    namedWindow("dst", WINDOW_AUTOSIZE);
    imshow("dst", dst);
    imwrite(TEST_SAVE_PATH, dst);
    waitKey(0);
  }

  return 0;
}
