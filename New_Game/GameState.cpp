#include "stdafx.h"
#include "GameState.h"
#define _CRT_SECURE_NO_WARNINGS

bool GameState::comp(const std::pair<int, std::string>& a, const std::pair<int, std::string>& b)
{
	return (a.first > b.first);
}

void GameState::initVariables()
{
	srand(static_cast<unsigned>(time(NULL)));
	this->camPosX = 0.f;
	this->camPosY = 0.f;
	this->mapPosXLeft = 0.f;
	this->mapPosYUp = 0.f;
	this->mapPosXRight = 0.f;
	this->mapPosYDown = 0.f;
	this->checkpointPlayer.x = 100.f;
	this->checkpointPlayer.y = 600.f;
	this->moveBossUp = true;
	this->jumpRandom = 0;
	this->textPos = 1020.f;
	this->checkSec = 10;
	this->getInBossStage = false;
	this->bossMaxHP = 100.f;
	this->getWin = false;
	this->bossAttack = false;
	this->bulletPosPattern2 = 1510.f;
	this->fullBullet = false;
	this->pattern = 0;
	this->bulletPattern = 0;
}

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gSettings->resolution.width, 
		this->stateData->gSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(
		0,
		0,
		this->stateData->gSettings->resolution.width,
		this->stateData->gSettings->resolution.height)
	);
}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gSettings->resolution.width),
			static_cast<float>(this->stateData->gSettings->resolution.height)
		)
	);
	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->stateData->gSettings->resolution.width) / 2.f,
			static_cast<float>(this->stateData->gSettings->resolution.height) / 2.f
		)
	);
}

void GameState::initSound()
{
	this->music.openFromFile("res/sound/GameNormal.wav");
	this->music.setVolume(25);

	this->bossMusic.openFromFile("res/sound/BossFight.wav");
	this->bossMusic.setVolume(25);

	this->endMusic.openFromFile("res/sound/Ending.wav");
	this->endMusic.setVolume(25);

	this->music.play();
	this->music.setLoop(true);

	this->bossMusic.setLoop(true);

	if(!this->soundshoot.loadFromFile("res/sound/Pew.wav"))
		throw "ERROR::GAMESTATE::FAILED_TO_LOAD_SOUND_SHOOT_EFFECT";

	if (!this->soundjump1.loadFromFile("res/sound/jump1.wav"))
		throw "ERROR::GAMESTATE::FAILED_TO_LOAD_SOUND_JUMP1_EFFECT";

	if (!this->soundjump2.loadFromFile("res/sound/jump2.wav"))
		throw "ERROR::GAMESTATE::FAILED_TO_LOAD_SOUND_JUMP2_EFFECT";

	if (!this->soundcheckpoint.loadFromFile("res/sound/Checkpoint.wav"))
		throw "ERROR::GAMESTATE::FAILED_TO_LOAD_SOUND_CHECKPOINT_EFFECT";

	if (!this->sounddeath.loadFromFile("res/sound/Death.wav"))
		throw "ERROR::GAMESTATE::FAILED_TO_LOAD_SOUND_DEATH_EFFECT";

	if (!this->soundwarp.loadFromFile("res/sound/warp.wav"))
		throw "ERROR::GAMESTATE::FAILED_TO_LOAD_SOUND_DEATH_EFFECT";

	if (!this->soundbosssound.loadFromFile("res/sound/bossSound.wav"))
		throw "ERROR::GAMESTATE::FAILED_TO_LOAD_SOUND_CHECKPOINT_EFFECT";

	if (!this->soundbosshurt.loadFromFile("res/sound/bossHurt.wav"))
		throw "ERROR::GAMESTATE::FAILED_TO_LOAD_SOUND_DEATH_EFFECT";

	if (!this->soundbossdie.loadFromFile("res/sound/BossDie.wav"))
		throw "ERROR::GAMESTATE::FAILED_TO_LOAD_SOUND_DEATH_EFFECT";

	this->shooteffect.setBuffer(this->soundshoot);
	this->shooteffect.setVolume(25);

	this->jump1effect.setBuffer(this->soundjump1);
	this->jump1effect.setVolume(50);

	this->jump2effect.setBuffer(this->soundjump2);
	this->jump2effect.setVolume(50);

	this->checkpointeffect.setBuffer(this->soundcheckpoint);
	this->checkpointeffect.setVolume(50);

	this->deatheffect.setBuffer(this->sounddeath);
	this->deatheffect.setVolume(50);

	this->warpeffect.setBuffer(this->soundwarp);
	this->warpeffect.setVolume(25);

	this->bosssoundeffect.setBuffer(this->soundbosssound);
	this->bosssoundeffect.setVolume(25);

	this->bosshurteffect.setBuffer(this->soundbosshurt);
	this->bosshurteffect.setVolume(25);

	this->bossdieeffect.setBuffer(this->soundbossdie);
	this->bossdieeffect.setVolume(25);
}

