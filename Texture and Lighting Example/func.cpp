#include "func.h"
#include "Model.h"
#include "globals.h"
#define ROTATION_SPEED PI/36

angles tempangles = { PI, 0 };

using namespace glm;

string LoadShader(const char* filename)
{
    string res;
    ifstream file(filename, ios::in);
    if (file.is_open()) {
        std::stringstream sstr; 
        sstr << file.rdbuf(); 
        res = sstr.str();   
        file.close();       
    }
    return res;
}

GLFWwindow* InitAll(int w, int h, bool Fullscreen)
{
   
    WinWidth = w;
    WinHeight = h;

    
    GLFWwindow* window = nullptr;

    
    if (!glfwInit()) {
        cerr << "ERROR: could not start GLFW3\n";
        exit(-1);
    }


    if (Fullscreen)
    {

        GLFWmonitor* mon = glfwGetPrimaryMonitor();
        const GLFWvidmode* vmode = glfwGetVideoMode(mon);
        WinWidth = vmode->width;
        WinHeight = vmode->height;
        window = glfwCreateWindow(WinWidth, WinHeight, "Cosmos", mon, NULL);

    }
    else
        window = glfwCreateWindow(WinWidth, WinHeight, "Cosmos", NULL, NULL);

   
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetKeyCallback(window, key_callbackGlobal);

   
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    stbi_set_flip_vertically_on_load(true);
    
    if (glewInit() != GLEW_OK) {
        cerr << "ERROR: could not start GLEW\n";
        return nullptr;
    }

   
    return window;
}
GLfloat FindRadius(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat rad = 0;
    rad = pow(x, 2) + pow(y, 2) + pow(z, 2);
    rad = sqrt(rad);
    return rad;
}
void EndAll()
{
    glfwTerminate();
}

void window_size_callback(GLFWwindow* window, int width, int height)
{

    WinWidth = width;
    WinHeight = height;
}

void key_callbackGlobal(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        cout << tempcoords.x << " x " << tempcoords.y << " y " << tempcoords.z
            << " z  coords" << endl;
        cout << CamTarget.x << " x " << CamTarget.y << " y " << CamTarget.z
            << " z  target" << endl;

        MoveCam(fi, teta, CamSpeed);



    }
    if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        MoveCam(fi - PI, -teta, CamSpeed);


    }
    if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        MoveCam(fi - PI / 2, 0, CamSpeed);

    }
    if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        MoveCam(fi + PI / 2, 0, CamSpeed);

    }
    if (key == GLFW_KEY_SPACE && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        MoveCam(fi, teta + PI / 2, CamSpeed);

    }
    if (key == GLFW_KEY_LEFT_SHIFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        MoveCam(fi, teta - PI / 2, CamSpeed);

    }
    if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        fi += ROTATION_SPEED;

        RotateCam(CamPosition, CamTarget, 2);
        CamMoved = true;
    }
    if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {

        fi -= ROTATION_SPEED;
        RotateCam(CamPosition, CamTarget, 2);
        CamMoved = true;
    }
    if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        teta += ROTATION_SPEED;
        RotateCam(CamPosition, CamTarget, 2);
        CamMoved = true;
    }
    if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        teta -= ROTATION_SPEED;
        RotateCam(CamPosition, CamTarget, 2);
        CamMoved = true;
    }
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        CamPosition = CamPositionL;
        fi = tempangles.fi;
        teta = tempangles.teta;
        cout << fi << " fiiiiiiii " << teta << " tetaaaaaaa " << endl;
        CamTarget = tempcoords;
        glfwSetKeyCallback(window, key_callbackLocal);
        CamMoved = true;
    }


}
void key_callbackLocal(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        MoveCam(fi - PI, -teta, CamSpeed);
        MoveObj(tempcoords, fi - PI, -teta);
    }
    if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        MoveCam(fi, teta, CamSpeed);
        MoveObj(tempcoords, fi, teta);
    }
    if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        MoveCam(fi + PI / 2, 0, CamSpeed);
        MoveObj(tempcoords, fi + PI / 2, 0);
    }
    if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {

        MoveCam(fi - PI / 2, 0, CamSpeed);
        MoveObj(tempcoords, fi - PI / 2, 0);
    }
    if (key == GLFW_KEY_SPACE && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        MoveCam(fi, teta + PI / 2, CamSpeed);
        MoveObj(tempcoords, fi, teta + PI / 2);
    }
    if (key == GLFW_KEY_LEFT_SHIFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        MoveCam(fi, teta - PI / 2, CamSpeed);
        MoveObj(tempcoords, fi, teta - PI / 2);
    }
    if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        fi -= ROTATION_SPEED;

        RotateCam(tempcoords, CamPosition, 1);
        CamTarget = tempcoords;
        CamMoved = true;
    }
    if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {

        fi += ROTATION_SPEED;

        RotateCam(tempcoords, CamPosition, 1);
        CamTarget = tempcoords;
        CamMoved = true;
    }
    if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        teta -= ROTATION_SPEED;
        RotateCam(tempcoords, CamPosition, 1);
        CamTarget = tempcoords;
        CamMoved = true;
    }
    if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        teta += ROTATION_SPEED;
        RotateCam(tempcoords, CamPosition, 1);
        CamTarget = tempcoords;
        CamMoved = true;
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        CamPositionL = CamPosition;
        CamPosition = { 0, 2, -2 };
        tempangles.fi = fi;
        tempangles.teta = teta;

        fi = 0;
        teta = -PI / 4;
        RotateCam(CamPosition, CamTarget, 1);
        glfwSetKeyCallback(window, key_callbackGlobal);
        CamMoved = true;
    }


}

