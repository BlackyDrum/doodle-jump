#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

#include <json/json.h>

#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <fstream>
#include <math.h>
#include <memory>
#include <limits>

#ifdef _WIN32
#include <Windows.h>
#include <Psapi.h>
#endif

const unsigned int SCREEN_WIDTH = 540, SCREEN_HEIGHT = 860;

#endif