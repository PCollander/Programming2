#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <numeric>
#include <algorithm>

using namespace std;

int main()
{
    string tiedoston_nimi = "";
    cout << "Input file: ";
    getline(cin, tiedoston_nimi);

    ifstream tiedosto_olio(tiedoston_nimi);
    if (not tiedosto_olio) {
        cout << "Error! The file " << tiedoston_nimi << " cannot be opened." << endl;
        return 1;
    }
    else {
        string merkkijono;
        int rivinro = 1;
        string rivi;
        map<string, vector<int>> sanalista;

        //käydään läpi koko riedosto
        while (getline(tiedosto_olio, rivi))
        {
            //parsitaan sanat
            stringstream ss(rivi);
            istream_iterator<string> begin(ss);
            istream_iterator<string> end;
            vector<std::string> vstrings(begin, end);

            //lisätään kaikki sanat ja niiden rivinumerot sanalistaan
            for (string sana : vstrings)
            {
                sanalista[sana].push_back(rivinro);
            }
            ++rivinro;
        }

        //käydään sanaparit sana kerrallaan läpi
        for (auto sanalistapari : sanalista)
        {
            string sana = sanalistapari.first;
            vector<int> rivinro_vektori = sanalistapari.second;
            int sanamaara = rivinro_vektori.size();

            sort(rivinro_vektori.begin(), rivinro_vektori.end());
            rivinro_vektori.erase(unique(rivinro_vektori.begin(), rivinro_vektori.end()), rivinro_vektori.end());

            string rivinumeroteksti;
            for (auto iter = rivinro_vektori.begin(); iter != rivinro_vektori.end(); ++iter)
                rivinumeroteksti = rivinumeroteksti + to_string(*iter) + ", ";
            rivinumeroteksti = rivinumeroteksti.substr(0, rivinumeroteksti.size() - 2);

            cout << sana + " " + to_string(sanamaara) + ": " + rivinumeroteksti << endl;
        }

    }
}
