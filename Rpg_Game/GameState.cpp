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
	if (!this->font2.loadFromFile("Fonts/Rundeck.ttf"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT2"); //exits the program and shows the error message
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
		throw std::runtime_error("ERROR::GAME_STATE::COULD_NOT_LOAD_KLEE_TEXTURE");
	}

	if (!this->textures["ADVENTURE_HOUSE"].loadFromFile("assets/The_Fan-tasy_Tileset/Art/Buildings/House_Hay_Stone_1.png"))
	{
		throw std::runtime_error("ERROR::GAME_STATE::COULD_NOT_LOAD_ADVENTURE_HOUSE_TEXTURE");
	}
	if (!this->textures["BLACKSMITH_HOUSE"].loadFromFile("assets/The_Fan-tasy_Tileset/Art/Buildings/House_Hay_Stone_3.png"))
	{
		throw std::runtime_error("ERROR::GAME_STATE::COULD_NOT_LOAD_BLACKSMITH_HOUSE_TEXTURE");
	}
	if (!this->textures["MARKET_HOUSE"].loadFromFile("assets/The_Fan-tasy_Tileset/Art/Buildings/House_Hay_Stone_4.png"))
	{
		throw std::runtime_error("ERROR::GAME_STATE::COULD_NOT_LOAD_MARKET_HOUSE_TEXTURE");
	}
	if (!this->inventoryMenuTexture.loadFromFile("assets/inventory/level.png"))
	{
		throw("ERROR::PLAYERGUI::COULD NOT LOAD INVENTORY TEXTURE");
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
	this->player->setPosition(100.f, 100.f);
	this->player->setScale(2.f, 2.f);
}


void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player);
}

void GameState::initNpc()
{
	 this->npcDialogue = {
		{QuestState::NOT_TAKEN, {
			"Ah, another adventurer come to\nanswer the king's call.",
			"You seek the bounty of the\ndragon, yes?",
			"I see it in your eyes - you are\nmore than capable.",
			"But be warned, the path to the\ndragon's lair is not for the faint\nof heart.",
			"For now prove your strength to me\nand slay that evil shroom in the\nmonster forest.",
			"If you manage to do that i will\nreward you and tell you more\nabout this kingdom."
		}},
		{QuestState::IN_PROGRESS, {
			"The dragon's lair awaits,\nadventurer. Have you slain the\nevil shroom yet?",
			"Hurry, time is of the essence.\nThe dragon will grow stronger.",
			"I hope you have the courage to\nface what's ahead!"
		}},
		{QuestState::COMPLETED, {
			"Ah, you've slain the shroom!\nThe kingdom thanks you.",
			"Now, the road to the dragon's lair\nis clear. Go and claim your prize.",
			"Remember, adventurer, the\nkingdom will forever be in your\ndebt."
		}}
	};

	this->npc = new Npc(this->textures["KLEE"], 
		npcDialogue,
		sf::Vector2f(1000.f, 200.f), *this->window);

	this->isCompleted = false;
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "assets/The_Fan-tasy_Tileset/Art/Ground_Tileset_100x100/4_textures.png");
	this->tileMap->loadFromFile("test.rpg");
}

void GameState::initHouse()
{
	this->AdventureHouse.setSize(sf::Vector2f(400.f, 400.f));
	this->AdventureHouse.setTexture(&this->textures["ADVENTURE_HOUSE"]);
	this->AdventureHouse.setPosition(1000.f, -100.f);

	this->BlacksmithHouse.setSize(sf::Vector2f(400.f, 400.f));
	this->BlacksmithHouse.setTexture(&this->textures["BLACKSMITH_HOUSE"]);
	this->BlacksmithHouse.setPosition(400.f, 700.f);

	this->MarketHouse.setSize(sf::Vector2f(400.f, 400.f));
	this->MarketHouse.setTexture(&this->textures["MARKET_HOUSE"]);
	this->MarketHouse.setPosition(1400.f, 700.f);
}

void GameState::initInventoryMenu()
{
	this->inventoryMenu.setSize(sf::Vector2f(1000.f, 1000.f));
	this->inventoryMenu.setTexture(&this->inventoryMenuTexture);
	this->inventoryMenu.setPosition(50.f, 50.f);
}

