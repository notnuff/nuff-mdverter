#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <regex>
#include "CommandsParser.h"
#include "IOfiles/OutputInterface.h"
#include "IOfiles/FileOutput.h"
#include "IOfiles/StandardTerminalOutput.h"

struct Token {
    int _beginI;
    int _length;
//    std::string token;
    std::string replacement;

    Token(int begin, int length) : _beginI(begin), _length(length) {};

    Token() : Token(-1, 0) {};

    virtual std::string Replacement() { return replacement; };

    virtual void Replacement(std::string re) {};

    //virtual std::string GetReplacementLeft();
    //virtual std::string GetReplacementRight();
    //virtual ~Token()=default;
};

struct TokenRegex : Token {
    virtual std::regex GetRegex() = 0;
};

struct TokenBold : TokenRegex {

    const std::regex re{R"(\*\*)"};

    std::regex GetRegex() override {
        return re;
    };

//    std::string GetReplacementLeft() override {
//        return repLeft;
//    };
//    std::string GetReplacementRight() override {
//        return repRight;
//    };
private:
    std::string repLeft = "<b>";
    std::string repRight = "</b>";
};

struct TokenItalic : TokenRegex {

    const std::regex re{R"(\_)"};

    std::regex GetRegex() override {
        return re;
    };
};

struct TokenMonospaced : TokenRegex {

    const std::regex re{R"(\`)"};

    std::regex GetRegex() override {
        return re;
    };
};

struct TokenSpace : TokenRegex {

    const std::regex re{R"(\s)"};

    std::regex GetRegex() override {
        return re;
    };
};

struct TokenString : Token {

    explicit TokenString(const std::string &line) : Token(0, int(line.size())) {
        replacement = line;
    }

};

static const std::vector<TokenRegex *> tokensPatterns{
        new TokenBold(),
        new TokenItalic(),
        new TokenMonospaced(),
        new TokenSpace()
        //std::regex (R"(\```)")
};


void tokenizer(const std::string &line,
               const std::regex &searchPattern,
               std::vector<std::unique_ptr<Token>> &tokens) {

    std::string str(line);

    std::sregex_iterator iterator(str.begin(), str.end(), searchPattern);
    std::sregex_iterator endIterator;

    while (iterator != endIterator) {
        std::smatch match = *iterator;
        auto token = std::make_unique<Token>(match.position(), match.length());
        tokens.emplace_back(std::move(token));
        ++iterator;
    }
}

void concatenator(const std::string &line,
                  std::vector<std::unique_ptr<Token>> &tokens,
                  std::vector<std::unique_ptr<Token>> &parsedTokens) {
    // Sort tokens based on the beginning iterator
    if (tokens.empty()) {
        std::unique_ptr<Token> lineToken = std::make_unique<TokenString>(line);
        parsedTokens.emplace_back(std::move(lineToken));
        return;
    }

    std::sort(tokens.begin(), tokens.end(), [](const std::unique_ptr<Token> &a, const std::unique_ptr<Token> &b) {
        return a->_beginI < b->_beginI;
    });

    std::unique_ptr<Token> endOfLineToken = std::make_unique<Token>(line.length() - 1, 0);
    tokens.emplace_back(std::move(endOfLineToken));

    for (int i = 0, nextI = 0; i < tokens.size(); i++) {
        if (tokens[i]->_length == 0) continue;

        auto currentI = nextI;
        nextI = tokens[i]->_beginI;

        auto substr = line.substr(currentI, nextI - currentI);

        //std::cout << '-' << substr << '-' << std::endl;

        if (!substr.empty()) parsedTokens.emplace_back(std::make_unique<TokenString>(substr));

        currentI = nextI;
        nextI += tokens[i]->_length;

        substr = line.substr(currentI, tokens[i]->_length);
        //std::cout << '-' << substr << '-' << std::endl;

        if (!substr.empty()) parsedTokens.emplace_back(std::make_unique<TokenString>(substr));
    }
}

void replacer(const std::string &line,
              std::vector<std::unique_ptr<Token>> &concatenatedStrings,
              std::vector<std::string> &parsedTokens) {

}

int main(int argc, char *argv[]) {


    CommandsParser cli;
    std::unique_ptr<OutputInterface> output;
    try {
        cli.parseCLI(argc, argv);
    } catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << "usage: nuff-mdverter <input> [--out|-o] <output> ...\n";
        return EXIT_FAILURE;
    }

    std::ifstream inputFile(cli.getInPath());
    if (inputFile.bad()) {
        std::cerr << "Input error: input file does not exists";
        return EXIT_FAILURE;
    }

    if (cli.isOutFlag()) {
        output = std::make_unique<FileOutput>();
        try {
            output->open(cli.getOutPath());
        } catch (std::exception &err) {
            std::cerr << "Output file error: ";
            std::cerr << &err;
            return EXIT_FAILURE;
        }
    } else {
        output = std::make_unique<StandardTerminalOutput>();
    }

    std::stringstream inputBuffer;
    std::stringstream outputBuffer;

    inputBuffer << inputFile.rdbuf();
    inputFile.close();

    std::string line;
    while (getline(inputBuffer, line)) {

        std::vector<std::unique_ptr<Token>> tokens;


        for (const auto &t: tokensPatterns)
            tokenizer(line, t->GetRegex(), tokens);

        std::vector<std::unique_ptr<Token>> concatenatedStrings;
        concatenator(line, tokens, concatenatedStrings);

        for (const auto &t: concatenatedStrings) {
            auto re = t->Replacement() == "\n" ? "n" : t->Replacement();
            std::cout << re << "\n";
        }
    }
}



