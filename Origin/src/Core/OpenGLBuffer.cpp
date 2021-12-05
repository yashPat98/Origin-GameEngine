// ---------------------------------------------------
// headers
// ---------------------------------------------------

#include <Origin.h>

// ---------------------------------------------------
// class declaration
// ---------------------------------------------------

class Buffer : public origin::OpenGLBuffer
{
    private:
        GLuint          m_vertexBufferObject;
        const void*     m_data;
        GLsizeiptr      m_size;
        GLenum          m_target;
        GLenum          m_usage;
        
    public:
        // constructors
        Buffer();

        // destructor
        ~Buffer(void);

        // non-static member functions
        void bind(void);                                                                                                                                 
        void push(void);
        void unbind(void); 
        void setBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage);

        void temp(void);
};

// ---------------------------------------------------
// class definition
// ---------------------------------------------------

Buffer::Buffer() : m_vertexBufferObject(0), m_target(0), m_usage(0), m_data(nullptr)
{
    // code
    glGenBuffers(1, &m_vertexBufferObject);
}

Buffer::~Buffer(void) 
{
    // code
    if(m_vertexBufferObject)
    {
        glDeleteBuffers(1, &m_vertexBufferObject);
        m_vertexBufferObject = 0;
    }
}

void Buffer::bind(void)
{
    // code
    glBindBuffer(m_target, m_vertexBufferObject);
}   

void Buffer::push(void)
{
    // code
    glBufferData(m_target, m_size, m_data, m_usage);
}   

void Buffer::unbind(void)
{
    // code
    glBindBuffer(m_target, 0);
}   

void Buffer::setBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage)
{
    // code
    m_target = target;
    m_size = size;
    m_data = data;
    m_usage = usage;
}   

// ---------------------------------------------------
// interface functions for object creation/destruction
// ---------------------------------------------------

origin::OpenGLBuffer* origin::OpenGLBuffer::CreateBuffer()
{
    // code
    return (new Buffer);
}

void origin::OpenGLBuffer::DeleteBuffer(OpenGLBuffer *buffer)
{
    // code
    delete (buffer);
}

