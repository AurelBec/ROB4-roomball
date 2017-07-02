#include "../hdr/Player.hpp"

const sf::Keyboard::Key Player::s_control[2][5] = {{sf::Keyboard::Left, 
													sf::Keyboard::Right, 
													sf::Keyboard::Up, 
													sf::Keyboard::Down,
													sf::Keyboard::RShift}, 

													{sf::Keyboard::Q, 
													sf::Keyboard::D, 
													sf::Keyboard::Z, 
													sf::Keyboard::S,
													sf::Keyboard::A}};


using namespace sf;
using namespace std;

// CONSTRUCTOR
/////////////////////////
Player::Player(const uint numPlayer)
: m_idRobotControlled(3)
, m_score(0)
, m_numPlayer(numPlayer)
, m_color(sf::Color::White)
, m_nom(randomName())
{
	std::string buffer;
	//sf::Vector2f center = sf::Vector2f(W_WINDOW/2, H_WINDOW/2);


	// std::cout << "Nom du joueur " << m_numPlayer + 1 << " : ";
	// std::getline(std::cin, buffer);
	// m_nom = new std::string(buffer);


	for (int i = 0; i < 4; ++i)
		m_actionState[i] = false;

	//m_robot[m_idRobotControlled]->setControlled(true);

	switch(numPlayer)
	{
		case 0:
			buffer = std::string("J1 : " + m_nom);
			m_textureNom = TextureText(m_color, buffer, FONT_SIZE, W_WINDOW/2, H_WINDOW - FONT_SIZE);

			buffer = std::string(num2str(m_score));
			m_textureScore = TextureText(m_color, buffer, FONT_SIZE, 2 * (FONT_SIZE + 5), H_WINDOW - FONT_SIZE);

			m_robot.push_back(new RobotAtk(m_color, 0));
			m_robot.push_back(new RobotDef(m_color, 0));
		break;

		case 1:
			buffer = std::string("J2 : " + m_nom);
			m_textureNom = TextureText(m_color, buffer, FONT_SIZE, W_WINDOW/2, FONT_SIZE);

			buffer = std::string(num2str(m_score));
			m_textureScore = TextureText(m_color, buffer, FONT_SIZE, 2 * (FONT_SIZE + 5), FONT_SIZE);

			m_robot.push_back(new RobotAtk(m_color, 1));
			m_robot.push_back(new RobotDef(m_color, 1));
		break;
	}
} 

// DESTRUCTOR
/////////////////////////
Player::~Player()
{
	for (IT_ROBOT robot = m_robot.begin(); robot != m_robot.end(); ++robot)
		delete (*robot);
	m_robot.clear();
}

// SETTERS
/////////////////////////
void
Player::setControlledRobot(const int id)
{
	m_idRobotControlled = id;
	if( id < 2 )
		m_robot[m_idRobotControlled]->setControlled(true);
}

void
Player::setColor(const Color color)
{
	m_color = color;
	m_textureScore.setColor(color);
	m_textureNom.setColor(color);

	for( IT_ROBOT robot = m_robot.begin(); robot != m_robot.end(); ++robot)
		(*robot)->setColor(color);
}


// GETTERS
/////////////////////////
int
Player::getScore() const
{
	return m_score;
}

string
Player::getName() const
{
	return m_nom;
}

Color
Player::getColor() const
{
	return m_color;
}

// OTHERS METHODS
/////////////////////////
void 
Player::update(const float dt)
{
	updateRobots(dt);
	updateScore();
}

void 
Player::updateScore()
{
	if( m_score == m_robot[0]->getScore() && m_score == m_robot[1]->getScore())
		return;
	m_score ++;
	m_textureScore.setStr(num2str(m_score));
	m_textureScore.setPosition(sf::Vector2f(2*FONT_SIZE, -1));

	m_robot[0]->setScore(m_score);
	m_robot[1]->setScore(m_score);
}

void 
Player::updateRobots(const float dt)
{
	for(uint i = 0; i < m_robot.size(); ++i)
		if( i == m_idRobotControlled)
		{
			for (int action = 0; action < 4; ++action)
				if(	m_actionState[action])
					m_robot[i]->update(action, dt);
		}
		else
		{
			m_robot[i]->moveRandom(dt);
		}
}

void 
Player::updateAction(const sf::Keyboard::Key key, const bool type)
{
	for( int i = 0; i < 4; ++i)
		if( key == s_control[m_numPlayer][i])
			m_actionState[i] = type;

	if( key == s_control[m_numPlayer][4] && type == false)
		changeRobot();
}

void 
Player::changeRobot()
{
	m_robot[m_idRobotControlled % m_robot.size()]->setControlled(false);
	m_idRobotControlled = (m_idRobotControlled + 1) % m_robot.size();
	m_robot[m_idRobotControlled]->setControlled(true);
}

void 
Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = NULL;

	target.draw(m_textureNom, states);
	target.draw(m_textureScore, states);
}

string
Player::randomName()
{
	vector<string> name;
	name.push_back("Licorne");
	name.push_back("Poney");
	name.push_back("Robot");
	name.push_back("Prof");
	name.push_back("Eleve");
	name.push_back("Mr");
	name.push_back("Adversaire");
	name.push_back("Pigeon");

	vector<string> adj;
	adj.push_back("sauvage");
	adj.push_back("fou");
	adj.push_back("mechant");
	adj.push_back("impitoyable");
	adj.push_back("roux");
	adj.push_back("albinos");

	return name[rand() % name.size()] + " " + adj[rand()%adj.size()];
}