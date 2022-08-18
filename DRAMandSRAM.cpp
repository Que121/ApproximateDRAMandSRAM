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
  StorageBits(BinaryTemp, storageSizecount);
  vector<vector<u_int8_t>>::iterator t = SRAM_Bits.begin();
  vector<vector<u_int8_t>>::iterator t_last = SRAM_LastBits.begin();
  while ((t != SRAM_Bits.end()) && (t_last != SRAM_Bits.end()))
  {
    vector<u_int8_t>::iterator l = (*t).begin();
    vector<u_int8_t>::iterator l_last = (*t_last).begin();
    while ((l != (*t).end()) && (l_last != (*t_last).end()))
    {
      if ((*l) != (*l_last))
      {
        count++;
      }
    }
  }
  SRAM_LastBits = SRAM_Bits;
  SRAM_Bits.clear();
  fmt::print("{:d} ", count);
  return count;
}

void SRAM::CalculateFlipProbability(std::bitset<8> &BinaryTemp, u_int32_t storageSizecount)
{
  double FlipProbability = 0;
 
}