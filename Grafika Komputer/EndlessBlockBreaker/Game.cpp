#include "Game.h"
#include "Constants.h"
#include <GL/glut.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

// --- Konstruktor dan Inisialisasi ---

Game::Game() {
    srand(time(0));
    m_highScore = 0;

    m_gameArea.left = 50.0f;
    m_gameArea.right = SCREEN_WIDTH - 50.0f;
    m_gameArea.top = SCREEN_HEIGHT - 70.0f;
    m_gameArea.bottom = 0.0f;

    // Inisialisasi properti balok
    m_blockCountX = 11;
    m_blockCountY = 5;
    m_blockWidth = 50.0f;
    m_blockHeight = 25.0f;
    m_blockSpacing = 5.0f;

    reset();
}

Game::~Game() {}

void Game::reset() {
    if (m_score > m_highScore) {
        m_highScore = m_score;
    }

    m_currentState = READY;
    m_score = 0;
    m_paddle = {SCREEN_WIDTH / 2.0f, 30.0f, 120.0f, 20.0f};

    m_balls.clear();
    m_activePowerUps.clear();

    Ball startBall;
    startBall.radius = 10.0f;
    startBall.x = m_paddle.x;
    startBall.y = m_paddle.y + m_paddle.h / 2 + startBall.radius;
    startBall.velX = 0;
    startBall.velY = 0;
    m_balls.push_back(startBall);

    initializeBlocks();
}

void Game::initializeBlocks() {
    m_blocks.clear();

    float gameAreaWidth = m_gameArea.right - m_gameArea.left;
    float totalBlockWidth = m_blockCountX * (m_blockWidth + m_blockSpacing) - m_blockSpacing;
    float sideGap = (gameAreaWidth - totalBlockWidth) / 2.0f;
    float startX = m_gameArea.left + sideGap;
    float startY = m_gameArea.top - 70.0f;

    for (int i = 0; i < m_blockCountY; ++i) {
        for (int j = 0; j < m_blockCountX; ++j) {
            Block b;
            b.x = startX + j * (m_blockWidth + m_blockSpacing);
            b.y = startY - i * (m_blockHeight + m_blockSpacing);
            b.w = m_blockWidth;
            b.h = m_blockHeight;
            b.isAlive = true;
            b.hasPowerUp = (rand() % 5 == 0) ? (PowerUpType)((rand() % 3) + 1) : NONE;
            m_blocks.push_back(b);
        }
    }
}

// --- Logika Utama ---

void Game::update() {
    if (m_currentState == READY) {
        if (!m_balls.empty()) {
            m_balls.front().x = m_paddle.x;
            m_balls.front().y = m_paddle.y + m_paddle.h / 2 + m_balls.front().radius;
        }
        return;
    }

    if (m_currentState != PLAYING) {
        return;
    }
    updateBalls();
    updatePowerUps();
    checkCollisions();
    checkGameState();
}

void Game::updateBalls() {
    for (auto& ball : m_balls) {
        ball.x += ball.velX;
        ball.y += ball.velY;
    }
}

void Game::updatePowerUps() {
    for (auto& item : m_activePowerUps) {
        if (item.isAlive) {
            item.y -= 2.0f;
            if (item.y < 0) item.isAlive = false;
        }
    }
}

