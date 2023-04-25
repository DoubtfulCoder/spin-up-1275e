#include "encodeControllerState.h"

std::bitset<44> encodeControllerState(ControllerState state)
{
  std::bitset<44> bits;

  // first 8 bits are left joystick x + 127
  int leftX = state.left.x + 127;
  for (int i = 0; i < 8; i++)
  {
    bits[i] = leftX & 1;
    leftX >>= 1;
  }

  // next 8 bits are left joystick y + 127
  int leftY = state.left.y + 127;
  for (int i = 8; i < 16; i++)
  {
    bits[i] = leftY & 1;
    leftY >>= 1;
  }

  // next 8 bits are right joystick x + 127
  int rightX = state.right.x + 127;
  for (int i = 16; i < 24; i++)
  {
    bits[i] = rightX & 1;
    rightX >>= 1;
  }

  // next 8 bits are right joystick y + 127
  int rightY = state.right.y + 127;
  for (int i = 24; i < 32; i++)
  {
    bits[i] = rightY & 1;
    rightY >>= 1;
  }

  // next 12 bits are buttons
  // Up, Down, Left, Right, A, B, X, Y, L1, L2, R1, R2
  bits[32] = state.UP;
  bits[33] = state.DOWN;
  bits[34] = state.LEFT;
  bits[35] = state.RIGHT;
  bits[36] = state.A;
  bits[37] = state.B;
  bits[38] = state.X;
  bits[39] = state.Y;
  bits[40] = state.L1;
  bits[41] = state.L2;
  bits[42] = state.R1;
  bits[43] = state.R2;

  return bits;
}