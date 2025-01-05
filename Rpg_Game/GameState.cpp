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

	if (!this->textures["LISA"].loadFromFile("assets/player/lisa_texture.png"))
	{
		throw std::runtime_error("ERROR::GAME_STATE::COULD_NOT_LOAD_LISA_TEXTURE");
	}

	if (!this->textures["DIALOGUEBOX_KLEE"].loadFromFile("assets/player/klee_text.png"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD DIALOGUE BOX KLEE TEXTURE");
	}

	if (!this->textures["DIALOGUEBOX_LISA"].loadFromFile("assets/player/lisa_text.png"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD DIALOGUE BOX LISA TEXTURE");
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


	if (!this->textures["ENCHANTED_FOREST"].loadFromFile("assets/The_Fan-tasy_Tileset/ToTheEnchantedForest.png"))
	{
		throw std::runtime_error("ERROR::GAME_STATE::COULD_NOT_LOAD_ENCHANTED_FOREST_TEXTURE");
	}

	if (!this->textures["MAGICAL_GARDEN"].loadFromFile("assets/The_Fan-tasy_Tileset/ToTheMagicalGarden.png"))
	{
		throw std::runtime_error("ERROR::GAME_STATE::COULD_NOT_LOAD_MAGICAL_GARDEN_TEXTURE");
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
	 this->npcDialogueKlee = {
		{QuestState::NOT_TAKEN, {
			"Ah, another adventurer come to\nanswer the king's call.",
			"You seek the bounty of the\ndragon, yes?",
			"I see it in your eyes - you are\nmore than capable.",
			"But be warned, the path to the\ndragon's lair is not for the faint\nof heart.",
			"For now prove your strength to me\nand slay that evil shroom in the\nmonster forest.",
			"If you manage to do that i will\nreward you and tell you more\nabout this kingdom.",
			"For now take this health potion\nand good luck."
		}},
		{QuestState::IN_PROGRESS, {
			"The dragon's lair awaits,\nadventurer. Have you slain the\nevil shroom yet?",
			"Hurry, time is of the essence.\nThe dragon will grow stronger.",
			"I hope you have the courage to\nface what's ahead!"
		}},
		{QuestState::COMPLETED, {
			"Ah, you've slain the shroom!\nThe kingdom thanks you.",
			"Now, the road to the dragon's lair\nis clear. Go and claim your prize.",
			"Remember, adventurer, the\nkingdom will forever be in your\ndebt.",
			"(You receive 200 exp)"
		}}
	};

	 this->questStateDescriptionKlee = "Quest 1 : Prove your strength \n\n Go to the enchanted forest and kill \n one mushroom enemy";
	 this->questStateDescriptionKleeFinished = "Quest 1 : Prove your strength \n\n Go to the enchanted forest and kill \n one mushroom enemy \n\n COMPLETED";

		 this->klee = new Npc(this->textures["KLEE"], this->textures["DIALOGUEBOX_KLEE"],
			 questStateDescriptionKlee, questStateDescriptionKleeFinished,
			 10.f, 300.f,
			 npcDialogueKlee,
			 sf::Vector2f(1000.f, 200.f), *this->window,
			 0.125f, 0.125f);

	this->isCompletedKlee = false;


	this->npcDialogueLisa = {
   {QuestState::NOT_TAKEN, {
	  "So the rumers were true, there is\na new traveler in town",
	  "I am Lisa, the kingdom's\nshopkeeper, but unfortunately\nmy shop is closed",
	  "until I can get a special\ningredient for my potions",
	  "that is only obtainable\nfrom a two-headed flower\nenemy in the magical garden",
	  "If you can get me 2 flowers\nfrom the enemy i will reward\nyou plenty",
   }},
   {QuestState::IN_PROGRESS, {
	   "Have you brought the two\nflowers yet?",
	   "Please hurry, I need to\nopen my shop for the kingdom."
   }},
   {QuestState::COMPLETED, {
	   "You've done me a great service,\ntraveler.",
	   "Please, take this as a token of\nmy gratitude.",
	   "(You receive 200 exp)"
   }}
	};

	this->questStateDescriptionLisa = "Quest 2 : Slay the 2 headed flower \n\n Go to the magical garden and obtain \n two flower enemy drops";
	this->questStateDescriptionLisaFinished = "Quest 2 : Slay the 2 headed flower \n\n Go to the magical garden and obtain \n two flower enemy drops \n\n COMPLETED";

	this->lisa = new Npc(this->textures["LISA"], this->textures["DIALOGUEBOX_LISA"],
		questStateDescriptionLisa, questStateDescriptionLisaFinished,
		10.f,500.f,
		npcDialogueLisa,
		sf::Vector2f(1300.f, 950.f), *this->window,
		0.125f,0.125f);


	this->isCompletedLisa = false;



}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 23, 16, "assets/The_Fan-tasy_Tileset/Art/Ground_Tileset_100x100/4_textures.png");
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

	this->EnchantedForest.setSize(sf::Vector2f(200.f, 200.f));
	this->EnchantedForest.setTexture(&this->textures["ENCHANTED_FOREST"]);
	this->EnchantedForest.setPosition(2050.f, 1020.f);

	this->MagicalGarden.setSize(sf::Vector2f(200.f, 200.f));
	this->MagicalGarden.setTexture(&this->textures["MAGICAL_GARDEN"]);
	this->MagicalGarden.setPosition(2050.f, 410.f);
}

void GameState::initInventoryMenu()
{
	this->inventoryMenu.setSize(sf::Vector2f(1000.f, 1000.f));
	this->inventoryMenu.setTexture(&this->inventoryMenuTexture);
	this->inventoryMenu.setPosition(50.f, 50.f);

	//this->inventory = new Inventory();

	this->playerInventory = new Inventory();
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
this->isFlowerPlantDead = false;
this->isMushroomDead = false;

}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->tileMap;
	delete this->playerGUI;
}

