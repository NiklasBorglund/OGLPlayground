//GLFWWindow.cpp
#include "GLFWWindow.h"
#include "OpenGLVersion.h"
#include "Vector2.h"
#include <iostream>

bool GLFWWindow::DidWindowResize = false;

GLFWWindow::GLFWWindow(OpenGLVersion desiredMinimumVersion, GLFWOpenGLProfile oglProfile): 
	_isInitialized(false), _windowWidth(0), _windowHeight(0)
{
	if(glfwInit())
	{
		_isInitialized = true;

		//Specify that we want to support the desired minimum
		glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, desiredMinimumVersion.GetMajorVersion());
		glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, desiredMinimumVersion.GetMinorVersion());

		//Opengl profile
		glfwOpenWindowHint( GLFW_OPENGL_PROFILE, oglProfile.GetProfile());
	}
}
GLFWWindow::~GLFWWindow()
{
	if(_isInitialized)
	{
		TerminateWindow();
	}
}
bool GLFWWindow::OpenWindowAndInitalizeGLEW(int width, int height,
					int redBits, int greenBits,
					int blueBits, int alphaBits,
					int depthBits, int stencilBits,
					bool fullscreen)
{
	int mode = fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW;
	if(!glfwOpenWindow( width,height, redBits,
						greenBits,blueBits,alphaBits,
						depthBits,stencilBits, mode ))
	{
		TerminateWindow();
		return false;
	}

	glfwSetWindowSizeCallback(OnWindowResize);

	//Set the window size params
	this->_windowWidth = width;
	this->_windowHeight = height;

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum err = glewInit(); 

	//We might get an INVALID_ENUM error here, so just clean the error for now
	//Explanation - http://www.opengl.org/wiki/OpenGL_Loading_Library
	glGetError();

	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return false;
	}
	return true;
}
void GLFWWindow::SwapBuffers()
{
	// Swap front and back rendering buffers
	glfwSwapBuffers();
}
void GLFWWindow::TerminateWindow()
{
	if(_isInitialized)
	{
		glfwTerminate();
		_isInitialized = false;
	}
}
const bool GLFWWindow::IsInitialized() const
{
	return this->_isInitialized;
}

