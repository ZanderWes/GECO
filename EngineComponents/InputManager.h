#pragma once
class InputManager
{
public:

	InputManager();
	~InputManager();

	static void Initialize();



private:
	static void SpecialKeyPress(int key, int x, int y);
	static void SpecialKeyRelease(int key, int x, int y);

	static void CharKeyPress(unsigned char key, int x, int y);
	static void CharKeyRelease(unsigned char key, int x, int y);
};

