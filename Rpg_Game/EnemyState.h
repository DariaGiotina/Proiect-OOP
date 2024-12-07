#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

#include "State.h"
#include "Gui.h"
#include "PlayerGUI.h"
#include "Player.h"
#include "AttributeComponent.h"

class EnemyState : public State
{
private:

	//Variables
	//DelayTurn
	float delayTimer;
	float delayDuration;
	bool isDelayActive;
	bool turn;
	int level;

	//Delay game over
	bool gameWon;
	bool isGameOver; 
	float messageDuration;    // Duration to display the message (5 seconds)
	sf::Clock messageTimer;   // Timer for the message
	sf::Text winnerText;

	//Objects
	Player* player;
	Enemy* enemy;
	PlayerGUI* playerGUI;
	AttributeComponent* attributeComponent;
	AnimationComponent* animationComponent;

	//GUI
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Font font;
	sf::Text turnText;
	sf::RectangleShape spellsbar;
	sf::Texture spellsbarTexture;
	
	//Player
	float exp;
	float newExp;
	//Enemy GUI
	float EnemyhpBarMaxWidth;
	sf::RectangleShape EnemyhpBarBack;
	sf::RectangleShape EnemyhpBarInner;
	sf::Texture EnemyhpBarBackTexture;
	sf::Texture EnemyhpBarInnerTexture;
	std::string EnemyhpBarString;
	sf::Text EnemyhpBarText;

	//Player GUI
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	
	//Buttons
	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, sf::Texture> idleTextures;
	std::map<std::string, sf::Texture> hoverTextures;
	std::map<std::string, sf::Texture> activeTextures;

	//Functions
	void initDeferredRender();
	void initVariables();
	void initBackground();
	void initFonts();
	void initTextures();
	void initKeybinds();
	void initPlayer();
	void initEnemy();
	void initButtons();
	void initPlayerGui();
	void initEnemyHPBar();
	void initTurnText();	
public:
	EnemyState(StateData* state_data, Player* player);
	virtual ~EnemyState();

	const bool isButtonPressed(const std::string key);

	void switchTurn();
	void startDelay(const float duration);
	void exitEnemyState(const float& dt);
	bool updateDelayTimer(const float& dt);
	void updateGame(const float& dt);
	void updateInput(const float& dt);
	void updatePlayerGUI(const float& dt);
	void updateEnemyHPBar();
	void updateTurnText();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void renderEnemyHPBar(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

#endif // 