﻿#pragma once

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


struct Material
{
    glm::vec3 ka; 
    glm::vec3 kd; 
    glm::vec3 ks; 
    GLfloat shininess; 
    Material()
    {
        ka = glm::vec3(0.0215, 0.1745, 0.0215);
        kd = glm::vec3(0.07568, 0.61424, 0.07568);
        ks = glm::vec3(0.633, 0.727811, 0.633);
        shininess = 128 * 0.6;
    };
};


struct DirLight
{
    
    glm::vec3 direction;
  
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct PointLight
{
   
    glm::vec3 position;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct SpotLight
{
   
    glm::vec3 position;
    glm::vec3 direction;
   
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};


struct LightsInfo {
 
    DirLight dirLight;
   
    std::vector<PointLight> pointLights;
 
    std::vector<SpotLight> spotLights;

    int numPLights;
    int numSLights;

};




class Model
{
public:
   
    Model(GLFWwindow* w, GLuint mode = 0) {
        glGenVertexArrays(1, &vao);
        window = w;
        modelMode = mode;
    };

  
    ~Model() {};

    void render(GLuint mode = GL_TRIANGLES);
  
    void render(glm::mat4 MVPMatrix, GLuint mode);
   
    void render(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix, GLuint mode);

    void render(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix, LightsInfo lights, GLuint mode);

    
    void load_coords(glm::vec3* verteces, size_t count);
   
    void load_colors(glm::vec3* colors, size_t count);

  
    void load_indices(GLuint* indices, size_t count);

    void load_normals(glm::vec3* normals, size_t count);

 
    void load_texcoord(glm::vec2* tex, size_t count);

  
    void load_texture(string path, string pathtomap);

   
    void load_shaders(const char* vect, const char* frag);

    
    void setMaterial(glm::vec3 a, glm::vec3 d, glm::vec3 s, GLfloat shine);


    void SetCoords(glm::vec3 _coords);

    glm::vec3 GetCoords();
private:

   
    GLuint vao = -1;    

    size_t verteces_count = 0;

    size_t indices_count = 0;

    GLuint shader_programme = -1;

    GLFWwindow* window;

    Material material;

   
 
    GLuint modelMode = 0;

    
    GLuint texture = -1;
    
    GLuint texturemap = -1;

    glm::vec3 coords = glm::vec3(0);



};

