#include "../hdr/Main.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	int i(argc);
	while( i > 0)
	{
		if( string(argv[i-1]) == "doc" || string(argv[i-1]) == "help" || string(argv[i-1]) == "more")
		{
			cout  << "Roomball Quick Documentation" << endl << endl;
			cout << "[./Roball (-ips X) (-vit X) (-aa X)]" << endl;
			cout << "-ips X : Set the number of IPS at value X" << endl;
			cout << "-vit X : Set the game speed at value X" << endl;
			cout << "-aa  X : Set the AntiAliasingLevel at value X" << endl;
			cout << endl << "--------------" << endl << endl;
			cout << "Roball is a 1 or 2 player game" << endl;
			cout << "2 teams face with 2 bots in" << endl;
			cout << "Each player controls one bot, no matter the team" << endl;
			cout << "Others bots are controlled by AI" << endl;
			cout << endl << "--------------" << endl << endl;
			cout << "Aurelien BEC - Antoine DEYRIS - Quentin HUET" << endl;
			cout << "2017 - Polytech Paris UPMC - ROB4"<< endl << endl;

			return EXIT_SUCCESS;
		}
		i --;
	}

	srand(time(0));

	Settings settings(argc, argv);
	Moteur2D moteur(settings);

	moteur.run();
	
	return EXIT_SUCCESS;
}
