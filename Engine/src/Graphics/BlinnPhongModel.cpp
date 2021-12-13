// ---------------------------------------------------
// headers
// ---------------------------------------------------

#include <Origin.h>

// ---------------------------------------------------
// class declaration
// ---------------------------------------------------

class CBlinnPhongModel : public origin::BlinnPhongModel
{
	private:
        origin::OpenGLProgram *m_shaderProgram;

        GLuint m_modelMatrixUniform;
        GLuint m_viewMatrixUniform;
        GLuint m_projectionMatrixUniform;
        
        GLuint m_lightAmbientUniform;
        GLuint m_lightDiffuseUniform;
        GLuint m_lightSpecularUniform;
        GLuint m_lightPositionUniform;

        GLuint m_materialAmbientUniform;
        GLuint m_materialDiffuseUniform;
        GLuint m_materialSpecularUniform;
        GLuint m_materialShininessUniform;

	public:
        // constructors
        CBlinnPhongModel(void);

        // destructor
        ~CBlinnPhongModel(void);

        // non-static member functions
        void bind(void);
        void unbind(void);

        void setModelMatrix(glm::mat4 modelMatrix);
        void setViewMatrix(glm::mat4 viewMatrix);
        void setProjectionMatrix(glm::mat4 projectionMatrix);

        void setLightAmbient(glm::vec3 lightAmbient);
        void setLightDiffuse(glm::vec3 lightDiffse);
        void setLightSpecular(glm::vec3 lightSpecular);
        void setLightPosition(glm::vec4 lightPosition);

        void setMaterialAmbient(glm::vec3 materialAmbient);
        void setMaterialDiffuse(glm::vec3 materialDiffuse);
        void setMaterialSpecular(glm::vec3 materialSpecular);
        void setMaterialShininess(GLfloat materialShininess);
};

// ---------------------------------------------------
// class definition
// ---------------------------------------------------

CBlinnPhongModel::CBlinnPhongModel(void) : m_shaderProgram(nullptr)
{
    // code
    m_shaderProgram = origin::OpenGLProgram::CreateProgram();

    origin::OpenGLShader* vertexShader = origin::OpenGLShader::CreateShader(GL_VERTEX_SHADER);
    origin::OpenGLShader* fragmentShader = origin::OpenGLShader::CreateShader(GL_FRAGMENT_SHADER);

    vertexShader->compileShaderFromFile("include/shaders/BlinnPhong/BlinnPhong.vs");
    fragmentShader->compileShaderFromFile("include/shaders/BlinnPhong/BlinnPhong.fs");

    m_shaderProgram->addShader(vertexShader);
    m_shaderProgram->addShader(fragmentShader);

    m_shaderProgram->bindAttribLocation(origin::ORIGIN_ATTRIBUTE_POSITION, "a_position");
    m_shaderProgram->bindAttribLocation(origin::ORIGIN_ATTRIBUTE_NORMAL, "a_normal");

    m_shaderProgram->link();

    m_modelMatrixUniform = m_shaderProgram->getUniformLocation("u_modelMatrix");
    m_viewMatrixUniform = m_shaderProgram->getUniformLocation("u_viewMatrix");
    m_projectionMatrixUniform = m_shaderProgram->getUniformLocation("u_projectionMatrix");

    m_lightAmbientUniform = m_shaderProgram->getUniformLocation("u_lightAmbient");
    m_lightDiffuseUniform = m_shaderProgram->getUniformLocation("u_lightDiffuse");
    m_lightSpecularUniform = m_shaderProgram->getUniformLocation("u_lightSpecular");
    m_lightPositionUniform = m_shaderProgram->getUniformLocation("u_lightPosition");

    m_materialAmbientUniform = m_shaderProgram->getUniformLocation("u_materialAmbient");
    m_materialDiffuseUniform = m_shaderProgram->getUniformLocation("u_materialDiffuse");
    m_materialSpecularUniform = m_shaderProgram->getUniformLocation("u_materialSpecular");
    m_materialShininessUniform = m_shaderProgram->getUniformLocation("u_materialShininess");

    origin::OpenGLShader::DeleteShader(vertexShader);
    origin::OpenGLShader::DeleteShader(fragmentShader);
}

CBlinnPhongModel::~CBlinnPhongModel(void)
{
    // code
    origin::OpenGLProgram::DeleteProgram(m_shaderProgram);
}

void CBlinnPhongModel::bind(void)
{
    // code
    m_shaderProgram->bind();
}

void CBlinnPhongModel::unbind(void)
{
    // code
    m_shaderProgram->unbind();
}

void CBlinnPhongModel::setModelMatrix(glm::mat4 modelMatrix)
{
    // code
    glUniformMatrix4fv(m_modelMatrixUniform, 1, GL_FALSE, &modelMatrix[0][0]);
}

void CBlinnPhongModel::setViewMatrix(glm::mat4 viewMatrix)
{
    // code
    glUniformMatrix4fv(m_viewMatrixUniform, 1, GL_FALSE, &viewMatrix[0][0]);
}

void CBlinnPhongModel::setProjectionMatrix(glm::mat4 projectionMatrix)
{
    // code
    glUniformMatrix4fv(m_projectionMatrixUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void CBlinnPhongModel::setLightAmbient(glm::vec3 lightAmbient)
{
    // code
    glUniform3fv(m_lightAmbientUniform, 1, &lightAmbient[0]);
}

void CBlinnPhongModel::setLightDiffuse(glm::vec3 lightDiffuse)
{
    // code
    glUniform3fv(m_lightDiffuseUniform, 1, &lightDiffuse[0]);
}

void CBlinnPhongModel::setLightSpecular(glm::vec3 lightSpecular)
{
    // code
    glUniform3fv(m_lightSpecularUniform, 1, &lightSpecular[0]);
}

void CBlinnPhongModel::setLightPosition(glm::vec4 lightPosition)
{
    // code
    glUniform4fv(m_lightPositionUniform, 1, &lightPosition[0]);
}

void CBlinnPhongModel::setMaterialAmbient(glm::vec3 materialAmbient)
{
    // code
    glUniform3fv(m_materialAmbientUniform, 1, &materialAmbient[0]);
}

void CBlinnPhongModel::setMaterialDiffuse(glm::vec3 materialDiffuse)
{
    // code
    glUniform3fv(m_materialDiffuseUniform, 1, &materialDiffuse[0]);
}

void CBlinnPhongModel::setMaterialSpecular(glm::vec3 materialSpecular)
{
    // code
    glUniform3fv(m_materialSpecularUniform, 1, &materialSpecular[0]);
}

void CBlinnPhongModel::setMaterialShininess(GLfloat materialShininess)
{
    // code
    glUniform1f(m_materialShininessUniform, materialShininess);
}

// ---------------------------------------------------
// interface functions for object creation/destruction
// ---------------------------------------------------

origin::BlinnPhongModel* origin::BlinnPhongModel::InitializeBlinnPhongModel(void)
{
    // code
    return (new CBlinnPhongModel);
}

void origin::BlinnPhongModel::DeleteBlinnPhongModel(origin::BlinnPhongModel* instance)
{
    // code
    delete (instance);
}
