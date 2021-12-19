// ---------------------------------------------------
// headers
// ---------------------------------------------------

#include <Origin.h>

// ---------------------------------------------------
// class declaration
// ---------------------------------------------------

class MSAA : public origin::OriginMSAA
{
	private:
		GLuint m_msaaFramebuffer;
		GLuint m_msaaColorTexture;
		GLuint m_msaaDepthRenderbuffer;

		GLuint m_intermediateFramebuffer;
		GLuint m_intermediateColorTexture;

		GLsizei m_width;
		GLsizei m_height;

	public:
		// constructors
		MSAA(GLsizei width, GLsizei height, GLsizei samples);

		// destructor
		~MSAA(void);

		// non-static member functions
	    void bind(void);
		void unbind(void);
		GLuint screenTexture(void);
};

// ---------------------------------------------------
// class definition
// ---------------------------------------------------

MSAA::MSAA(GLsizei width, GLsizei height, GLsizei samples)  
{
	// code
	m_width = width;
	m_height = height;

	glGenFramebuffers(1, &m_msaaFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_msaaFramebuffer);
		// color attachment
		glGenTextures(1, &m_msaaColorTexture);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_msaaColorTexture);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, m_width, m_height, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

		// depth attachment
		glGenRenderbuffers(1, &m_msaaDepthRenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, m_msaaDepthRenderbuffer);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, m_width, m_height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		// attch to msaa framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_msaaColorTexture, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_msaaDepthRenderbuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glGenFramebuffers(1, &m_intermediateFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_intermediateFramebuffer);
		// color attachment 
		glGenTextures(1, &m_intermediateColorTexture);
		glBindTexture(GL_TEXTURE_2D, m_intermediateColorTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		
		// attch to intermediate framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_intermediateColorTexture, 0);

		glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

MSAA::~MSAA(void)
{
	// code
	if (m_msaaFramebuffer)
	{
		glDeleteFramebuffers(1, &m_msaaFramebuffer);
		m_msaaFramebuffer = 0;
	}

	if (m_intermediateFramebuffer)
	{
		glDeleteFramebuffers(1, &m_intermediateFramebuffer);
		m_intermediateFramebuffer = 0;
	}

	if (m_msaaColorTexture)
	{
		glDeleteTextures(1, &m_msaaColorTexture);
		m_msaaColorTexture = 0;
	}

	if (m_intermediateColorTexture)
	{
		glDeleteTextures(1, &m_intermediateColorTexture);
		m_intermediateColorTexture = 0;
	}

	if (m_msaaDepthRenderbuffer)
	{
		glDeleteRenderbuffers(1, &m_msaaDepthRenderbuffer);
		m_msaaDepthRenderbuffer = 0;
	}
}

void MSAA::bind(void)
{
	// code
	glBindFramebuffer(GL_FRAMEBUFFER, m_msaaFramebuffer);
}

void MSAA::unbind(void)
{
	// code
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_msaaFramebuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_intermediateFramebuffer);
	glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint MSAA::screenTexture(void)
{
	// code
	return (m_intermediateColorTexture);
}

// ---------------------------------------------------
// interface functions for object creation/destruction
// ---------------------------------------------------

MSAA::OriginMSAA* origin::OriginMSAA::CreateMSAA(GLsizei width, GLsizei height, GLsizei samples)
{
	// code
	return (new MSAA(width, height, samples));
}

void origin::OriginMSAA::DeleteMSAA(MSAA::OriginMSAA* msaa)
{
	// code
	delete (msaa);
}

