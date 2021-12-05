#ifndef _ORIGIN_SHADER_
#define _ORIGIN_SHADER_

namespace origin 
{
    // class declaration
    class OpenGLShader
    { 
        public:
            // constructors
            OpenGLShader(void) { }

            // destructor
            virtual ~OpenGLShader(void) { }

            // non-static member functions
            virtual void compileShader(const GLchar* shaderSource)          = 0;
            virtual void compileShader(std::string& shaderSource)           = 0;
            virtual void compileShaderFromFile(const char* shaderPath)      = 0;
            virtual GLuint getShaderObject(void)                            = 0;

            // static member functions
            static OpenGLShader* CreateShader(GLenum type);
            static void DeleteShader(OpenGLShader *shader);         
    };
}

#endif /* _ORIGIN_SHADER_ */

