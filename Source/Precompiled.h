#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <IL\il.h>
#include <IL\ilu.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <glm.hpp>


extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include "LuaBridge.h"