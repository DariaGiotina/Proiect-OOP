#include "stdafx.h"
#include "Npc.h"



void Npc::initTextures()
{

}

void Npc::initFont()
{
	if (!this->font.loadFromFile("Fonts/AncientModernTales-a7Po.ttf"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT"); //exits the program and shows the error message
	}
}

void Npc::initNpc(const sf::Texture& texture, sf::Vector2f position, float x,float y)
{
	this->NPC.setTexture(texture);
	this->NPC.setPosition(position);
	this->NPC.setScale(sprite_size_x, sprite_size_y);


}

void Npc::initDialogue(const std::string& text,const sf::Texture* dialogueTexture)
{
	this->DialogueBox.setTexture(dialogueTexture);
	this->DialogueBox.setSize(sf::Vector2f(800.f, 250.f));

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

void Npc::initQuestStateText()
{
	questStateText.setFont(this->font);
	questStateText.setCharacterSize(25);
	questStateText.setFillColor(sf::Color(80,18,63,255));
	questStateText.setPosition(DialogueBox.getPosition().x + questPosX, DialogueBox.getPosition().y + questPosY);
}

Npc::Npc(const sf::Texture& texture,const sf::Texture& dialogueTexture,
	const sf::String& questStateDescription, const sf::String& questStateDescriptionFinished,
	const float& questPosX, const float& questPosY,
	const std::map<QuestState,
	std::vector<std::string>>& dialogueMap,
	sf::Vector2f position, const sf::RenderWindow& window,float size_x, float size_y)

	:dialogues(dialogueMap), dialogueIndex(0), isTalking(false), 
	window(window), questState(QuestState::NOT_TAKEN), 
	sprite_size_x(size_x), sprite_size_y(size_y), 
	questStateDescription(questStateDescription),questStateDescriptionFinished(questStateDescriptionFinished),
	questPosX(questPosX), questPosY(questPosY),
	hasDisplayedFinalDialogue(false)
{

	this->initTextures();
	this->initFont();
	this->initNpc(texture,position, sprite_size_x, sprite_size_y);
	this->initQuestStateText();


	if (!dialogues.empty()) {
		this->initDialogue(dialogues[questState][0],&dialogueTexture); // Initialize with the first dialogue line
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

	if (newState == QuestState::COMPLETED) {
		hasDisplayedFinalDialogue = false;  // Reset flag when quest is completed
	}
}

QuestState Npc::getQuestState() const
{
	return this->questState;
}

float Npc::getDistanceToKlee(const sf::Vector2f& playerPosition) const
{
	sf::Vector2f npcPosition = NPC.getPosition();

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
	else if (questState == QuestState::NOT_TAKEN) {
		// Only transition to IN_PROGRESS after finishing all "NOT_TAKEN" dialogues
		if (dialogueIndex >= dialogues[QuestState::NOT_TAKEN].size()) {
			isTalking = false;
			setQuestState(QuestState::IN_PROGRESS);
		}
	}
	else if (questState == QuestState::COMPLETED && !hasDisplayedFinalDialogue) {
		hasDisplayedFinalDialogue = true;  // Mark final dialogue shown
	}
	else if (questState == QuestState::COMPLETED && hasDisplayedFinalDialogue) {
		isTalking = false;
		setQuestState(QuestState::FINISHED);  // Transition to FINISHED state
	}
	else {
		isTalking = false;  // Default behavior for unhandled cases
	}
}

bool Npc::getIsTalking() const
{
	return this->isTalking;
}

void Npc::startTalking()
{
	isTalking = true;
	dialogueIndex = 0;  // Reset to the start of the dialogue
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
		return "FINISHED";
		break;
	}
}

void Npc::renderNpc(sf::RenderTarget& target)
{
	target.draw(NPC);
}

void Npc::renderDialogue(sf::RenderTarget& target)
{
	if (isTalking) {
		target.draw(DialogueBox);
		target.draw(dialogueText);
		target.draw(nextText);
	}



}