void GameState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	this->bossBackground.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->bgTexture.loadFromFile("res/image/background.png"))
	{
		throw "ERROR::GAMESTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	if (!this->bgBossTexture.loadFromFile("res/image/bossBackground.png"))
	{
		throw "ERROR::GAMESTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->bgTexture);
	this->bossBackground.setTexture(&this->bgBossTexture);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();

}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Font.ttf"))
	{
		throw "ERROR::GAMESTATE::FAILED_TO_LOAD_FONT";
	}
}

void GameState::initText()
{
	this->text.setFont(this->font);
	this->text.setString("test");
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(30);
	this->text.setPosition(this->textPos, 20.f);
}

void GameState::initTexture()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("res/image/mainCharacter.png"))
	{
		throw "ERROR::GAMESTATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["BULLET"].loadFromFile("res/image/Bullet.png"))
	{
		throw "ERROR::GAMESTATE::COULD_NOT_LOAD_BULLET_TEXTURE";
	}
	if (!this->textures["MONSTER"].loadFromFile("res/image/monster.png"))
	{
		throw "ERROR::GAMESTATE::COULD_NOT_LOAD_MONSTER_TEXTURE";
	}
	if (!this->textures["BOSS"].loadFromFile("res/image/Boss.png"))
	{
		throw "ERROR::GAMESTATE::COULD_NOT_LOAD_BOSS_TEXTURE";
	}
	if (!this->textures["ITEM"].loadFromFile("res/image/JumpItem.png"))
	{
		throw "ERROR::GAMESTATE::COULD_NOT_LOAD_ITEM_TEXTURE";
	}
	if (!this->textures["BOSS_BULLET"].loadFromFile("res/image/Boss_Bullet.png"))
	{
		throw "ERROR::GAMESTATE::COULD_NOT_LOAD_BOSS_BULLET_TEXTURE";
	}
}

void GameState::initTextBox()
{
	this->playername = new Textbox(20, sf::Color::White, true, *this->window, this->font);

	this->playername->addButton("ENTER", 520.f, "Enter");
	this->playername->setPosition(sf::Vector2f(480.f,360.f));
	this->playername->setlimit(true, 10);

	fp = fopen("Score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s", &temp);
		name[i] = temp;
		fscanf(fp, "%d", &score[i]);

		userScore.push_back(make_pair(score[i], name[i]));
		std::cout << temp << " " << score;
	}
	sort(userScore.begin(), userScore.end());


	fclose(fp);
}



void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 520.f, "Leave");
}

void GameState::initPlayer()
{
	this->player = new Player(100, 600, this->textures["PLAYER_SHEET"]);
	//this->player = new Player(10060, 1260, this->textures["PLAYER_SHEET"]);
}

void GameState::initMonster()
{
	this->monsters.push_back(new Monster(150, 400, this->textures["MONSTER"], MonsterTypes::WALKING));
	this->monsters.push_back(new Monster(4890, 120, this->textures["MONSTER"], MonsterTypes::WALKING));
	this->monsters.push_back(new Monster(4580, 310, this->textures["MONSTER"], MonsterTypes::JUSTIDLE));
	this->monsters.push_back(new Monster(4930, 330, this->textures["MONSTER"], MonsterTypes::WALKING));
	this->monsters.push_back(new Monster(5230, 330, this->textures["MONSTER"], MonsterTypes::WALKING));
	this->monsters.push_back(new Monster(5060, 580, this->textures["MONSTER"], MonsterTypes::RANDOMJUMPIDLE));
	this->monsters.push_back(new Monster(5260, 580, this->textures["MONSTER"], MonsterTypes::RANDOMJUMPIDLE));
	this->monsters.push_back(new Monster(5630, 600, this->textures["MONSTER"], MonsterTypes::RANDOMJUMPWALKING));
	this->monsters.push_back(new Monster(5830, 600, this->textures["MONSTER"], MonsterTypes::RANDOMJUMPWALKING));
	this->monsters.push_back(new Monster(6090, 600, this->textures["MONSTER"], MonsterTypes::RANDOMJUMPWALKING));
	this->monsters.push_back(new Monster(6290, 600, this->textures["MONSTER"], MonsterTypes::RANDOMJUMPWALKING));
	this->monsters.push_back(new Monster(8900, 590, this->textures["MONSTER"], MonsterTypes::WALKING));
	this->monsters.push_back(new Monster(9500, 590, this->textures["MONSTER"], MonsterTypes::WALKING));
	this->monsters.push_back(new Monster(9250, 360, this->textures["MONSTER"], MonsterTypes::RANDOMJUMPWALKING));
}

