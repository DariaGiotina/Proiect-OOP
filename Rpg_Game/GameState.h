#ifndef GAMESTATE_H
#define GAMESTATE_H


#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "EnemyState.h"

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

	sf::Font font;
	PauseMenu *pmenu;

	Player *player;
	PlayerGUI* playerGUI;
	TileMap* tileMap;

	//Functions
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initPlayerGUI();
	void initTileMap();

public:
		GameState(StateData* state_data);
		virtual ~GameState();


	//functions
		void updateView(const float& dt);
		void updateInput(const float& dt);
		void updatePlayerInput(const float& dt);
		void updatePlayerGUI(const float& dt);
		void getToEnemyState(const float& dt);
		void updatePauseMenuButtons();
		void update(const float& dt);
		void render(sf::RenderTarget* target = nullptr);
};
#endif 