void Game::checkCollisions() {
    for (auto& ball : m_balls) {
        if ((ball.x + ball.radius > m_gameArea.right && ball.velX > 0) ||
            (ball.x - ball.radius < m_gameArea.left && ball.velX < 0)) {
            ball.velX = -ball.velX;
        }
        if (ball.y + ball.radius > m_gameArea.top && ball.velY > 0) {
            ball.velY = -ball.velY;
        }

        if (ball.y - ball.radius < m_paddle.y + m_paddle.h / 2 && ball.y + ball.radius > m_paddle.y - m_paddle.h / 2 &&
            ball.x > m_paddle.x - m_paddle.w / 2 && ball.x < m_paddle.x + m_paddle.w / 2) {
            if (ball.velY < 0) {
                ball.velY = -ball.velY;
                float hitPos = (ball.x - m_paddle.x) / (m_paddle.w / 2);
                ball.velX = hitPos * 5.0f;
            }
        }

        for (auto& block : m_blocks) {
            if (block.isAlive && ball.x + ball.radius > block.x && ball.x - ball.radius < block.x + block.w &&
                ball.y + ball.radius > block.y && ball.y - ball.radius < block.y + block.h) {
                block.isAlive = false;
                ball.velY = -ball.velY;

                m_score += 10;

                if (isRowCleared(block.y)) {
                    m_score += 100;
                    descendAndRespawn();
                }

                if (block.hasPowerUp != NONE) {
                    m_activePowerUps.push_back({block.x + block.w / 2, block.y + block.h / 2, 10.0f, true, block.hasPowerUp});
                }
                break;
            }
        }
    }

    for (auto& item : m_activePowerUps) {
        if (item.isAlive && item.x > m_paddle.x - m_paddle.w / 2 && item.x < m_paddle.x + m_paddle.w / 2 &&
            item.y > m_paddle.y - m_paddle.h / 2 && item.y < m_paddle.y + m_paddle.h / 2) {
            item.isAlive = false;
            activatePowerUp(item.type);
        }
    }

    m_balls.erase(std::remove_if(m_balls.begin(), m_balls.end(), [](const Ball& b){ return b.y - b.radius < 0; }), m_balls.end());
    m_activePowerUps.erase(std::remove_if(m_activePowerUps.begin(), m_activePowerUps.end(), [](const PowerUpItem& p){ return !p.isAlive; }), m_activePowerUps.end());
}


void Game::checkGameState() {
    if (m_balls.empty() && m_currentState == PLAYING) {
        m_currentState = LOST;
    }

    for (const auto& block : m_blocks) {
        if (block.isAlive && block.y < m_paddle.y + m_paddle.h) {
            m_currentState = LOST;
            return;
        }
    }
}

bool Game::isRowCleared(float y_coord) const {
    for (const auto& block : m_blocks) {
        if (std::abs(block.y - y_coord) < 1.0f && block.isAlive) {
            return false;
        }
    }
    return true;
}

void Game::descendAndRespawn() {
    for (auto& block : m_blocks) {
        block.y -= (m_blockHeight + m_blockSpacing);
    }

    float current_top_y = -1000.0f;
    for(const auto& block : m_blocks) {
        if(block.y > current_top_y) {
            current_top_y = block.y;
        }
    }

    float new_row_y = current_top_y + m_blockHeight + m_blockSpacing;

    float gameAreaWidth = m_gameArea.right - m_gameArea.left;
    float totalBlockWidth = m_blockCountX * (m_blockWidth + m_blockSpacing) - m_blockSpacing;
    float sideGap = (gameAreaWidth - totalBlockWidth) / 2.0f;
    float startX = m_gameArea.left + sideGap;

    int respawned_count = 0;
    for (auto& block : m_blocks) {
        if (!block.isAlive) {
            block.x = startX + respawned_count * (m_blockWidth + m_blockSpacing);
            block.y = new_row_y;
            block.isAlive = true;
            block.hasPowerUp = (rand() % 5 == 0) ? (PowerUpType)((rand() % 3) + 1) : NONE;

            respawned_count++;
            if (respawned_count >= m_blockCountX) {
                break;
            }
        }
    }
}


void Game::activatePowerUp(PowerUpType type) {
    switch (type) {
        case PADDLE_GROW:
            m_paddle.w = std::min(200.0f, m_paddle.w + 40.0f);
            break;
        case MULTI_BALL: {
            if (!m_balls.empty()) {
                size_t currentBallCount = m_balls.size();
                for (size_t i = 0; i < currentBallCount; ++i) {
                    Ball newBall = m_balls[i];
                    newBall.velX = -newBall.velX;
                    m_balls.push_back(newBall);
                }
            }
            break;
        }
        case SPEED_UP: {
            const float MAX_SPEED = 12.0f;
            for (auto& ball : m_balls) {
                float currentSpeed = std::sqrt(ball.velX * ball.velX + ball.velY * ball.velY);
                if (currentSpeed < MAX_SPEED) {
                    ball.velX *= 1.2f;
                    ball.velY *= 1.2f;
                }
            }
            break;
        }
        default: break;
    }
}

// --- Logika Menggambar ---

