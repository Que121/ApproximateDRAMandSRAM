#include "outputQualityEvaluate.hpp"

u_int32_t QuantizationTable[8][8] = {{16, 11, 10, 16, 24, 40, 51, 61}, //标准亮度量化表
                                     {12, 12, 14, 19, 26, 58, 60, 55},
                                     {14, 13, 16, 24, 40, 57, 69, 56},
                                     {14, 17, 22, 29, 51, 87, 80, 62},
                                     {18, 22, 37, 56, 68, 109, 103, 77},
                                     {24, 35, 55, 64, 81, 104, 113, 92},
                                     {49, 64, 78, 87, 103, 121, 120, 101},
                                     {72, 92, 95, 98, 112, 100, 103, 99}};

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
      dst.at<int>(i, j) =
          (int)(dst.at<int>(i, j) / QuantizationTable[i][j]);
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
      dst.at<int>(i, j) =
          (int)(dst.at<int>(i, j) * QuantizationTable[i][j]);
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