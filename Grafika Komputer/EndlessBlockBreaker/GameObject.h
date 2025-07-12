#pragma once
#include "Constants.h"
#include <vector>

// Struktur untuk Papan (Paddle)
struct Paddle {
    float x, y;
    float w, h;
};

// Struktur untuk Bola
struct Ball {
    float x, y;
    float radius;
    float velX, velY;
};

// Struktur untuk Balok
struct Block {
    float x, y;
    float w, h;
    bool isAlive;
    PowerUpType hasPowerUp;
};

// Struktur untuk item power-up yang jatuh
struct PowerUpItem {
    float x, y;
    float size;
    bool isAlive;
    PowerUpType type;
};
