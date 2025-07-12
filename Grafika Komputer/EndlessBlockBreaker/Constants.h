#pragma once

// --- Konfigurasi Global ---
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Status permainan
enum GameState {
    READY,
    PLAYING,
    LOST
};

// Tipe-tipe Power-up
enum PowerUpType {
    NONE,
    PADDLE_GROW,
    MULTI_BALL,
    SPEED_UP
};
