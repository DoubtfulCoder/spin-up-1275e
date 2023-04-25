#include "decodeControllerState.h"

ControllerState decodeControllerState(std::bitset<44> encoded)
{
  ControllerState state;

  // first 8 bits are left joystick x + 127
  int leftX = 0;
  for (int i = 0; i < 8; i++)
  {
    leftX |= encoded[i] << i;
  }
  state.left.x = leftX - 127;

  // next 8 bits are left joystick y + 127
  int leftY = 0;
  for (int i = 8; i < 16; i++)
  {
    leftY |= encoded[i] << (i - 8);
  }
  state.left.y = leftY - 127;

  // next 8 bits are right joystick x + 127
  int rightX = 0;
  for (int i = 16; i < 24; i++)
  {
    rightX |= encoded[i] << (i - 16);
  }
  state.right.x = rightX - 127;

  // next 8 bits are right joystick y + 127
  int rightY = 0;
  for (int i = 24; i < 32; i++)
  {
    rightY |= encoded[i] << (i - 24);
  }
  state.right.y = rightY - 127;

  // next 12 bits are buttons
  // Up, Down, Left, Right, A, B, X, Y, L1, L2, R1, R2
  state.UP = encoded[32];
  state.DOWN = encoded[33];
  state.LEFT = encoded[34];
  state.RIGHT = encoded[35];
  state.A = encoded[36];
  state.B = encoded[37];
  state.X = encoded[38];
  state.Y = encoded[39];
  state.L1 = encoded[40];
  state.L2 = encoded[41];
  state.R1 = encoded[42];
  state.R2 = encoded[43];

  return state;
}