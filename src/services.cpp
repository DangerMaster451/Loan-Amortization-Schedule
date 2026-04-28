#include "services.h"
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

namespace HTMLService {

}

namespace ServerService {

    std::string buildPage() {
        return R"(
            <!DOCTYPE html>
            <html><body>
            <p>Loan Amortization App</p>
            <form action="/add" method="POST">
                <label for="principal">Principal:</label><br>
                <input type="number" id="principal" name="principal"><br>
                <label for="term">Term (Years):</label><br>
                <input type="number" id="term" name="term"><br>
                <label for="APR">APR:</label><br>
                <input type="number" id="APR" name="APR" min=0 max=100 step=0.01><br>
                <input type="submit" value="Submit">
            </form>
            </body></html>
        )";
    }

    void run() {
        httplib::Server svr;

        svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
            res.set_content(ServerService::buildPage(), "text/html");
        });

        svr.Post("/add", [](const httplib::Request& req, httplib::Response& res) {
            std::cout << "Principal: " << req.get_param_value("principal") << std::endl;
            std::cout << "Term: "      << req.get_param_value("term")      << std::endl;
            std::cout << "APR: "       << req.get_param_value("APR")       << std::endl;

            res.set_redirect("/");
        });

        svr.listen("0.0.0.0", 8080);
    }
}

