#include "../hdr/Robots.hpp"

RobotAtk::RobotAtk(const sf::Color color, const uint num) 
: Robot(color, num, 20)
{
	switch(num)
	{
		case 0:
			m_border[0] = H_WINDOW/2.f;
			m_border[1] = H_WINDOW/2.f + H_WINDOW/4.f - FONT_SIZE - 5;
			m_angle = - PI/2;
		break;

		case 1:
			m_border[0] = H_WINDOW/2.f - H_WINDOW/4.f + FONT_SIZE + 5;
			m_border[1] = H_WINDOW/2.f;
			m_angle = PI/2;
		break;
	}

	m_center = sf::Vector2f( W_WINDOW/2 , (m_border[0] + m_border[1]) / 2);
	m_texture = TextureRobot(m_color, m_center, m_angle, m_radius);
}

void 
RobotAtk::update(const int action, const float dt)
{
	m_speed = 0;
	switch(action)
	{
		case Action_LEFT:
			m_angle -= 8*dt;
			break;
		case Action_RIGHT:
			m_angle += 8*dt;
			break;
		case Action_UP:
			m_speed = 250;
			break;
		case Action_DOWN:
			m_speed = -250;
			break;
	}

	m_center.x += m_speed*dt * cos(m_angle);
	m_center.y += m_speed*dt * sin(m_angle);

	m_texture.setPosture(m_center, m_angle);
}
