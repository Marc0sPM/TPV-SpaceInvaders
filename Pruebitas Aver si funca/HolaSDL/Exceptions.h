#pragma once
#include <stdexcept>
#include <SDL.h>
#include <string>

class InvadersError : public std::logic_error {
public:
    InvadersError(const std::string& message) : logic_error(message) {}
};

class SDLError : public InvadersError {
public:
    SDLError(const std::string& message) : InvadersError("SDL error: " + message + SDL_GetError()) {}
};

class FileNotFoundError : public InvadersError {
public:
    FileNotFoundError(const std::string& filename) : InvadersError("File not found: " + filename) {}
};

class FileFormatError : public InvadersError {
public:
    FileFormatError(const std::string& message) : InvadersError(message) {}
};
