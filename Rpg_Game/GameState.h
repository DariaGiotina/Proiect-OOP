#ifndef GAMESTATE_H
#define GAMESTATE_H


#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "EnemyState.h"
#include "EnemyStateMimic.h"
#include "Npc.h"
#include "Inventory.h"


class GameState : public State
{
private:
	//Variables
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	//Delay
	bool canEnterEnemyState;
	sf::Clock teleportCooldownClock;
	const float teleportCooldown = 2.f;

	//Booleans
	bool isInventoryMenuOpen;
	bool isCompletedKlee;
	bool isCompletedLisa;
	bool isFlowerPlantDead;
	bool isMushroomDead;

	sf::Font font;
	sf::Font font2;
	PauseMenu *pmenu;

	//Objects
	Player *player;
	PlayerGUI* playerGUI;
	Npc* klee;
	Npc* lisa;
	TileMap* tileMap;
	AttributeComponent* attributeComponent;
	Inventory* playerInventory;
	
	//Quest
	std::map<QuestState, std::vector<std::string>> npcDialogueKlee;
	std::map<QuestState, std::vector<std::string>> npcDialogueLisa;
	QuestState* currentQuestState;
	sf::String questStateDescriptionKlee;
	sf::String questStateDescriptionLisa;
	sf::String questStateDescriptionKleeFinished;
	sf::String questStateDescriptionLisaFinished;

	//House
	sf::RectangleShape AdventureHouse;
	sf::RectangleShape BlacksmithHouse;
	sf::RectangleShape MarketHouse;

	std::map<std::string, sf::Texture> houseTextures;

	//Signs
	sf::RectangleShape MagicalGarden;
	sf::RectangleShape EnchantedForest;


	//Inventory
	sf::RectangleShape inventoryMenu;
	sf::Texture inventoryMenuTexture;


	//Inventory Text
	sf::Text inventoryTextlevel;
	sf::Text inventoryTexthealth;

	sf::Text inventoryTextstrength;
	sf::Text inventoryTextconstitution;
	sf::Text inventoryTextdexterity;
	sf::Text inventoryTextwisdom;
	sf::Text inventoryTextintelligence;
	sf::Text inventoryTextcharisma;


	//Initializers
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initPlayerGUI();
	void initNpc();
	void initTileMap();
	void initHouse();
	void initInventoryMenu();
	void initInventoryText();

public:
	//Constructors/Destructors
		GameState(StateData* state_data, Player* player);
		virtual ~GameState();


	//functions

		//Inventory
		void addHealthPot();
		void addFlowerPlantLoot();
		void addMushroomLoot();

		//Quest
		void CompleteLisaQuest();

		//Teleport
		void getToEnemyState(const float& dt);

		//Update
		void updateInput(const float& dt);
		void updateView(const float& dt);
		void updatePlayerInput(const float& dt);
		void updatePlayerGUI(const float& dt);
		void updateInventoryText(const float& dt);
		void updateExpwhenComplete(const float& dt);
		void updatePauseMenuButtons();
		void update(const float& dt);

		//Render
		void renderHouses(sf::RenderTarget& target);
		void renderInventoryMenu(sf::RenderTarget& target);
		void render(sf::RenderTarget* target = nullptr);
};
#endif 
