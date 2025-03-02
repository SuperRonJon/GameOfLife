#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include <vector>

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;
const int GRID_SIZE = 5; 
const int GRID_WIDTH = WINDOW_WIDTH / GRID_SIZE;
const int GRID_HEIGHT = WINDOW_HEIGHT / GRID_SIZE;
const int FRAMERATE = 30;

const sf::Color ALIVE = sf::Color::White;
const sf::Color DEAD = sf::Color::Black;

std::vector<std::vector<sf::Color>> initCells(bool randomize);
std::vector<std::vector<sf::Color>> updateCells(std::vector<std::vector<sf::Color>>  const &cells);
void drawGrid(sf::RenderWindow& window);
void drawGridFromCells(sf::RenderWindow& window, std::vector<std::vector<sf::Color>> const &cells);
std::vector<std::vector<sf::Color>> randomizeCells(std::vector<std::vector<sf::Color>> const &cells);
int modulo(int a, int b);

int main() {

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Conway's Game of Life");
    window.setFramerateLimit(FRAMERATE);
    std::vector<std::vector<sf::Color>> cells = initCells(true);
    bool isPlaying = true;

    bool mouseButtonHeld = false;

    while (window.isOpen()) {
        bool stepOne = false;
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                switch(keyPressed->scancode) {
                    case sf::Keyboard::Scancode::Right:
                        stepOne = true;
                        break;
                }
            }
            else if(const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
                switch(keyReleased->scancode) {
                    case sf::Keyboard::Scancode::Space:
                        isPlaying = !isPlaying;
                        break;
                    case sf::Keyboard::Scancode::Backspace:
                        cells = initCells(false);
                        break;
                    case sf::Keyboard::Scancode::Enter:
                        cells = initCells(true);
                        break;
                    case sf::Keyboard::Scancode::Escape:
                        window.close();
                        break;
                }
            }
            else if(const auto* mouseClicked = event->getIf<sf::Event::MouseButtonPressed>()) {
                switch(mouseClicked->button) {
                    case sf::Mouse::Button::Left:
                        if(!isPlaying) {
                            int xPos = mouseClicked->position.x - (mouseClicked->position.x % GRID_SIZE);
                            int yPos = mouseClicked->position.y - (mouseClicked->position.y % GRID_SIZE);
                            cells[yPos / GRID_SIZE][xPos / GRID_SIZE] = ALIVE;
                            mouseButtonHeld = true;
                        }
                        
                        break;
                }
            }
            else if(const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
                switch(mouseReleased->button) {
                    case sf::Mouse::Button::Left:
                        if(!isPlaying) {
                            mouseButtonHeld = false;
                        }
                        break;
                }
            }
            else if(const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
                if(!isPlaying && mouseButtonHeld) {
                    int xPos = mouseMoved->position.x - (mouseMoved->position.x % GRID_SIZE);
                    int yPos = mouseMoved->position.y - (mouseMoved->position.y % GRID_SIZE);
                    cells[yPos / GRID_SIZE][xPos / GRID_SIZE] = ALIVE;
                }
            }
        }
        window.clear();    
        drawGridFromCells(window, cells);   
         
        window.display();
        if(isPlaying || stepOne) {
            cells = updateCells(cells);
        }
    }

    return 0;
}

void drawGrid(sf::RenderWindow& window){
    // Draw the grid
    for (int row = 0; row < GRID_HEIGHT; ++row) {
        for (int col = 0; col < GRID_WIDTH; ++col) {
            sf::RectangleShape square(sf::Vector2f(GRID_SIZE, GRID_SIZE));
            square.setPosition(sf::Vector2f(col * GRID_SIZE, row * GRID_SIZE));

            // Alternate colors
            if ((row + col) % 2 == 0)
                square.setFillColor(sf::Color::White);
            else
                square.setFillColor(sf::Color::Black);

            window.draw(square);
        }
    }
}

void drawGridFromCells(sf::RenderWindow& window, std::vector<std::vector<sf::Color>> const &cells){
    for(int row = 0; row < GRID_HEIGHT; ++row){
        for(int col = 0; col < GRID_WIDTH; ++col){
            sf::RectangleShape square(sf::Vector2f(GRID_SIZE, GRID_SIZE));
            square.setPosition(sf::Vector2f(col*GRID_SIZE, row*GRID_SIZE));
            square.setFillColor(cells[row][col]);
            window.draw(square);
        }
    }
}

std::vector<std::vector<sf::Color>> initCells(bool randomize){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 3);
    std::vector<std::vector<sf::Color>> cells;

    for(int i = 0; i < GRID_HEIGHT; i++){
        std::vector<sf::Color> row(GRID_WIDTH, DEAD);
        cells.push_back(row);
        for(int j = 0; j < GRID_WIDTH; j++){
            if(distr(gen) == 0 && randomize){
                cells[i][j] = ALIVE;
            }
        }
    }

    return cells;
}

std::vector<std::vector<sf::Color>> randomizeCells(std::vector<std::vector<sf::Color>> const &cells) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 3);
    std::vector<std::vector<sf::Color>> nextCells;

    for(int i = 0; i < GRID_HEIGHT; i++) {
        std::vector<sf::Color> row(GRID_WIDTH, DEAD);
        nextCells.push_back(row);
        for(int j = 0; j < GRID_WIDTH; j++) {
            if(distr(gen) == 0) {
                nextCells[i][j] = ALIVE;
            }
        }
    }

    return nextCells;
}

std::vector<std::vector<sf::Color>> updateCells(std::vector<std::vector<sf::Color>> const &cells){
    std::vector<std::vector<sf::Color>> nextCells;
    
    for(int i = 0; i < GRID_HEIGHT; i++) {
        std::vector<sf::Color> row(GRID_WIDTH, DEAD);
        nextCells.push_back(row);
        for(int j = 0; j < GRID_WIDTH; j++) {
            const int LEFT = modulo((j - 1), GRID_WIDTH);
            const int RIGHT = modulo((j + 1), GRID_WIDTH);
            const int UP = modulo((i - 1), GRID_HEIGHT);
            const int DOWN = modulo((i + 1), GRID_HEIGHT);

            int numNeighbors = 0;
            if(cells[UP][LEFT] == ALIVE)
                numNeighbors++;
            if(cells[UP][j] == ALIVE)
                numNeighbors++;
            if(cells[UP][RIGHT] == ALIVE)
                numNeighbors++;
            if(cells[i][LEFT] == ALIVE)
                numNeighbors++;
            if(cells[i][RIGHT] == ALIVE)
                numNeighbors++;
            if(cells[DOWN][LEFT] == ALIVE)
                numNeighbors++;
            if(cells[DOWN][j] == ALIVE)
                numNeighbors++;
            if(cells[DOWN][RIGHT] == ALIVE)
                numNeighbors++;
            
            if(cells[i][j] == ALIVE && (numNeighbors == 2 || numNeighbors == 3)) {
                nextCells[i][j] = ALIVE;
            }
            else if(cells[i][j] == DEAD && numNeighbors == 3) {
                nextCells[i][j] = ALIVE;
            }
            else {
                nextCells[i][j] = DEAD;
            }
        }
    }

    return nextCells;
}

int modulo(int a, int b) {
    return (b + (a % b)) % b;
}