#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>

using namespace std;

bool key_tarkistus(string key){
    string::size_type i = 0;
    i = key.length();
    if (i != 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return false;
    }
    for (int k = 0; k <= 25; ++k) {
        if (islower(key[k]) == false){
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return false;
        }
    }
    for (int l = 97; l <= 122; ++l) {
        if (key.find(l) == string::npos) {
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            return false;
        }
    }
    return true;
}

bool salattava_tarkistus(string salattava){
    for (int i = 0; salattava.length(); ++i){
        if ((isupper(salattava.at(i)) or isdigit(salattava.at(i)))){
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return false;
        }else{
            return true;
}
}
    return true;
}

string palauta_ascii(string teksti, string key){
    string tulos = "";
    for (long unsigned int i = 0; i < teksti.length(); i++){
        int merkin_ascii_arvo = static_cast< int >( teksti[i] );
            tulos += key.at(merkin_ascii_arvo - 97);

    }
    return tulos;
}


int main()
{
    string key = "";
    cout << "Enter the encryption key: ";
    getline(cin, key);

    if (key_tarkistus (key)){
        string salattava = "";
        cout << "Enter the text to be encrypted: ";
        getline(cin, salattava);
                if (salattava_tarkistus(salattava)){
                    cout << "Encrypted text: " << palauta_ascii(salattava, key) << endl;
        }

    }
    else

    return 1;
}
