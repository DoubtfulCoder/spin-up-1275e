#include "toBase64.h"

std::string toBase64(std::bitset<44> bits)
{

  std::bitset<48> extended;

  for(int i = 0; i < 44; i++)
  {
    extended[i] = bits[i];
  }

  std::string out;

  std::string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  // convert to string by converting 6 bits at a time (last bits are 0-padded)
  for (int i = 0; i < 8; i++)
  {
    std::bitset<8> byte;
    for (int j = 0; j < 6; j++)
    {
      byte[j] = bits[i * 6 + j];
    }
    out += base64Chars[byte.to_ulong()];
  }

  return out;
}