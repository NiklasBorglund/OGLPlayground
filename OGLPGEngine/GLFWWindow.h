//GLFWWindow.h
#ifndef GLFWWINDOW_H_INCLUDED
#define GLFWWINDOW_H_INCLUDED

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL\glfw.h>

class GLFWOpenGLProfile
{
public:
	static GLFWOpenGLProfile LetSystemDecide(){return GLFWOpenGLProfile(0);};
	static GLFWOpenGLProfile CoreProfile(){return GLFWOpenGLProfile(GLFW_OPENGL_CORE_PROFILE);};
	static GLFWOpenGLProfile CompatibilityProfile(){return GLFWOpenGLProfile(GLFW_OPENGL_COMPAT_PROFILE);};

	int GetProfile() const
	{
		return this->_glProfile;
	}
private:
	explicit GLFWOpenGLProfile(int glProfile):_glProfile(glProfile){};
	int _glProfile;
};

class OpenGLVersion;
class Vector2;
class GLFWWindow
{
public:
	GLFWWindow(OpenGLVersion desiredMinimumVersion, GLFWOpenGLProfile oglProfile);
	~GLFWWindow();

	bool OpenWindowAndInitalizeGLEW(int width, int height,
					int redBits, int greenBits,
					int blueBits, int alphaBits,
					int depthBits, int stencilBits,
					bool fullscreen);
	void SwapBuffers();
	void TerminateWindow();
	const bool IsInitialized() const;

	/* glfw window hints(to be used BEFORE the window has been opened)*/
	void SetForwardCompatibility(bool forwardCompatibility);
	void SetCreateDebugContext(bool debugContext);
	void SetFSAASamples(int fsaaSamples);
	void SetWindowResizable(bool isResizable);
	void SetStereoRendering(bool stereoRendering);
	void SetAuxiliaryBuffers(int auxiliaryBuffers);
	void SetAccumulationBuffers(int redBits, int greenBits, int blueBits, int alphaBits);
	void SetRefreshRate(int refreshRate);
	/* glfw window hints(to be used BEFORE the window has been opened)*/

	/* glfw window params(to be used AFTER the window has been opened)*/
	void SetWindowTitle(const char* title);
	void SetWindowSize(int width, int height);
	/* glfw window params(to be used AFTER the window has been opened)*/

	void SetSwapInterval(int swapInterval);

	const Vector2 GetWindowSize() const;
	const bool IsWindowOpen() const;
	const bool IsFocused()const;
	const bool IsIconified()const;
	const bool IsHardwareAccelerated()const;
	const bool IsStereoRendered()const;
	const bool IsWindowResizable()const;
	const bool IsForwardCompatible()const;
	const bool IsDebugContext()const;
	const int OpenGLProfile()const;
	const int OpenGLMajorVersion()const;
	const int OpenGLMinorVersion()const;
	const int RefreshRate()const;
	const int NumberOfFSAASamples()const;
	const int NumberOfAuxiliaryBuffers()const;
	const int NumberOfRedBits()const;
	const int NumberOfGreenBits()const;
	const int NumberOfBlueBits()const;
	const int NumberOfAlphaBits()const;
	const int NumberOfDepthBits()const;
	const int NumberOfStencilBits()const;
	const int NumberOfRedBitsInAccBuffer()const;
	const int NumberOfGreenBitsInAccBuffer()const;
	const int NumberOfBlueBitsInAccBuffer()const;
	const int NumberOfAlphaBitsInAccBuffer()const;

private:
	bool _isInitialized;
	int _windowHeight;
	int _windowWidth;
	
	void SetOpenWindowHint(int target, int hint);
	const int GetWindowParameter(int parameter)const;

	//Window resize callback
	static void GLFWCALL OnWindowResize(int width, int height);
};


#endif //GLFWWINDOW_H_INCLUDED