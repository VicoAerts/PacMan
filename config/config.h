/**
 * @file config.h
 * @brief Configuration constants for the Pacman game.
 */

#pragma once

namespace config {

// --- Window / rendering ---
constexpr unsigned int window_width = 778;
constexpr unsigned int window_height = 900;
constexpr unsigned int max_fps = 60;
constexpr unsigned int UI_TOP = 80;
constexpr unsigned int UI_BOTTOM = 80;
constexpr unsigned int UI_LEFT = 50;
constexpr unsigned int UI_RIGHT = 50;

// --- Gameplay ---
constexpr float pacman_speed = 0.3f;
constexpr float ghost_base_speed = 0.25f;
constexpr double fear_base_duration_s = 6.0;

} // namespace config