void MoveObj(glm::vec3& obj, GLfloat _fi, GLfloat _teta)
{
    obj.z += (CamSpeed)*cos(_fi) * cos(_teta);
    obj.x += (CamSpeed)*sin(_fi) * cos(_teta);
    obj.y += (CamSpeed)*sin(_teta);
    ObjMoved = true;
}

void MoveCam(GLfloat fi, GLfloat teta, GLfloat speed)
{
    CamPosition.z += (speed)*cos(fi) * cos(teta);
    CamPosition.x += (speed)*sin(fi) * cos(teta);
    CamPosition.y += (speed)*sin(teta);
    CamTarget.z += (speed)*cos(fi) * cos(teta);
    CamTarget.x += (speed)*sin(fi) * cos(teta);
    CamTarget.y += (speed)*sin(teta);
    CamMoved = true;
}

void RotateCam(glm::vec3 pos, glm::vec3& target, GLfloat _radius)
{
    target.z = (_radius)*cos(fi) * cos(teta) + pos.z;
    target.x = (_radius)*sin(fi) * cos(teta) + pos.x;
    target.y = (_radius)*sin(teta) + pos.y;
}

bool loadOBJ(const char* path, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outTextures, std::vector<glm::vec3>& outNormals)
{
   
    std::vector< unsigned int > vertexIndices, vtIndices, normalIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_textures;
    std::vector< glm::vec3 > temp_normals;

    
    string buf;
    
    std::stringstream sstr;
    bool cont = false;

   
    ifstream file(path, ios::in);
    if (file.is_open()) {
        sstr << file.rdbuf();
        file.close();
    }
    else
        return false;

    
    outNormals.clear();
    outVertices.clear();
    outTextures.clear();

    
    while (cont || sstr >> buf) {
        cont = false;

      
        if (buf == "v") {
            glm::vec3 vertex;
            sstr >> vertex.x;
            sstr >> vertex.y;
            sstr >> vertex.z;
            temp_vertices.push_back(vertex);
        }
       
        else if (buf == "vt") {
            glm::vec2 texture;
            sstr >> texture.x;
            sstr >> texture.y;
            temp_textures.push_back(texture);
        }
      
        else if (buf == "vn") {
            glm::vec3 normal;
            sstr >> normal.x;
            sstr >> normal.y;
            sstr >> normal.z;
            temp_normals.push_back(normal);
        }
       
        else if (buf == "f") {
           
            vector<string> vertexes;
            vector<int> vertindexes;
            while (!cont)
            {
               
                sstr >> buf;
               
                if (buf.find('/') != string::npos)
                    vertexes.push_back(buf);
               
                else
                {
                  
                    for (string vert : vertexes)
                    {
                        std::replace(vert.begin(), vert.end(), '/', ' ');
                        std::stringstream tmpstream(vert);
                        int v, vt, n;
                        tmpstream >> v;
                        tmpstream >> vt;
                        tmpstream >> n;
                      
                        vertindexes.push_back(v);
                        vertindexes.push_back(vt);
                        vertindexes.push_back(n);
                    }
                   
                    for (int i = 0; i < 3; i++)
                    {
                        vertexIndices.push_back(vertindexes[i * 3 + 0]);
                        vtIndices.push_back(vertindexes[i * 3 + 1]);
                        normalIndices.push_back(vertindexes[i * 3 + 2]);
                    }
                   
                    size_t tmpsize = vertexes.size();
                    if (tmpsize > 3)
                    {
                       
                        for (int i = 3; i < tmpsize; i++)
                        {
                            vertexIndices.push_back(vertindexes[0]);
                            vtIndices.push_back(vertindexes[1]);
                            normalIndices.push_back(vertindexes[2]);
                            vertexIndices.push_back(vertindexes[(i - 1) * 3 + 0]);
                            vtIndices.push_back(vertindexes[(i - 1) * 3 + 1]);
                            normalIndices.push_back(vertindexes[(i - 1) * 3 + 2]);
                            vertexIndices.push_back(vertindexes[i * 3 + 0]);
                            vtIndices.push_back(vertindexes[i * 3 + 1]);
                            normalIndices.push_back(vertindexes[i * 3 + 2]);
                        }
                    }
                   
                    cont = true;
                }
            }
        }
    }
    
    size_t tmpsize = vertexIndices.size();
    for (unsigned int i = 0; i < tmpsize; i++)
    {
        
        glm::vec3 vertex = temp_vertices[vertexIndices[i] - 1];
        outVertices.push_back(vertex);
        glm::vec3 normal = temp_normals[normalIndices[i] - 1];
        outNormals.push_back(normal);
        glm::vec2 vt = temp_textures[vtIndices[i] - 1];
        outTextures.push_back(vt);
    }
    return true;
}

