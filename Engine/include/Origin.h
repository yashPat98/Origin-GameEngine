#ifndef _ORIGIN_
#define _ORIGIN_

// standard headers
#include <Windows.h>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>

// opengl headers
#include <gl/glew.h>
#include <gl/GL.h>

// 3D math headers
#define _USE_MATH_DEFINES  1       
#include <math.h>
#include <glm/glm.hpp>             
#include <glm/ext.hpp>
#include <glm/gtc/matrix_inverse.hpp>

// imgui headers
#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_opengl3.h>

// engine headers
#include <OriginLogger.h>
#include <OriginGUI.h>
#include <OriginApplication.h>
#include <OriginResources.h>
#include <OpenGLProgram.h>
#include <OpenGLShader.h>
#include <OpenGLBuffer.h>
#include <OpenGLVertexArray.h>
#include <OpenGLTexture.h>
#include <OpenGLFramebuffer.h>

// graphics headers
#include <ScreenQuad.h>
#include <MSAA.h>
#include <BlinnPhongModel.h>

#endif /* _ORIGIN_ */
