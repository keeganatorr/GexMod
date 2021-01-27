#pragma once
#include "pch.h"
#include <stdio.h>
#include <Windows.h>
#include <string>
#include "detours.h"
#pragma comment(lib, "detours.lib")

#include "loguru.hpp"

#include <ddraw.h>
#include <sstream>
#include <vector>
#include <list>
#include <time.h>
#include <iostream>

#include "Globals.h"

GEX_VAR(1, 0x48294c, unsigned int, DAT_004a294c_FreezeGame, 0);