//Functions 

//Inventory
void GameState::addHealthPot()
{
	Item* healthPotion = new Item("potion_001", "Health Potion", 1, true, "assets/MF_Items/MF_Items_potions_9.png");
	
	// Add to player's inventory
	this->playerInventory->addItem(healthPotion);
}

void GameState::addFlowerPlantLoot()
{
	Item* FlowerLoot = new Item("flowerPlantLoot", "Flower Petals", 1, true, "assets/MF_Items/MF_Items_flower_4.png");

	this->playerInventory->addItem(FlowerLoot);
}

void GameState::addMushroomLoot()
{
	Item* MushroomLoot = new Item("mushroomLoot", "Mushroom Spores", 1, true, "assets/MF_Items/MF_Items_mushroom_1.png");

	this->playerInventory->addItem(MushroomLoot);
}


//Quest
void GameState::CompleteLisaQuest()
{
	std::string flowerId = "flowerPlantLoot";
	std::cout << "Checking if player has 2 flower petals...\n";
	std::cout << this->playerInventory->getItemQuantity(flowerId) << "\n";

	lisa->setQuestState(QuestState::COMPLETED);
	isCompletedLisa = true;
	playerInventory->removeItem(flowerId, 2);

	// Explicitly call checkQuestCompletion for Lisa
	checkQuestCompletion(lisa);

}

void GameState::addQuest(const std::string& description, QuestState intialState, Npc* npc)
{
	Quest newQuest;
	newQuest.questText.setFont(this->font);
	newQuest.questText.setString(description);
	newQuest.questText.setCharacterSize(25);
	newQuest.questText.setFillColor(sf::Color::Color(80, 18, 63, 255));
	newQuest.state = intialState;
	newQuest.npc = npc;  // Link to the NPC

	activeQuests.push_back(newQuest);
	updateQuestPositions();
}

void GameState::removeQuest(int index)
{
	if (index >= 0 && index < activeQuests.size()) {
		std::cout << "Removing quest at index " << index << "\n";
		activeQuests.erase(activeQuests.begin() + index);
		updateQuestPositions();
	}
}

void GameState::updateQuestPositions()
{
	float startX = 10.f;  // Starting x-position for quests
	float startY = 350.f;  // Starting y-position for the first quest
	float verticalSpacing = 150.f;  // Spacing between quests

	for (size_t i = 0; i < activeQuests.size(); ++i) {
		activeQuests[i].questText.setPosition(startX, startY + i * verticalSpacing);
	}
}

