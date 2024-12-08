#include "stdafx.h"
#include "EnemyState.h"


void EnemyState::initDeferredRender()
{
	this->renderTexture.create(this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0, 0,
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height));
}

void EnemyState::initVariables()
{
	this->turn = 1; // Player's turn initially
	this->gameWon = false; // Game hasn't ended initially
	this->messageDuration = 3.f; // Display message for 5 seconds
	this->isGameOver = false;
	this->messageTimer.restart();

	// Initialize winner text
	this->winnerText.setFont(this->font);
	this->winnerText.setCharacterSize(50);
	this->winnerText.setFillColor(sf::Color::White);
	this->winnerText.setPosition(
		this->window->getSize().x / 2.f - 100.f,
		this->window->getSize().y / 2.f - 25.f
	);

	

}

void EnemyState::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("assets/spells/background1.jpeg"))
	{
		throw "ERROR::ENEMYSTATE::FAILED TO LOAD BACKGROUND TEXTURE";
	}

	if (!this->spellsbarTexture.loadFromFile("assets/spells/spellsbar.png"))
	{
		throw "ERROR::ENEMYSTATE::FAILED TO LOAD SPELLSBAR TEXTURE";
	}

	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)));


	this->background.setTexture(&this->backgroundTexture);
	this->spellsbar.setTexture(&this->spellsbarTexture);
	this->spellsbar.setSize(sf::Vector2f(650.f, 300.f));
	this->spellsbar.setPosition(650.f, 750.f);

}

void EnemyState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/AncientModernTales-a7Po.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT"); //exits the program and shows the error message
	}
}

void EnemyState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("assets/Knight_player/Idle+Walking_KG_1.png"))
	{
		throw std::runtime_error("ERROR::ENEMY_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE");
	}
	if (!this->textures["ENEMY_SHEET"].loadFromFile("assets/Forest_Monsters_FREE/Mushroom/Mushroom_with_VFX/Mushroom-AllAnimations.png"))
	{
		throw std::runtime_error("ERROR::ENEMY_STATE::COULD_NOT_LOAD_ENEMY_TEXTURE");
	}

	// Load button textures
	if (!this->idleTextures["MOON"].loadFromFile("assets/spells/spell1.png") ||
		!this->hoverTextures["MOON"].loadFromFile("assets/spells/spell1_pressed.png") ||
		!this->activeTextures["MOON"].loadFromFile("assets/spells/spell1_pressed.png") ||
		!this->idleTextures["CIRCLE"].loadFromFile("assets/spells/spell2.png") ||
		!this->hoverTextures["CIRCLE"].loadFromFile("assets/spells/spell2_pressed.png") ||
		!this->activeTextures["CIRCLE"].loadFromFile("assets/spells/spell2_pressed.png") ||
		!this->idleTextures["IDK"].loadFromFile("assets/spells/spell3.png") ||
		!this->hoverTextures["IDK"].loadFromFile("assets/spells/spell3_pressed.png") ||
		!this->activeTextures["IDK"].loadFromFile("assets/spells/spell3_pressed.png") ||
		!this->idleTextures["STARS"].loadFromFile("assets/spells/spell4.png") ||
		!this->hoverTextures["STARS"].loadFromFile("assets/spells/spell4_pressed.png") ||
		!this->activeTextures["STARS"].loadFromFile("assets/spells/spell4_pressed.png") 
		)
	{
		throw "ERROR::ENEMYSTATE::FAILED TO LOAD BUTTON TEXTURES";
	}
	if (!this->EnemyhpBarBackTexture.loadFromFile("assets/game_gui/healthbar_back2.png"))
	{
		throw("ERROR::PLAYERGUI::COULD NOT LOAD HP BAR BACK TEXTURE");
	}

	if (!this->EnemyhpBarInnerTexture.loadFromFile("assets/game_gui/healthbargreen_front.png"))
	{
		throw("ERROR::PLAYERGUI::COULD NOT LOAD HP BAR INNER TEXTURE");
	}

}

