#include "Window.h"
#include <iostream>

Window::Window() :
	windowTitle(""),
	windowSize({ 0,0 }),
	isFullscreen(false),
	isDone(false)
{ }

Window::~Window() { destroy(); }

void Window::setup(const std::string& title, const sf::Vector2u& size)
{
	windowTitle = title;
	windowSize = size;
	create();
}


void Window::create()
{
	auto style = (isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	window.create({ windowSize.x, windowSize.y, 32 }, windowTitle, style);
}

void Window::destroy()
{
	window.close();
}

void Window::update()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			isDone = true;
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
			toggleFullscreen();
	}
}

void Window::toggleFullscreen()
{
	isFullscreen = !isFullscreen;
	redraw();
}

void Window::redraw()
{
	destroy();
	create();
}

void Window::beginDraw() { window.clear(sf::Color::Black); }
void Window::endDraw() { window.display(); }

bool Window::isWindowDone() const { return isDone; }
bool Window::isWindowFullscreen() const { return isFullscreen; }
const sf::Vector2u& Window::getWindowSize() const { return windowSize; }

void Window::draw(sf::Drawable& drawable) {
	window.draw(drawable);
}