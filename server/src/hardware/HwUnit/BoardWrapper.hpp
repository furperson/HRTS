#pragma once

//обёртка , абстракция над физическим устройством(плате fpga)


enum class BoardState {Monday = 1, Mon = 1, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };

class BoardWrapper
{
private:
    BoardState boardState;
    /* data */
public:
    BoardWrapper(/* args */);
    ~BoardWrapper();
};
