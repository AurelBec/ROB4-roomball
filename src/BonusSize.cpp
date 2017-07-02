#include "../hdr/Bonus.hpp"

BonusPoint::BonusPoint(const int dim_x, const int dim_y) :
	Bonus(sf::Color::Yellow,sf::Vector2f(std::rand()%dim_x,std::rand()%dim_y), 3)
{
}

BonusPoint::~BonusPoint()
{

}

void BonusPoint::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
		states.transform *= getTransform();
		states.texture = NULL;

		target.draw(m_textureParticles, states);
		target.draw(m_textureBonus, states);
	}

void BonusPoint::update(const float dt)
{
	m_lifetime -= sf::seconds(dt);
	m_textureParticles.update(dt);
}