void genSphere(std::vector<GLuint>& outIndexes, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outTextures, std::vector<glm::vec3>& outNormals, float radius, int sectorCount, int stackCount)
{
    //??????? ???????? ????????
    outIndexes.clear();
    outNormals.clear();
    outVertices.clear();
    outTextures.clear();

    //??????????????? ?????????? ??? ???????? ????????????? ??????
    float x, y, z, xy;
    float nx, ny, nz, lengthInv = 1.0f / radius;
    float s, t;
    float sectorStep = 2.0f * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    //???? ?? ?????? ?????????
    for (int i = 0; i <= stackCount; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // ??????? ?? PI/2 ? ?? -PI/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // ?? ?????? ????????? ??????????? (sectorCount+1) ??????
        // ??? ?????? ? ????????? ????????? ??????? ? ???????, ?? ?????????? ?????????? ??????????
        for (int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // ?? 0 ?? 2PI

            // ????????????? ?????????? (x, y, z)
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            glm::vec3 vert;
            vert.x = x;
            vert.y = y;
            vert.z = z;
            outVertices.push_back(vert);

            // ????????????? ?????? ??????? (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            glm::vec3 norm;
            norm.x = nx;
            norm.y = ny;
            norm.z = nz;
            outNormals.push_back(norm);

            
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            glm::vec2 vt;
            vt.s = s;
            vt.t = t;
            outTextures.push_back(vt);
        }

        
        int k1, k2;
        for (int i = 0; i < stackCount; ++i)
        {
            k1 = i * (sectorCount + 1);     
            k2 = k1 + sectorCount + 1;      

            for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
            {
               
                if (i != 0)
                {
                    outIndexes.push_back(k1);
                    outIndexes.push_back(k2);
                    outIndexes.push_back(k1 + 1);
                }

                // k1+1 => k2 => k2+1
                if (i != (stackCount - 1))
                {
                    outIndexes.push_back(k1 + 1);
                    outIndexes.push_back(k2);
                    outIndexes.push_back(k2 + 1);
                }
            }
        }
    }
}


void InitSunLights(LightsInfo& Lights, DirLight& lSource, PointLight& P, SpotLight& SP)
{

    Lights.numPLights = 2;
    Lights.numSLights = 0;

    vec3 SunlightPos = { 0,0,0 };
    vec3 StarlightPos = { 3.0,3.0,3.0 };




    lSource.ambient = { 0.2f, 0.2f, 0.2f };
    lSource.diffuse = { 0.5f, 0.5f, 0.5f };
    lSource.specular = { 1,1,1 };
    lSource.direction = vec3(0, -1, 0);

    Lights.dirLight = lSource;


    P.ambient = vec3(0.4f, 0.4f, 0.4f);
    P.diffuse = vec3(0.8f, 0.8f, 0.8f);
    P.specular = vec3(1, 1, 1);
    P.position = SunlightPos;
    P.constant = 1;
    P.linear = 0.09;
    P.quadratic = 0.032;
    Lights.pointLights.push_back(P);

    P.ambient = vec3(0.4f, 0.4f, 0.4f);
    P.diffuse = vec3(0.8f, 0.8f, 0.8f);
    P.specular = vec3(1, 1, 1);
    P.position = StarlightPos;
    P.constant = 1;
    P.linear = 0.09;
    P.quadratic = 0.032;
    Lights.pointLights.push_back(P);

}