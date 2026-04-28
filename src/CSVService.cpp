#include "CSVService.h"
#include "loan.h"
#include <string>
#include <vector>
#include <fstream>

namespace CSVService {
    void generateFile(std::vector<Payment*> payments, std::string fileName)
    {
        std::fstream fout;

        fout.open(fileName, std::ios::out);

        for (Payment* p : payments) {
            fout << p->toCSVRow() << std::endl;
        }
    }
}

