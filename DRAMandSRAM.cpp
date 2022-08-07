#include "DRAMandSRAM.hpp"

DRAM::DRAM()
{
}

DRAM::~DRAM()
{
}

void DRAM::StorageBits(std::bitset<8> &BinaryTemp)
{
  for (u_int8_t i = BinaryTemp.size() - 1; i > 0; i--)
  {
    DRAM_Bits[CountBinaryTemp].push_back(BinaryTemp[i]);
  }
  CountBinaryTemp++;
}

void DRAM::ShowStorageBits()
{
  vector<vector<u_int8_t>>::iterator t;
  vector<u_int8_t>::iterator l;
  for (t = DRAM_Bits.begin(); t != DRAM_Bits.end(); t++)
  {
    for (l = (*t).begin(); l != (*t).end(); l++)
    {
      printf("\033[29m"
             "--> ");
      fmt::print("{:x} ", *l);
    }
    fmt::print("\n");
  }
}

u_int32_t DRAM::CountHighBits(vector<vector<u_int8_t>> &DRAM_Bits)
{
}

SRAM::SRAM(/* args */)
{
}

SRAM::~SRAM()
{
}