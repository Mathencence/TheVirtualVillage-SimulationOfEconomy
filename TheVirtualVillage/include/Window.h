#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>
class Game;

class Window
{
public:
	Window();
	~Window();

	void beginDraw();
	void endDraw();

	void update();

	bool isWindowDone() const;
	bool isWindowFullscreen() const;
	const sf::Vector2u& getWindowSize() const;

	void toggleFullscreen();
	void draw(sf::Drawable& drawable);
	void redraw();
	sf::RenderWindow* getRWin() { return &window; }

	void setup(const std::string& title, const sf::Vector2u& size);
	inline void setTitle(const std::string& t) { windowTitle = t; }
	inline void setSize(const sf::Vector2u& size) { windowSize = size; }

private:

	const int fontSize = 50;

	void destroy();
	void create();


	sf::RenderWindow window;
	sf::Vector2u windowSize;
	std::string windowTitle;

	bool isDone;
	bool isFullscreen;
};