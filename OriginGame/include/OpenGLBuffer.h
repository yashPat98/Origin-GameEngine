#ifndef _ORIGIN_BUFFER_
#define _ORIGIN_BUFFER_

namespace origin 
{
    // class declaration
    class OpenGLBuffer
    {
        public:
            // constructors
            OpenGLBuffer(void) { }

            // destructor
            virtual ~OpenGLBuffer(void) { }

            // non-static member functions
            virtual void bind(void)                                                                     = 0;
            virtual void push(void)                                                                     = 0;
            virtual void unbind(void)                                                                   = 0;
            virtual void setBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage)  = 0;    

            // static member functions
            static OpenGLBuffer* CreateBuffer(void);
            static void DeleteBuffer(OpenGLBuffer *buffer);
    };
}

#endif /* _ORIGIN_BUFFER_ */