void GameState::checkQuestCompletion(Npc* npc) {

	for (size_t i = 0; i < activeQuests.size(); ++i) {
		Quest& quest = activeQuests[i];

		if (quest.npc == npc /*&& quest.state == QuestState::COMPLETED*/) {
			std::cout << "Removing completed quest for NPC: " << typeid(*npc).name() << "\n";
			quest.state = QuestState::FINISHED;
			removeQuest(i);
			this->player->gainExp(200);
			--i;  // Adjust index after removal
		}
	}
}



//Teleport the player to the enemy state
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

	sf::Vector2f targetPosition2(2150.f, 510.f); // Target zone for EnemyState
	// Check if the player is outside and re-enters the zone
	static bool playerExitedZone = false;

	if (playerPosition.x < targetPosition.x - 50.f || playerPosition.y < targetPosition.y - 50.f)
	{
		playerExitedZone = true; // Mark the player as having exited the zone
	}

	if (playerExitedZone &&
		playerPosition.x >= targetPosition.x && playerPosition.y >= targetPosition.y)
	{
		std::cout << "Entering EnemyState!\n" << "QuestState for Klee: " << this->klee->toString(currentQuestState) << "\n";
		std::cout << "Entering EnemyState!\n" << "QuestState for Lisa: " << this->lisa->toString(currentQuestState) << "\n";

		this->stateData->states->push(new EnemyState(this->stateData, this->player, this->klee, this->isMushroomDead));

		this->canEnterEnemyState = false;
		this->teleportCooldownClock.restart();
		playerExitedZone = false; // Reset the zone exit flag
		this->updateInventoryText(dt);
	}

	if (playerExitedZone &&
		playerPosition.x >= targetPosition2.x && playerPosition.y >= targetPosition2.y &&
		playerPosition.y <= targetPosition2.y + 50.f)
	{
		std::cout << "Entering EnemyStateMimic!\n" << "QuestState for Klee: " << this->klee->toString(currentQuestState) << "\n";
		std::cout << "Entering EnemyStateMimic!\n" << "QuestState for Lisa: " << this->lisa->toString(currentQuestState) << "\n";


		this->stateData->states->push(new EnemyStateMimic(this->stateData, this->player, this->lisa, this->isFlowerPlantDead));

		this->canEnterEnemyState = false;
		this->teleportCooldownClock.restart();
		playerExitedZone = false; // Reset the zone exit flag
		this->updateInventoryText(dt);
	}


	if (isMushroomDead)
	{
		std::cout << "Mushroom is dead, adding loot to inventory\n";
		addMushroomLoot();
		this->isMushroomDead = false;
	}

	if (isFlowerPlantDead)
	{
		std::cout << "Flower Plant is dead, adding loot to inventory\n";
		addFlowerPlantLoot();
		this->isFlowerPlantDead = false;
	}


}



