#include "outputQualityEvaluate.hpp"

u_int32_t QuantizationTable[8][8] = {{16, 11, 10, 16, 24, 40, 51, 61}, //标准亮度量化表
                                     {12, 12, 14, 19, 26, 58, 60, 55},
                                     {14, 13, 16, 24, 40, 57, 69, 56},
                                     {14, 17, 22, 29, 51, 87, 80, 62},
                                     {18, 22, 37, 56, 68, 109, 103, 77},
                                     {24, 35, 55, 64, 81, 104, 113, 92},
                                     {49, 64, 78, 87, 103, 121, 120, 101},
                                     {72, 92, 95, 98, 112, 100, 103, 99}};

// floor和ceil方法 无法精确到小数点几位
inline double round(double &r)
{
  return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

// 输入流方法 可以精确到小数点几位
inline double round(double &number, const u_int8_t &bits)
{
  stringstream ss;
  ss << fixed << setprecision(bits) << number;
  ss >> number;
  return number;
}

double PSNR_computing(cv::Mat &dst1, cv::Mat &dst2)
{
  return cv::PSNR(dst1, dst2);
}

void imgTo32FC1(cv::Mat &dst)
{
  dst.convertTo(dst, CV_64FC1);
}

void imgTo8UC1(cv::Mat &dst)
{
  dst.convertTo(dst, CV_8UC1);
}

void DCT_transform(cv::Mat &dst)
{
  cv::dct(dst, dst, 0);
}

void IDCT_transform(cv::Mat &dst)
{
  cv::idct(dst, dst, 0);
}

void imgRound(cv::Mat &dst, const int &bits)
{
  for (u_int8_t row = 0; row < dst.rows; row++)
  {
    for (u_int8_t col = 0; col < dst.cols; col++)
    {
      // fmt::print("四舍五入前：{:f} \n", dst.at<double>(row, col));
      dst.at<double>(row, col) =
          round(dst.at<double>(row, col), bits);
      // fmt::print("四舍五入后：{:f} \n", dst.at<double>(row, col));
    }
  }
}

ImgQuantization::ImgQuantization()
{
}

ImgQuantization::~ImgQuantization()
{
}

void ImgQuantization::ImgQuantify(cv::Mat &dst)
{
  for (u_int8_t i = 0; i < imgQuantizationRows; i++)
  {
    for (u_int8_t j = 0; j < imgQuantizationCols; j++)
    {
      dst.at<double>(i, j) =
          (double)(dst.at<double>(i, j) / (double)QuantizationTable[i][j]);
    }
  }
}

ImgDequantization::ImgDequantization()
{
}

ImgDequantization::~ImgDequantization()
{
}

void ImgDequantization::ImgDequantify(cv::Mat &dst)
{
  for (u_int8_t i = 0; i < imgDequantizationRows; i++)
  {
    for (u_int8_t j = 0; j < imgDequantizationCols; j++)
    {
      dst.at<double>(i, j) =
          (double)(dst.at<double>(i, j) * (double )QuantizationTable[i][j]);
    }
  }
}

ImgChunkandMerge::ImgChunkandMerge()
{
}

ImgChunkandMerge::~ImgChunkandMerge()
{
}

void ImgChunkandMerge::imgChunking(cv::Mat &dst)
{
  for (u_int8_t i = 0; i < imgChunkRows; i++)
  {
    for (u_int8_t j = 0; j < imgChunkCols; j++)
    {
      cv::Rect rect(i * (dst.rows / imgChunkRows), j * (dst.cols / imgChunkCols),
                    (dst.rows / imgChunkRows), (dst.cols / imgChunkCols));
      cutImg = Mat(dst, rect);
      roiImg = cutImg.clone();
      ImgChunk.push_back(roiImg);
    }
  }
}
void ImgChunkandMerge::showImgChunk()
{
  u_int32_t num = 0;
  for (auto i : ImgChunk)
  {
    cv::imshow("num", i);
    num++;
  }
}

void ImgChunkandMerge::imgMerging(cv::Mat &dst)
{
  u_int16_t ImgChunkNum = 0;
  Mat MergeImage(Size(dst.rows, dst.cols), IMREAD_GRAYSCALE);
  for (u_int8_t i = 0; i < imgChunkRows; i++)
  {
    for (u_int8_t j = 0; j < imgChunkCols; j++)
    {
      Rect ROI(i * (dst.rows / imgChunkRows), j * (dst.cols / imgChunkCols),
               (dst.rows / imgChunkRows), (dst.cols / imgChunkCols));
      ImgChunk[ImgChunkNum].copyTo(MergeImage(ROI));
      ImgChunkNum++;
    }
  }
  dst = MergeImage;
  ImgChunk.clear();
}