void GameState::initItem()
{
	this->items.push_back(new Item(500, 200, this->textures["ITEM"]));
	this->items.push_back(new Item(700, 200, this->textures["ITEM"]));
	this->items.push_back(new Item(900, 200, this->textures["ITEM"]));
	this->items.push_back(new Item(2820, 200, this->textures["ITEM"]));
	this->items.push_back(new Item(3020, 200, this->textures["ITEM"]));
	this->items.push_back(new Item(10120, 530, this->textures["ITEM"]));
	this->items.push_back(new Item(10290, 530, this->textures["ITEM"]));
	this->items.push_back(new Item(9970, 895, this->textures["ITEM"]));
	this->items.push_back(new Item(10035, 950, this->textures["ITEM"]));
	this->items.push_back(new Item(10100, 1015, this->textures["ITEM"]));
	this->items.push_back(new Item(10165, 1080, this->textures["ITEM"]));
	this->items.push_back(new Item(10230, 1145, this->textures["ITEM"]));
}

void GameState::initBoss()
{
	this->boss = new Boss(1220, 1580, this->textures["BOSS"]);
	this->bossHP.setFillColor(sf::Color::White);
	this->bossHP.setPosition(sf::Vector2f(0.f, 0.f));
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 350, 225, "res/image/Tileset.png");
	this->tileMap->loadFromFile("text.eosmp");
}

GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initDeferredRender();
	this->initView();
	this->initSound();
	this->initBackground();
	this->initKeybinds();
	this->initFonts();
	this->initText();
	this->initTexture();
	this->initTextBox();
	this->initPauseMenu();

	this->initPlayer();
	this->initMonster();
	this->initItem();
	this->initBoss();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->playername;
	delete this->pmenu;
	delete this->player;
	delete this->boss;
	for (size_t i = 0; i < this->monsters.size(); i++)
	{
		delete this->monsters[i];
	}
	delete this->tileMap;
}

void GameState::updateView(const float& dt)
{
	this->mapPosXLeft = this->camPosX * this->stateData->gSettings->resolution.width;
	this->mapPosYUp = this->camPosY * this->stateData->gSettings->resolution.height;
	this->mapPosXRight = (this->camPosX + 1.f) * this->stateData->gSettings->resolution.width;
	this->mapPosYDown = (this->camPosY + 1.f) * this->stateData->gSettings->resolution.height;
	//Cam move right
	if (this->player->getPosition().x > this->mapPosXRight)
	{
		this->view.move(static_cast<float>(this->stateData->gSettings->resolution.width), 0.f);
		camPosX++;
	}
	//Cam move left
	if (this->player->getPosition().x < this->mapPosXLeft)
	{
		this->view.move(static_cast<float>(this->stateData->gSettings->resolution.width) * -1.f, 0.f);
		camPosX--;
	}
	//Cam move up
	if (this->player->getPosition().y < this->mapPosYUp)
	{
		this->view.move(0.f, static_cast<float>(this->stateData->gSettings->resolution.height) * -1.f);
		camPosY--;
	}
	//Cam move down
	if (this->player->getPosition().y > this->mapPosYDown)
	{
		this->view.move(0.f, static_cast<float>(this->stateData->gSettings->resolution.height));
		camPosY++;
	}
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("C"))) && this->getKeytime1())
		if (this->player->getCanJump())
		{
			this->player->jump();
			if (this->player->getJumpCount() == 1)
				jump1effect.play();
			else if (this->player->getJumpCount() == 2)
				jump2effect.play();
		}
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("X"))) && this->getKeytime2() && this->bullets.size() < 5)
	{
		this->shooteffect.play();
		this->bullets.push_back(new Bullet(this->player->getPosition().x + 36.f, this->player->getPosition().y + 14.f, this->textures["BULLET"]));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Z"))) && this->getKeytime3())
	{
		this->player->checkpointJumpCount();
		this->player->stopVelocity();
		this->player->setPosition(checkpointPlayer.x, checkpointPlayer.y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("R"))) && this->getKeytime3())
	{
		this->player->setPosition(100.f, 600.f);
	}
}

