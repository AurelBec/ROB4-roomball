#include "../hdr/Moteur2D.hpp"

using namespace std;
using namespace sf;

// CONSTRUCTOR
/////////////////////////
Moteur2D::Moteur2D(Settings &settings) 
: m_state(IN_MENU)
, m_settings(settings)
, m_window(VideoMode(W_WINDOW, H_WINDOW), "ROOMBALL", Style::Default, *(m_settings.getSFMLSettings()))
{
}

Moteur2D&
Moteur2D::operator = ( const Moteur2D &copy)
{
	m_state = copy.m_state;
	m_settings = copy.m_settings;
	m_window.create(VideoMode(W_WINDOW, H_WINDOW), "ROOMBALL", Style::Default, *(m_settings.getSFMLSettings()));

	return *this;
}


// DESRUCTOR
/////////////////////////
Moteur2D::~Moteur2D()
{ 
	//delete m_game;
}

// SETTERS
/////////////////////////


// GETTERS
/////////////////////////


// OTHERS METHODS
/////////////////////////
void 
Moteur2D::run()
{
	switch( m_state)
	{
		case IN_GAME:
			m_game.setOptions(m_menu.getChoix(0), m_menu.getChoix(1));
			updateGame();
			break;

		case IN_MENU:
			updateMenu();
			break;

		default : break;
	}
}

void 
Moteur2D::updateMenu()
{
	float dt;
	bool m_paused = false;
	Event event;

	while (m_window.isOpen())
	{
		while(m_window.pollEvent(event))
		{
			if(event.type == Event::Closed)
				m_window.close();

			if(event.type == Event::LostFocus) m_paused = true;
			if(event.type == Event::GainedFocus) m_paused = false;

			if(event.type == Event::KeyPressed)
			{
				if(event.key.code == Keyboard::Escape)
				{
					switch(m_menu.prevMenu())
					{
						case QUIT:
							m_window.close();
							break;

						default: break;
					}
				}

				if(event.key.code == Keyboard::Return)
				{
					switch(m_menu.nextMenu())
					{
						case IN_GAME:
							m_game.setOptions(m_menu.getChoix(0), m_menu.getChoix(1));
							updateGame();
							m_menu.ending(m_game.getWinnerName(), m_game.getWinnerColor(), m_game.getScore(1), m_game.getScore(0));
							break;

						case QUIT:
							m_window.close();
							break;

						default: break;
					}
				}

				if(event.key.code == Keyboard::Up || event.key.code == Keyboard::Left)
				{
					m_menu.prevSelection();
				}

				if(event.key.code == Keyboard::Down || event.key.code ==Keyboard::Right)
				{
					m_menu.nextSelection();
				}
			}
		}
		
		dt = m_clock.restart().asSeconds();
		if( m_paused ) dt = 0;

		m_menu.update(dt);
		
		m_window.clear();
		m_window.draw(m_menu);
		m_window.display();

		sleep( milliseconds( 1000* (1.f/m_settings.getIPS() - dt - m_clock.getElapsedTime().asSeconds())));
	}

}

void 
Moteur2D::updateGame()
{
	float dt;
	bool m_paused = false;
	bool m_end = false;
	Event event;

	while (m_window.isOpen() && !m_end)
	{
		while(m_window.pollEvent(event))
		{
			if(event.type == Event::Closed)
				m_window.close();

			if(event.type == Event::LostFocus) m_paused = true;
			if(event.type == Event::GainedFocus) m_paused = false;

			if(event.type == Event::KeyPressed)
			{
				if(event.key.code == Keyboard::Escape)
					m_window.close();

				m_game.updateAction(event.key.code, true);
			}

			if(event.type == Event::KeyReleased)
			{
				if(event.key.code == Keyboard::Escape)
					m_window.close();

				if(event.key.code == Keyboard::Space)
					m_paused = !m_paused;

				m_game.updateAction(event.key.code, false);
			}
		}

		dt = m_clock.restart().asSeconds();
		if( m_paused ) dt = 0;
		
		m_game.update(dt * m_settings.getVit());
		
		m_window.clear();
		m_window.draw(m_game);
		m_window.display();

		sleep( milliseconds( 1000* (1.f/m_settings.getIPS() - dt - m_clock.getElapsedTime().asSeconds())));
		m_end = m_game.getFinish();
	}
}


void
Moteur2D::collision(Robot *robot, Bonus *bonus, const float dt)
{
	float dx, dy, r;

	dx = robot->getX() - bonus->getX();
	dy = robot->getY() - bonus->getY();
	r = robot->getRadius() + bonus->getRadius();

	if( dx*dx + dy*dy > r*r) return;
	else bonus->effect(robot);
}

