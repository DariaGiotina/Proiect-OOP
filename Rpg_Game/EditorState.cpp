#include "stdafx.h"
#include "EditorState.h"
#include "GameState.h"  

//Initializer functions
void EditorState::initVariables() {

	this->textureRect  = sf::IntRect(0, 0,static_cast<int>( this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));

}

void EditorState::initBackground()
{

}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/AncientModernTales-a7Po.ttf"))
	{
		throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT"); //exits the program and shows the error message
	}
}

void EditorState::initText()
{

	this->cursorText.setFont(this->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(16);
	this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y);


}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");
	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();


}

void EditorState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("MAIN MENU", 670.f, 210.f, "MAIN MENU");
	this->pmenu->addButton("LOAD", 670.f, 380.f, "LOAD");
	this->pmenu->addButton("SAVE", 670.f, 560.f, "SAVE");
	this->pmenu->addButton("QUIT", 670.f, 740.f, "QUIT");

}

void EditorState::initButtons()
{

	
}

void EditorState::initGui()
{
	this->sidebar.setSize(sf::Vector2f(80.f, 1080.f));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);


	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

	this->selectorRect.setFillColor(sf::Color(255,255,255,150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Magenta);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(
		20.f, 20.f, 500.f, 500.f,
		this->stateData->gridSize, this->tileMap->getTileSheet(),
		this->font);
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize,10,10,"assets/The_Fan-tasy_Tileset/Art/Ground_Tileset_100x100/4_textures.png");
}

//Constructor / Destructor

EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();
}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	delete this->pmenu;
	delete this->tileMap;
	delete this->textureSelector;
}

//Functions

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
	{
		//Add a tile to the tilemap
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())
		{
			if (!this->textureSelector->getActive())
			{
				this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
			}
			else
			{
				this->textureRect = this->textureSelector->getTextureRect();
			}
		}



		//Remove a tile from the tilemap
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime())
		{
			if (!this->textureSelector->getActive())
				this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
		}
	}

}

void EditorState::updateButtons()
{
	//Updates all the buttons in the state and handles their functionality
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

}

void EditorState::updateGui(const float& dt)
{

	this->textureSelector->update(this->mousePosWindow,dt);

	if (!this->textureSelector->getActive()) {
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
	}

	this->cursorText.setPosition(this->mousePosView.x + 100.f, this->mousePosView.y - 50);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y << "\n" << 
	mousePosGrid.x << " " << this->mousePosGrid.y << "\n" <<
	this->textureRect.left << " " << this->textureRect.top;
	this->cursorText.setString(ss.str());

}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("MAIN MENU"))
	{
		this->endState();
	}

	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->window->close();
	}

	if (this->pmenu->isButtonPressed("SAVE"))
	{
		this->tileMap->saveToFile("test.rpg");
	}

	if (this->pmenu->isButtonPressed("LOAD"))
	{
		this->tileMap->loadFromFile("test.rpg");
	}
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeyTime(dt);
	this->updateInput(dt);

	if (!this->paused) //Unpaused
	{
		this->updateButtons();
		this->updateGui(dt);
		this->updateEditorInput(dt);
	}
	else //Paused
	{
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}



}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target)
{

	if (!this->textureSelector->getActive())
		target.draw(this->selectorRect);

	this->textureSelector->render(target);
	target.draw(this->cursorText);

	target.draw(this->sidebar);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	this->tileMap->render(*target);

	this->renderButtons(*target);
	this->renderGui(*target);

	if (this->paused) //paused menu render
	{
		this->pmenu->render(*target);
	}


}
