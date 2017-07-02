#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <unistd.h>
#include <sstream>       
#include <iostream>       
#include <assert.h>
#include <SFML/Graphics.hpp>

#define DEFAULT_IPS 60
#define DEFAULT_VIT 1
#define DEFAULT_AA 8

class Settings
{
private:
	sf::ContextSettings m_SFMLsettings;
	float m_vit;
	int m_ips;

public:
	Settings(const uint ips = DEFAULT_IPS, const uint antialiasing = DEFAULT_AA, const float vit = DEFAULT_VIT)
	: m_vit(vit)
	, m_ips(ips)
	{
		m_SFMLsettings.antialiasingLevel = antialiasing;
	}

	Settings(int argc, char* argv[])
	{
		using namespace std;
		
		m_ips = DEFAULT_IPS;
		m_vit = DEFAULT_VIT;
		m_SFMLsettings.antialiasingLevel = DEFAULT_AA;

		while( argc > 0)
		{
			if( string(argv[argc-1]) == "-ips")
			{
				istringstream buffer(argv[argc]);
				assert(buffer >> m_ips);
				cout << "Warning : IPS set at " << m_ips << ". Estimate CPU use : " << min(m_ips/8, 50) << "~" << min(m_ips/6, 55) << "%" << endl;
			}

			if( string(argv[argc-1]) == "-vit")
			{
				istringstream buffer(argv[argc]);
				assert(buffer >> m_vit);
				cout << "Warning : Game speed set at " << m_vit << ". Colliding errors may appear" << endl;
			}

			if( string(argv[argc-1]) == "-aa")
			{
				istringstream buffer(argv[argc]);
				assert(buffer >> m_SFMLsettings.antialiasingLevel);
			}

			argc --;
		}
	}

	uint getIPS() const { return m_ips;}
	float getVit() const { return m_vit;}
	sf::ContextSettings *getSFMLSettings() { return &m_SFMLsettings;}
};


#endif