void 
Moteur2D::collision(Robot *robot1, Robot *robot2, const float dt)
{
	float dx, dy, r, da, v1, v2, a1, a2;

	dx = robot1->getX() - robot2->getX();
	dy = robot1->getY() - robot2->getY();
	r = robot1->getRadius() + robot2->getRadius();

	if( dx*dx + dy*dy > r*r) return;

	da = PI/2 - atan2(dy, dx);

	//float m1 = r1->getM();
	v1 = robot1->getSpeed();
	a1 = robot1->getAngle() + da;
	//float m2 = r2->getM();
	v2 = robot2->getSpeed();
	a2 = robot2->getAngle() + da;


	//Recalage des objets pour eviter la sur-collision
	robot1->backPreviousPos(dt);
	robot2->backPreviousPos(dt);

	if( ! robot1->isControlled())
	{
		robot1->setAngle( atan( (v2/v1) * (sin(a2)/cos(a1))) - da);
		//r1->setVit( sqrt(v2*sin(a2)*v2*sin(a2) + v1*v1*cos(a1)*cos(a1)));
	}
	if( ! robot2-> isControlled())
	{
		robot2->setAngle( atan( (v1/v2) * (sin(a1)/cos(a2))) - da);
		//r2->setVit( sqrt(v1*sin(a1)*v1*sin(a1) + v2*v2*cos(a2)*cos(a2)));
	}

	robot1->update(-1, 0);
	robot2->update(-1, 0);
}

void 
Moteur2D::collision(Robot *robot, Ball *ball, const float dt)
{
	float dx, dy, r, da, v1, v2, a1, a2;

	//Calcul des parametres de collision
	dx = robot->getX() - ball->getX();
	dy = robot->getY() - ball->getY();
	r = robot->getRadius() + ball->getRadius();

	if( dx*dx + dy*dy > r*r) return;

	da = PI/2 - atan2(dy, dx);
	
	v1 = robot->getSpeed();
	a1 = robot->getAngle() + da;

	v2 = ball->getSpeed();
	a2 = ball->getAngle() + da;

	//Recalage des objets pour eviter la sur-collision, on repositionne a l'endroit avant collision
	robot->backPreviousPos(0);
	ball->backPreviousPos(2*dt);
	
	//Calcul des nouveaux angles et vitesses
	//float angle_methode_physique = atan( 2*(v1*sin(a1))/(v2*cos(a2)) - tan(a2)) - da;
	ball->setAngle(atan( 2*(v1*sin(a1))/(v2*cos(a2)) - tan(a2)) - da);

	//float foo = 2*v1*sin(a1) - v2*sin(a2);
	ball->setSpeed( sqrt((2*v1*sin(a1) - v2*sin(a2))*(2*v1*sin(a1) - v2*sin(a2)) + v2*v2*cos(a2)*cos(a2)));
	
	ball->update(0);
}

/*void Moteur2D::collision(Robot *robot, Bonus *bonus)
{

}*/

// int 
// Moteur2D::collision(Ball *ball, Goal *goal)
// {
// 	if(!((ball->getX() >= goal->getX() + goal->getW())      // trop à droite
// 		|| (ball->getX() + 2*ball->getRadius() <= goal->getX()) // trop à gauche
// 		|| (ball->getY() >= goal->getY() + goal->getH()) // trop en bas
// 		|| (ball->getY() + 2*ball->getRadius() <= goal->getY())))  // trop en haut
// 	{
// 		//On recup equipe qui marque
// 		uint teamWin = 1 - goal->getNum();

// 		//On remet la balle au centre
// 		ball->reset();
// 		return teamWin;
// 	}
// 	else
// 	{
// 		return -1;
// 	}
// }


void 
Moteur2D::collisionBorder(Ball *ballon, const Vector2f &dim)
{
	if( ballon->getX() + ballon->getRadius() > (W_WINDOW + dim.x)/2)
	{
		ballon->setX((W_WINDOW + dim.x)/2 - ballon->getRadius());
		ballon->setAngle( PI - ballon->getAngle());
	}
	if( ballon->getX() - ballon->getRadius() < (W_WINDOW - dim.x)/2)
	{
		ballon->setX((W_WINDOW - dim.x)/2 + ballon->getRadius());
		ballon->setAngle( PI - ballon->getAngle());
	}
	if( ballon->getY() + ballon->getRadius() > (H_WINDOW + dim.y)/2)
	{
		ballon->setY((H_WINDOW + dim.y)/2 - ballon->getRadius());
		ballon->setAngle( - ballon->getAngle());
	}
	if( ballon->getY() - ballon->getRadius() < (H_WINDOW - dim.y)/2)
	{
		ballon->setY((H_WINDOW - dim.y)/2 + ballon->getRadius());
		ballon->setAngle( - ballon->getAngle());
	}
}
