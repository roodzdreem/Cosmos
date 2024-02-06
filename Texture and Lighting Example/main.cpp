#include "Model.h"
#include "func.h"

#define PI 3.14159265358979323846f  
#define SUNROTATIONSPEED 0.5f 

using namespace glm;
const  mat4 WorldMatrix = mat4(1.0f);

vec3 tempcoords = vec3(1, 0, 0);;

int WinWidth;
int WinHeight;


vec3 CamPositionL;
vec3 CamPosition;

GLfloat fi = 0;
GLfloat teta = -PI / 4;

vec3 CamTarget = vec3(0);
bool CamMoved = false;
bool ObjMoved = true;
GLfloat CamSpeed = 0.1;

int main() {
    srand(time(nullptr));

    GLFWwindow* window = InitAll(1024, 768, false);
    if (window == nullptr)
    {
        EndAll();
        return -1;
    }



    
    std::vector<  vec3 > temp_vertices;
    std::vector<  vec2 > temp_textures;
    std::vector<  vec3 > temp_normals;
    std::vector<  vec3 > temp_colors;
    std::vector< GLuint > temp_indices;
    size_t size;

    //sun
    genSphere(temp_indices, temp_vertices, temp_textures, temp_normals, 5, 50, 50);
    size = temp_vertices.size();
    Model sun(window, 2);
    sun.load_coords(temp_vertices.data(), size);
    sun.load_normals(temp_normals.data(), temp_normals.size());
    sun.load_texcoord(temp_textures.data(), temp_textures.size());
    sun.load_indices(temp_indices.data(), temp_indices.size());
    sun.setMaterial(vec3(0), vec3(0), vec3(0), 2);
    sun.load_shaders("texvs.glsl", "texfs.glsl");
    sun.load_texture("sun.jpg", "");

    //star
    genSphere(temp_indices, temp_vertices, temp_textures, temp_normals, 5, 50, 50);
    size = temp_vertices.size();
    Model star(window, 2);
    star.load_coords(temp_vertices.data(), size);
    star.load_normals(temp_normals.data(), temp_normals.size());
    star.load_texcoord(temp_textures.data(), temp_textures.size());
    star.load_indices(temp_indices.data(), temp_indices.size());
    star.setMaterial(vec3(0), vec3(0), vec3(0), 2);
    star.load_shaders("texvs.glsl", "texfs.glsl");
    star.load_texture("star.jpg", "");

    //Cosmos
    
    genSphere(temp_indices, temp_vertices, temp_textures, temp_normals, 5, 50, 50);
    size = temp_vertices.size();
    Model cosmos(window, 2);
    cosmos.load_coords(temp_vertices.data(), size);
    cosmos.load_normals(temp_normals.data(), temp_normals.size());
    cosmos.load_texcoord(temp_textures.data(), temp_textures.size());
    cosmos.load_indices(temp_indices.data(), temp_indices.size());
    cosmos.setMaterial(vec3(0), vec3(0), vec3(0), 2);
    cosmos.load_shaders("texvs.glsl", "texfs.glsl");
    cosmos.load_texture("cosmos.jpg", "");
    //spaceship
    loadOBJ("13884_UFO_Saucer_v1_l2.obj", temp_vertices, temp_textures, temp_normals);
    size = temp_vertices.size();
    Model spaceship(window,2);
   
    spaceship.load_coords(temp_vertices.data(), size);
    spaceship.load_normals(temp_normals.data(), temp_normals.size());
    spaceship.load_texcoord(temp_textures.data(), temp_textures.size());
    spaceship.load_shaders("texvs.glsl", "texfs.glsl");
    spaceship.setMaterial(glm::vec3(0), glm::vec3(0), glm::vec3(0), 128);
    spaceship.load_texture("13884_Diffuse.jpg", "");
    

    //planet 1
    genSphere(temp_indices, temp_vertices, temp_textures, temp_normals, 5, 50, 50);
    size = temp_vertices.size();
    Model planet(window, 2);
    planet.load_coords(temp_vertices.data(), size);
    planet.load_normals(temp_normals.data(), temp_normals.size());
    planet.load_texcoord(temp_textures.data(), temp_textures.size());
    planet.load_indices(temp_indices.data(), temp_indices.size());
    planet.setMaterial(vec3(0), vec3(0), vec3(0), 2);
    planet.load_shaders("texvs.glsl", "texfs.glsl");
    planet.load_texture("planet.jpg", "");

    //planet 2
    genSphere(temp_indices, temp_vertices, temp_textures, temp_normals, 5, 50, 50);
    size = temp_vertices.size();
    Model starplanet(window, 2);
    starplanet.load_coords(temp_vertices.data(), size);
    starplanet.load_normals(temp_normals.data(), temp_normals.size());
    starplanet.load_texcoord(temp_textures.data(), temp_textures.size());
    starplanet.load_indices(temp_indices.data(), temp_indices.size());
    starplanet.setMaterial(vec3(0), vec3(0), vec3(0), 2);
    starplanet.load_shaders("texvs.glsl", "texfs.glsl");
    starplanet.load_texture("mars.jpg", "");

    LightsInfo SunLights;
    DirLight lSource;
    PointLight P;
    SpotLight SP;
    InitSunLights(SunLights, lSource, P, SP);


    mat4 MMatr = WorldMatrix;
    mat4 VMatr = WorldMatrix;
    mat4 PMatr = WorldMatrix;

    
    PMatr = perspective(radians(67.0f),
        (float)WinWidth / WinHeight, 0.01f, 10000.0f);

   

    CamPositionL = { 1, 0, -1 };
    CamPosition = { 0, 2, -2 };
    VMatr = lookAt(CamPosition, CamTarget, vec3(0, 1, 0));

    
    glClearColor(0.f, 0.f, 0.f, 0.f);

   
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    float rotation = PI / 30;
    vec3 temp = { 3,3,3 };
    star.SetCoords(temp);
    starplanet.SetCoords(temp);

  
    double start_time = glfwGetTime();

    
    while (!glfwWindowShouldClose(window)) {
        glViewport(0, 0, WinWidth, WinHeight);
        rotation = glfwGetTime() - start_time;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        if (CamMoved)
        {
            VMatr = WorldMatrix;
            VMatr = lookAt(CamPosition, CamTarget, vec3(0, 1, 0));
            CamMoved = false;
        }


        // Sun
        MMatr = WorldMatrix;
        MMatr = rotate(MMatr, radians(-90.0f), vec3(1.0, 0.0, 0.0));
        MMatr = rotate(MMatr, rotation * 1, vec3(0.0, 0.0, 1.0));
        MMatr = scale(MMatr, vec3(0.1, 0.1, 0.1));
        sun.render(MMatr, VMatr, PMatr, SunLights, GL_TRIANGLES);
        // Cosmos
        MMatr = WorldMatrix;
        MMatr = scale(MMatr, vec3(2, 2, 2));
        cosmos.render(MMatr, VMatr, PMatr, SunLights, GL_TRIANGLES);

        rotation -= radians(SUNROTATIONSPEED);
        //Star
        MMatr = WorldMatrix;
        MMatr = translate(MMatr, star.GetCoords());
        MMatr = rotate(MMatr, radians(-90.0f), vec3(1.0, 0.0, 0.0));
        MMatr = rotate(MMatr, rotation * 1, vec3(0.0, 0.0, 1.0));
        MMatr = scale(MMatr, vec3(0.1, 0.1, 0.1));
        star.render(MMatr, VMatr, PMatr, SunLights, GL_TRIANGLES);
        rotation -= radians(SUNROTATIONSPEED);
        // Spaceship
        MMatr = WorldMatrix;
        if (ObjMoved)
        {
            spaceship.SetCoords(tempcoords);
            ObjMoved = false;
        }

       
        MMatr = translate(MMatr, spaceship.GetCoords());
        MMatr = scale(MMatr, vec3(0.001, 0.001, 0.001));
        MMatr = rotate(MMatr, radians(-90.0f), vec3(1.0, 0.0, 0.0));

        spaceship.render(MMatr, VMatr, PMatr, SunLights, GL_TRIANGLES);

        // planet 1
        MMatr = WorldMatrix;


        MMatr = rotate(MMatr, rotation, vec3(1.0, 0.0, 0.0));
        MMatr = translate(MMatr, vec3(0.0, 1.0, 0.0));
        MMatr = rotate(MMatr, rotation, vec3(0.0, 1.0, 0.0));
        MMatr = scale(MMatr, vec3(0.05, 0.05, 0.05));
        planet.render(MMatr, VMatr, PMatr, SunLights, GL_TRIANGLES);

        // planet 2
        MMatr = WorldMatrix;

        MMatr = rotate(MMatr, rotation, vec3(temp.x , temp.y, temp.z));
        MMatr = translate(MMatr, vec3(temp.x, temp.y + 2.0, temp.z));
        MMatr = rotate(MMatr, rotation, vec3(temp.x, temp.y, temp.z));
        MMatr = scale(MMatr, vec3(0.05, 0.05, 0.05));
        starplanet.render(MMatr, VMatr, PMatr, SunLights, GL_TRIANGLES);
        



        glfwPollEvents();
        glfwSwapBuffers(window);
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, 1);
        }
    }

    return 0;
}
