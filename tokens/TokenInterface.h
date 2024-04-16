//
// Created by notnuff on 09.03.24.
//

#ifndef NUFF_MDVERTER_TOKENINTERFACE_H
#define NUFF_MDVERTER_TOKENINTERFACE_H

#include <string>

class TokenInterface {

public:
    virtual char* getTokenStart() = 0;
    virtual char* getTokenEnd() = 0;
    virtual bool isLeft() = 0;
    virtual bool isRight() = 0;
    virtual std::string getReplacement() = 0;
};


#endif //NUFF_MDVERTER_TOKENINTERFACE_H
