#ifndef NPC_H
#define NPC_H

#include "Entity.h"

enum class QuestState {
	NOT_TAKEN,
	IN_PROGRESS,
	COMPLETED,
	FINISHED
};

class Npc;

struct Quest {
	sf::Text questText;
	QuestState state;
	Npc* npc;
};

class Npc
{
private:
	

	sf::Sprite NPC;
	sf::RectangleShape DialogueBox;
	std::map<QuestState, std::vector<std::string>> dialogues;
	size_t dialogueIndex;
	sf::Text dialogueText;
	sf::Text nextText;
	sf::Text questStateText;
	sf::String questStateDescription;
	sf::String questStateDescriptionFinished;
	const sf::RenderWindow& window;

	bool isTalking;
	bool hasDisplayedFinalDialogue;

	sf::Font font;
	sf::Texture texture;
	sf::Texture dialogueTexture;

	sf::Vector2f position;
	float sprite_size_x;
	float sprite_size_y;

	float questPosX;
	float questPosY;

	void initTextures();
	void initFont();
	void initNpc(const sf::Texture& texture, sf::Vector2f position, float x, float y);
	void initDialogue(const std::string& text, const sf::Texture* dialogueTexture);
	void initQuestStateText();
public:



	Npc(const sf::Texture& texture, const sf::Texture& dialogueTexture,
		const sf::String& questStateDescription, const sf::String& questStateDescriptionFinished,
		const float& questPosX, const float& questPosY,
		const std::map<QuestState, 
		std::vector<std::string>>& dialogueMap,
		sf::Vector2f position, const sf::RenderWindow& window,
		float size_x, float size_y);
	virtual ~Npc();
	
	QuestState questState;

	void setQuestState(QuestState state);
	QuestState getQuestState() const;

	float getDistanceToKlee(const sf::Vector2f& playerPosition) const;

	void updateDialogueText();
	void nextDialogue();
	bool getIsTalking() const;
	void startTalking();

	std::string toString(QuestState* currentQuest) const;
	void renderNpc(sf::RenderTarget& target);
	void renderDialogue(sf::RenderTarget& target);
	//void renderBoundingBox(sf::RenderTarget& target);
	//void render(sf::RenderTarget& target);
};

#endif // !NPC_H