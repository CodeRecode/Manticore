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
#include <gtc\type_ptr.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtx\transform.hpp>


extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include "LuaBridge.h"