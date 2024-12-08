#include "stdafx.h"
#include "Game.h"  

void Game::initTextures()
{
    if (!this->textures["PLAYER_SHEET"].loadFromFile("assets/Knight_player/Idle+Walking_KG_1.png"))
    {
        throw std::runtime_error("ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE");
    }
}

void Game::initVariables()
{
	this->window = nullptr;
	this->dt = 0.f;
	this->dtClock.restart();
	this->gridSize = 100.f;

    this->player = new Player(0.f, 0.f,textures["PLAYER_SHEET"]);
}

void Game::initGraphicsSettings()
{

    this->gfxSettings.loadFromFile("Config/graphics.ini");

}


void Game::initWindow()
{


   if (this->gfxSettings.fullscreen)
	   this->window = new sf::RenderWindow(
           this->gfxSettings.resolution, 
           this->gfxSettings.title,
           sf::Style::Fullscreen , 
           this->gfxSettings.contextSettings);
   else
       this->window = new sf::RenderWindow(
           this->gfxSettings.resolution, 
           this->gfxSettings.title,
           sf::Style::Titlebar | sf::Style::Close, 
           this->gfxSettings.contextSettings);

   this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
   this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initKeys()
{
   std::ifstream ifs("Config/supported_keys.ini"); // Fix for incomplete type error

   if (ifs.is_open())
   {
	   std::string key = "";
	   int key_value = 0;

	   while (ifs >> key >> key_value)
	   {
		   this->supportedKeys[key] = key_value;
	   }
   }
   ifs.close();


   //for (auto i : this->supportedKeys)
   //{
	  // std::cout << i.first << " " << i.second << "\n";
   //}
   
}

void Game::initStateData()
{
	this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
}


void Game::initStates()
{
   this->states.push(new MainMenuState(&this->stateData,this->player));

}

// Constructors / Destructors
Game::Game()
{
   this->initTextures();
   this->initVariables();
   this->initGraphicsSettings();
   this->initWindow();
   this->initKeys();
   this->initStateData();
   this->initStates();
}

Game::~Game()
{
   delete this->window;
 

   while (!this->states.empty())
   {
       delete this->states.top();
       this->states.pop(); //while there are still states in the stack when we want to close the game we pop them until there are none left      
   }
   delete this->player;
}

// Functions

void Game::endApplication() //function that ends the application
{
   std::cout << "Ending Application!" << std::endl;
}

void Game::updateDT()
{
   this->dt = this->dtClock.restart().asSeconds(); // Updates the dt variable with the time it takes to update and render one frame
   //Delta time is the time elapsed between the current frame and the previous frame
   //system("cls");
   //std::cout << this->dt << std::endl;
}

const bool Game::running() const
{
   return this->window->isOpen();
}

void Game::updateSFMLEvents()
{
   while (this->window->pollEvent(this->ev))
   {
       if (this->ev.type == sf::Event::Closed)
           this->window->close();
   }
}

void Game::update() //function that updates the states of the game
{

   this->updateSFMLEvents(); // updates the events of the game

   if (!this->states.empty())
   {
       this->states.top()->update(this->dt); //If the states stack is not empty, this line retrieves the top State object from the stack and calls its update method

       if (this->states.top()->getQuit()) //if the top state in the stack has the quit flag set to true we pop it off the stack
       {
           this->states.top()->endState();
           delete this->states.top();
           this->states.pop();
       }
   }
   //Application end
   else
   {
       this->endApplication();
       this->window->close(); // if the stack is empty we close the window
   }
}

void Game::render()
{
   this->window->clear();

   // Render game objects here
   if (!this->states.empty())
   {
       this->states.top()->render(); //If the states stack is not empty, this line retrieves the top State object from the stack and calls its render method
   }
   this->window->display();
}

void Game::run()
{
   while (this->running())
   {
       this->updateDT(); //resets the clock for every frame
       this->update();
       this->render();
   }
}
