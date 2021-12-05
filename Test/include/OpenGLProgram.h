#ifndef _ORIGIN_PROGRAM_
#define _ORIGIN_PROGRAM_

namespace origin 
{
    // enum attributes
    enum
    {
        ORIGIN_ATTRIBUTE_POSITION  = 0,
        ORIGIN_ATTRIBUTE_COLOR     = 1,
        ORIGIN_ATTRIBUTE_NORMAL    = 2,
        ORIGIN_ATTRIBUTE_TEXCOORD  = 3,
        ORIGIN_ATTRIBUTE_TANGENT   = 4,
        ORIGIN_ATTRIBUTE_BITANGENT = 5
    };

    // foreward declaration of class
    class OpenGLShader;

    // class declaration
    class OpenGLProgram
    {
        public:
            // constructors
            OpenGLProgram(void) { }

            // destructor
            virtual ~OpenGLProgram(void) { }

            // non-static member functions
            virtual void addShader(OpenGLShader *shader)                        = 0;
            virtual void link(void)                                             = 0;
            virtual void bindAttribLocation(GLuint index, const GLchar *name)   = 0;
            virtual GLint getUniformLocation(const GLchar *name)                = 0;
            virtual void bind(void)                                             = 0;
            virtual void unbind(void)                                           = 0;

            // static member functions
            static OpenGLProgram* CreateProgram(void);
            static void DeleteProgram(OpenGLProgram *program);
    };
}

#endif /* _ORIGIN_PROGRAM_ */
