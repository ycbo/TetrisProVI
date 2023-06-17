#include "tetromino.hpp"

Tetromino::Tetromino(const bool* shape, const int dimension, const sf::Color& color, const sf::Vector2f& pos)
                    : shape{ shape },
                    dimension{ dimension },
                    color{ color },
                    boardPos{ pos.x / 2 - dimension / 2, 0 },
                    currentRotation{ Rotation::UP }
{
}

void Tetromino::MoveDown()
{
    boardPos.y += 1;
}

void Tetromino::RotateClockwise()
{
    currentRotation = Rotation((int(currentRotation) + 1) % 4);
}

void Tetromino::RotateCounterClockwise()
{
    if (currentRotation == Rotation::UP) {
        currentRotation = Rotation::LEFT;
    }
    else {
        currentRotation = Rotation(int(currentRotation) - 1);
    }
}

void Tetromino::Update(std::vector<std::vector<unsigned char>>& matrix)
{
    for (unsigned char x = 0; x < dimension; x++) {
        for (unsigned char y = 0; y < dimension; y++) {
            bool cell = false;

            switch (currentRotation) {
                case Tetromino::Rotation::UP:
                    cell = shape[y * dimension + x];
                    break;
                case Tetromino::Rotation::RIGHT:
                    cell = shape[dimension * (dimension - 1) - x * dimension + y];
                    break;
                case Tetromino::Rotation::DOWN:
                    cell = shape[(dimension * dimension - 1) - y * dimension - x];
                    break;
                case Tetromino::Rotation::LEFT:
                    cell = shape[(dimension - 1) + x * dimension - y];
                    break;
            }

            matrix[x + boardPos.x][y + boardPos.y] = cell;
        }
    }
}