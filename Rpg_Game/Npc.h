#ifndef NPC_H
#define NPC_H

#include "Entity.h"

enum class QuestState {
	NOT_TAKEN,
	IN_PROGRESS,
	COMPLETED
};

class Npc
{
private:
	

	sf::Sprite sprite;
	sf::RectangleShape DialogueBox;
	sf::Texture dialogueBoxTexture;
	std::map<QuestState, std::vector<std::string>> dialogues;
	size_t dialogueIndex;
	bool isTalking;
	sf::Text dialogueText;
	sf::Text nextText;
	const sf::RenderWindow& window;


	sf::Font font;
	sf::Texture texture;
	sf::Vector2f position;

	void initTextures();
	void initFont();
	void initNpc(const sf::Texture& texture, sf::Vector2f position);
	void initDialogue(const std::string& text);
public:
	Npc(const sf::Texture& texture, const std::map<QuestState, std::vector<std::string>>& dialogueMap, sf::Vector2f position, const sf::RenderWindow& window);
	virtual ~Npc();
	
	QuestState questState;

	void setQuestState(QuestState state);
	QuestState getQuestState() const;

	float getDistanceToNpc(const sf::Vector2f& playerPosition) const;

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