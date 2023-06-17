#pragma once

#include <SFML/Graphics.hpp>
#include <assert.h>


class Tetromino
{
    enum class Rotation
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };
public:

    Tetromino(const bool* shape, const int dimension, const sf::Color& color, const sf::Vector2f& pos);
    virtual ~Tetromino() {}

    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void RotateClockwise();
    void RotateCounterClockwise();

    void Update(std::vector<std::vector<unsigned char>>& matrix);

    sf::Color GetColor() const { return color; }

protected:
    const bool*  shape;
    const int    dimension;
    sf::Color    color;
    sf::Vector2f boardSize;
    sf::Vector2f boardPos;
    Rotation     currentRotation;
  //  std::vector<std::vector<unsigned char>>* matrix;

    std::vector<std::vector<unsigned char>> GetShape();
    sf::Vector2f CheckBoundary(std::vector<std::vector<unsigned char>> matrix,
                               const std::vector<std::vector<unsigned char>>& shape);

};

class Straight : public Tetromino
{
public:
    Straight(const sf::Vector2f& pos) : Tetromino(shape, dimension, sf::Color::Cyan, pos)
    {
        static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
    }

private:
    // https://stackoverflow.com/questions/13865842/does-static-constexpr-variable-inside-a-function-make-sense
    // static constexpr will be initialized only once
    static constexpr bool shape[] = { 0,0,0,0,
                                      1,1,1,1,
                                      0,0,0,0,
                                      0,0,0,0 };
    static constexpr int dimension = 4;
};

class Square : public Tetromino
{
public:
    Square(const sf::Vector2f& pos) : Tetromino(shape, dimension, sf::Color::Yellow, pos)
    {
        static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
    }

private:
    static constexpr bool shape[] = { 1,1,
                                      1,1 };
    static constexpr int dimension = 2;
};

class Tee : public Tetromino
{
public:
    Tee(const sf::Vector2f& pos) : Tetromino(shape, dimension, sf::Color::Magenta, pos)
    {
        static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
    }

private:
    static constexpr bool shape[] = { 0,1,0,
                                      1,1,1,
                                      0,0,0 };
    static constexpr int dimension = 3;
};

class Jay : public Tetromino
{
public:
    Jay(const sf::Vector2f& pos) : Tetromino(shape, dimension, sf::Color::Blue, pos)
    {
        static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
    }

private:
    static constexpr bool shape[] = { 1,0,0,
                                      1,1,1,
                                      0,0,0 };
    static constexpr int dimension = 3;
};

class El : public Tetromino
{
public:
    El(const sf::Vector2f& pos) : Tetromino(shape, dimension, sf::Color(255, 127, 80), pos)
    {
        static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
    }

private:
    static constexpr bool shape[] = { 0,0,1,
                                      1,1,1,
                                      0,0,0 };
    static constexpr int dimension = 3;
};

class SkewS : public Tetromino
{
public:
    SkewS(const sf::Vector2f& pos) : Tetromino(shape, dimension, sf::Color::Green, pos)
    {
        static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
    }

private:
    static constexpr bool shape[] = { 0,1,1,
                                      1,1,0,
                                      0,0,0 };
    static constexpr int dimension = 3;
};

class SkewZ : public Tetromino
{
public:
    SkewZ(const sf::Vector2f& pos) : Tetromino(shape, dimension, sf::Color::Red, pos)
    {
        static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
    }

private:
    static constexpr bool shape[] = { 1,1,0,
                                      0,1,1,
                                      0,0,0 };
    static constexpr int dimension = 3;
};