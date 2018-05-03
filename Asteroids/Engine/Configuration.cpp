#include "Configuration.h"

#include "Random.h"

ResourceManager<sf::Texture, int> Configuration::textures;
ResourceManager<sf::Font, int> Configuration::fonts;
ResourceManager<sf::SoundBuffer, int> Configuration::sounds;
ResourceManager<sf::Music, int> Configuration::musics;

ActionMap<int> Configuration::playerInputs;
int Configuration::level;
int Configuration::lives;

Player* Configuration::player = nullptr;

int Configuration::_score;
sf::Text Configuration::_txt_score;
sf::Sprite Configuration::_spr_lives;

void Configuration::initialize()
{
	initTextures();
	initFonts();
	initSounds();
	initMusics();

	initPlayerInputs();

	rand_init();
	_txt_score.setFont(fonts.get(Fonts::Gui));
	_txt_score.setCharacterSize(24);

	_spr_lives.setTexture(textures.get(Textures::PlayerLife));

	musics.get(Musics::Theme).setLoop(true);
	musics.get(Musics::Theme).play();

	lives = level = _score = -1;
}

void Configuration::reset()
{
	level = 1;
	lives = 3;

	_score = 0;
	_txt_score.setString("0");
}

bool Configuration::isGameOver()
{
	return lives < 0;
}

void Configuration::addScore(int s)
{
	int old_score = _score;
	_score += s*level;
	lives += _score / 10000 - old_score / 10000;
	_txt_score.setString(std::to_string(_score));
}

int Configuration::getScore()
{
	return _score;
}

void Configuration::draw(sf::RenderTarget& target)
{
	target.draw(_txt_score);
	for (int i = 0; i < lives; ++i)
	{
		_spr_lives.setPosition(40 * i, 40);
		target.draw(_spr_lives);
	}
}

void Configuration::initTextures()
{
	//player
	textures.load(Textures::PlayerLife, "SFMLEngineTest/Asteroids/Media/Player/life.png");
	textures.load(Textures::PlayerTexture, "SFMLEngineTest/Asteroids/Media/Player/sprite.png");

	//saucers
	textures.load(Textures::BigSaucer, "SFMLEngineTest/Asteroids/Media/Saucer/Big.png");
	textures.load(Textures::SmallSaucer, "SFMLEngineTest/Asteroids/Media/Saucer/Small.png");

	//meteors
	textures.load(Textures::BigMeteor1, "SFMLEngineTest/Asteroids/Media/Meteor/Big1.png");
	textures.load(Textures::BigMeteor2, "SFMLEngineTest/Asteroids/Media/Meteor/Big2.png");
	textures.load(Textures::BigMeteor3, "SFMLEngineTest/Asteroids/Media/Meteor/Big3.png");
	textures.load(Textures::BigMeteor4, "SFMLEngineTest/Asteroids/Media/Meteor/Big4.png");

	textures.load(Textures::MediumMeteor1, "SFMLEngineTest/Asteroids/Media/Meteor/Medium1.png");
	textures.load(Textures::MediumMeteor2, "SFMLEngineTest/Asteroids/Media/Meteor/Medium2.png");

	textures.load(Textures::SmallMeteor1, "SFMLEngineTest/Asteroids/Media/Meteor/Small1.png");
	textures.load(Textures::SmallMeteor2, "SFMLEngineTest/Asteroids/Media/Meteor/Small2.png");
	textures.load(Textures::SmallMeteor3, "SFMLEngineTest/Asteroids/Media/Meteor/Small3.png");
	textures.load(Textures::SmallMeteor4, "SFMLEngineTest/Asteroids/Media/Meteor/Small4.png");

	//lasers
	textures.load(Textures::ShootPlayer, "SFMLEngineTest/Asteroids/Media/Shoot/Player.png");
	textures.load(Textures::ShootSaucer, "SFMLEngineTest/Asteroids/Media/Shoot/Saucer.png");
}

void Configuration::initFonts()
{
	fonts.load(Fonts::Gui, "SFMLEngineTest/Asteroids/Media/Font/trs-million.ttf");
}

void Configuration::initSounds()
{
	//laser
	sounds.load(Sounds::LaserPlayer, "SFMLEngineTest/Asteroids/Media/SFX/laser1.ogg");
	sounds.load(Sounds::LaserEnemy, "SFMLEngineTest/Asteroids/Media/SFX/laser2.ogg");
	//saucers
	sounds.load(Sounds::SaucerSpawn1, "SFMLEngineTest/Asteroids/Media/SFX/spawn1.flac");
	sounds.load(Sounds::SaucerSpawn2, "SFMLEngineTest/Asteroids/Media/SFX/spawn2.flac");
	//Boom
	sounds.load(Sounds::Boom, "SFMLEngineTest/Asteroids/Media/SFX/boom.flac");
	sounds.load(Sounds::Boom2, "SFMLEngineTest/Asteroids/Media/SFX/boom2.flac");
	//Explosion
	sounds.load(Sounds::Explosion1, "SFMLEngineTest/Asteroids/Media/SFX/explosion1.flac");
	sounds.load(Sounds::Explosion2, "SFMLEngineTest/Asteroids/Media/SFX/explosion2.flac");
	sounds.load(Sounds::Explosion3, "SFMLEngineTest/Asteroids/Media/SFX/explosion3.flac");
	//others
	sounds.load(Sounds::Jump, "SFMLEngineTest/Asteroids/Media/SFX/hyperspace.flac");
}

void Configuration::initMusics()
{
	musics.load(Musics::Theme, "SFMLEngineTest/Asteroids/Media/Music/theme.ogg");
}

void Configuration::initPlayerInputs()
{
	playerInputs.map(PlayerInputs::Up, Action(sf::Keyboard::Up));
	playerInputs.map(PlayerInputs::Right, Action(sf::Keyboard::Right));
	playerInputs.map(PlayerInputs::Left, Action(sf::Keyboard::Left));
	playerInputs.map(PlayerInputs::Shoot, Action(sf::Keyboard::Z));
	playerInputs.map(PlayerInputs::Hyperspace, Action(sf::Keyboard::X));
}