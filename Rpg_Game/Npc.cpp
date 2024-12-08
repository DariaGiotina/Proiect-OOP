#include "stdafx.h"
#include "Npc.h"



void Npc::initTextures()
{
	if (!this->dialogueBoxTexture.loadFromFile("assets/player/klee_text.png"))
	{
		throw("ERROR::PLAYERGUI::COULD NOT LOAD HP BAR BACK TEXTURE");
	}
}

void Npc::initFont()
{
	if (!this->font.loadFromFile("Fonts/AncientModernTales-a7Po.ttf"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT"); //exits the program and shows the error message
	}
}

void Npc::initNpc(const sf::Texture& texture, sf::Vector2f position)
{
	this->sprite.setTexture(texture);
	this->sprite.setPosition(position);

	this->sprite.setScale(0.3f, 0.3f);
}

void Npc::initDialogue(const std::string& text)
{
	DialogueBox.setTexture(&dialogueBoxTexture);
	DialogueBox.setSize(sf::Vector2f(800.f, 250.f));

	// Get the window size
	sf::Vector2u windowSize = window.getSize();

	// Position the dialogue box at the center-bottom of the screen
	DialogueBox.setPosition((windowSize.x - DialogueBox.getSize().x) / 2.f, windowSize.y - DialogueBox.getSize().y - 40.f);

	nextText.setString("Press E to continue...");
	nextText.setFont(this->font);
	nextText.setCharacterSize(20);
	nextText.setFillColor(sf::Color::Black);
	nextText.setPosition(DialogueBox.getPosition().x + 475.f, DialogueBox.getPosition().y + 200.f);

	// Set the dialogue text's font, size, and position within the box
	dialogueText.setFont(this->font);
	dialogueText.setString(text);
	dialogueText.setCharacterSize(40);
	dialogueText.setFillColor(sf::Color::Black);
	dialogueText.setPosition(DialogueBox.getPosition().x + 320.f, DialogueBox.getPosition().y + 50.f);

}

Npc::Npc(const sf::Texture& texture, const std::map<QuestState, std::vector<std::string>>& dialogueMap, sf::Vector2f position, const sf::RenderWindow& window)
	:dialogues(dialogueMap), dialogueIndex(0), isTalking(false), window(window), questState(QuestState::NOT_TAKEN)
{

	this->initTextures();
	this->initFont();
	this->initNpc(texture,position);


	if (!dialogues.empty()) {
		this->initDialogue(dialogues[questState][0]); // Initialize with the first dialogue line
	}
}


Npc::~Npc()
{


}
void Npc::setQuestState(QuestState newState)
{
	if (questState != newState) {
		questState = newState;
		dialogueIndex = 0;  // Reset dialogue when changing the quest state
		updateDialogueText();
	}
	else if (questState == QuestState::IN_PROGRESS) {
		dialogueIndex = 0;

	}
}

QuestState Npc::getQuestState() const
{
	return this->questState;
}

float Npc::getDistanceToNpc(const sf::Vector2f& playerPosition) const
{
	sf::Vector2f npcPosition = sprite.getPosition();

	// Calculate the distance between the player and NPC
	float distance = sqrt(pow(npcPosition.x - playerPosition.x, 2) + pow(npcPosition.y - playerPosition.y, 2));

	return distance;
}



void Npc::updateDialogueText()
{
	if (dialogues.find(questState) != dialogues.end() && dialogues[questState].size() > dialogueIndex) {
		dialogueText.setString(dialogues[questState][dialogueIndex]);
	}
	else {
		dialogueText.setString("..."); // Handle end of dialogue or unhandled quest state
	}

}

void Npc::nextDialogue() {
	if (dialogues.find(questState) != dialogues.end() && dialogues[questState].size() > dialogueIndex) {
		++dialogueIndex;
		updateDialogueText();
	}
	else if(this->questState == QuestState::IN_PROGRESS || this->questState == QuestState::NOT_TAKEN) {
		isTalking = false;  // End dialogue if no more text
		this->setQuestState(QuestState::IN_PROGRESS);
	}
	else {
		isTalking = false;
	}
}

bool Npc::getIsTalking() const
{
	return this->isTalking;
}

void Npc::startTalking()
{
	isTalking = true;
	updateDialogueText();
}


std::string Npc::toString(QuestState* currentQuest) const
{
	switch (questState)
	{
	case QuestState::NOT_TAKEN:
		return "NOT_TAKEN";
		break;
	case QuestState::IN_PROGRESS:
		return "IN_PROGRESS";
		break;
	case QuestState::COMPLETED:
		return "COMPLETED";
		break;
	default:
		return "UNKNOWN";
		break;
	}
}

void Npc::renderNpc(sf::RenderTarget& target)
{
	target.draw(sprite);
}

void Npc::renderDialogue(sf::RenderTarget& target)
{
	if (isTalking) {
		target.draw(DialogueBox);
		target.draw(dialogueText);
		target.draw(nextText);
	}
}

//void Npc::renderBoundingBox(sf::RenderTarget& target)
//{
//	sf::FloatRect bounds = sprite.getGlobalBounds();
//	sf::RectangleShape outline(sf::Vector2f(bounds.width, bounds.height));
//	outline.setPosition(bounds.left, bounds.top);
//	outline.setFillColor(sf::Color(0, 255, 0, 50));  // Light green fill for visibility
//	outline.setOutlineColor(sf::Color::Red);         // Red outline
//	outline.setOutlineThickness(2);
//	target.draw(outline);  // Draw the bounding box
//}

//void Npc::render(sf::RenderTarget& target)
//{
//	renderNpc(target);
//	renderDialogue(target);
//	//renderBoundingBox(target);
//
//}
