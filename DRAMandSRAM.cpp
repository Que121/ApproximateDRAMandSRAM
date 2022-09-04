#include "DRAMandSRAM.hpp"

DRAM::DRAM()
{
}

DRAM::~DRAM()
{
}

void DRAM::StorageBits(std::bitset<8> &BinaryTemp)
{
  vector<u_int8_t> temp;
  for (int8_t i = BinaryTemp.size() - 1; i > -1; i--)
  {
    temp.push_back(BinaryTemp[i]);
  }
  DRAM_Bits.push_back(temp);
}

void DRAM::ShowStorageBits()
{
  vector<vector<u_int8_t>>::iterator t;
  vector<u_int8_t>::iterator l;
  for (t = DRAM_Bits.begin(); t != DRAM_Bits.end(); t++)
  {
    // printf("\033[29m"
    //        "--> ");
    for (l = (*t).begin(); l != (*t).end(); l++)
    {
      fmt::print("{:x} ", *l);
    }
    fmt::print("\n");
  }
}

void DRAM::ShowGroupsBits()
{
  fmt::print("{:d} ", DRAM_Bits.size());
}

u_int32_t DRAM::GetAllBits()
{
  return DRAM_Bits.size() * 8;
}

void DRAM::WriteExcelBits(const cv::String &excelName)
{
  u_int32_t count = 0;
  vector<vector<u_int8_t>>::iterator t;
  vector<u_int8_t>::iterator l;
  ofstream opt;
  opt.open(excelName, ios::out | ios::trunc);
  for (t = DRAM_Bits.begin(); t != DRAM_Bits.end(); t++)
  {
    for (l = (*t).begin(); l != (*t).end(); l++)
    {
      opt << *l;
    }
  }
  opt.close();
}

u_int32_t DRAM::CountHighBits()
{
  u_int32_t count = 0;
  vector<vector<u_int8_t>>::iterator t;
  vector<u_int8_t>::iterator l;
  for (t = DRAM_Bits.begin(); t != DRAM_Bits.end(); t++)
  {
    for (l = (*t).begin(); l != (*t).end(); l++)
    {
      if (*l == 1)
      {
        count++;
      }
    }
  }
  return count;
}

double DRAM::GetHighBitsAverage()
{
  return (double)(CountHighBits()) / (IMAGE_WIDTH * IMAGE_HEIGHT);
}

double DRAM::GetHighBitsPercentage()
{
  return (double)(CountHighBits()) / (double)(GetAllBits());
}

SRAM::SRAM()
{
  SRAM_LastBits.resize(SRAM_storageSizeByte,
                       vector<u_int8_t>(BITS_8)); // 初始化
}

SRAM::~SRAM()
{
}

void SRAM::StorageBits(std::bitset<8> &BinaryTemp, u_int32_t storageSizecount)
{
  if (SRAM_Bits.size() < storageSizecount)
  {
    vector<u_int8_t> temp;
    for (int8_t i = BinaryTemp.size() - 1; i > -1; i--)
    {
      temp.push_back(BinaryTemp[i]);
    }
    SRAM_Bits.push_back(temp);
  }
}

void SRAM::ShowStorageBits()
{
  vector<vector<u_int8_t>>::iterator t;
  vector<u_int8_t>::iterator l;
  for (t = SRAM_Bits.begin(); t != SRAM_Bits.end(); t++)
  {
    for (l = (*t).begin(); l != (*t).end(); l++)
    {
      fmt::print("{:x} ", *l);
    }
    fmt::print("\n");
  }
}

u_int32_t SRAM::ShowGroupsBits()
{
  return SRAM_Bits.size();
}

u_int32_t SRAM::GetAllBits()
{
  return SRAM_Bits.size() * BITS_8;
}

u_int32_t SRAM::CalculateFlipBits(std::bitset<8> &BinaryTemp, u_int32_t storageSizecount)
{
  u_int32_t count = 0;
  u_int32_t storageBitsFlag = storageSizecount;
  // StorageBits(BinaryTemp, storageBitsFlag); // 正常
  if (SRAM_Bits.size() == storageBitsFlag)
  {
    vector<vector<u_int8_t>>::iterator t;
    vector<vector<u_int8_t>>::iterator t_last = SRAM_LastBits.begin();
    vector<u_int8_t>::iterator l;
    vector<u_int8_t>::iterator l_last;
    for (t = SRAM_Bits.begin(), t_last = SRAM_LastBits.begin();
         (t != SRAM_Bits.end()) && (t_last != SRAM_LastBits.end()); t++, t_last++)
    {
      for (l = (*t).begin(), l_last = (*t_last).begin();
           (l != (*t).end()) && (l_last != (*t_last).end()); l++)
      {
        if ((*l) != (*l_last))
        {
          count++;
        }
      }
    }
    SRAM_LastBits = SRAM_Bits;
    SRAM_Bits.clear();
    // fmt::print("{:d} ", count);
  }
  return count;
}

double SRAM::CalculateFlipProbability()
{
  return (double)(SRAM_FlipTimes) / (double)(SRAM_Bits.size() * BITS_8);
}

double SRAM::CalculateAllFlipProbability()
{
  u_int32_t allFilpTimes = this->allFilpTimes;
  this->allFilpTimes = 0;
  return (double)(allFilpTimes) / (double)(IMAGE_WIDTH * IMAGE_HEIGHT * BITS_8);
}

void SRAM::CalculateFlipBits(u_int32_t &StorageLoopTimes, u_int32_t &storageBitsFlag)
{
  if (SRAM_Bits.size() == storageBitsFlag)
  {
    u_int32_t count = 0;
    vector<vector<u_int8_t>>::iterator t;
    vector<vector<u_int8_t>>::iterator t_last = SRAM_LastBits.begin();
    vector<u_int8_t>::iterator l;
    vector<u_int8_t>::iterator l_last;
    for (t = SRAM_Bits.begin(), t_last = SRAM_LastBits.begin();
         (t != SRAM_Bits.end()) && (t_last != SRAM_LastBits.end()); t++, t_last++)
    {
      for (l = (*t).begin(), l_last = (*t_last).begin();
           (l != (*t).end()) && (l_last != (*t_last).end()); l++)
      {
        if ((*l) != (*l_last))
        {
          count++;
        }
      }
    }
    SRAM_FlipTimes = count;
    allFilpTimes += count;
    fmt::print("翻转个数：{:d} 总比特：{:d}\n第{:d}次存储的翻转概率为：{:f}\n", SRAM_FlipTimes, SRAM_Bits.size() * BITS_8,
               StorageLoopTimes_flag, CalculateFlipProbability());
    if (StorageLoopTimes_flag < StorageLoopTimes)
    {
      SRAM_LastBits = SRAM_Bits;
      SRAM_Bits.clear();
    }
    StorageLoopTimes_flag++;
  }
}