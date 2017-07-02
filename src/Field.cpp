#include "../hdr/Field.hpp"
#include "../hdr/Moteur2D.hpp"

using namespace std;
using namespace sf;

// CONSTRUCTOR
/////////////////////////
Field::Field() 
: m_dim(W_WINDOW - 4 * (FONT_SIZE + 5), H_WINDOW - 4 * (FONT_SIZE + 5))
, m_center(W_WINDOW / 2, H_WINDOW  / 2)
, m_texture(Color::White, m_center, m_dim + Vector2f(2*H_BORD, 2*H_BORD), H_BORD)
{
	m_elements.push_back( new Ball(Color::Green, m_center, 10));

	m_elements.push_back( new BonusPoint(m_dim.x/2, m_dim.y/2));
	
	m_goals.push_back( new Goal(Color::White, 0, Vector2f(m_center.x, m_center.y + (m_dim.y - H_CAGE)/2 + H_BORD/2), Vector2f(W_CAGE, H_CAGE)) );
	m_goals.push_back( new Goal(Color::White, 1, Vector2f(m_center.x, m_center.y - (m_dim.y - H_CAGE)/2 - H_BORD/2), Vector2f(W_CAGE, H_CAGE)) );
}

// DESTRUCTOR
/////////////////////////
Field::~Field()
{
	for(IT_ELEMENT elem = m_elements.begin(); elem != m_elements.end(); ++elem)
		delete (*elem);
	m_elements.clear();

	for(IT_GOAL goal = m_goals.begin(); goal != m_goals.end(); ++goal)
		delete (*goal);
	m_goals.clear();
}

// SETTERS
/////////////////////////
void
Field::setColor(const int i, const Color color)
{
	//m_goals(i).setColor(color);
	m_texture.setColorLimit(i, color);
	m_goals[i]->setColor(color);
}


// GETTERS
/////////////////////////


// OTHERS METHODS
/////////////////////////
void 
Field::addRobot(const vector<Robot*> *v_robot)
{
	for(IT_ROBOT robot = (*v_robot).begin(); robot != (*v_robot).end(); ++robot)
		m_robots.push_back(*robot);
}

void 
Field::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = NULL;

	target.draw(m_texture, states);

	for(IT_GOAL goal = m_goals.begin(); goal != m_goals.end(); ++goal)
		target.draw(**goal, states);

	for(IT_ROBOT robot = m_robots.begin(); robot != m_robots.end(); ++robot)
		target.draw(**robot, states);

	for(IT_ELEMENT elem = m_elements.begin(); elem != m_elements.end(); ++elem)
		target.draw(**elem, states);
}

void 
Field::checkCollisionBorder(Robot *robot)
{
	if( robot->getX() + robot->getRadius() > (W_WINDOW + m_dim.x)/2 )
		robot->setX((W_WINDOW + m_dim.x)/2 - robot->getRadius());
	if( robot->getX() - robot->getRadius() < (W_WINDOW - m_dim.x)/2 )
		robot->setX((W_WINDOW - m_dim.x)/2 + robot->getRadius());
	if( robot->getY() > robot->getBorder(1))
		robot->setY(robot->getBorder(1));
	if( robot->getY() < robot->getBorder(0))
		robot->setY(robot->getBorder(0));

	if( !robot->isControlled())
	{
		if( robot->getX() + robot->getRadius() == (W_WINDOW + m_dim.x)/2 || robot->getX() - robot->getRadius() == (W_WINDOW - m_dim.x)/2)
			robot->setAngle( PI - robot->getAngle());
		if( robot->getY() == robot->getBorder(1) || robot->getY() == robot->getBorder(0))
			robot->setAngle( - robot->getAngle());
	}
}

void 
Field::checkGoal()
{
	//Le ballon est assez petit pour etre considéré carré
	Ball *ballon = (Ball*) m_elements[0];

	for(IT_GOAL goal = m_goals.begin(); goal != m_goals.end(); ++goal)
	{
		if(!((ballon->getX() >= (*goal)->getX() + (*goal)->getW())      // trop à droite
			|| (ballon->getX() + 2*ballon->getRadius() <= (*goal)->getX()) // trop à gauche
			|| (ballon->getY() >= (*goal)->getY() + (*goal)->getH()) // trop en bas
			|| (ballon->getY() + 2*ballon->getRadius() <= (*goal)->getY())))  // trop en haut
		{
			//On recup equipe qui marque
			uint teamWin = 1 - (*goal)->getNum();

			//On donne 1pt
			for(IT_ROBOT robot = m_robots.begin(); robot != m_robots.end(); ++robot)
				if((*robot)->getNum() == teamWin)
					(*robot)->addPoint();

			//On remet la balle au centre
			ballon->reset();
			break;
		}
	}
}


void 
Field::update(const float dt)
{ 
	Ball* ball = static_cast<Ball*>(m_elements[0]);

	//ROBOT - BORD
	for(IT_ROBOT robot = m_robots.begin(); robot != m_robots.end(); ++robot)
		checkCollisionBorder(*robot);

	//BALLON - BORD
	Moteur2D::collisionBorder(ball, m_dim);

	for(IT_GOAL goal = m_goals.begin(); goal != m_goals.end(); ++goal)
		checkGoal();

	//BALLON - ROBOT
	for(IT_ROBOT robot = m_robots.begin(); robot != m_robots.end(); ++robot)
		Moteur2D::collision(*robot, ball, dt);
	
	//ROBOT - ROBOT
	for(IT_ROBOT r1 = m_robots.begin(); r1 != m_robots.end(); ++r1)
		for(IT_ROBOT r2 = r1 + 1; r2 != m_robots.end(); ++r2)
			Moteur2D::collision(*r1, *r2, dt);

	//ROBOT - BONUS
	for(IT_ROBOT robot = m_robots.begin(); robot != m_robots.end(); ++robot)
		for(IT_ELEMENT elem = m_elements.begin() + 1; elem != m_elements.end(); ++elem)
			Moteur2D::collision(*robot, static_cast<Bonus*>(*elem) , dt);


	for(int i = 1; i < m_elements.size(); ++i)
		if( static_cast<Bonus*>(m_elements[i])->getLifetime() <= sf::seconds(0))
			m_elements.erase (m_elements.begin() + i);

	if(m_elements.size() == 1 && rand()%300 == 0)
		m_elements.push_back( new BonusPoint((W_WINDOW + m_dim.x)/2, (H_WINDOW + m_dim.y)/2));

	for(IT_ELEMENT elem = m_elements.begin(); elem != m_elements.end(); ++elem)
		(*elem)->update(dt);

}