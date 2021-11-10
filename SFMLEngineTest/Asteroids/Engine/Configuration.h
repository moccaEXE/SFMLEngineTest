#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>

#include "ResourceManager.h"
#include "ActionMap.h"

class Player;
class Configuration
{
public:
	Configuration() = delete;
	Configuration(const Configuration&) = delete;
	Configuration& operator=(const Configuration&) = delete;

	enum Textures : int {PlayerTexture, PlayerLife, BigSaucer, SmallSaucer, BigMeteor1, BigMeteor2, BigMeteor3, BigMeteor4, SmallMeteor1, SmallMeteor2, SmallMeteor3, SmallMeteor4, MediumMeteor1,  MediumMeteor2,
		ShootSaucer, ShootPlayer,};
	enum Sounds : int {Jump, Boom, Boom2, SaucerSpawn1, SaucerSpawn2, Explosion1, Explosion2, Explosion3, LaserEnemy, LaserPlayer};

	static ResourceManager<sf::Texture, int> textures;

	enum Fonts : int {Gui};
	static ResourceManager<sf::Font, int> fonts;

	static ResourceManager<sf::SoundBuffer, int> sounds;

	enum PlayerInputs : int {Up, Right, Left, Shoot, Hyperspace};
	
	enum Musics : int {Theme};

	static ResourceManager<sf::Music, int> musics;

	static ActionMap<int> playerInputs;

	static void initialize();
	static void reset();

	static bool isGameOver();

	static void addScore(int points);

	static void draw(sf::RenderTarget& target);

	static int getScore();	

	static int level;
	static int lives;

	static Player* player;

private:
	static void initTextures();
	static void initFonts();
	static void initSounds();
	static void initMusics();

	static void initPlayerInputs();

	static sf::Text _txt_score;
	static sf::Sprite _spr_lives;
	static int _score;

//	static Player* player;
};
