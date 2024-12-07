#include "stdafx.h"
#include "GameState.h"  


//Initializer functions
void GameState::initDeferredRender()
{
	this->renderTexture.create(this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0, 0, 
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height));
}

void GameState::initView()
{
	this->view.setSize(sf::Vector2f(this->stateData->gfxSettings->resolution.width, 
		this->stateData->gfxSettings->resolution.height));

	this->view.setCenter(this->stateData->gfxSettings->resolution.width / 2.f,
		this->stateData->gfxSettings->resolution.height / 2.f);
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
	if (!this->textures["KLEE"].loadFromFile("assets/player/klee_texture.png"))
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
	this->player = new Player(100.f, 100.f, this->textures["PLAYER_SHEET"]);
}


void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player);
}

void GameState::initNpc()
{
	this->npc = new Npc(this->textures["KLEE"], 
		{ "Ah, another adventurer come to \n answer the king's call.","You seek the bounty of the\ndragon, yes?","I see it in your eyes - you are\nmore than capable", "But be warned, the path to the\ndragon's lair is not for the faint\nof heart.", "For now prove your strength to me\nand slay that evil shroom in the\nmonster forest.","If you manage to do that i will\nreward you and tell you more\nabout this kingdom."},
		sf::Vector2f(1000.f, 200.f), *this->window);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "assets/The_Fan-tasy_Tileset/Art/Ground_Tileset_100x100/4_textures.png");
	this->tileMap->loadFromFile("test.rpg");
}


//Constructor / Destructor
GameState::GameState(StateData* state_data)
	: State(state_data)
{
this->initDeferredRender();
this->initView();
this->initKeybinds();
this->initFonts();
this->initTextures();
this->initPauseMenu();

this->initPlayers();
this->initPlayerGUI();
this->initNpc();
this->initTileMap();

this->canEnterEnemyState = true;
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->tileMap;
	delete this->playerGUI;
}

//Functions

void GameState::updateView(const float& dt)
{
	this->view.setCenter(this->player->getPosition());
}

void GameState::updateInput(const float& dt)
{
	sf::Vector2f playerPos = this->player->getPosition();

	const float interactionRange = 150.f;  // Adjust the range as needed

	if (this->npc->getDistanceToNpc(playerPos) < interactionRange) {
		// If the player presses the "E" key and the dialogue isn't finished
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && this->getKeyTime()) {
			// If the NPC is not talking yet, start the dialogue
			if (!this->npc->getIsTalking()) {
				std::cout << "Player is close to NPC, starting dialogue..." << std::endl;
				this->npc->startTalking();
			}
			else {
				// If the NPC is talking, go to the next part of the dialogue
				std::cout << "Advancing dialogue..." << std::endl;
				this->npc->nextDialogue();
			}
		}
	}

	// Optionally, you can add a condition to stop the dialogue if the player moves far enough from the NPC
	if (this->npc->getIsTalking() && this->npc->getDistanceToNpc(playerPos) >= interactionRange) {
		std::cout << "Player moved away from NPC, stopping dialogue..." << std::endl;
		this->npc->nextDialogue(); // End the dialogue or continue it
	}

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
	this->player->move(0.f, 1.f, dt);


}

void GameState::updatePlayerGUI(const float& dt)
{
	this->playerGUI->update(dt);
}


void GameState::getToEnemyState(const float& dt)
{
	if (!this->canEnterEnemyState)
	{
		if (this->teleportCooldownClock.getElapsedTime().asSeconds() >= this->teleportCooldown)
		{
			this->canEnterEnemyState = true; // Enable teleportation
			std::cout << "Cooldown ended, teleport enabled.\n";
			std::cout << "GameState Player EXP: " << player->getAttributeComponent()->exp << "\n";
		}
		return; // Prevent execution if cooldown is still active
	}

	sf::Vector2f playerPosition = this->player->getPosition();
	sf::Vector2f targetPosition(2150.f, 1110.f); // Target zone for EnemyState

	// Check if the player is outside and re-enters the zone
	static bool playerExitedZone = false;

	if (playerPosition.x < targetPosition.x - 50.f || playerPosition.y < targetPosition.y - 50.f)
	{
		playerExitedZone = true; // Mark the player as having exited the zone
	}

	if (playerExitedZone &&
		playerPosition.x >= targetPosition.x && playerPosition.y >= targetPosition.y)
	{
		std::cout << "Entering EnemyState!\n";
		this->stateData->states->push(new EnemyState(this->stateData));
		this->canEnterEnemyState = false;
		this->teleportCooldownClock.restart();
		playerExitedZone = false; // Reset the zone exit flag
	}

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
	this->updateMousePositions(&this->view);
	this->updateKeyTime(dt);
	this->updateInput(dt);
	this->getToEnemyState(dt);

	if (!this->paused) //unpaused update
	{
		this->updateView(dt);
	
		this->updatePlayerInput(dt);

		this->player->update(dt);

		this->playerGUI->update(dt);

	
    }
	else //paused update
	{
	
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}

}

void GameState::render(sf::RenderTarget* target)
{
if (!target)
{
	target = this->window;
}
this->renderTexture.clear();

this->renderTexture.setView(this->view);
this->tileMap->render(this->renderTexture);
//Render NPC
this->npc->renderNpc(this->renderTexture);

//Render player
this->player->render(this->renderTexture);

// Reset the view to default for GUI rendering
this->renderTexture.setView(this->renderTexture.getDefaultView());

//Render GUI
this->playerGUI->render(this->renderTexture);

this->npc->renderDialogue(this->renderTexture);

if (this->paused) //paused menu render
{
	//this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->pmenu->render(this->renderTexture);
}

//Final render
this->renderTexture.display();
this->renderSprite.setTexture(this->renderTexture.getTexture());
target->draw(this->renderSprite);

}
