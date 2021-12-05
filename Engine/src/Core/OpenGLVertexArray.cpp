// ---------------------------------------------------
// headers
// ---------------------------------------------------

#include <Origin.h>

// ---------------------------------------------------
// class declaration
// ---------------------------------------------------

class VertexArray : public origin::OpenGLVertexArray
{
    private:
        GLuint m_vertexArrayObject;
        origin::OpenGLBuffer* m_currentBuffer;

    public:
        // constructors
        VertexArray(void);

        // destructor
        ~VertexArray(void);

        // non-static member functions
        void setVertexAttribPointer(GLuint index, GLint size, GLenum type, 
                                    GLboolean normalized, GLsizei stride, 
                                    const void *pointer);                                                    
        void enableVertexAttribArray(GLuint index);                                                                          
        void setVertexBuffer(origin::OpenGLBuffer *buffer);
        void setIndexBuffer(origin::OpenGLBuffer *buffer);
        void bind(void);                                                                                                     
        void unbind(void);                                                                                                                                  
    
        void drawArrays(GLenum mode, GLint first, GLsizei count);                                                          
        void drawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount);                           
        void drawElements(GLenum mode, GLsizei count, GLenum type, const void* indices);                                      
        void drawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instanceCount);    
};

// ---------------------------------------------------
// class definition
// ---------------------------------------------------

VertexArray::VertexArray(void) : m_vertexArrayObject(0), m_currentBuffer(nullptr)
{
    // code
    glGenVertexArrays(1, &m_vertexArrayObject);
}

VertexArray::~VertexArray(void)
{
    // code
    m_currentBuffer = nullptr;
    if(m_vertexArrayObject)
    {
        glDeleteVertexArrays(1, &m_vertexArrayObject);
        m_vertexArrayObject = 0;
    }
}

void VertexArray::setVertexAttribPointer(GLuint index, GLint size, GLenum type, 
                                        GLboolean normalized, GLsizei stride, 
                                        const void *pointer)       
{
    // code
    this->bind();
    m_currentBuffer->bind();   
    m_currentBuffer->push();  
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
    m_currentBuffer->unbind();
    this->unbind();
}   

void VertexArray::setVertexBuffer(origin::OpenGLBuffer *buffer)
{
    // code
    m_currentBuffer = buffer;
}

void VertexArray::setIndexBuffer(origin::OpenGLBuffer *buffer)
{
    // code
    m_currentBuffer = buffer;

    this->bind();
    m_currentBuffer->bind();
    m_currentBuffer->push();
    m_currentBuffer->unbind();
    this->unbind();
}

void VertexArray::bind(void)   
{
    // code
    glBindVertexArray(m_vertexArrayObject);
}   

void VertexArray::unbind(void)                                                                                                                                  
{
    // code
    glBindVertexArray(0);
}   

void VertexArray::drawArrays(GLenum mode, GLint first, GLsizei count)
{
    // code
    this->bind();
    glDrawArrays(mode, first, count);       
    this->unbind();
}   

void VertexArray::drawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount)      
{
    // code
    this->bind();
    glDrawArraysInstanced(mode, first, count, instanceCount);       
    this->unbind();
}                        

void VertexArray::drawElements(GLenum mode, GLsizei count, GLenum type, const void* indices)    
{
    // code
    this->bind();
    m_currentBuffer->bind();
    glDrawElements(mode, count, type, indices);  
    m_currentBuffer->unbind();
    this->unbind();
}   

void VertexArray::drawElementsInstanced(GLenum mode, GLsizei count, GLenum type, 
                                        const void* indices, GLsizei instanceCount)    
{
    // code
    this->bind();
    m_currentBuffer->bind();
    glDrawElementsInstanced(mode, count, type, indices, instanceCount); 
    m_currentBuffer->unbind();
    this->unbind();
}   

// ---------------------------------------------------
// interface functions for object creation/destruction
// ---------------------------------------------------

origin::OpenGLVertexArray* origin::OpenGLVertexArray::CreateVertexArray(void)
{
    // code
    return (new VertexArray);
}

void origin::OpenGLVertexArray::DeleteVertexArray(origin::OpenGLVertexArray *vertexArray)
{
    // code
    delete (vertexArray);
}

