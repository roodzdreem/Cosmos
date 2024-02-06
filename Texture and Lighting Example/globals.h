#pragma once

#include <glm/glm.hpp>
#include "stb_image.h"

#define PI 3.14159265358979323846f  

extern const glm::mat4 WorldMatrix;


extern int WinWidth;
extern int WinHeight;

extern GLfloat fi;
extern GLfloat teta;


extern glm::vec3 CamPositionL;
extern glm::vec3 CamPosition;
extern glm::vec3 CamTarget;

extern bool CamMoved;
extern GLfloat CamSpeed;

extern glm::vec3 tempcoords;
extern bool ObjMoved;