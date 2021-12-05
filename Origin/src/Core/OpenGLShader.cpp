// ---------------------------------------------------
// headers
// ---------------------------------------------------

#include <Origin.h>

// ---------------------------------------------------
// class declaration
// ---------------------------------------------------

class Shader : public origin::OpenGLShader
{
    private:
        GLuint m_shaderObject;
        GLenum m_shaderType;
        
        // helper functions
        std::string getTypeString(GLenum type);
        GLuint getShaderObject(void);

    public:
        // constructors
        Shader(GLenum type);

        // destructor
        ~Shader(void);

        // non-static member functions
        void compileShader(const GLchar* shaderSource);
        void compileShader(std::string& shaderSource);
        void compileShaderFromFile(const char* shaderPath);
};

// ---------------------------------------------------
// class definition
// ---------------------------------------------------

Shader::Shader(GLenum type) : m_shaderObject(0), m_shaderType(type)
{
    // code
    m_shaderObject = glCreateShader(m_shaderType);
}

Shader::~Shader(void) 
{
    // code
    if(m_shaderObject)
    {
        glDeleteShader(m_shaderObject);        
        m_shaderObject = 0;
    }
}

void Shader::compileShader(const GLchar* shaderSource)
{
    //variable declarations
    GLint infoLogLength = 0;
    GLint shaderCompiledStatus = 0;
    GLchar* szInfoLog = NULL;

    // code
    glShaderSource(m_shaderObject, 1, (const GLchar**)&shaderSource, NULL);
    glCompileShader(m_shaderObject);

    glGetShaderiv(m_shaderObject, GL_COMPILE_STATUS, &shaderCompiledStatus);
    if(shaderCompiledStatus == GL_FALSE)
    {
        glGetShaderiv(m_shaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
        if(infoLogLength > 0)
        {
            szInfoLog = (GLchar*)malloc(sizeof(GLchar) * infoLogLength);
            if(szInfoLog != NULL)
            {
                GLsizei written;
                glGetShaderInfoLog(m_shaderObject, infoLogLength, &written, szInfoLog);
                ORIGIN_ERROR(getTypeString(m_shaderType) + std::string(" Compilation Log"));
                ORIGIN_BUFFER(szInfoLog);
                free(szInfoLog);
                return;
            }
        }
    } 
}

void Shader::compileShader(std::string& shaderSource)
{
    // code
    compileShader(shaderSource.data());
}

void Shader::compileShaderFromFile(const char* shaderPath)
{
    //variable declarations
    FILE *pFile = NULL;
    size_t sizeSourceLength;

    //code
    if(fopen_s(&pFile, shaderPath, "rb") != 0)
    {
        ORIGIN_ERROR(std::string("fopen_s() failed to open file ") + std::string(shaderPath));
        return;
    }

    fseek(pFile, 0, SEEK_END);
    sizeSourceLength = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    char *sourceString = (char *)malloc(sizeSourceLength + 1);
    if(sourceString == NULL)
    {
        ORIGIN_FATAL(std::string("malloc() failed to allocate memory for buffer from ") + std::string(shaderPath));
        fclose(pFile);
        pFile = NULL; 
        return;
    }

    if(fread(sourceString, sizeSourceLength, 1, pFile) != 1)
    {
        ORIGIN_ERROR(std::string("fread() failed to read from file ") + std::string(shaderPath));
        fclose(pFile);
        free(sourceString);
        pFile = NULL;
        sourceString = NULL;
        return;
    }

    sourceString[sizeSourceLength] = '\0';

    fclose(pFile);
    pFile = NULL;

    compileShader(sourceString);
}

// ---------------------------------------------------
// helper function implementation
// ---------------------------------------------------

GLuint Shader::getShaderObject(void)
{
    // code
    return (m_shaderObject);
}

std::string Shader::getTypeString(GLenum type)
{
    //code
    switch(type)
    {
        case GL_VERTEX_SHADER:
            return (std::string("Vertex Shader"));

        case GL_TESS_CONTROL_SHADER:
            return (std::string("Tessellation Control Shader"));

        case GL_TESS_EVALUATION_SHADER:
            return (std::string("Tessellation Evaluation Shader"));

        case GL_GEOMETRY_SHADER:
            return (std::string("Geometry Shader"));

        case GL_FRAGMENT_SHADER:
            return (std::string("Fragment Shader"));
        
        case GL_COMPUTE_SHADER:
            return (std::string("Compute Shader"));
    }

    return std::string("");
}

// ---------------------------------------------------
// interface functions for object creation/destruction
// ---------------------------------------------------

origin::OpenGLShader* origin::OpenGLShader::CreateShader(GLenum type)
{
    // code
    return (new Shader(type));
}

void origin::OpenGLShader::DeleteShader(origin::OpenGLShader *shader)
{
    // code
    delete (shader);
}
