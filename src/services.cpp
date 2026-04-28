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

    std::string buildPage()
    {
        std::string html = R"(
                <!DOCTYPE html>
                <html><body>
                <p>Loan Amoritization App</p>
                <form>
                    <label for="principal">Principal:</label><br>
                    <input type="number" id="principal" name="principal"><br>
                    <label for="term">Term (Years):</label><br>
                    <input type="number" id="term" name="term"><br>
                    <label for="APR">APR:</label><br>
                    <input type="number" id="APR" name="APR"><br>
                    <input type="submit" value="Submit">
                </form>
                </body></html>
            )";
        return html;
    }



    void run()
    {
        httplib::Server svr;

        svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
            std::string html = buildPage();
            res.set_content(html, "text/html");
        });
        
        svr.listen("0.0.0.0", 8080);
    }
}

