//OpenGLVersion.h
//Relying on the automatic compiler dtor for this class
#ifndef OPENGLVERSION_H_INCLUDED
#define OPENGLVERSION_H_INCLUDED
class OpenGLVersion 
{ 
public:
	static OpenGLVersion OpenGL1_1(){return OpenGLVersion(1,1);};
	static OpenGLVersion OpenGL1_2(){return OpenGLVersion(1,2);};
	static OpenGLVersion OpenGL1_3(){return OpenGLVersion(1,3);};
	static OpenGLVersion OpenGL1_4(){return OpenGLVersion(1,4);};
	static OpenGLVersion OpenGL1_5(){return OpenGLVersion(1,5);};
	static OpenGLVersion OpenGL2_0(){return OpenGLVersion(2,0);};
	static OpenGLVersion OpenGL2_1(){return OpenGLVersion(2,1);};
	static OpenGLVersion OpenGL3_0(){return OpenGLVersion(3,0);};
	static OpenGLVersion OpenGL3_1(){return OpenGLVersion(3,1);};
	static OpenGLVersion OpenGL3_2(){return OpenGLVersion(3,2);};
	static OpenGLVersion OpenGL3_3(){return OpenGLVersion(3,3);};
	static OpenGLVersion OpenGL4_0(){return OpenGLVersion(4,0);};
	static OpenGLVersion OpenGL4_1(){return OpenGLVersion(4,1);};
	static OpenGLVersion OpenGL4_2(){return OpenGLVersion(4,2);};
	static OpenGLVersion OpenGL4_3(){return OpenGLVersion(4,3);};

	const int GetMajorVersion() const
	{
		return this->_majorVersion;
	}
	const int GetMinorVersion() const
	{
		return this->_minorVersion;
	}
private:
	OpenGLVersion(int majorVersion, int minorVersion): _majorVersion(majorVersion), _minorVersion(minorVersion){}
	int _majorVersion;
	int _minorVersion;
};

#endif //OPENGLVERSION_H_INCLUDED