#ifndef _ORIGIN_TEXTURE_
#define _ORIGIN_TEXTURE_

namespace origin
{
    // class declaration
    class OpenGLTexture
    {
    public:
        // constructors
        OpenGLTexture(void) { }

        // destructor
        virtual ~OpenGLTexture(void) { }

        // non-static member functions
        virtual void setBorder(GLint border) = 0;
        virtual void setMipmapLevel(GLint mipmapLevel) = 0;
        virtual void setInternalFormat(GLint internalFormat) = 0;
        virtual void setFormat(GLenum format) = 0;
        virtual void setSize(GLsizei width, GLsizei height) = 0;

        virtual void setTextureParameter(GLenum pname, GLint param) = 0;
        virtual void setTextureParameter(GLenum pname, GLfloat param) = 0;

        virtual void loadTexture(const char* filename) = 0;
        virtual void loadTexture(const void* data, GLenum type) = 0;

        virtual void bind(GLenum textureUnit) = 0;
        virtual void unbind(void) = 0;

        // static member functions
        static OpenGLTexture* CreateTexture(GLenum target);
        static void DeleteTexture(OpenGLTexture* texture);
    };
}

#endif /* _ORIGIN_TEXTURE_ */