void GameState::updateTime()
{
	this->gameTime = this->clock.getElapsedTime();
	//std::cout << this->gameTime.asSeconds() << "\n";
	this->sec = static_cast<int>(this->gameTime.asSeconds());
	this->text.setString(std::to_string(this->sec));
	if (this->sec == this->checkSec)
	{
		this->checkSec *= 10;
		this->textPos -= 20.f;
		this->text.setPosition(this->textPos, 20.f);
	}
}

void GameState::updatePlayer(const float& dt)
{
	this->updatePlayerInput(dt);

	this->player->update(dt);
}

void GameState::updateMonster(const float& dt)
{
	for (size_t i = 0; i < this->monsters.size(); i++)
	{	
		this->monsters[i]->update(dt);
		this->moveMonsterRight.push_back(true);

		if (this->monsters[i]->getType() == MonsterTypes::RANDOMJUMPIDLE)
		{
			this->jumpRandom = rand() % 100;
			if(this->jumpRandom == 5)
				this->monsters[i]->jump();
		}
		else if (this->monsters[i]->getType() == MonsterTypes::WALKING)
		{
			if (this->moveMonsterRight[i])
			{
				this->monsters[i]->move(1.f, 0.f, dt);
				if (this->tileMap->getMonsterCollision(this->monsters[i], dt))
					this->moveMonsterRight[i] = false;
			}
			else
			{
				this->monsters[i]->move(-1.f, 0.f, dt);
				if (this->tileMap->getMonsterCollision(this->monsters[i], dt))
					this->moveMonsterRight[i] = true;
			}
		}
		else if (this->monsters[i]->getType() == MonsterTypes::RANDOMJUMPWALKING)
		{
			if (this->moveMonsterRight[i])
			{
				this->jumpRandom = rand() % 100;
				if (this->jumpRandom == 5)
					this->monsters[i]->jump();
				this->monsters[i]->move(1.f, 0.f, dt);
				if (this->tileMap->getMonsterCollision(this->monsters[i], dt))
					this->moveMonsterRight[i] = false;
			}
			else
			{
				this->jumpRandom = rand() % 100;
				if (this->jumpRandom == 5)
					this->monsters[i]->jump();
				this->monsters[i]->move(-1.f, 0.f, dt);
				if (this->tileMap->getMonsterCollision(this->monsters[i], dt))
					this->moveMonsterRight[i] = true;
			}
		}
		if (this->monsters[i]->getIntersects(this->player->getGlobalBounds()))
		{
			this->deatheffect.play();
			this->player->checkpointJumpCount();
			this->player->stopVelocity();
			this->player->setPosition(checkpointPlayer.x, checkpointPlayer.y);
		}

		for (size_t j = 0; j < this->bullets.size(); j++)
		{
			if (this->monsters[i]->getIntersects(this->bullets[j]->getGlobalBounds()))
				this->bullets.erase(bullets.begin() + j);
		}
	}
}

void GameState::updateItem(const float& dt)
{
	for (size_t i = 0; i < this->items.size(); i++)
	{
		this->items[i]->update(dt);

		if (this->items[i]->getIntersects(this->player->getGlobalBounds()))
		{
			this->player->checkpointJumpCount();
			this->itemPos.push_back(sf::Vector2f(this->items[i]->getPosition().x, this->items[i]->getPosition().y)); //Save Pos item
			this->itemTime.push_back(sf::Clock());
			this->items.erase(items.begin() + i);
		}
		
	}
	for (size_t j = 0; j < this->itemPos.size(); j++)
	{
		sf::Time elapsed = this->itemTime[j].getElapsedTime();
		if (elapsed.asSeconds() >= 3.f)
		{
			this->items.push_back(new Item(this->itemPos[j].x, this->itemPos[j].y, this->textures["ITEM"]));
			this->itemPos.erase(itemPos.begin() + j);
			this->itemTime.erase(itemTime.begin() + j);
		}
	}
}