/* glfw window hints(to be used BEFORE the window has been opened)*/
void GLFWWindow::SetForwardCompatibility(bool forwardCompatibility)
{
	int mode = forwardCompatibility ? GL_TRUE : GL_FALSE;
	SetOpenWindowHint( GLFW_OPENGL_FORWARD_COMPAT, mode);
}
void GLFWWindow::SetCreateDebugContext(bool debugContext)
{
	int mode = debugContext ? GL_TRUE : GL_FALSE;
	SetOpenWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, mode);
}
void GLFWWindow::SetFSAASamples(int fsaaSamples)
{
	SetOpenWindowHint( GLFW_FSAA_SAMPLES, fsaaSamples);
}
void GLFWWindow::SetWindowResizable(bool isResizable)
{
	int mode = isResizable ? GL_TRUE : GL_FALSE;
	SetOpenWindowHint( GLFW_WINDOW_NO_RESIZE, mode);
}
void GLFWWindow::SetStereoRendering(bool stereoRendering)
{
	int mode = stereoRendering ? GL_TRUE : GL_FALSE;
	SetOpenWindowHint( GLFW_STEREO, mode);
}
void GLFWWindow::SetAuxiliaryBuffers(int auxiliaryBuffers)
{
	SetOpenWindowHint( GLFW_AUX_BUFFERS, auxiliaryBuffers);
}
void GLFWWindow::SetAccumulationBuffers(int redBits, int greenBits, int blueBits, int alphaBits)
{
	SetOpenWindowHint( GLFW_ACCUM_RED_BITS, redBits);
	SetOpenWindowHint( GLFW_ACCUM_GREEN_BITS, greenBits);
	SetOpenWindowHint( GLFW_ACCUM_BLUE_BITS, blueBits);
	SetOpenWindowHint( GLFW_ACCUM_ALPHA_BITS, alphaBits);
}
void GLFWWindow::SetRefreshRate(int refreshRate)
{
	SetOpenWindowHint(GLFW_REFRESH_RATE, refreshRate);
}
/* glfw window params(to be used AFTER the window has been opened)*/
void GLFWWindow::SetWindowTitle(const char* title)
{
	glfwSetWindowTitle(title);
}
void GLFWWindow::SetWindowSize(int width, int height)
{
	glfwSetWindowSize(width, height);
}
const Vector2 GLFWWindow::GetWindowSize() const
{
	int width, height = 0;
	glfwGetWindowSize(&width,&height);

	//Set the static resize variable to false
	GLFWWindow::DidWindowResize = false;

	return Vector2((float)width, (float)height);
}
void GLFWWindow::SetSwapInterval(int swapInterval)
{
	glfwSwapInterval(swapInterval);
}
const bool GLFWWindow::IsWindowOpen() const{return GetWindowParameter(GLFW_OPENED) ? true : false;}
const bool GLFWWindow::IsFocused()const{return GetWindowParameter(GLFW_ACTIVE) ? true : false;}
const bool GLFWWindow::IsIconified()const{return GetWindowParameter(GLFW_ICONIFIED) ? true : false;}
const bool GLFWWindow::IsHardwareAccelerated()const{return GetWindowParameter(GLFW_ACCELERATED) ? true : false;}
const bool GLFWWindow::IsStereoRendered()const{return GetWindowParameter(GLFW_STEREO) ? true : false;}
const bool GLFWWindow::IsWindowResizable()const{return GetWindowParameter(GLFW_WINDOW_NO_RESIZE) ? false : true;}
const bool GLFWWindow::IsForwardCompatible()const{return GetWindowParameter(GLFW_OPENGL_FORWARD_COMPAT) ? true : false;}
const bool GLFWWindow::IsDebugContext()const{return GetWindowParameter(GLFW_OPENGL_DEBUG_CONTEXT) ? true : false;}
const int GLFWWindow::OpenGLProfile()const{return GetWindowParameter(GLFW_OPENGL_PROFILE);}
const int GLFWWindow::OpenGLMajorVersion()const{return GetWindowParameter(GLFW_OPENGL_VERSION_MAJOR);}
const int GLFWWindow::OpenGLMinorVersion()const{return GetWindowParameter(GLFW_OPENGL_VERSION_MINOR);}
const int GLFWWindow::RefreshRate()const{return GetWindowParameter(GLFW_REFRESH_RATE);}
const int GLFWWindow::NumberOfFSAASamples()const{return GetWindowParameter(GLFW_FSAA_SAMPLES);}
const int GLFWWindow::NumberOfAuxiliaryBuffers()const{return GetWindowParameter(GLFW_AUX_BUFFERS);}
const int GLFWWindow::NumberOfRedBits()const{return GetWindowParameter(GLFW_RED_BITS);}
const int GLFWWindow::NumberOfGreenBits()const{return GetWindowParameter(GLFW_GREEN_BITS);}
const int GLFWWindow::NumberOfBlueBits()const{return GetWindowParameter(GLFW_BLUE_BITS);}
const int GLFWWindow::NumberOfAlphaBits()const{return GetWindowParameter(GLFW_ALPHA_BITS);}
const int GLFWWindow::NumberOfDepthBits()const{return GetWindowParameter(GLFW_DEPTH_BITS);}
const int GLFWWindow::NumberOfStencilBits()const{return GetWindowParameter(GLFW_STENCIL_BITS);}
const int GLFWWindow::NumberOfRedBitsInAccBuffer()const{return GetWindowParameter(GLFW_ACCUM_RED_BITS);}
const int GLFWWindow::NumberOfGreenBitsInAccBuffer()const{return GetWindowParameter(GLFW_ACCUM_GREEN_BITS);}
const int GLFWWindow::NumberOfBlueBitsInAccBuffer()const{return GetWindowParameter(GLFW_ACCUM_BLUE_BITS);}
const int GLFWWindow::NumberOfAlphaBitsInAccBuffer()const{return GetWindowParameter(GLFW_ACCUM_ALPHA_BITS);}

//Private functions
void GLFWWindow::SetOpenWindowHint(int target, int hint)
{
	glfwOpenWindowHint(target, hint);
}
const int GLFWWindow::GetWindowParameter(int parameter)const
{
	return glfwGetWindowParam(parameter);
}
void GLFWCALL GLFWWindow::OnWindowResize(int width, int height)
{
	//Set the glviewPort
	glViewport(0,0,(GLsizei)width, (GLsizei)height);

	GLFWWindow::DidWindowResize = true;
}