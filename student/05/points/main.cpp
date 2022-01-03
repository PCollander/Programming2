#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
    string tiedoston_nimi = "";
    cout << "Input file: ";
    getline(cin, tiedoston_nimi);

    ifstream tiedosto_olio(tiedoston_nimi);
    if ( not tiedosto_olio ) {
        cout << "Error! The file " << tiedoston_nimi << " cannot be opened." << endl;
        return 1;
    } else {
        string rivi;
        map<string, int> pistelista;
        while ( getline(tiedosto_olio, rivi) ) {

            string nimi = rivi.substr(0, rivi.find(":"));
            int pisteet = stoi(rivi.substr(rivi.find(":") + 1));

            if (pistelista.find(nimi) == pistelista.end()){
                pistelista.insert({nimi, pisteet});

            }else{
                pistelista.at(nimi) += pisteet;
            }
        }
        cout << "Final scores: " << endl;
        for ( auto tietopari : pistelista ) {
            cout << tietopari.first << ": "<< tietopari.second << endl;
        }
        tiedosto_olio.close();
    }
}
