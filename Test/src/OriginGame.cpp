#include <iostream>
#include <Origin.h>

using namespace glm;
using namespace origin;

class Scene : public OriginApplication
{
    private:     
        OpenGLProgram      *colored_shader;  

        OpenGLVertexArray  *cube;
        OpenGLBuffer       *cube_position_buffer;
        OpenGLBuffer       *cube_color_buffer;
        OpenGLTexture      *smiley_texture;

        GLuint              mvpMatrixUniform;  
        GLuint              textureUniform;
        mat4                projectionMatrix;  
        vec3                translation;
        vec3                rotation;

    public:
        void initialize(void);
        void resize(int width, int height);
        void render(void);
        void update(void);
        void uninitialize(void);

        void imgui_initialize(HWND hwnd);
        void imgui_callback(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
        void imgui_render(void);
        void imgui_uninitialize(void);
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    Scene scene;
    return (scene.exec(hInstance));
}

void Scene::initialize(void)
{    
    // code     
    // pass through shader program 
    colored_shader = OpenGLProgram::CreateProgram();
    OpenGLShader *vertexShader = OpenGLShader::CreateShader(GL_VERTEX_SHADER);
    OpenGLShader *fragmentShader = OpenGLShader::CreateShader(GL_FRAGMENT_SHADER);

    vertexShader->compileShaderFromFile("shaders/colored.vs");
    fragmentShader->compileShaderFromFile("shaders/colored.fs");

    colored_shader->addShader(vertexShader);
    colored_shader->addShader(fragmentShader);

    colored_shader->bindAttribLocation(ORIGIN_ATTRIBUTE_POSITION, "vPosition");
    colored_shader->bindAttribLocation(ORIGIN_ATTRIBUTE_TEXCOORD, "vTexcoord");

    colored_shader->link();

    // get uniform location
    mvpMatrixUniform = colored_shader->getUniformLocation("mvpMatrix");
    textureUniform = colored_shader->getUniformLocation("textureSampler");

    // vertex data
    const GLfloat cubeVertices[] = 
    {
        //near 
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 
        1.0f, -1.0f, 1.0f,

        //right
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,

        //far
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,

        //left
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,

        //top
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        //bottom
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f
    };

    const GLfloat cubeTexcoords[] =
    {
        // near
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        // right
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        // far 
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        //left
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        // top
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        // bottom
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
    };

    // setup vao and vbo
    cube                        = OpenGLVertexArray::CreateVertexArray();
    cube_position_buffer        = OpenGLBuffer::CreateBuffer();
    cube_color_buffer           = OpenGLBuffer::CreateBuffer();

    cube_position_buffer->setBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    cube_color_buffer->setBufferData(GL_ARRAY_BUFFER, sizeof(cubeTexcoords), cubeTexcoords, GL_STATIC_DRAW);

    cube->setVertexBuffer(cube_position_buffer);
    cube->setVertexAttribPointer(ORIGIN_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    cube->setVertexBuffer(cube_color_buffer);
    cube->setVertexAttribPointer(ORIGIN_ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    // opengl states
    glShadeModel(GL_SMOOTH);                  
    glClearDepth(1.0f);                                     
    glEnable(GL_DEPTH_TEST);                                
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  

    // initialize variables
    projectionMatrix = mat4(1.0);
    translation = vec3(0.0f, 0.0f, -6.0f);
    rotation = vec3(0.0f, 0.0f, 0.0f);

    // load textures
    smiley_texture = OpenGLTexture::CreateTexture(GL_TEXTURE_2D);
    smiley_texture->setTextureParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    smiley_texture->setTextureParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    smiley_texture->loadTexture("textures/Smiley.png");

    // release shaders
    OpenGLShader::DeleteShader(vertexShader);
    OpenGLShader::DeleteShader(fragmentShader);
}

void Scene::imgui_initialize(HWND hwnd)
{
    // variable declaration
    const char* glsl_version = "#version 430";

    // code
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void Scene::imgui_callback(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    // code
    ImGui_ImplWin32_WndProcHandler(hwnd, iMsg, wParam, lParam);
}

void Scene::resize(int width, int height)
{
    // code 
    if(height == 0)
        height = 1;

    // set viewport transformation
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    projectionMatrix = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
}

void Scene::render(void)
{
    //variable declarations
    mat4 modelViewMatrix(1.0f);
    mat4 modelViewProjectionMatrix(1.0f);

    //code
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    colored_shader->bind();

        modelViewMatrix = translate(modelViewMatrix, translation);
        modelViewMatrix = rotate(modelViewMatrix, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
        modelViewMatrix = rotate(modelViewMatrix, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
        modelViewMatrix = rotate(modelViewMatrix, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));
        modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;
        glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, &modelViewProjectionMatrix[0][0]);

        smiley_texture->bind(GL_TEXTURE0);
        glUniform1i(textureUniform, 0);

        cube->drawArrays(GL_TRIANGLE_FAN, 0, 4);
        cube->drawArrays(GL_TRIANGLE_FAN, 4, 4);
        cube->drawArrays(GL_TRIANGLE_FAN, 8, 4);
        cube->drawArrays(GL_TRIANGLE_FAN, 12, 4);
        cube->drawArrays(GL_TRIANGLE_FAN, 16, 4);
        cube->drawArrays(GL_TRIANGLE_FAN, 20, 4);

        smiley_texture->unbind();

    colored_shader->unbind();
}

void Scene::update(void)
{
    // code 
}

void Scene::imgui_render(void)
{
    // code
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Debug window");
    ImGui::SliderFloat3("Translation", &translation.x, -6.0f, 6.0f);
    ImGui::SliderFloat3("Rotation", &rotation.x, 0.0f, 360.0f);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Scene::uninitialize(void)
{
    // code
    OpenGLProgram::DeleteProgram(colored_shader);
    OpenGLTexture::DeleteTexture(smiley_texture);
    OpenGLBuffer::DeleteBuffer(cube_position_buffer);
    OpenGLBuffer::DeleteBuffer(cube_color_buffer);
    OpenGLVertexArray::DeleteVertexArray(cube);
}

void Scene::imgui_uninitialize(void)
{
    // code
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

