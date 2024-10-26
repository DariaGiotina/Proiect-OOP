#include "Game.h"

// Private functions
void Game::initWindow()
{
    // Display the list of all the video modes available for fullscreen
	std::string title = "None";

    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < modes.size(); ++i)
    {
        sf::VideoMode mode = modes[i];
       /* std::cout << "Mode #" << i << ": "
            << mode.width << "x" << mode.height << " - "
            << mode.bitsPerPixel << " bpp" << std::endl;*/
    }

    // Create a window with the same resolution as the desktop
	this->window = new sf::RenderWindow(sf::VideoMode(this->desktop.width, this->desktop.height, this->desktop.bitsPerPixel), "Rpg Game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    this->window->setFramerateLimit(120);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initKeys()
{
	this->supportedKeys["Escape"] = sf::Keyboard::Escape;
	this->supportedKeys["A"] = sf::Keyboard::A;
	this->supportedKeys["D"] = sf::Keyboard::D;
	this->supportedKeys["W"] = sf::Keyboard::W;
	this->supportedKeys["S"] = sf::Keyboard::S;


	//Debug Remove Later
	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << "\n";
	}

}

void Game::initStates()
{
	this->states.push(new GameState(this->window,&this->supportedKeys));//pushes a new game state object to the top of the stack
}

// Constructors / Destructors
Game::Game(){

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
        this->states.pop();//while there are still states in the stack when we want to close the game we pop them until there are none left      
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
        this->states.top()->update(this->dt);//If the states stack is not empty, this line retrieves the top State object from the stack and calls its update method

        if (this->states.top()->getQuit())//if the top state in the stack has the quit flag set to true we pop it off the stack
        {

            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }

    //Application end
    else {
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
		this->states.top()->render();//If the states stack is not empty, this line retrieves the top State object from the stack and calls its render method
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
