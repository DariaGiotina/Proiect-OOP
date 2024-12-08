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

Npc::Npc(const sf::Texture& texture, const std::vector<std::string>& dialogueLines, sf::Vector2f position, const sf::RenderWindow& window)
	: dialogue(dialogueLines), dialogueIndex(0), isTalking(false), window(window), questState(QuestState::NOT_TAKEN)
{

	this->initTextures();
	this->initFont();
	this->initNpc(texture,position);

	if (!dialogue.empty()) {
		this->initDialogue(dialogue[0]); // Initialize with the first dialogue line
	}
}


Npc::~Npc()
{

}


float Npc::getDistanceToNpc(const sf::Vector2f& playerPosition) const
{
	sf::Vector2f npcPosition = sprite.getPosition();

	// Calculate the distance between the player and NPC
	float distance = sqrt(pow(npcPosition.x - playerPosition.x, 2) + pow(npcPosition.y - playerPosition.y, 2));

	return distance;
}

bool Npc::getIsTalking() const
{
	return this->isTalking;
}

void Npc::startTalking()
{
	isTalking = true;
	dialogueIndex = 0;
	updateDialogueText();
}

void Npc::nextDialogue() {
	if (dialogueIndex < dialogue.size()) {
		++dialogueIndex;
		updateDialogueText();
	}
	else {
		isTalking = false; // End of dialogue
	}
}

void Npc::updateDialogueText()
{
	if (dialogueIndex < dialogue.size()) {
		dialogueText.setString(dialogue[dialogueIndex]);
	}
	else {
		dialogueText.setString("");
	}

}

void Npc::setQuestState(QuestState state)
{
	this->questState = state;

}

QuestState Npc::getQuestState() const
{
	return this->questState;
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
