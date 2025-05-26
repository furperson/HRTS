#include "BoardWrapper.hpp"

BoardWrapper::BoardWrapper(int port):port(port),boardState(BoardState::IDLE){};

BoardWrapper::~BoardWrapper(){};