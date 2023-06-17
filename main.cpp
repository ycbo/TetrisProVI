#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "main.hpp"
#include "tetromino.hpp"

int main()
{
    // Window size and the frame size of the operation area
    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * COULUMNS * SCREEN_RESIZE, CELL_SIZE * ROWS * SCREEN_RESIZE), "tertis");
    window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * COULUMNS, CELL_SIZE * ROWS)));

    std::vector<std::vector<unsigned char>> matrix(COULUMNS, std::vector<unsigned char>(ROWS));

    // Load a music to play
    //sf::Music music;
   // if (!music.openFromFile("Music/Korobeiniki.flac")) { return EXIT_FAILURE; }
   // music.play();

    auto tetromino = std::make_unique<Jay>(sf::Vector2f(COULUMNS, ROWS));
    tetromino->Update(matrix);

    while (window.isOpen()) {

        window.clear();
        sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: window.close(); break;
                case sf::Event::KeyReleased:
                {
                    switch (event.key.code) {
                        case sf::Keyboard::Down:
                        {
                            tetromino->MoveDown();
                            break;
                        }
                        case sf::Keyboard::Left:
                        {
                            break;
                        }
                        case sf::Keyboard::Right:
                        {
                            break;
                        }
                        // Clockweise
                        case sf::Keyboard::X:
                        {
                            tetromino->RotateClockwise();
                            break;
                        }
                        // Counter clockweise
                        case sf::Keyboard::Z:
                        {
                            tetromino->RotateCounterClockwise();
                            break;
                        }
                        default: break;

                    }
                }
            }
        }
        window.clear();
        tetromino->Update(matrix);
        for (unsigned char cell_x = 0; cell_x < COULUMNS; cell_x++) {
            for (unsigned char cell_y = 0; cell_y < ROWS; cell_y++) {
                if (matrix[cell_x][cell_y] == 1) {
                    cell.setFillColor(tetromino->GetColor());
                }
                else {
                    cell.setFillColor(sf::Color(162, 181, 205));
                }
                cell.setPosition(float(CELL_SIZE * cell_x), float(CELL_SIZE * cell_y));
                window.draw(cell);
            }
        }
        window.display();
    }
}