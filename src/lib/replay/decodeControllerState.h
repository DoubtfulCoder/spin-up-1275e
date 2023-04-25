#pragma once
#include "../controller.h"
#include <bitset>

ControllerState decodeControllerState(std::bitset<44> encoded);