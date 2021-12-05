// ---------------------------------------------------
// headers
// ---------------------------------------------------

#include <Origin.h>

// ---------------------------------------------------
// class declaration
// ---------------------------------------------------

class Program : public origin::OpenGLProgram
{
    private:
        GLuint m_programObject;

    public:
        // constructors
        Program(void);

        // destructor
        ~Program(void);

        // non-static member functions
        void addShader(origin::OpenGLShader *shader);
        void link(void);
        void bindAttribLocation(GLuint index, const GLchar *name);
        GLint getUniformLocation(const GLchar *name);
        void bind(void);
        void unbind(void);
};

// ---------------------------------------------------
// class definition
// ---------------------------------------------------

Program::Program(void) : m_programObject(glCreateProgram())
{
    // code
}

Program::~Program(void)
{
    // code
    if(m_programObject)
    {
        GLsizei shader_count;
        GLuint* p_shaders = NULL;

        glUseProgram(m_programObject);
        glGetProgramiv(m_programObject, GL_ATTACHED_SHADERS, &shader_count);

        p_shaders = (GLuint*)malloc(shader_count * sizeof(GLuint));
        memset((void*)p_shaders, 0, shader_count * sizeof(GLuint));
    
        glGetAttachedShaders(m_programObject, shader_count, &shader_count, p_shaders);

        for (GLsizei i = 0; i < shader_count; i++)   
        {
            glDetachShader(m_programObject, p_shaders[i]);
        }

        free(p_shaders);
        p_shaders = NULL;

        glDeleteProgram(m_programObject);
        m_programObject = 0;
        glUseProgram(0);
    }
}

void Program::addShader(origin::OpenGLShader *shader)
{
    // code
    glAttachShader(m_programObject, shader->getShaderObject());
}

void Program::link(void)
{
    //variable declarations
    GLint shaderLinkStatus = 0;
    GLint infoLogLength = 0;
    GLchar* szInfoLog = NULL;

    // code
    glLinkProgram(m_programObject);

    glGetProgramiv(m_programObject, GL_LINK_STATUS, &shaderLinkStatus);
    if(shaderLinkStatus == GL_FALSE)
    {
        glGetProgramiv(m_programObject, GL_INFO_LOG_LENGTH, &infoLogLength);
        if(infoLogLength > 0)
        {
            szInfoLog = (GLchar*)malloc(sizeof(GLchar) * infoLogLength);
            if(szInfoLog != NULL)
            {
                GLsizei written;
                glGetProgramInfoLog(m_programObject, infoLogLength, &written, szInfoLog);
                ORIGIN_ERROR("Shader Program Link Log : ");
                ORIGIN_BUFFER(szInfoLog);
                free(szInfoLog);
                return;
            }
        }
    }
}

void Program::bindAttribLocation(GLuint index, const GLchar *name)
{
    // code
    glBindAttribLocation(m_programObject, index, name);
}

GLint Program::getUniformLocation(const GLchar *name)
{
    // code
    return (glGetUniformLocation(m_programObject, name));
}

void Program::bind(void)
{
    // code
    glUseProgram(m_programObject);
}

void Program::unbind(void)
{
    // code
    glUseProgram(0);
}

// ---------------------------------------------------
// interface functions for object creation/destruction
// ---------------------------------------------------

origin::OpenGLProgram* origin::OpenGLProgram::CreateProgram(void)
{
    // code
    return (new Program);
}

void origin::OpenGLProgram::DeleteProgram(origin::OpenGLProgram *program)
{
    // code
    delete (program);
}