void GameState::updateBoss(const float& dt)
{
	if (this->getInBossStage)
	{
		sf::Time bossElapsed = bossTiming.getElapsedTime();

		//std::cout << bossElapsed.asSeconds() << "\n";

		if (bossElapsed.asSeconds() >= 5.f && !this->getWin)
		{
			this->bosssoundeffect.play();
			this->bossTiming.restart();
		}
			
		
		this->boss->update(dt);

		if (this->moveBossUp)
		{
			this->boss->move(0.f, -1.f, dt);
			if (this->boss->getPosition().y < this->mapPosYUp + 50.f)
			{
				this->boss->setPosition(this->boss->getPosition().x, this->mapPosYUp + 50.f);
				this->boss->stopVelocityY();
				this->moveBossUp = false;
			}
		}
		else
		{
			this->boss->move(0.f, 1.f, dt);
			if (this->boss->getPosition().y > this->mapPosYDown - 300.f)
			{
				this->boss->setPosition(this->boss->getPosition().x, this->mapPosYDown - 300.f);
				this->boss->stopVelocityY();
				this->moveBossUp = true;
			}
		}

		for (size_t i = 0; i < this->bullets.size(); i++)
		{
			if (this->boss->getIntersects(this->bullets[i]->getGlobalBounds()) && this->bossMaxHP > 0.f)
			{
				this->bosshurteffect.play();
				this->bossMaxHP -= 1.f;
				this->bullets.erase(bullets.begin() + i);
			}
		}
		if (this->bossMaxHP == 0.f)
		{
			this->bossMusic.stop();
			this->bossdieeffect.play();
			this->getWin = true;
			this->playername->setGetWin(true);
		}
		if (!this->bossAttack)
		{
			this->pattern = rand() % 3 + 1;
			this->bossAttack = true;
			for (size_t j = 0; j < this->playerPos.size(); j++)
			{
				this->playerPos.pop_back();
			}
		}
	}
}

void GameState::updateBossAttackPattern1(const float& dt)
{
	std::cout << "PATTERN1" << "\n";
	sf::Time bossDelayElapsed = bossDelay.getElapsedTime();
	if (bossDelayElapsed.asSeconds() >= 0.5f && this->bossBullets.size() < 8 && !this->fullBullet && this->bulletPattern < 8)
	{
		this->bossBullets.push_back(new BossBullet(770.f, static_cast<float>(rand() % 720) + this->mapPosYUp, this->textures["BOSS_BULLET"], static_cast<short>(rand() % 4) + 1));
		this->bulletPattern++;
		this->bossDelay.restart();
	}
	else if (this->bossBullets.size() >= 8)
		this->fullBullet = true;

	if (this->bulletPattern >= 8 && this->bossBullets.size() == 0)
	{
		this->bulletPattern = 0;
		this->bossAttack = false;
		this->fullBullet = false;
		this->pattern = 0;
	}
}

void GameState::updateBossAttackPattern2(const float& dt)
{
	std::cout << "PATTERN2" << "\n";
	this->bulletPosYPattern3 = static_cast<float>(rand() % 720) + this->mapPosYUp;
	if (this->bossBullets.size() < 3 && !this->fullBullet)
	{
		this->bossBullets.push_back(new BossBullet(770.f, this->bulletPosYPattern3, this->textures["BOSS_BULLET"], 4));
		this->bossBullets.push_back(new BossBullet(770.f, this->bulletPosYPattern3 + 38.f, this->textures["BOSS_BULLET"], 4));
		this->bossBullets.push_back(new BossBullet(770.f, this->bulletPosYPattern3 + 76.f, this->textures["BOSS_BULLET"], 4));
		this->bulletPattern += 3;
	}
	else if (this->bossBullets.size() >= 3)
		this->fullBullet = true;

	if (this->bulletPattern >= 3 && this->bossBullets.size() == 0)
	{
		this->bulletPattern = 0;
		this->bossAttack = false;
		this->fullBullet = false;
		this->pattern = 0;
	}
}

