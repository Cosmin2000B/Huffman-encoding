#include"Reader.h"

Reader::Reader()
{
    this->litNr = 0;

    for(int i = 0; i<26; ++i)
         ap.insert(std::pair<char,int>('a' + i, 0));
}

int Reader::getLitNr()
{
    return this->litNr;
}

std::map<char,int> Reader::getAp()
{
    return this->ap;
}

void Reader::actAp(char c)
{
    // keeping track for low and big letters
    // as the same letter ('A' -> noted as 'a' presence)

    // low letter
    if(97 <= c && c <= 122)
    {
        ap[c]++;
        litNr++;
    }

    // big letter
    if(65 <= c && c <= 90)
    {
        ap[c + 32]++;
        litNr++;
    }
}

void Reader::read(std::string file)
{
    std::ifstream in (file);
    // reading from in at character level
    char c;

    while(in.peek() != EOF)
    {
        in >> c;

        // actualization of the character number of
        // appearences if it's a letter
        actAp(c);
    }

    // finished reading
    in.close();
}

void Reader::showAp(std::string file)
{
    std::ofstream out (file);

    out << "Letter apparition:" << std::endl << std::endl;
    out << "Letter\tNumber of Apparitions" << std::endl;

    for(std::map<char,int>::iterator i = ap.begin(); i != ap.end(); ++i)
           out << '\t' << i->first << '\t' << '\t' << '\t'
               << i->second << std::endl;

    out << "Total number of letters: " << this->litNr;

    // finnished writing
    out.close();
}
