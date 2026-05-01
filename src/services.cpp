#include "services.h"
#include "loan.h"
#include <string>
#include <vector>
#include <fstream>

void CSVService::generateFile(std::vector<Payment*> payments, std::string fileName)
{
    std::fstream fout;

    fout.open(fileName, std::ios::out);

    for (Payment* p : payments) {
        fout << p->toCSVRow() << std::endl;
    }
}


namespace HTMLService {

}

ServerService::UserInput::UserInput(float principal, int term, float APR) {
    this->principal = principal;
    this->term = term;
    this->APR = APR;
}

std::string ServerService::buildTable(UserInput* input)
{
    if (input == nullptr)
    {
        return R"(
        <p>Nothing here yet :)</p>
        )";
    }

    Loan l = Loan(input->principal, input->term, input->APR);
	std::vector<Payment*> payments = l.generatePayments();

    std::string data;

	for (Payment* p : payments)
	{
		data+=p->toHTMLRow();
	}


    return R"(
    <table>
        <tr>
            <th>Payment #</th>
            <th>Payment $</th>
            <th>Principal</th>
            <th>Interest</th>
            <th>Balence</th>
        </tr>)"
        + data +
        R"(</table>
    )";
}

std::string ServerService::buildPage(UserInput* input) {
    std::string table = buildTable(input);
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
        <table>)" + 
            table + 
        R"(</table>
        </body></html>
    )";
}

void ServerService::run() {
    httplib::Server svr;
    UserInput* input = nullptr;

    svr.Get("/", [&input](const httplib::Request&, httplib::Response& res) {
        res.set_content(ServerService::buildPage(input), "text/html");
    });

    svr.Post("/add", [&input](const httplib::Request& req, httplib::Response& res) {
        float principal = stof(req.get_param_value("principal"));
        int term = stof(req.get_param_value("term"));
        float APR = stof(req.get_param_value("APR"));
        res.set_redirect("/");

        input = new UserInput(principal, term, APR);
    });

    svr.listen("0.0.0.0", 8080);
}