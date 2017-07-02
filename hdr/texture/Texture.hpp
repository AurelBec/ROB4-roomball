#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SFML/Graphics.hpp>
#include "../define.h"


class Texture : public sf::Drawable, public sf::Transformable
{
public:
	Texture(){};
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {(void) target; (void) states;};
};

#endif