//NPC interactions and quest updates
void GameState::updateInput(const float& dt)
{
	sf::Vector2f playerPos = this->player->getPosition();

	const float interactionRange = 150.f;  // Adjust the range as needed


	///FOR KLEE!!
	if (this->klee->getDistanceToKlee(playerPos) < interactionRange) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && this->getKeyTime()) {
			if (!this->klee->getIsTalking()) {
				this->klee->startTalking();

				if (this->klee->getQuestState() == QuestState::NOT_TAKEN) {
					this->questStateDescriptionKlee = "Quest : Prove your strength \n\n Go to the enchanted forest and kill \n one mushroom enemy";
					addQuest(
						questStateDescriptionKlee,
						QuestState::IN_PROGRESS,
						klee
					);
					this->addHealthPot();
				}
					
			}

			if (this->klee->getQuestState() == QuestState::COMPLETED) {				
				this->klee->nextDialogue();
				if (!this->klee->getIsTalking()) {
					checkQuestCompletion(klee);
					}
			}

			else {
				this->klee->nextDialogue();
			}
		}
	}


	if (this->klee->getIsTalking() && this->klee->getDistanceToKlee(playerPos) >= interactionRange) {
		this->klee->nextDialogue(); 
	}


	///FOR LISA!!
	if (this->lisa->getDistanceToKlee(playerPos) < interactionRange) {
		// If the player presses the "E" key and the dialogue isn't finished
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && this->getKeyTime()) {
			// If the NPC is not talking yet, start the dialogue
			if (!this->lisa->getIsTalking()) {
				this->lisa->startTalking();

				if (this->lisa->getQuestState() == QuestState::NOT_TAKEN) {
					this->questStateDescriptionLisa = "Quest : Slay the 2 headed flower \n\n Go to the magical garden and obtain \n two flower enemy drops";
					addQuest(
						questStateDescriptionLisa,
						QuestState::IN_PROGRESS,
						lisa
					);
	
				}

				std::string flowerId = "flowerPlantLoot";
				if (this->lisa->getQuestState() == QuestState::IN_PROGRESS && this->playerInventory->getItemQuantity(flowerId) >= 2)
					this->CompleteLisaQuest();
			}

			else {
				// If the NPC is talking, go to the next part of the dialogue
				this->lisa->nextDialogue();
			}
		}
	}


	if (this->lisa->getIsTalking() && this->lisa->getDistanceToKlee(playerPos) >= interactionRange) {
		this->lisa->nextDialogue(); // End the dialogue or continue it
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


//Update functions
void GameState::updateView(const float& dt)
{
	sf::Vector2f playerPosition = this->player->getPosition();

	// Get the size of the view and the window
	sf::Vector2f viewSize = this->view.getSize();
	sf::Vector2f halfViewSize = viewSize / 2.0f;

	// Calculate the maximum bounds for the view's center
	float maxX = this->tileMap->getMaxSize().x * this->tileMap->getGridSize() - halfViewSize.x;
	float maxY = this->tileMap->getMaxSize().y * this->tileMap->getGridSize() - halfViewSize.y;

	float minX = halfViewSize.x;
	float minY = halfViewSize.y;

	// Clamp the view's center position
	sf::Vector2f clampedCenter = playerPosition;

	if (clampedCenter.x < minX)
		clampedCenter.x = minX;
	else if (clampedCenter.x > maxX)
		clampedCenter.x = maxX;

	if (clampedCenter.y < minY)
		clampedCenter.y = minY;
	else if (clampedCenter.y > maxY)
		clampedCenter.y = maxY;

	// Update the view's center
	this->view.setCenter(clampedCenter);
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
	if (this->klee->getQuestState() == QuestState::FINISHED && this->klee->getIsTalking() && !isCompletedKlee) {
		this->player->gainExp(200);
		this->isCompletedKlee = true;
	}


	if (this->lisa->getQuestState() == QuestState::FINISHED && this->lisa->getIsTalking() && !isCompletedLisa) {
		this->player->gainExp(200);
		this->isCompletedLisa = true;
		//this->lisa->setQuestState(QuestState::FINISHED);
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
	
		this->updatePlayerInput(dt);

		this->player->update(dt);

		this->updateView(dt);

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


//Render functions

void GameState::renderQuests(sf::RenderTarget& target)
{
	for (const auto& quest : activeQuests) {
		target.draw(quest.questText);
	}
}

void GameState::renderHouses(sf::RenderTarget& target)
{
	target.draw(this->AdventureHouse);
	target.draw(this->BlacksmithHouse);
	target.draw(this->MarketHouse);

	target.draw(this->EnchantedForest);
	target.draw(this->MagicalGarden);
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

	/*this->inventory->renderInventory(target, *this->inventory, this->houseTextures["BLACKSMITH_HOUSE"], this->font);*/

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
	;

	//Render NPC
	this->klee->renderNpc(this->renderTexture);
	this->lisa->renderNpc(this->renderTexture);

	//Render player
	this->player->render(this->renderTexture);

	// Reset the view to default for GUI rendering
	this->renderTexture.setView(this->renderTexture.getDefaultView());

	//Render GUI
	this->playerGUI->render(this->renderTexture);

	this->renderQuests(this->renderTexture);

	this->klee->renderDialogue(this->renderTexture);
	this->lisa->renderDialogue(this->renderTexture);

	//Render Inventory Menu
	if (this->isInventoryMenuOpen)
{
	this->renderInventoryMenu(this->renderTexture);
	sf::Vector2f inventoryPosition(667, 300); // Example position
	this->playerInventory->render(this->renderTexture , this->inventoryMenuTexture, inventoryPosition);
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