void GameState::initInventoryText()
{
	this->inventoryTexthealth.setFont(this->font2);
	this->inventoryTexthealth.setCharacterSize(20);
	this->inventoryTexthealth.setFillColor(sf::Color(96, 68, 93, 255));
	this->inventoryTexthealth.setPosition(580.f, 203.f);
	this->inventoryTexthealth.setString(sf::String(std::to_string(this->player->getAttributeComponent()->hpMax)));

	this->inventoryTextlevel.setFont(this->font2);
	this->inventoryTextlevel.setCharacterSize(20);
	this->inventoryTextlevel.setFillColor(sf::Color(96, 68, 93, 255));
	this->inventoryTextlevel.setPosition(360.f, 203.f);
	this->inventoryTextlevel.setString(sf::String(std::to_string(this->player->getAttributeComponent()->level)));


	this->inventoryTextstrength.setFont(this->font2);
	this->inventoryTextstrength.setCharacterSize(20);
	this->inventoryTextstrength.setFillColor(sf::Color(96,68,93,255));
	this->inventoryTextstrength.setPosition(380.f, 747.f);
	this->inventoryTextstrength.setString(sf::String(std::to_string(this->player->getAttributeComponent()->strength)));

	this->inventoryTextconstitution.setFont(this->font2);
	this->inventoryTextconstitution.setCharacterSize(20);
	this->inventoryTextconstitution.setFillColor(sf::Color(96, 68, 93, 255));
	this->inventoryTextconstitution.setPosition(380.f, 790.f);
	this->inventoryTextconstitution.setString(sf::String(std::to_string(this->player->getAttributeComponent()->constitution)));

	this->inventoryTextdexterity.setFont(this->font2);
	this->inventoryTextdexterity.setCharacterSize(20);
	this->inventoryTextdexterity.setFillColor(sf::Color(96, 68, 93, 255));
	this->inventoryTextdexterity.setPosition(380.f, 830.f);
	this->inventoryTextdexterity.setString(sf::String(std::to_string(this->player->getAttributeComponent()->dexterity)));

	this->inventoryTextwisdom.setFont(this->font2);
	this->inventoryTextwisdom.setCharacterSize(20);
	this->inventoryTextwisdom.setFillColor(sf::Color(96, 68, 93, 255));
	this->inventoryTextwisdom.setPosition(600.f, 747.f);
	this->inventoryTextwisdom.setString(sf::String(std::to_string(this->player->getAttributeComponent()->wisdom)));


	this->inventoryTextintelligence.setFont(this->font2);
	this->inventoryTextintelligence.setCharacterSize(20);
	this->inventoryTextintelligence.setFillColor(sf::Color(96, 68, 93, 255));
	this->inventoryTextintelligence.setPosition(600.f, 790.f);
	this->inventoryTextintelligence.setString(sf::String(std::to_string(this->player->getAttributeComponent()->intelligence)));

	this->inventoryTextcharisma.setFont(this->font2);
	this->inventoryTextcharisma.setCharacterSize(20);
	this->inventoryTextcharisma.setFillColor(sf::Color(96, 68, 93, 255));
	this->inventoryTextcharisma.setPosition(600.f, 830.f);
	this->inventoryTextcharisma.setString(sf::String(std::to_string(this->player->getAttributeComponent()->charisma)));

}



//Constructor / Destructor
GameState::GameState(StateData* state_data, Player* player)
	: State(state_data), player(player)
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
this->initHouse();

this->initInventoryMenu();
this->initInventoryText();

this->canEnterEnemyState = true;
this->isInventoryMenuOpen = false;



}

GameState::~GameState()
{
	delete this->pmenu;
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INVENTORY"))) && this->getKeyTime())
	{
		this->isInventoryMenuOpen = !this->isInventoryMenuOpen;
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

void GameState::updateInventoryText(const float& dt)
{
	this->inventoryTextstrength.setString(sf::String(std::to_string(this->player->getAttributeComponent()->strength)));
	this->inventoryTextconstitution.setString(sf::String(std::to_string(this->player->getAttributeComponent()->constitution)));
	this->inventoryTextdexterity.setString(sf::String(std::to_string(this->player->getAttributeComponent()->dexterity)));
	this->inventoryTextwisdom.setString(sf::String(std::to_string(this->player->getAttributeComponent()->wisdom)));
	this->inventoryTextintelligence.setString(sf::String(std::to_string(this->player->getAttributeComponent()->intelligence)));
	this->inventoryTextcharisma.setString(sf::String(std::to_string(this->player->getAttributeComponent()->charisma)));
	this->inventoryTexthealth.setString(sf::String(std::to_string(this->player->getAttributeComponent()->hpMax)));
	this->inventoryTextlevel.setString(sf::String(std::to_string(this->player->getAttributeComponent()->level)));
}

void GameState::updateExpwhenComplete(const float& dt)
{
	if (this->npc->getQuestState() == QuestState::COMPLETED && this->npc->getIsTalking() && !isCompleted) {
		this->player->gainExp(200);
		this->isCompleted = true;
	}
}


void GameState::getToEnemyState(const float& dt)
{
	if (!this->canEnterEnemyState)
	{
		if (this->teleportCooldownClock.getElapsedTime().asSeconds() >= this->teleportCooldown)
		{
			this->canEnterEnemyState = true; // Enable teleportation
			std::cout << "Cooldown ended, teleport enabled.\n";
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
		std::cout << "Entering EnemyState!\n" << "QuestState: "<< this->npc->toString(currentQuestState) <<"\n";
		this->stateData->states->push(new EnemyState(this->stateData,this->player,this->npc));
		this->canEnterEnemyState = false;
		this->teleportCooldownClock.restart();
		playerExitedZone = false; // Reset the zone exit flag
		this->updateInventoryText(dt);
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

		this->updateInventoryText(dt);

		this->updateExpwhenComplete(dt);
	
    }
	else //paused update
	{
	
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}

}

void GameState::renderHouses(sf::RenderTarget& target)
{
	target.draw(this->AdventureHouse);
	target.draw(this->BlacksmithHouse);
	target.draw(this->MarketHouse);
}

void GameState::renderInventoryMenu(sf::RenderTarget& target)
{
	target.draw(this->inventoryMenu);

	target.draw(this->inventoryTextlevel);
	target.draw(this->inventoryTexthealth);
	target.draw(this->inventoryTextstrength);
	target.draw(this->inventoryTextconstitution);
	target.draw(this->inventoryTextdexterity);
	target.draw(this->inventoryTextwisdom);
	target.draw(this->inventoryTextintelligence);
	target.draw(this->inventoryTextcharisma);
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

	//Render Houses
	this->renderHouses(this->renderTexture);

	//Render NPC
	this->npc->renderNpc(this->renderTexture);

	//Render player
	this->player->render(this->renderTexture);

	// Reset the view to default for GUI rendering
	this->renderTexture.setView(this->renderTexture.getDefaultView());

	//Render GUI
	this->playerGUI->render(this->renderTexture);

	this->npc->renderDialogue(this->renderTexture);

	//Render Inventory Menu
	if (this->isInventoryMenuOpen)
{
	this->renderInventoryMenu(this->renderTexture);
}

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
