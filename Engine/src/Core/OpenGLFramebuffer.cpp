// ---------------------------------------------------
// headers
// ---------------------------------------------------

#include <Origin.h>

// ---------------------------------------------------
// class declaration
// ---------------------------------------------------

class Framebuffer : public origin::OpenGLFramebuffer
{
    private:
        GLuint m_framebufferObject;
        std::vector<GLuint> attachments;

    public:
        // constructors
        Framebuffer(void);

        // destructor
        ~Framebuffer(void);

        // non-static member functions
        void attach(GLenum attachment, origin::OpenGLTexture* texture);
        void attach(GLenum attachment, GLenum internalFormat, GLsizei width, GLsizei height);
        bool isComplete(void);
        void bind(void);
        void unbind(void);
};

// ---------------------------------------------------
// class definition
// ---------------------------------------------------

Framebuffer::Framebuffer(void) : m_framebufferObject(0)
{
    // code
    glGenFramebuffers(1, &m_framebufferObject);
}

Framebuffer::~Framebuffer(void)
{
    // code
    glDeleteFramebuffers(1, &m_framebufferObject);
    glDeleteRenderbuffers((GLsizei)attachments.size(), attachments.data());
}

void Framebuffer::attach(GLenum attachment, origin::OpenGLTexture* texture)
{
    // code   
    this->bind();
    texture->bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture->getTextureObject(), texture->getMipmapLevel());
    texture->unbind();
    this->unbind();
}

void Framebuffer::attach(GLenum attachment, GLenum internalFormat, GLsizei width, GLsizei height)
{
    // variable declarations
    GLuint rbo;

    // code
    this->bind();
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    this->unbind();
    
    attachments.push_back(rbo);
}

bool Framebuffer::isComplete(void)
{
    // variable declarations
    GLenum framebufferStatus;

    // code
    this->bind();
    framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    this->unbind();

    if (framebufferStatus != GL_FRAMEBUFFER_COMPLETE)
        return (false);
    else 
        return (true);
}

void Framebuffer::bind(void)
{
    // code
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferObject);
}

void Framebuffer::unbind(void)
{
    // code
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// ---------------------------------------------------
// interface functions for object creation/destruction
// ---------------------------------------------------

origin::OpenGLFramebuffer* origin::OpenGLFramebuffer::CreateFramebuffer(void)
{
    // code
    return (new Framebuffer);
}

void origin::OpenGLFramebuffer::DeleteFramebuffer(origin::OpenGLFramebuffer* framebuffer)
{
    // code
    delete framebuffer;
}

