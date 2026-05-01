#pragma once
#include "loan.h"
#include "httplib.h"
#include <string>
#include <vector>

namespace CSVService {
    void generateFile(std::vector<Payment*> payments, std::string fileName);
}

namespace HTMLService {

}

namespace ServerService {
    struct UserInput {
        float principal;
        int term;
        float APR;
        UserInput() = default;
        UserInput(float principal, int term, float APR);
    };

    void run();
    std::string buildPage(UserInput* input);
    std::string buildTable(UserInput* input);   
}