#include "Game.h"  
#include <fstream> // Add this include to fix the incomplete type error

void Game::initVariables()
{
	this->window = nullptr;
	this->fullscreen = false;
	this->dt = 0.f;
	this->dtClock.restart();
}

// Private functions
void Game::initWindow()
{
   // Display the list of all the video modes available for fullscreen

   std::ifstream ifs("Config/window.ini");
   this->videoModes = sf::VideoMode::getFullscreenModes();

   std::string title = "None";
   sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
   bool fullscreen = false;
   unsigned framerate_limit = 120;
   bool vertical_sync_enabled = false;
   unsigned antialiasing_level = 0;

   if (ifs.is_open())
   {
	   std::getline(ifs, title);
	   ifs >> window_bounds.width >> window_bounds.height;
	   ifs >> fullscreen;
	   ifs >> framerate_limit;
	   ifs >> vertical_sync_enabled;
	   ifs >> antialiasing_level;
   }
   ifs.close();
   
   this->fullscreen = fullscreen;
   this->windowSettings.antialiasingLevel = antialiasing_level;

   if (this->fullscreen)
	   this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen , windowSettings);
   else
       this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);

   this->window->setFramerateLimit(framerate_limit);
   this->window->setVerticalSyncEnabled(vertical_sync_enabled);
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


   for (auto i : this->supportedKeys)
   {
	   std::cout << i.first << " " << i.second << "\n";
   }
   
}

void Game::initStates()
{
   this->states.push(new MainMenuState(this->window, &this->supportedKeys,&this->states));
   //this->states.push(new GameState(this->window, &this->supportedKeys)); //pushes a new game state object to the top of the stack
}

// Constructors / Destructors
Game::Game()
{
   this->initWindow();
   this->initKeys();
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
