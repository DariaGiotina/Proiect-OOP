#include "stdafx.h"
#include "GameState.h"  

//Initializer functions
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
	if (!this->font.loadFromFile("Fonts/AncientModernTales-a7Po.ttf"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT"); //exits the program and shows the error message
	}
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("assets/Knight_player/Idle+Walking_KG_1.png"))
	{
		throw std::runtime_error("ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE");
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window,this->font);

	this->pmenu->addButton("MAIN MENU", 670.f, 560.f, "MAIN MENU");
	this->pmenu->addButton("QUIT", 670.f, 740.f, "QUIT");

}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
	this->player->setScale(2.f, 2.f); 
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
}


//Constructor / Destructor
GameState::GameState(StateData* state_data)
	: State(state_data)
{
this->initKeybinds();
this->initFonts();
this->initTextures();
this->initPauseMenu();

this->initPlayers();
this->initTileMap();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->tileMap;
}

//Functions

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
	}
}

void GameState::updatePlayerInput(const float & dt)
{

//Update player input
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	this->player->move (- 1.f, 0.f,dt);
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	this->player->move( 1.f, 0.f, dt);
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	this->player->move( 0.f, -1.f,dt);
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	this->player->move( 0.f, 1.f, dt);


}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("MAIN MENU"))
	{
		this->endState();
	}

    if (this->pmenu->isButtonPressed("QUIT"))
    {
    this->window->close();
    }

}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeyTime(dt);
	this->updateInput(dt);

	if (!this->paused) //unpaused update
	{
	
		this->updatePlayerInput(dt);

		this->player->update(dt);
    }
	else //paused update
	{
	
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}

}

void GameState::render(sf::RenderTarget* target)
{
if (!target)
{
	target = this->window;
}
//this->map.render(*target);

this->player->render(*target);

if (this->paused) //paused menu render
{
	this->pmenu->render(*target);
}

}
