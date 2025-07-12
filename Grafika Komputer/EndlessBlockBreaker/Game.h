#pragma once
#include "GameObject.h"
#include <vector>

// Struktur untuk mendefinisikan area permainan
struct GameArea {
    float left, right, top, bottom;
};

class Game {
public:
    // Konstruktor
    Game();
    ~Game();

    // Fungsi utama
    void update();
    void render();
    void reset();

    // Fungsi input handler
    void handleMouse(int x, int y);
    void handleKeyboard(unsigned char key);
    void handleMouseClick(int button, int state, int x, int y);

    // Getter untuk status game
    GameState getState() const;

private:
    // Fungsi helper internal
    void initializeBlocks();
    void updateBalls();
    void updatePowerUps();
    void checkCollisions();
    void checkGameState();
    void activatePowerUp(PowerUpType type);
    bool isRowCleared(float y_coord) const;
    void descendAndRespawn();

    // Fungsi helper untuk menggambar
    void drawPaddle();
    void drawBalls();
    void drawBlocks();
    void drawPowerUps();
    void drawUI();
    void drawScore();
    void drawBorders();

    // Variabel anggota (state game)
    GameState m_currentState;
    GameArea m_gameArea;
    Paddle m_paddle;
    std::vector<Ball> m_balls;
    std::vector<Block> m_blocks;
    std::vector<PowerUpItem> m_activePowerUps;
    int m_score;
    int m_highScore;

    // Variabel anggota untuk properti balok
    int m_blockCountX;
    int m_blockCountY;
    float m_blockWidth;
    float m_blockHeight;
    float m_blockSpacing;
};
