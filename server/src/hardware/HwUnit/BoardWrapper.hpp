#pragma once

//обёртка , абстракция над физическим устройством(плате fpga)


enum class BoardState {IDLE,IN_WORK,DISABLED};

class BoardWrapper
{
private:
    BoardState boardState;
    int port;
    //PLACEHOLDER 

public:
    BoardWrapper()=delete;
    BoardWrapper(int);
    ~BoardWrapper();
};
