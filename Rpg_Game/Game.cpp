#include "Game.h"

// Private functions
void Game::initWindow()
{
    // Display the list of all the video modes available for fullscreen
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < modes.size(); ++i)
    {
        sf::VideoMode mode = modes[i];
        std::cout << "Mode #" << i << ": "
            << mode.width << "x" << mode.height << " - "
            << mode.bitsPerPixel << " bpp" << std::endl;
    }

    // Create a window with the same resolution as the desktop
	this->window = new sf::RenderWindow(sf::VideoMode(this->desktop.width, this->desktop.height, this->desktop.bitsPerPixel), "Rpg Game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
   
}
// Constructors / Destructors
Game::Game(){

    this->initWindow();

}

Game::~Game()
{
    delete this->window;
}


void Game::updateDT()
{
	this->dt = this->dtClock.restart().asSeconds(); // Updates the dt variable with the time it takes to update and render one frame
    //Delta time is the time elapsed between the current frame and the previous frame. It is commonly used in game development to ensure smooth and consistent movement and animations, regardless of the frame rate.
	system("cls");
	std::cout << this->dt << std::endl;
}

// Functions
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

void Game::update()
{
	this->updateSFMLEvents();
}

void Game::render()
{
    this->window->clear();

    // Render game objects here
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
