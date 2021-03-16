#include<map>
#include<string>
#include<fstream>

class Reader
{
    // numarul de litere prezente in text
    int litNr;

    // mapa pentru retinerea aparitiilor, cheia este litera
    std::map<char,int>ap;

    // file to write results
    std::ofstream out;

    // actualizing letter apparitions
    void actAp(char c);

public:
    Reader();

    int getLitNr();
    std::map<char,int> getAp();

    // reading from a text file
    void read(std::string file);

    //show letter appearance
    void showAp(std::string file);
};