void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (m_currentState == PLAYING || m_currentState == READY) {
        drawBorders();
        drawPaddle();
        drawBalls();
        drawBlocks();
        drawPowerUps();
    } else {
        drawUI();
    }
    drawScore();
    glutSwapBuffers();
}

void Game::drawBorders() {
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(m_gameArea.left, m_gameArea.bottom);
        glVertex2f(m_gameArea.left, m_gameArea.top);
        glVertex2f(m_gameArea.right, m_gameArea.top);
        glVertex2f(m_gameArea.right, m_gameArea.bottom);
    glEnd();
}

void Game::drawScore() {
    char scoreText[100];
    sprintf(scoreText, "Skor: %d   Skor Tertinggi: %d", m_score, m_highScore);

    glColor3f(1.0f, 1.0f, 1.0f);
    float textWidth = glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)scoreText);
    glRasterPos2f((SCREEN_WIDTH - textWidth) / 2, SCREEN_HEIGHT - 40);

    for (const char* c = scoreText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void Game::drawPaddle() { glColor3f(0.8f, 0.8f, 1.0f); glRectf(m_paddle.x - m_paddle.w / 2, m_paddle.y - m_paddle.h / 2, m_paddle.x + m_paddle.w / 2, m_paddle.y + m_paddle.h / 2); }
void Game::drawBalls() { for (const auto& ball : m_balls) { glColor3f(1.0f, 0.5f, 0.5f); glPushMatrix(); glTranslatef(ball.x, ball.y, 0); glBegin(GL_TRIANGLE_FAN); glVertex2f(0.0f, 0.0f); for (int i = 0; i <= 20; i++) { float angle = 2.0f * 3.14159f * float(i) / 20.0f; glVertex2f(ball.radius * cosf(angle), ball.radius * sinf(angle)); } glEnd(); glPopMatrix(); } }
void Game::drawBlocks() { for (const auto& block : m_blocks) { if (block.isAlive) { if (block.hasPowerUp != NONE) glColor3f(1.0f, 0.8f, 0.2f); else glColor3f(0.5f, 1.0f, 0.5f); glRectf(block.x, block.y, block.x + block.w, block.y + block.h); } } }
void Game::drawPowerUps() { for (const auto& item : m_activePowerUps) { if (item.isAlive) { switch (item.type) { case PADDLE_GROW: glColor3f(0.5f, 0.5f, 1.0f); break; case MULTI_BALL: glColor3f(1.0f, 1.0f, 0.5f); break; case SPEED_UP: glColor3f(1.0f, 0.5f, 1.0f); break; default: glColor3f(1.0f, 1.0f, 1.0f); break; } glRectf(item.x - item.size, item.y - item.size, item.x + item.size, item.y + item.size); } } }

void Game::drawUI() {
    if (m_currentState == LOST) {
        const char* text1 = "GAME OVER";
        const char* text2 = "Tekan 'R' untuk Mulai Ulang";

        glColor3f(1.0f, 1.0f, 1.0f);

        glRasterPos2f(SCREEN_WIDTH / 2.0f - 80.0f, SCREEN_HEIGHT / 2.0f);
        for (const char* c = text1; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }

        glRasterPos2f(SCREEN_WIDTH / 2.0f - 120.0f, SCREEN_HEIGHT / 2.0f - 30.0f);
        for (const char* c = text2; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
    }
}

// --- Input Handlers ---

void Game::handleMouse(int x, int y) {
    m_paddle.x = x;
    if (m_paddle.x - m_paddle.w / 2 < m_gameArea.left) m_paddle.x = m_gameArea.left + m_paddle.w / 2;
    if (m_paddle.x + m_paddle.w / 2 > m_gameArea.right) m_paddle.x = m_gameArea.right - m_paddle.w / 2;
}

void Game::handleKeyboard(unsigned char key) {
    if (key == 'r' || key == 'R') {
        if (m_currentState != PLAYING && m_currentState != READY) reset();
    }
}

void Game::handleMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (m_currentState == READY) {
            m_currentState = PLAYING;
            if (!m_balls.empty()) {
                m_balls.front().velX = 2.0f;
                m_balls.front().velY = 5.0f;
            }
        }
    }
}

GameState Game::getState() const {
    return m_currentState;
}
