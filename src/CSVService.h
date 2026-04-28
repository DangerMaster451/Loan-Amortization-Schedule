#pragma once
#include "loan.h"
#include <string>
#include <vector>

namespace CSVService {
    void generateFile(std::vector<Payment*> payments, std::string fileName);
}