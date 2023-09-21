#include "Window.h"
#include <Raylib/raylib.h>

GameGraphics::Window::Window(int width, int height, const char* title)
{
	m_height = height;
	m_width = width;
	m_title = title;

}

bool GameGraphics::Window::getShouldClose()
{
	return WindowShouldClose();
}

int GameGraphics::Window::getFrameRate()
{

	return GetFPS();
}

void GameGraphics::Window::setTargetFrameRate(int fps)
{
	SetTargetFPS(fps);
}

void GameGraphics::Window::open()
{
	InitWindow(m_width, m_height, m_title);
}

void GameGraphics::Window::beginDrawing()
{
	BeginDrawing();
	ClearBackground(BLACK);
}

void GameGraphics::Window::endDrawing()
{
	EndDrawing();
}

void GameGraphics::Window::close()
{
	CloseWindow();
}
