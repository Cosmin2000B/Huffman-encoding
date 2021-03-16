#include "CalcFreq.h"

CalcFrq::CalcFrq()
{
    this->sum = 0;

    for(int i = 0; i<26; ++i)
        fr.insert(std::pair<char,int>('a' + i, 0));
}

std::map<char, double> CalcFrq::getFre()
{
    return this->fr;
}

void CalcFrq::calcFr(int nrLit, std::map<char,int> ap)
{
    int k = 97;

    for(std::map<char,int>::iterator i = ap.begin(); i != ap.end(); ++i)
        fr.at(k++) = (double)(i->second)/nrLit;
}

void CalcFrq::writeFr(std::string file)
{
    std::ofstream out (file);

    out << "Letter frequency:" << std::endl << std::endl;
    out << "Letter\tFrequency of Apparitions" << std::endl;

    for(std::map<char,double>::iterator i = fr.begin(); i != fr.end(); ++i)
    {
           out << '\t' << i->first << '\t' << '\t' << '\t'
               << std::setprecision(3) << i->second << std::endl;

           sum += i->second;
    }

    out <<  std::endl;
    out << "The sum of all frequencies is: " << sum <<
        " ( sum = 1 => the process is valid )";

    // finnished writing
    out.close();
}
