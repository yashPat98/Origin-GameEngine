#ifndef _ORIGIN_BLINN_PHONG_
#define _ORIGIN_BLINN_PHONG_

namespace origin 
{
    // class declarations
    class BlinnPhongModel
    {
        public:
            // constructors
            BlinnPhongModel(void) { }

            // destructor
            virtual ~BlinnPhongModel(void) { }

            // non-static member functions
            virtual void bind(void)                                             = 0;
            virtual void unbind(void)                                           = 0;

            virtual void setModelMatrix(glm::mat4 modelMatrix)                  = 0;
            virtual void setViewMatrix(glm::mat4 viewMatrix)                    = 0;
            virtual void setProjectionMatrix(glm::mat4 projectionMatrix)        = 0;

            virtual void setLightAmbient(glm::vec3 lightAmbient)                = 0;
            virtual void setLightDiffuse(glm::vec3 lightDiffuse)                = 0;
            virtual void setLightSpecular(glm::vec3 lightSpecular)              = 0;
            virtual void setLightPosition(glm::vec4 lightPosition)              = 0;

            virtual void setMaterialAmbient(glm::vec3 materialAmbient)          = 0;
            virtual void setMaterialDiffuse(glm::vec3 materialDiffuse)          = 0;
            virtual void setMaterialSpecular(glm::vec3 materialSpecular)        = 0;
            virtual void setMaterialShininess(GLfloat materialShininess)        = 0;

            // static member functions 
            static BlinnPhongModel* InitializeBlinnPhongModel(void);
            static void DeleteBlinnPhongModel(BlinnPhongModel* instance);
    };
}

#endif /* _ORIGIN_BLINN_PHONG_ */
