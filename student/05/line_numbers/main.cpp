#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string tiedoston_nimib = "";
    string tiedoston_nimi = "";
    cout << "Input file: ";
    getline(cin, tiedoston_nimi);
    cout << "Output file: " ;
    getline(cin, tiedoston_nimib);

    ifstream tiedosto_olio(tiedoston_nimi);
    if ( not tiedosto_olio ) {
        cout << "Error! The file " << tiedoston_nimi << " cannot be opened." << endl;
        return 1;
    } else {
        ofstream tiedosto_oliob(tiedoston_nimib);
        string rivi;
        int i = 1;
        while ( getline(tiedosto_olio, rivi) ) {
            tiedosto_oliob << i << " " << rivi<< endl;
            i += 1;
        }
        tiedosto_olio.close();
        tiedosto_oliob.close();
    }
}
