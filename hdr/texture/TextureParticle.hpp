#ifndef TEXTPARTICLE_HPP
#define TEXTPARTICLE_HPP

#include "Texture.hpp"


class TextureParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
	TextureParticleSystem() 
	{}

	TextureParticleSystem(uint const count, const sf::Color &color) 
	: m_particles(count)
	, m_lifetime(sf::seconds(3))
	, m_center(0, 0)
	, m_color(color)
	, m_vertices(sf::Points, count)
	{
	}

	TextureParticleSystem &operator=(const TextureParticleSystem &copy)
	{
		m_particles = copy.m_particles;
		m_lifetime = copy.m_lifetime;
		m_center = copy.m_center;
		m_color = copy.m_color;
		m_vertices = copy.m_vertices;

		return *this;
	}

	void setCenter(const sf::Vector2f &center)
	{
		m_center = center;
	}

	void update(const float dt)
	{
		for (std::size_t i = 0; i < m_particles.size(); ++i)
		{
			Particle& p = m_particles[i];
			p.lifetime -= sf::seconds(dt);

			if (p.lifetime <= sf::seconds(0))
				resetParticle(i);

			m_vertices[i].position += p.velocity * dt;

			float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
			m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
			m_vertices[i].color.r = m_color.r;
			m_vertices[i].color.g = m_color.g;
			m_vertices[i].color.b = m_color.b;
		}
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;
		target.draw(m_vertices, states);
	}

private:

	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
	};

	void resetParticle(std::size_t index)
	{
		float angle = (std::rand() % 360) * 3.14f / 180.f;
		float speed = (std::rand() % 50) + 50.f;
		m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

		m_vertices[index].position = m_center;
	}

	std::vector<Particle> m_particles;
	sf::Time m_lifetime;
	sf::Vector2f m_center;
	sf::Color m_color;
	
	sf::VertexArray m_vertices;
};

#endif