#include "BoardWrapper.hpp"

BoardWrapper::BoardWrapper(int port) : port(port), boardState(BoardState::IDLE) {};
BoardWrapper::BoardWrapper(int port, std::string boardName)
    : port(port), boardState(BoardState::IDLE), boardName(boardName) {};

BoardWrapper::~BoardWrapper() {};