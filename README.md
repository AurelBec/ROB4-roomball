MOD : 07/06/2016 - 19:05

INTRODUCTION
------------------------
L'equipe : Aurelien BEC, Antoine Deyris et Quentin Huet (ROB4)

Le but de ce projet est de realiser un jeu multijoueur sur le meme ecran.
L'utilisateur doit pouvoir jouer contre une intelligence artificielle.

Le jeu presente se rapproche par son gameplay a un babyfoot.
2 equipes de 2 robots s'affrontent sur un terrain de type terrain de football.
Chaque robot evolue dans une zone rectangulaire identique pour chaque robot.
Les controles seront detailles plus bas, mais le joueur a la possibilite de controler son gardien ou son attaquant. Le robot non controle sera laisse piloter par l'ordinateur.

La partie dure 2 minutes, ce parametre peut etre modifier, ainsi que les dimensions du terrain par exemple dans le fichier "hdr/define.h"
Le jeu peut etre lance par la commande './Roombal'
Certains arguments sont pris en charge, la documentation est accessible avec la commande './Roomball help' ou './Roomball doc'



INSTALLATION
------------------------
Des la decompression du projet, il est necessaire de taper la commande 'cmake ./'
Cette commande va generer le makefile necessaire a la compilation du projet, qui peut etre lancee par 'make'

Le jeu est maintenant compile et peut etre lance par './Roomball'



LES CLASSES
------------------------

Moteur2D
--------------
Gere le lancement du jeu et du menu
Gere aussi les collisions entre les objets

Menu
--------------
Gere l'affichage et la mise a jour des menus du jeu.
Les menus sont dessines dans les fichiers "texturesXXXX.h" dans le fichier "hdr/texture/menu"

Game
--------------
Gere l'affichage et la mise a jour du jeu
Un jeu est compose d'un terrain et de 2 joueurs

Terrain
--------------
Gere l'affichage et la mise a jour du terrain
Un terrain est compose de robots, d'elements et de goals

Joueur
--------------
Gere l'affichage des infos du joueur a l'ecran
Un joueur controle 2 robots, 1 attaquant et 1 defenseur
Le joueur 1, en bas joue avec "Up", "Left", "Down" et "Right" et change de robot avec "Shift"
Le joueur 2, en haut joue avec "Z", "Q", "S" et "D" et change de robot avec "A"

Robot
--------------
Gere la mise a jour et l'affichage des robots
Il y a 3 classes derivees de celle ci avec les propres caracteristiques : 
	- Les robots attaquants
	- Les robots defenseurs (plus lent mais plus gros)
	- les robots menus, qui sont present en arrere plan du menu

Goals
--------------
Gere l'affichage des cages

Elements
--------------
Gere la mise a jour et l'affichage des elements sur le terrain
Il y a 2 types d'elements:
	- Le ballon
	- Les bonus



INFOS SUPPLEMENTAIRES
------------------------
Toutes ces classes sauf Moteur2D sont des classes derivees de sf::Drawable et sf::Transformable
Elles doivent donc implementer une fonction 'draw' mais sont donc tres facilement dessinables a l'ecran ainsi que les objets qu'elles contiennent par appel de cette fonction.
Ces classes possedent un attribut m_texture ou plus, qui contiennent un objet simple permettant de dessiner l'objet
Cette methode permet un gain en performance par une enorme economie de calcul tres important

Les bonus ont commence a etre implementes mais n'ont pas ete beaucoup plus devellopes

La musique aurait du etre presente, mais cet ajout a ete laisse de cote par l'equipe

L'avantage des fichiers textures.h dans le dossier "hdr/texture" est principalement la création d'un objet texture, dont le constructeur se charge d'initialiser tout les elements simples constituants le dessin, comme les lignes et les cercles
En plus de ce constructeur, la texture contient forcement un fonction draw qui affiche ces elements de dessin
Chaque tour de boucle se contente donc seulement d'afficher des objets, et pas a chaque fois de les recreer, ce qui economise de nombreux calculs 

Enfin le jeu présente encore de groooooos problemes de collisions dont l'origine est encore inconnue
Ce bug apparait de maniere recurente lors d'un match J vs IA
Ces problemes de collision provoquent la disparition de deux robots, de la balle et l'augmentation sans fin des points d'un joueur
C'est facheux

L'intelligence est encore pour le moment aleatoire, la tentative d'intelligence suiveuse de balle a porté ses fruits, mais les robots d'un meme camps finissait par se renvoyer la balle qu'entre eux
