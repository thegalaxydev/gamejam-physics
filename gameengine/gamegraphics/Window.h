#pragma once

namespace GameGraphics
{
	class Window
	{
	public:
		Window() {}
		Window(int width, int height, const char* title = "Window");

		int getWidth() { return m_width; }
		int getHeight() { return m_height; }

		bool getShouldClose();

		int getFrameRate();
		void setTargetFrameRate(int fps);

		void open();
		void beginDrawing();
		void endDrawing();
		void close();

	private:
		int m_width;
		int m_height;
		const char* m_title;
	};
}