void EnemyState::initKeybinds()
{
	std::ifstream ifs("Config/enemystate_keybinds.ini");
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

void EnemyState::initPlayer()
{
	this->player->setPosition(100.f, 550.f);
	this->player->setScale(5.f, 5.f);
}

void EnemyState::initEnemy()
{
	this->enemy = new Enemy(1300.f, 550.f, this->textures["ENEMY_SHEET"]);
	this->enemy->setScale(5.f, 5.f);
}

void EnemyState::initButtons()
{

	sf::Color newGameColor = sf::Color(0, 0, 0, 200);

	this->buttons["MOON"] = new gui::Button(692.f, 773.f, 150.f, 120.f,
		&this->font, "", newGameColor,
		this->idleTextures["MOON"], this->hoverTextures["MOON"], this->activeTextures["MOON"]

	);
	this->buttons["CIRCLE"] = new gui::Button(832.f, 773.f, 150.f, 120.f,
		&this->font, "", newGameColor,
		this->idleTextures["CIRCLE"], this->hoverTextures["CIRCLE"], this->activeTextures["CIRCLE"]

	);
	this->buttons["IDK"] = new gui::Button(692.f, 888.f, 150.f, 120.f,
		&this->font, "", newGameColor,
		this->idleTextures["IDK"], this->hoverTextures["IDK"], this->activeTextures["IDK"]

	);
	this->buttons["STARS"] = new gui::Button(832.f, 888.f, 150.f, 120.f,
		&this->font, "", newGameColor,
		this->idleTextures["STARS"], this->hoverTextures["STARS"], this->activeTextures["STARS"]

	);

}

void EnemyState::initPlayerGui()
{
	this->playerGUI = new PlayerGUI(this->player);
}

void EnemyState::initEnemyHPBar()
{
	float width = 300.f;
	float height = 200.f;
	float x = 1600.f;
	float y = 0.f;

	this->EnemyhpBarMaxWidth = 245.f;

	this->EnemyhpBarText.setFont(this->font);
	this->EnemyhpBarText.setCharacterSize(20);
	this->EnemyhpBarText.setFillColor(sf::Color::White);

	this->EnemyhpBarBack.setSize(sf::Vector2f(width, height));
	this->EnemyhpBarBack.setPosition(x, y);
	this->EnemyhpBarBack.setTexture(&this->EnemyhpBarBackTexture);

	this->EnemyhpBarInner.setSize(sf::Vector2f(245.f, 85.f));
	this->EnemyhpBarInner.setTexture(&this->EnemyhpBarInnerTexture);
	this->EnemyhpBarInner.setPosition(x + 35.f, y + 35.f);

	this->EnemyhpBarText.setPosition(x + 137.f, y + 71.f);

}

void EnemyState::initTurnText()
{
	this->turnText.setFont(this->font);
	this->turnText.setCharacterSize(50);
	this->turnText.setFillColor(sf::Color::White);
	this->turnText.setPosition(
		this->window->getSize().x / 2.f - 50.f,
		75.f
	);
	this->updateTurnText();
}



EnemyState::EnemyState(StateData* state_data,Player* player,Npc* currentNpc)
	: State(state_data), player(player), currentNpc(currentNpc)
{

	this->initDeferredRender();
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initTextures();
	this->initKeybinds();
	this->initPlayer();
	this->initEnemy();
	this->initButtons();
	this->initPlayerGui();
	this->initEnemyHPBar();
	this->initTurnText();

}

EnemyState::~EnemyState()
{
	delete this->enemy;
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

const bool EnemyState::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}




void EnemyState::switchTurn()
{
	this->turn = (this->turn == 1) ? 0 : 1;
	this->updateTurnText();
	std::cout << "Turn switched!" << std::endl;
}

void EnemyState::startDelay(const float duration)
{
	this->delayTimer = duration;
	this->delayDuration = 0.f;
	this->isDelayActive = true;
}

void EnemyState::exitEnemyState(const float& dt)
{ // If the game is won and the message hasn't been displayed for enough time, wait
	if (this->isGameOver)
	{
		// Wait for the message duration
		if (this->messageTimer.getElapsedTime().asSeconds() >= this->messageDuration)
		{
			this->endState();  // Exit the state after the message duration is up
			this->player->setScale(2.f, 2.f); 
			this->player->setPosition(2100.f, 1110.f);

		}
	}
}

bool EnemyState::updateDelayTimer(const float& dt)
{
	if (this->isDelayActive)
	{
		this->delayDuration += dt;

		if (this->delayDuration >= this->delayTimer)
		{
			this->delayTimer = 0.f;       // Reset timer
			this->isDelayActive = false; // Deactivate delay
			return true;
		} 
	}
	return false;
}

void EnemyState::updateGame(const float& dt)
{

	if (this->isGameOver) return;

	if (player->getAttributeComponent()->hp <= 0 || this->enemy->hp <= 0)
	{
		this->gameWon = true;  // Mark the game as over
		this->messageTimer.restart();  // Restart the message timer
		this->isGameOver = true; // Set the game over flag to true

		// Set the winner text
		if (this->player->getAttributeComponent()->hp <= 0)
		{
			this->winnerText.setString("Enemy Won!");
		}
		else
		{
			this->winnerText.setString("Player Won!");
			this->player->gainExp(100); // Add EXP
	
			if(this->currentNpc->getQuestState() == QuestState::IN_PROGRESS)
				this->currentNpc->setQuestState(QuestState::COMPLETED); // Complete the quest
		
		}

		// Start the message timer so the state knows to wait for a few seconds
		this->exitEnemyState(dt);
	}

	if (this->updateDelayTimer(dt))
	{
		// Delay finished, switch turns
		this->switchTurn();
	}

	// If delay is active, prevent further input processing
	if (this->isDelayActive)
		return;

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	if (this->turn == 1)
	{
		if (this->buttons["MOON"]->isPressed() && this->isButtonPressed("MOON")) {
			std::cout << "Moon button pressed!" << std::endl;

			this->player->startAttackAnimation(dt,1);

			this->enemy->loseHP(10);

			this->startDelay(3.f);
		}
		else if (this->buttons["CIRCLE"]->isPressed() && this->isButtonPressed("CIRCLE")) {
			std::cout << "Circle button pressed!" << std::endl;

			this->player->startAttackAnimation(dt, 2);

			this->enemy->loseHP(3);

			this->startDelay(3.f);
		}
		else if (this->buttons["IDK"]->isPressed() && this->isButtonPressed("IDK")) {
			std::cout << "Idk button pressed!" << std::endl;

			this->player->startAttackAnimation(dt, 3);

			this->enemy->loseHP(2);

			this->startDelay(4.f);
		}
		else if (this->buttons["STARS"]->isPressed() && this->isButtonPressed("STARS")) {
			std::cout << "Stars button pressed!" << std::endl;

			this->player->startAttackAnimation(dt, 4);

			this->enemy->loseHP(4);

			this->startDelay(4.f);
		}
	}
	else if (!this->isGameOver) {
		this->enemy->startAttackAnimation(dt);
		this->player->getAttributeComponent()->hp -= 1;
		this->startDelay(3.f);
	}


}

void EnemyState::updateInput(const float& dt)
{
}

void EnemyState::updatePlayerGUI(const float& dt)
{
	this->playerGUI->update(dt);
}


void EnemyState::updateEnemyHPBar()
{
	float percent = static_cast<float>(this->enemy->hp) / static_cast<float>(this->enemy->hpMax);

	this->EnemyhpBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(
				this->EnemyhpBarMaxWidth * percent)),
			this->EnemyhpBarInner.getSize().y));

	this->EnemyhpBarString = std::to_string(this->enemy->hp) + " / " + std::to_string(this->enemy->hpMax);
	this->EnemyhpBarText.setString(this->EnemyhpBarString);
}

