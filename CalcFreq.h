#include <fstream>
#include <map>
#include <string>
#include <iomanip>

class CalcFrq
{
    // sum of all frequencies - for validation
    double sum;
    std::map<char,double>fr;

public:
    CalcFrq();
    std::map<char, double> getFre();
    void calcFr(int nrLit, std::map<char,int> ap);
    void writeFr(std::string file);
};
