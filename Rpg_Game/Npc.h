#ifndef NPC_H
#define NPC_H

#include "Entity.h"

enum class QuestState {
	NOT_TAKEN,
	IN_PROGRESS,
	COMPLETED,
	NOQUEST
};

class Npc
{
private:
	QuestState questState;

	sf::Sprite sprite;
	sf::RectangleShape DialogueBox;
	sf::Texture dialogueBoxTexture;
	std::vector<std::string> dialogue;
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
	Npc(const sf::Texture& texture, const std::vector<std::string>& dialogueLines, sf::Vector2f position, const sf::RenderWindow& window);
	virtual ~Npc();
	
	float getDistanceToNpc(const sf::Vector2f& playerPosition) const;
	bool getIsTalking() const;

	void startTalking();
	void nextDialogue();
	void updateDialogueText();

	void setQuestState(QuestState state);
	QuestState getQuestState() const;

	void renderNpc(sf::RenderTarget& target);
	void renderDialogue(sf::RenderTarget& target);
	//void renderBoundingBox(sf::RenderTarget& target);
	//void render(sf::RenderTarget& target);
};

#endif // !NPC_H