void GameState::updateBossAttackPattern3(const float& dt)
{
	//std::cout << "PATTERN3" << "\n";
	sf::Time bossDelayElapsed = bossDelay.getElapsedTime();
	if (bossDelayElapsed.asSeconds() >= 1.f && this->bossBullets.size() < 4 && !this->fullBullet && this->bulletPattern < 4)
	{
		this->bossBullets.push_back(new BossBullet(770.f, this->bulletPosPattern2, this->textures["BOSS_BULLET"], 2));
		this->playerPos.push_back(sf::Vector2f(this->player->getPosition()));
		this->bossDelay.restart();
		this->bulletPosPattern2 += 147.5f;
		this->bulletPattern++;
	}
	else if (this->bulletPosPattern2 >= 2100.f)
	{
		this->bulletPosPattern2 = 1510.f;
		this->fullBullet = true;
	}

	if (this->bulletPattern >= 4 && this->bossBullets.size() == 0)
	{
		this->bulletPattern = 0;
		this->bossAttack = false;
		this->fullBullet = false;
		this->pattern = 0;
	}
}

void GameState::updateBossHP()
{
	this->bossHP.setPosition(sf::Vector2f(0.f, 710.f));
	this->bossHP.setSize(sf::Vector2f(static_cast<float>(this->stateData->gSettings->resolution.width) * this->bossMaxHP / 100.f, 10.f));
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT") && this->getKeytime())
	{
		this->nowInMainMenuState();
		this->endState();
	}
}

void GameState::updateMusic()
{
	if (!this->getInBossStage && this->music.getStatus() == 0 && !this->getWin)
	{
		this->music.play();
		this->bossMusic.stop();
	}
	else if (this->getInBossStage && this->bossMusic.getStatus() == 0 && !this->getWin)
	{
		this->music.stop();
		this->bossMusic.play();
	}
	else if (this->getInBossStage && this->getWin && this->endMusic.getStatus() == 0)
	{
		this->music.stop();
		this->bossMusic.stop();
		this->endMusic.play();
	}
}

void GameState::updateBackgroundPosition(float pos_x, float pos_y)
{
	this->background.setPosition(pos_x, pos_y);
	this->bossBackground.setPosition(pos_x, pos_y);
}

void GameState::updateBullet(const float& dt)
{
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i]->update(dt);

		this->bullets[i]->move(1.f, 0.f, dt);

		if (this->bullets[i]->getPosition().x > this->mapPosXRight)
			this->bullets.erase(bullets.begin() + i);
		else if (this->bullets[i]->getPosition().x < this->mapPosXLeft)
			this->bullets.erase(bullets.begin() + i);
		else if (this->bullets[i]->getPosition().y > this->mapPosYDown)
			this->bullets.erase(bullets.begin() + i);
		else if (this->bullets[i]->getPosition().y < this->mapPosYUp)
			this->bullets.erase(bullets.begin() + i);
		else if (this->tileMap->getBulletCollision(this->bullets[i], dt))
			this->bullets.erase(bullets.begin() + i);
		else if (this->tileMap->getCheckPoint(this->bullets[i], dt))
		{
			this->checkpointeffect.play();
			this->checkpointPlayer.x = this->player->getPosition().x;
			this->checkpointPlayer.y = this->player->getPosition().y;
			this->bullets.erase(bullets.begin() + i);
		}
	}
}

