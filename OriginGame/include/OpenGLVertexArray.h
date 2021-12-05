#ifndef _ORIGIN_VERTEX_ARRAY_
#define _ORIGIN_VERTEX_ARRAY_

namespace origin 
{
    // class declaration
    class OpenGLVertexArray
    {
        public:
            // constructors
            OpenGLVertexArray(void) { }

            // destructor
            virtual ~OpenGLVertexArray(void) { }

            // non-static member functions
            virtual void setVertexAttribPointer(GLuint index, GLint size, GLenum type, 
                                                GLboolean normalized, GLsizei stride, 
                                                const void *pointer)                                                                    = 0;
            
            virtual void setVertexBuffer(origin::OpenGLBuffer *buffer)                                                                  = 0;
            virtual void setIndexBuffer(origin::OpenGLBuffer *buffer)                                                                   = 0;
            virtual void bind(void)                                                                                                     = 0;
            virtual void unbind(void)                                                                                                   = 0;                               
            
            virtual void drawArrays(GLenum mode, GLint first, GLsizei count)                                                            = 0;
            virtual void drawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount)                            = 0;
            virtual void drawElements(GLenum mode, GLsizei count, GLenum type, const void* indices)                                     = 0;   
            virtual void drawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instanceCount)     = 0;

            // static member functions
            static OpenGLVertexArray* CreateVertexArray(void);
            static void DeleteVertexArray(OpenGLVertexArray *vertexArray);
    };                              
}

#endif /* _ORIGIN_VERTEX_ARRAY_ */
