#include "tetromino.hpp"

Tetromino::Tetromino(const bool* shape, const int dimension, const sf::Color& color, const sf::Vector2f& pos)
    : shape { shape },
    dimension { dimension },
    color { color },
    boardSize { pos },
    boardPos { pos.x / 2 - dimension / 2, 0 },
    currentRotation { Rotation::UP }
{
}

void Tetromino::MoveDown()
{
    if (boardPos.y + 1 < boardSize.y) {
        boardPos.y += 1;
    }
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
    std::vector<std::vector<unsigned char>> currentShape = GetShape();

    sf::Vector2f newBoardPos = CheckBoundary(matrix, currentShape);

    for (unsigned char x = 0; x < dimension; x++) {
        for (unsigned char y = 0; y < dimension; y++) {
            const bool cell = currentShape[x][y];

            if ((x + boardPos.x >= boardSize.x) || (y + boardPos.y >= boardSize.y)) break;
            matrix[x + boardPos.x][y + boardPos.y] = cell;
        }
    }
}

std::vector<std::vector<unsigned char>> Tetromino::GetShape()
{
    std::vector<std::vector<unsigned char>> currentShape(dimension, std::vector<unsigned char>(dimension));
    // Column
    for (unsigned char x = 0; x < dimension; x++) {
        // Row
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

            currentShape[x][y] = cell;
        }
    }
    return currentShape;
}

sf::Vector2f Tetromino::CheckBoundary(std::vector<std::vector<unsigned char>> matrix, const std::vector<std::vector<unsigned char>>& shape)
{
    // Check the first column
    unsigned char maxRow = dimension;

    if (boardPos.y + dimension > boardSize.y) {
        for (char row = dimension - 1; row >= 0; row--) {
            bool emptyRow = true;
            for (char col = 0; col < dimension; col++) {
                if (shape[col][row]) {
                    emptyRow &= false;
                }
            }
            if (emptyRow) { maxRow--; }
            else { break; }
        }
    }

    if (boardPos.y == 18) {
        bool stop = true;
    }
    if (boardPos.y + maxRow > boardSize.y) {
        boardPos.y = boardSize.y - 1 - (dimension - maxRow);
    }
    return sf::Vector2f();
}