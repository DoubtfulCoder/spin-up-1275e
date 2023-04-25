#include "fromBase64.h"

std::bitset<44> fromBase64(std::string base64)
{
  std::bitset<44> out;

  std::string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  // convert to string by converting 6 bits at a time (last bits are 0-padded)
  for (int i = 0; i < 44; i += 6)
  {
    int val = 0;
    for (int j = 0; j < 6; j++)
    {
      val <<= 1;
      val |= base64Chars.find(base64[i + j]);
    }
    for (int j = 0; j < 6; j++)
    {
      out[i + j] = val & 1;
      val >>= 1;
    }
  }

  return out;
}