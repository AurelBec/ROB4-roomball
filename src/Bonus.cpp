#include "../hdr/Bonus.hpp"

Bonus::Bonus(const sf::Color color, const sf::Vector2f center, int lifetime) :
	Element(color, center),
	m_rayon(5),
	m_lifetime(sf::seconds(lifetime)),
	m_textureBonus(color, center, m_rayon),
	m_textureParticles(200, color)
{
	
	m_textureParticles.setCenter(m_center);
}
