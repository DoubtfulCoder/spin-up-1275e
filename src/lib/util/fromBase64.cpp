#include "fromBase64.h"

std::bitset<44> fromBase64(std::string base64)
{
  std::bitset<44> out;

  std::string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  // convert to string by converting 1 char at a time
  for(int i = 0; i < base64.length(); i++)
  {
    int val = base64Chars.find(base64[i]);
    for(int j = 0; j < 6; j++)
    {
      out[i * 6 + j] = val & 1;
      val >>= 1;
    }
  }

  return out;
}