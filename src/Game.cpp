#include "../hdr/Game.hpp"

using namespace std;
using namespace sf;

// CONSTRUCTOR
/////////////////////////
Game::Game() 
: m_dim(W_WINDOW, H_WINDOW)
, m_paused(false)
, m_J1(0)
, m_J2(1)
, m_timer(PLAY_TIME)
, m_textureTimer(Color::White, num2str(90), 15, W_WINDOW/2, H_WINDOW/2)
{
	m_field.addRobot(m_J1.getEquipe());
	m_field.addRobot(m_J2.getEquipe());
}

// DESTRUCTOR
/////////////////////////
Game::~Game()
{
}

// SETTERS
/////////////////////////
void
Game::setOptions( int r1, int r2)
{
	if(r1 > 1)
	{
		m_J1.setColor(sf::Color::Red);
		m_field.setColor(0, sf::Color::Red);

		m_J2.setColor(sf::Color::Blue);
		m_field.setColor(1, sf::Color::Blue);
	}
	else
	{
		m_J1.setColor(sf::Color::Blue);
		m_field.setColor(0, sf::Color::Blue);
		m_J2.setColor(sf::Color::Red);
		m_field.setColor(1, sf::Color::Red);
	}

	m_J1.setControlledRobot((int) (r1 == 0 || r1 == 3));
	m_J2.setControlledRobot((int) ((r2 == 0 || r2 == 3) + 2*(r2 == 4)));
}


// GETTERS
/////////////////////////
bool
Game::getFinish() const
{
	return ! (m_timer > 0);
}

string
Game::getWinnerName() const
{
	if(getScore(0) > getScore(1))
		return m_J1.getName();
	else if(getScore(0) < getScore(1))
		return m_J2.getName();
	else
		return "Egalite";
}

Color
Game::getWinnerColor() const
{
	if(getScore(0) > getScore(1))
		return m_J1.getColor();
	else if(getScore(0) < getScore(1))
		return m_J2.getColor();
	else
		return Color::White;
}

int
Game::getScore(const int i) const
{
	return (i == 0) ? m_J1.getScore() : m_J2.getScore();
}


// OTHERS METHODS
/////////////////////////
void
Game::update(const float dt)
{
	m_J1.update(dt); 
	m_J2.update(dt);
	m_field.update(dt);

	m_timer -= dt;
	m_textureTimer.setStr(num2str((int) m_timer));
	//m_Texture
}

void
Game::updateAction(const Keyboard::Key key, const bool type)
{
	m_J1.updateAction(key, type);
	m_J2.updateAction(key, type);
}

void
Game::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = NULL;

	target.draw(m_field, states);
	target.draw(m_textureTimer);
	target.draw(m_J1, states);
	target.draw(m_J2, states);
}