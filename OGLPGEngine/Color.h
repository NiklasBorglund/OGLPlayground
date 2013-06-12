//Color.h
#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

class Color
{
public:
	union
	{
		struct  
		{
			float _r;
			float _g;
			float _b;
			float _a;
		};
		float values[4];
	};
	Color(float r, float g, float b, float a):_r(r), _g(g), _b(b), _a(a){}
	explicit Color(float value): _r(value), _g(value), _b(value), _a(value) {}
	Color(): _r(0), _g(0), _b(0), _a(0){}
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		_r = (r / 255.0f);
		_g = (g / 255.0f);
		_b = (b / 255.0f);
		_a = (a / 255.0f);
	}
	~Color(){}

	static Color Black()										{ return Color(0.0f, 0.0f, 0.0f, 1.0f); }
	static Color White()										{ return Color(1.0f, 1.0f, 1.0f, 1.0f); }
	static Color Red()											{ return Color(1.0f, 0.0f, 0.0f, 1.0f); }
	static Color Green()										{ return Color(0.0f, 1.0f, 0.0f, 1.0f); }
	static Color Blue()											{ return Color(0.0f, 0.0f, 1.0f, 1.0f); }
	static Color LightSlateGray()								{ return Color(0.464f, 0.531f, 0.597f, 1.0f); }
	static Color CornflowerBlue()								{ return Color(0.394f, 0.609f,0.933f,1.0f); }
};
#endif //COLOR_H_INCLUDED