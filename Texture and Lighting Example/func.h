#pragma once

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Model.h"


using namespace std;
struct angles
{
    GLfloat fi;
    GLfloat teta;
};

string LoadShader(const char* filename);


GLFWwindow* InitAll(int w = 640, int h = 480, bool Fullscreen = false);

void EndAll();

void window_size_callback(GLFWwindow* window, int width, int height);

void key_callbackGlobal(GLFWwindow* window, int key, int scancode, int action, int mods);
void key_callbackLocal(GLFWwindow* window, int key, int scancode, int action, int mods);
void MoveObj(glm::vec3& obj, GLfloat _fi, GLfloat _teta);
void MoveCam(GLfloat fi, GLfloat teta, GLfloat speed);
void RotateCam(glm::vec3 CamPos, glm::vec3& target, GLfloat _radius);
void InitSunLights(LightsInfo& Lights, DirLight& lSource, PointLight& P, SpotLight& SP);
GLfloat FindRadius(GLfloat x, GLfloat y, GLfloat z);

bool loadOBJ(
    const char* path,
    std::vector < glm::vec3 >& outVertices,
    std::vector < glm::vec2 >& outTextures,
    std::vector < glm::vec3 >& outNormals
);

void genSphere(
    std::vector < GLuint >& outIndexes,
    std::vector < glm::vec3 >& outVertices,
    std::vector < glm::vec2 >& outTextures,
    std::vector < glm::vec3 >& outNormals,
    float radius,
    int sectorCount,
    int stackCount
);


