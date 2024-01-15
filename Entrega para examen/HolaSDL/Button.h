#pragma once
#include "Vector2D.h"
#include "GameObject.h"
#include "EventHandler.h"
#include "texture.h"
#include <ostream>
#include <functional>
class Game;
class Button: public GameObject, public EventHandler
{
public:
	using Callback = std::function<void(void)>;
private:
	Texture* texture;
	Point2D<int> pos;
	Callback callback;
	std::unique_ptr<SDL_Rect> rect;
	bool hover;
public:
	Button(Game* game, Texture* texture, Point2D<int> pos);
	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event& event) override;
	void save(std::ostream& os) const override;
	void connect(Button::Callback callback);
};