void EnemyState::updateTurnText()
{
	if (this->turn == 1)
		this->turnText.setString("Your Turn");
	else
		this->turnText.setString("Enemy's Turn");
}


void EnemyState::update(const float& dt)
{
	this->updateMousePositions();

	this->updateInput(dt);
	this->player->update(dt);
	this->enemy->update(dt);

	if (this->isGameOver)
	{
		this->exitEnemyState(dt); 
		return; 
	}

	this->updateGame(dt);
	this->updatePlayerGUI(dt);
	this->updateEnemyHPBar();
	this->updateTurnText();
}



void EnemyState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void EnemyState::renderEnemyHPBar(sf::RenderTarget& target)
{
	target.draw(this->EnemyhpBarBack);
	target.draw(this->EnemyhpBarInner);
	target.draw(this->EnemyhpBarText);
}

void EnemyState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	this->renderTexture.clear();

	// Render background
	this->renderTexture.draw(this->background);
	this->renderTexture.draw(this->spellsbar);

	// Render player
	this->player->render(this->renderTexture);
	this->enemy->render(this->renderTexture);

	//Render GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);

	// Render enemy HP bar
	this->renderEnemyHPBar(this->renderTexture);

	// Render turn text
	this->renderTexture.draw(this->turnText);

	// If game is won, show the winner message
	if (this->gameWon && this->messageTimer.getElapsedTime().asSeconds() < this->messageDuration)
	{
		this->renderTexture.draw(this->winnerText);
	}

	// Final render
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);

	//Render buttons
	this->renderButtons(*target);

}
