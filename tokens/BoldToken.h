//
// Created by notnuff on 09.03.24.
//

#ifndef NUFF_MDVERTER_BOLDTOKEN_H
#define NUFF_MDVERTER_BOLDTOKEN_H


#include "TokenInterface.h"

class BoldToken : public TokenInterface{
private:
    const std::string replacement = "<b>";
    char* begin;
    char* end;
    bool left;
    bool right;

public:
    char* getTokenStart() override;
    char* getTokenEnd() override;
    bool isLeft();
    bool isRight();
    std::string getReplacement() override;
};


#endif //NUFF_MDVERTER_BOLDTOKEN_H
