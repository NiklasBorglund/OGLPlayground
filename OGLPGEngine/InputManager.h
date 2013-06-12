//InputManager.h
#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL\glfw.h>

class InputManager
{
public:
	InputManager();
	~InputManager();

	static bool IsKeyPressed(int key)
	{
		return glfwGetKey(key) == GLFW_PRESS;
	}
	static bool IsMouseButtonPressed(int button)
	{
		return glfwGetMouseButton(button) == GLFW_PRESS;
	}
	static Vector2 GetMousePosition()
	{
		int x;
		int y;
		glfwGetMousePos(&x, &y);
		return Vector2((float)x,(float)y);
	}
	static void SetMousePosition(Vector2 mousePosition)
	{
		glfwSetMousePos((int)mousePosition._x, (int)mousePosition._y);
	}
};

#endif //INPUTMANAGER_H_INCLUDED