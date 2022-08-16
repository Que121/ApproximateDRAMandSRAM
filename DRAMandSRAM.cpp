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
  vector<vector<u_int8_t>>::iterator t;
  vector<u_int8_t>::iterator l;
  ofstream opt;
  opt.open(excelName, ios::out | ios::trunc);
  for (t = DRAM_Bits.begin(); t != DRAM_Bits.end(); t++)
  {
    for (l = (*t).begin(); l != (*t).end(); l++)
    {
      opt << *l << endl;
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
  return  (double)(CountHighBits())/(double)(GetAllBits());
}

SRAM::SRAM(/* args */)
{
}

SRAM::~SRAM()
{
}