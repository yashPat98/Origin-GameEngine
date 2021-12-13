// ---------------------------------------------------
// headers
// ---------------------------------------------------

#include <Origin.h>

// ---------------------------------------------------
// class declaration
// ---------------------------------------------------

class CScreenQuad : public origin::ScreenQuad
{
	private:
		origin::OpenGLProgram*		m_shaderProgram;
		origin::OpenGLVertexArray*	m_vao;
		origin::OpenGLBuffer*		m_vbo;

	public:
		// constructors
		CScreenQuad(void);

		// destructor
		~CScreenQuad(void);

		// non-static member functions
	    void renderToScreen(origin::OpenGLTexture* texture);
};

// ---------------------------------------------------
// class definition
// ---------------------------------------------------

CScreenQuad::CScreenQuad(void) : m_shaderProgram(0)
{
	// code
	// setup shaders
	m_shaderProgram = origin::OpenGLProgram::CreateProgram();

	origin::OpenGLShader* vertexShader = origin::OpenGLShader::CreateShader(GL_VERTEX_SHADER);
	origin::OpenGLShader* fragmentShader = origin::OpenGLShader::CreateShader(GL_FRAGMENT_SHADER);

	vertexShader->compileShaderFromFile("include/shaders/ScreenQuad/ScreenQuad.vs");
	fragmentShader->compileShaderFromFile("include/shaders/ScreenQuad/ScreenQuad.fs");

	m_shaderProgram->addShader(vertexShader);
	m_shaderProgram->addShader(fragmentShader);

	m_shaderProgram->bindAttribLocation(origin::ORIGIN_ATTRIBUTE_POSITION, "a_position");
	m_shaderProgram->bindAttribLocation(origin::ORIGIN_ATTRIBUTE_TEXCOORD, "a_texcoord");

	m_shaderProgram->link();

	origin::OpenGLShader::DeleteShader(vertexShader);
	origin::OpenGLShader::DeleteShader(fragmentShader);

	// setup vao and vbo
	m_vao = origin::OpenGLVertexArray::CreateVertexArray();
	m_vbo = origin::OpenGLBuffer::CreateBuffer();

	const GLfloat quad[] =
	{
		// position           // texcoords 
		1.0f,  1.0f,  0.0f,   1.0f,  1.0f,
	   -1.0f,  1.0f,  0.0f,   0.0f,  1.0f,
	   -1.0f, -1.0f,  0.0f,   0.0f,  0.0f,
		1.0f, -1.0f,  0.0f,   1.0f,  0.0f,
	};

	m_vbo->setBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

	m_vao->setVertexBuffer(m_vbo);
	m_vao->setVertexAttribPointer(origin::ORIGIN_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	m_vao->setVertexAttribPointer(origin::ORIGIN_ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
}

CScreenQuad::~CScreenQuad(void)
{
	// code
	origin::OpenGLBuffer::DeleteBuffer(m_vbo);
	origin::OpenGLVertexArray::DeleteVertexArray(m_vao);
	origin::OpenGLProgram::DeleteProgram(m_shaderProgram);
}

void CScreenQuad::renderToScreen(origin::OpenGLTexture* texture)
{
	// code
	m_shaderProgram->bind();
		
		texture->bind(GL_TEXTURE0);
		glUniform1i(m_shaderProgram->getUniformLocation("u_texture"), 0);

		m_vao->drawArrays(GL_TRIANGLE_FAN, 0, 4);

	m_shaderProgram->unbind();
}

// ---------------------------------------------------
// interface functions for object creation/destruction
// ---------------------------------------------------

origin::ScreenQuad* origin::ScreenQuad::CreateScreenQuad(void)
{
	// code
	return (new CScreenQuad);
}

void origin::ScreenQuad::DeleteScreenQuad(origin::ScreenQuad* screenQuad)
{
	// code
	delete (screenQuad);
}
