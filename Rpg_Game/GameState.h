#ifndef GAMESTATE_H
#define GAMESTATE_H


#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "EnemyState.h"
#include "Npc.h"

class PauseMenu;
class TileMap;
class Player;
class PlayerGUI;
class sf::View;
class sf::Font;
class sf::RenderTexture;

class GameState : public State
{
private:
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	//Delay
	bool canEnterEnemyState;
	sf::Clock teleportCooldownClock;
	const float teleportCooldown = 2.f;
	bool isInventoryMenuOpen;

	sf::Font font;
	sf::Font font2;
	PauseMenu *pmenu;

	Player *player;
	PlayerGUI* playerGUI;
	Npc* npc;
	TileMap* tileMap;
	AttributeComponent* attributeComponent;


	//House
	sf::RectangleShape AdventureHouse;
	sf::RectangleShape BlacksmithHouse;
	sf::RectangleShape MarketHouse;

	std::map<std::string, sf::Texture> houseTextures;


	//Inventory
	sf::RectangleShape inventoryMenu;
	sf::Texture inventoryMenuTexture;

	sf::Text inventoryTextlevel;
	sf::Text inventoryTexthealth;

	sf::Text inventoryTextstrength;
	sf::Text inventoryTextconstitution;
	sf::Text inventoryTextdexterity;
	sf::Text inventoryTextwisdom;
	sf::Text inventoryTextintelligence;
	sf::Text inventoryTextcharisma;

	//Functions
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
		GameState(StateData* state_data, Player* player);
		virtual ~GameState();


	//functions
		void updateView(const float& dt);
		void updateInput(const float& dt);
		void updatePlayerInput(const float& dt);
		void updatePlayerGUI(const float& dt);
		void updateInventoryText(const float& dt);
		void getToEnemyState(const float& dt);
		void updatePauseMenuButtons();
		void update(const float& dt);
		void renderHouses(sf::RenderTarget& target);
		void renderInventoryMenu(sf::RenderTarget& target);
		void render(sf::RenderTarget* target = nullptr);
};
#endif 