void GameState::updateBossBullet(const float& dt)
{
	for (size_t i = 0; i < this->bossBullets.size(); i++)
	{
		this->bossBullets[i]->update(dt);

		if (this->pattern == 1)
		{
			for (size_t i = 0; i < this->bossBullets.size(); i++)
			{
				this->bossBullets[i]->move(-1.f, 0.f, dt);
			}
		}
		else if (this->pattern == 2)
		{
			for (size_t i = 0; i < this->bossBullets.size(); i++)
			{
				this->bossBullets[i]->move(-1.f, 0.f, dt);
			}
		}
		else if (this->pattern == 3)
		{
			for (size_t i = 0; i < this->bossBullets.size(); i++)
			{
				if (this->bossBullets[i]->getPosition().y < this->playerPos[i].y)
				{
					this->bossBullets[i]->move(
						-1.f * (this->bossBullets[i]->getPosition().x - this->playerPos[i].x) * (this->bossBullets[i]->getPosition().x - this->playerPos[i].x) / 1000000.f,
						(this->bossBullets[i]->getPosition().y - this->playerPos[i].y) * (this->bossBullets[i]->getPosition().y - this->playerPos[i].y) / 1000000.f,
						dt);
				}
				else if (this->bossBullets[i]->getPosition().y >= this->playerPos[i].y)
				{
					this->bossBullets[i]->move(
						-1.f * (this->bossBullets[i]->getPosition().x - this->playerPos[i].x)* (this->bossBullets[i]->getPosition().x - this->playerPos[i].x) / 1000000.f,
						-1.f * (this->bossBullets[i]->getPosition().y - this->playerPos[i].y)* (this->bossBullets[i]->getPosition().y - this->playerPos[i].y) / 1000000.f,
						dt);
				}
			}
		}
		if (this->bossBullets[i]->getIntersects(this->player->getGlobalBounds()))
		{
			this->deatheffect.play();
			this->player->checkpointJumpCount();
			this->player->stopVelocity();
			this->player->setPosition(checkpointPlayer.x, checkpointPlayer.y);
			this->bossMaxHP = 100.f;
			this->getInBossStage = false;
		}

		if (this->bossBullets[i]->getPosition().x > this->mapPosXRight)
			this->bossBullets.erase(bossBullets.begin() + i);
		else if (this->bossBullets[i]->getPosition().x < this->mapPosXLeft)
			this->bossBullets.erase(bossBullets.begin() + i);
		else if (this->bossBullets[i]->getPosition().y > this->mapPosYDown)
			this->bossBullets.erase(bossBullets.begin() + i);
		else if (this->bossBullets[i]->getPosition().y < this->mapPosYUp)
			this->bossBullets.erase(bossBullets.begin() + i);
	}
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->update();
	this->tileMap->updateCollision(this->player, dt);
	for (size_t i = 0; i < this->monsters.size(); i++)
	{
		this->tileMap->updateCollision(this->monsters[i], dt);
	}
	if (this->tileMap->getDamageCollision(this->player, dt))
	{
		this->deatheffect.play();
		this->player->checkpointJumpCount();
		this->player->stopVelocity();
		this->player->setPosition(checkpointPlayer.x, checkpointPlayer.y);
	}
	if (this->tileMap->getBossStageCollision(this->player, dt))
	{
		this->warpeffect.play();
		this->player->checkpointJumpCount();
		this->player->stopVelocity();
		this->player->setPosition(40.f, 2040.f);
		this->getInBossStage = true;
	}
}

void GameState::updateBossStage(const float& dt)
{
	if (this->getInBossStage && !this->getWin)
	{
		if (this->boss->getPosition().x > 800.f)
			this->boss->move(-1.f, 0.f, dt);

		if (this->bossAttack)
		{
			if (this->pattern == 1)
			{
				this->updateBossAttackPattern1(dt);
			}
			else if (this->pattern == 2)
			{
				this->updateBossAttackPattern2(dt);
			}
			else if (this->pattern == 3)
			{
				this->updateBossAttackPattern3(dt);
			}
		}
	}
}

