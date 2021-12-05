// ---------------------------------------------------
// headers
// ---------------------------------------------------

#include <Origin.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// ---------------------------------------------------
// class declaration
// ---------------------------------------------------

class Texture : public origin::OpenGLTexture
{
	private:
        GLuint m_textureObject;
        GLenum m_target;

        GLint m_mipmapLevel;
        GLint m_internalFormat;
        GLsizei m_width;
        GLsizei m_height;
        GLint m_border;
        GLenum m_format;

	public:
		// constructors
		Texture(GLenum target);

		// destructor
		~Texture(void);

		// non-static member functions
        void setBorder(GLint border);
        void setMipmapLevel(GLint mipmapLevel);
        void setInternalFormat(GLint internalFormat);
        void setFormat(GLenum format);
        void setSize(GLsizei width, GLsizei height);

        void setTextureParameter(GLenum pname, GLint param);
        void setTextureParameter(GLenum pname, GLfloat param);

        void loadTexture(const char* filename);
        void loadTexture(const void* data, GLenum type);

        void bind(GLenum textureUnit);
        void bind(void);
        void unbind(void);
};

// ---------------------------------------------------
// class definition
// ---------------------------------------------------

Texture::Texture(GLenum target) : m_target(target), m_mipmapLevel(0), 
                                  m_internalFormat(GL_RGBA), m_width(0), m_height(0),
                                  m_border(0), m_format(GL_RGBA)
{
    // code
    glGenTextures(1, &m_textureObject);
}

Texture::~Texture(void)
{
    if (m_textureObject)
    {
        glDeleteTextures(1, &m_textureObject);
        m_textureObject = 0;
    }
}

void Texture::setBorder(GLint border)
{
    // code
    m_border = border;
}

void Texture::setMipmapLevel(GLint mipmapLevel)
{
    // code
    m_mipmapLevel = mipmapLevel;
}

void Texture::setInternalFormat(GLint internalFormat)
{
    // code
    m_internalFormat = internalFormat;
}

void Texture::setFormat(GLenum format)
{
    // code
    m_format = format;
}

void Texture::setSize(GLsizei width, GLsizei height)
{
    // code
    m_width = width;
    m_height = height;
}

void Texture::setTextureParameter(GLenum pname, GLint param)
{
    // code
    this->bind();
    glTexParameteri(m_target, pname, param);
    this->unbind();
}

void Texture::setTextureParameter(GLenum pname, GLfloat param)
{
    // code
    this->bind();
    glTexParameterf(m_target, pname, param);
    this->unbind();
}

void Texture::loadTexture(const char* filename)
{
    // variable declarations
    unsigned char* pixel_data = NULL;
    int components;

    // code
    pixel_data = stbi_load(filename, &m_width, &m_height, &components, 0);
    if (pixel_data == NULL)
    {
        char str[64];
        sprintf_s(str, "Failed To Load %s Texture", filename);
        ORIGIN_ERROR(str);
        return;
    }

    if (components == 1)
        m_format = GL_RED;
    else if (components == 3)
        m_format = GL_RGB;
    else if (components == 4)
        m_format = GL_RGBA;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    this->bind();
    glTexImage2D(m_target, m_mipmapLevel, m_internalFormat, m_width, m_height, m_border, m_format, GL_UNSIGNED_BYTE, (const void*)pixel_data);
    glGenerateMipmap(m_target);
    this->unbind();

    stbi_image_free(pixel_data);
    pixel_data = NULL;
}

void Texture::loadTexture(const void* data, GLenum type)
{
    // code
    this->bind();
    glTexImage2D(m_target, m_mipmapLevel, m_internalFormat, m_width, m_height, m_border, m_format, type, data);
    glGenerateMipmap(m_target);
    this->unbind();
}

void Texture::bind(GLenum textureUnit)
{
    // code
    glActiveTexture(textureUnit);
    this->bind();
}

void Texture::bind(void)
{
    // code
    glBindTexture(m_target, m_textureObject);
}

void Texture::unbind(void)
{
    // code
    glBindTexture(m_target, 0);
}

// ---------------------------------------------------
// interface functions for object creation/destruction
// ---------------------------------------------------

origin::OpenGLTexture* origin::OpenGLTexture::CreateTexture(GLenum target)
{
    // code
    return (new Texture(target));
}

void origin::OpenGLTexture::DeleteTexture(OpenGLTexture* texture)
{
    // code
    delete (texture);
}

