#include "toBase64.h"

std::string toBase64(std::bitset<44> bits)
{
  std::string out;

  std::string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  // convert to string by converting 6 bits at a time (last bits are 0-padded)
  for (int i = 0; i < 44; i += 6)
  {
    int val = 0;
    for (int j = 0; j < 6; j++)
    {
      val <<= 1;
      val |= bits[i + j];
    }
    out += base64Chars[val];
  }

  return out;
}