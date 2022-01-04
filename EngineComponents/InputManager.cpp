#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Initialize()
{
	glutSpecialFunc(SpecialKeyPress);
	glutSpecialUpFunc(SpecialKeyRelease);
	glutKeyboardFunc(CharKeyPress);
	glutKeyboardUpFunc(CharKeyRelease);

}

void InputManager::SpecialKeyPress(int key, int x, int y)
{
}

void InputManager::SpecialKeyRelease(int key, int x, int y)
{
}

void InputManager::CharKeyPress(unsigned char key, int x, int y)
{
}

void InputManager::CharKeyRelease(unsigned char key, int x, int y)
{
}