void GameState::updateTextbox()
{

	if (this->getWin)
	{
		if (this->playername->isButtonPressed("ENTER") && this->getKeytime())
		{
			this->nowInMainMenuState();
			this->sname = this->playername->gettext();
			if(sname == "\0")
				this->sname = "Unknown";
			this->sscore = this->sec;
			if (sscore == 0)
				this->sscore = 999999;

			userScore.push_back(make_pair(sscore, sname));
			sort(userScore.begin(), userScore.end());

			fp = fopen("Score.txt", "w");
			for (unsigned i = 0; i < userScore.size(); i++)
			{

				strcpy(temp, userScore[i].second.c_str());
				fprintf(fp, "%s %d\n", temp, userScore[i].first);
			}
			fclose(fp);
			this->endState();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("A"))) && this->getKeytime3())
		{
			this->playername->typeOn(65);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("B"))) && this->getKeytime3())
		{
			this->playername->typeOn(66);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("C"))) && this->getKeytime3())
		{
			this->playername->typeOn(67);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("D"))) && this->getKeytime3())
		{
			this->playername->typeOn(68);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("E"))) && this->getKeytime3())
		{
			this->playername->typeOn(69);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("F"))) && this->getKeytime3())
		{
			this->playername->typeOn(70);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("G"))) && this->getKeytime3())
		{
			this->playername->typeOn(71);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("H"))) && this->getKeytime3())
		{
			this->playername->typeOn(72);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("I"))) && this->getKeytime3())
		{
			this->playername->typeOn(73);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("J"))) && this->getKeytime3())
		{
			this->playername->typeOn(74);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("K"))) && this->getKeytime3())
		{
			this->playername->typeOn(75);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("L"))) && this->getKeytime3())
		{
			this->playername->typeOn(76);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("M"))) && this->getKeytime3())
		{
			this->playername->typeOn(77);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("N"))) && this->getKeytime3())
		{
			this->playername->typeOn(78);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("O"))) && this->getKeytime3())
		{
			this->playername->typeOn(79);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("P"))) && this->getKeytime3())
		{
			this->playername->typeOn(80);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Q"))) && this->getKeytime3())
		{
			this->playername->typeOn(81);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("R"))) && this->getKeytime3())
		{
			this->playername->typeOn(82);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("S"))) && this->getKeytime3())
		{
			this->playername->typeOn(83);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("T"))) && this->getKeytime3())
		{
			this->playername->typeOn(84);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("U"))) && this->getKeytime3())
		{
			this->playername->typeOn(85);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("V"))) && this->getKeytime3())
		{
			this->playername->typeOn(86);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("W"))) && this->getKeytime3())
		{
			this->playername->typeOn(87);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("X"))) && this->getKeytime3())
		{
			this->playername->typeOn(88);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Y"))) && this->getKeytime3())
		{
			this->playername->typeOn(89);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Z"))) && this->getKeytime3())
		{
			this->playername->typeOn(90);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && this->getKeytime3())
		{
		this->playername->typeOn(8);
		}
	}
	
}

void GameState::update(const float& dt)
{
	//std::cout << this->getWin << "\n";
	this->updateMousePosition(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (this->getWin)
	{
		this->playername->update(this->mousePosWindow);
		this->updateTextbox();
	}

	else if (!this->paused)
	{
		this->updateMusic();

		this->updateBackgroundPosition(this->mapPosXLeft, this->mapPosYUp);

		this->updateView(dt);

		this->updateTime();

		this->updatePlayer(dt);

		this->updateItem(dt);

		this->updateMonster(dt);

		if (this->getInBossStage)
		{
			this->updateBossHP();

			this->updateBoss(dt);

			this->updateBossStage(dt);

			this->updateBossBullet(dt);
		}

		this->updateBullet(dt);
		
		this->updateTileMap(dt);
	}
	else
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::renderTextbox(sf::RenderTarget& target)
{
	this->playername->render(target);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	
	this->renderTexture.clear();

	this->renderTexture.setView(this->view);

	if(!this->getInBossStage)
		this->renderTexture.draw(this->background);
	else
		this->renderTexture.draw(this->bossBackground);

	this->tileMap->render(this->renderTexture, this->player->getGridPosition(static_cast<int>(this->stateData->gridSize)));

	this->player->render(this->renderTexture);

	for (size_t i = 0; i < this->items.size(); i++)
	{
		this->items[i]->render(this->renderTexture);
	}

	for (size_t i = 0; i < this->monsters.size(); i++)
	{
		this->monsters[i]->render(this->renderTexture);
	}

	if(!this->getWin && this->getInBossStage)
		this->boss->render(this->renderTexture);

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i]->render(this->renderTexture);
	}

	for (size_t i = 0; i < this->bossBullets.size(); i++)
	{
		this->bossBullets[i]->render(this->renderTexture);
	}
	

	this->tileMap->renderDeferred(this->renderTexture);

	if (this->paused)
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}
	else if (this->getWin)
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->playername->render(this->renderTexture);


		/*userScore.push_back(std::make_pair(sscore, sname));

		sort(userScore.begin(), userScore.end(), &comp);

		fp = fopen("Score.txt", "w");
		for (int i = 0; i < 5; i++)
		{
			strcpy(temp, userScore[i].second.c_str());
			fprintf(fp, "%s %d\n", temp, userScore[i].first);
		}
		fclose(fp);*/
	}
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
	target->draw(this->text);
	if(!this->getWin && this->getInBossStage)
		target->draw(this->bossHP);
	
}
