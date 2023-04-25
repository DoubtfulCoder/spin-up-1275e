#pragma once

struct Joystick
{
  int x;
  int y;
};

struct ControllerState
{
  Joystick left;
  Joystick right;
  bool UP;
  bool DOWN;
  bool LEFT;
  bool RIGHT;
  bool A;
  bool B;
  bool X;
  bool Y;
  bool L1;
  bool L2;
  bool R1;
  bool R2;
};