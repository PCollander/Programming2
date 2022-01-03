/* Kauppaketju : Projekti, tehtävä 7.3
 *
 * Kuvaus:
 * Ohjelma lukee tiedoston, jossa on riveittäin puolipilkuin eriteltyjä
 * tietueita, joiden kelvollisuudet ohjelma tarkistaa. Ohjelma tallentaa tiedot
 * sopivaan tietorakenteeseen. Käyttäjällä on mahdollisuus syöttää ennalta
 * määrättyjä komentoja ja ehtoja, joiden mukaan ohjelma tulostaa tiedoston
 * tietoja. Ohjelman on tarkoitus lukea tiedostosta kauppojen tietoja muodossa
 * ketju;liike;tuote;hinta. Käyttäjä voi tarkastella näitä tietoja edellä
 * mainituilla komennoilla. Väärän tai virheellisen komennon tapauksessa ohjelma
 * ilmoittaa asiasta asianmukaisesti käyttäjälle. Ohjelman suoritus päättyy, jos
 * tiedostoa ei saada auki, sen luvussa tapahtuu virhe tai jos käyttäjä syöttää
 * komennon "quit".
 *
 * Tekijä
 * Nimi: Pyry Collander
 * Student number: 255284
 * UserID: collande
 * E-Mail: pyry.collander@tuni.fi
 *
 * */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>
#include <cstring>
#include <cctype>
#include<stdio.h>
#include<stdlib.h>

using namespace std;


struct Tuote{
    // Luodaan tuotteelle struct-rakenne tuotetietojen tallentamista varten
    string tuotenimi;
    double hinta;
};

// Luodaan hyödynnettävät tietorakenteet ja nimetään vakio TUOTE_LOPPU
using Ketjumap = map < string, map < string, vector < Tuote > > >;
using Liikemap = map < string, vector < Tuote > >;
const double TUOTE_LOPPU = -1;

// Funktio tarkistaa tiedoston luettauuden ja palauttaa tiedon onnistumisesta
// tai epäonnistumisesta. Ottaa arvona viitteen ifstreamiin.
bool tiedoston_tarkistus(ifstream &filu)
{
    // Luetaan syötetty tiedostonimi
    string tiedoston_nimi = "";
    cout << "Input file: ";
    getline(cin, tiedoston_nimi);

    // Avataan tiedosto ja testataan sen sopivuus. Palautus onnistumisen mukaan.
    filu.open(tiedoston_nimi, ifstream::in);
    if ( not filu ) {
        cout << "Error: the input file cannot be opened" << endl;
        return false;
    } else {
        return true;
    }
}

// Funktio ottaa arvona käyttäjän syötteen ja merkin, jonka avulla syöte
// katkaistaan ja tallennetaan sitten vektoriin. Funktio palauttaa pilkotun
// syötteen vektorina.
vector<string> split(const string& s, const char delimiter)
{
    vector<string> result;
    string tmp = s;

    // Käydään läpi merkkijonoa läpi, katkaistaan se aina rajoittimen kohdalta
    // kunnes sitä ei enää löydy ja tallennetaan se vektoriin result.
    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    // Lisätään vielä viimeinen merkkijonon pätkä vektoriin, kun rajoitinta ei
    // löydy enää.
    if(not (tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

// Tarkistaa luettavan tiedoston rivien kelvollisuuden. Ottaa parametrina rivin
// ja palauttaa kelvollisuudesta joko true tai false.
bool tarkista_rivit (vector < string > parts){

    if(parts.size() != 4){
        cout << "Error: the input file has an erroneous line" << endl;
        return false;
    }

    // Jos neljännessä osassa on jotain muuta kuin out-of-stock tai
    // desimaaliluku, se ei kelpaa
    if (parts[3] != "out-of-stock"){
        for (auto merkki : parts[3]){
            if (!isdigit(merkki)){
                if (merkki == '.'){
                    continue;
                }else{
                    cout<< "Error: the input file has an erroneous line"<< endl;
                    return false;
                }
            }
        }
    }

    // Tarkistetaan ettei riveillä ole tyhjiä osia
    for (auto part : parts){
        if (part.size() == 0){
            cout << "Error: the input file has an erroneous line"<<endl;
            return false;
        }
        if (part == " "){
            return false;
        }
    }
    return true;
}

//Funktio ottaa parametkikseen luetun ja luettavan tiedoston. Käy tiedoston läpi
// rivi kerrallaan ja tarkistaa ovatko rivit ja niiden tiedot käyttökelpoisia.
// Tallentaa tiedot luotuihin tietorakenteisiin ja palauttaa tietorakenteen,
// johon tiedot on tallenettu.
Ketjumap tiedoston_luku(ifstream &tiedosto_olio)
{
    // Alustetaan muuttujat, joita hyödynetään tiedoston lukemisessa, rivien
    // pilkkomisessa ja tietorakenteen tallentamisessa.
    const char delimiter = ';';
    string rivi;
    Ketjumap ketjurakenne;

    // Pilkotaan tiedoston rivit osiin.
    while ( getline(tiedosto_olio, rivi) ) {
        vector<string> parts = split(rivi, delimiter);

        // Tarkistetaan rivien kelvollisuudet.
        if (not tarkista_rivit(parts)){
            return {};
        }else{

            string ketju = parts[0];
            string liike = parts[1];
            string tuote = parts[2];
            double hinta;

            // Jos tuote on loppu, mutta olemassa, käytetään siitä TUOTE_LOPPU
            // apumuuttujaa, jonka arvo on -1.
            if (parts[3] == "out-of-stock"){
                hinta = TUOTE_LOPPU;
            }
            else{
                hinta = stod(parts[3]);
            }
            // Otetaan Tuote-struct käyttöön
            Tuote uusi_tuote = {tuote, hinta};

            // Tallennetaan tietorakenteeseen uusi ketju, uusi liike tai uusi
            // tuote sen mukaan, löytyykö vastaava jo tietorakenteesta
            // kyseisillä tiedoilla.
            if (ketjurakenne.count(ketju) == 1){

                if (ketjurakenne[ketju].count(liike) == 1){
                    // Tarkistetaan tuotteen olemassaolo Lisätään jos ei ole
                    // olemassa. Muutoin päivitetään hinta.
                    for (auto tuotestruct : ketjurakenne[ketju][liike]){

                        if (tuotestruct.tuotenimi == tuote){
                            tuotestruct.hinta = hinta;
                            break;
                        }
                    }
                ketjurakenne[ketju][liike].push_back(uusi_tuote);
                }
                // Lisätään uusi liike ja siinä oleva tuote tietoineen
                // tietorakenteeseen oleamssa olevan ketjun kohdalle.
                else{
                    ketjurakenne[ketju][liike].push_back(uusi_tuote);
                }
            }
            // Lisätään ketjulle ensimmäinen liike tuotteineen.
            else{
                Liikemap uusi_liike;
                uusi_liike[liike] = {uusi_tuote};
                ketjurakenne[ketju] = uusi_liike;
            }
        }
    }
    return ketjurakenne;
}

// Funktio ottaa parametrinaan tietorakenteen, tallentaa sieltä ketjut
// set-säiliöön ja tulostaa ne.
void tulosta_ketjut(const Ketjumap &rakenne)
{
    set <string> ketjut;

    for (auto ketju = rakenne.begin(); ketju != rakenne.end(); ++ ketju ){
        ketjut.insert(ketju->first);
    }
    for (auto ketju : ketjut){
        cout << ketju << endl;
    }
}

// Funktio ottaa parametreinaan tietorakenteen ja ketjun, tallentaa
// tietorakenteesta liikkeet set-säiliöön ja tulostaa ne.
void tulosta_liikkeet(const Ketjumap &rakenne, string avain)
{
    set <string> liikkeet;

    if (rakenne.count(avain) != 1){
        cout << "Error: unknown chain name" << endl;
    }else{
        for (auto liike = rakenne.at(avain).begin();liike
            != rakenne.at(avain).end(); ++ liike ){
            liikkeet.insert(liike->first);
        }
        for (auto liike : liikkeet){
            cout << liike << endl;
        }
    }
}

// Funktio ottaa paramtereinaan tietorakenteen, ketjun sekä liikkeen ja tulostaa
// kyseisen liikken tuotteet hintatietoineen.
void tulosta_tarjonta(const Ketjumap &rakenne, string ketju, string liike)
{
    map <string, double> tuote_hinta;

    if (rakenne.count(ketju) != 1){
        cout << "Error: unknown chain name" << endl;
    }else if (rakenne.at(ketju).count(liike) != 1){
        cout << "Error: unknown store" << endl;
    }else{
        for (auto tuote = rakenne.at(ketju).at(liike).begin(); tuote !=
            rakenne.at(ketju).at(liike).end(); ++tuote){
            tuote_hinta[tuote->tuotenimi] = tuote->hinta;
        }
        map<string, double>::iterator tuote;
        tuote = tuote_hinta.begin();
        while (tuote != tuote_hinta.end()){
            if (tuote->second == TUOTE_LOPPU){
                cout << tuote->first << " out of stock" << endl;
                ++ tuote;
            }else{
                cout << tuote->first << " " << fixed << setprecision(2) <<
                        tuote->second << endl;
                ++ tuote;
            }
        }
    }
}

// Funktio ottaa parametreinaan tietorakenteen ja kysytyn tuotteen. Käy läpi
// kaikkien ketjujen kaikki liikkeet kyseisen tuotteen osalta, tallentaa
// halvimman saatavilla olevan hinnan ja tulostaa kyseisen hinnan sekä liikkeet
// ketjuineen, joista tuotetta saa kyseiseen hintaan. Jos tuote on tarjolla,
// mutta tilapäisesti loppu, tulostuu siitä asianmukainen ilmoitus.
void tulosta_halvin(const Ketjumap &rakenne, string tuote)
{
    set <string> ketjut_liikkeet;
    double halvin = 0.0;

    for (Ketjumap::const_iterator ketju = rakenne.begin();
         ketju != rakenne.end(); ++ketju){

            for (Liikemap::const_iterator liike = ketju->second.begin();
                 liike != ketju->second.end(); ++liike){

                for (Tuote tuotetieto : liike->second){

                    if (tuotetieto.tuotenimi == tuote){
                        if (ketjut_liikkeet.size() == 0){
                            ketjut_liikkeet.insert(ketju->first + " " +
                                                   liike->first);
                            halvin = tuotetieto.hinta;

                        }else if (halvin > tuotetieto.hinta){
                            if (tuotetieto.hinta == TUOTE_LOPPU){
                                continue;
                            }else{
                                ketjut_liikkeet.clear();
                                ketjut_liikkeet.insert(ketju->first + " " +
                                                       liike->first);
                                halvin = tuotetieto.hinta;
                            }
                        }else if (halvin == TUOTE_LOPPU and
                                  tuotetieto.hinta > 0){
                            ketjut_liikkeet.clear();
                            ketjut_liikkeet.insert(ketju->first + " " +
                                                   liike->first);
                            halvin = tuotetieto.hinta;

                        }else if (halvin == tuotetieto.hinta){
                            ketjut_liikkeet.insert(ketju->first + " " +
                                                   liike->first);

                        }else if (halvin < tuotetieto.hinta){
                            continue;
                        }else{
                            continue;
                        }
                    }
                }
            }
    }
    if (ketjut_liikkeet.size() == 0){
        cout << "The product is not part of product selection" << endl;
    }else{
        if (halvin == TUOTE_LOPPU){
            cout << "The product is temporarily out of stock everywhere"<< endl;
        }else{
            cout << fixed << setprecision(2) << halvin << " euros" << endl;
            for (auto kauppa : ketjut_liikkeet){
                cout << kauppa << endl;
            }
        }
    }
}

// Funktio ottaa parametrinaan tietorakenteen ja tulostaa kaikkien ketjujen
// kaikkien liikkeiden tuotteet aakkosjärjestyksessä kerran, oli niitä
// saatavilla tai ei.
void tulosta_tuotteet(const Ketjumap &rakenne)
{
    set <string> tuotteet;

    for (Ketjumap::const_iterator ketju = rakenne.begin();
         ketju != rakenne.end(); ++ketju){

            for (Liikemap::const_iterator liike = ketju->second.begin();
                 liike != ketju->second.end(); ++liike){

                for (Tuote tuotetieto : liike->second){
                    if (tuotteet.count(tuotetieto.tuotenimi) == 0){
                        tuotteet.insert(tuotetieto.tuotenimi);
                    }else{
                        continue;
                    }
                }
            }
    }
    for (auto tuote : tuotteet){
        cout << tuote << endl;
    }
}

// Antaa virheilmoituksen tunnistetusta, mutta virheellisestä komennosta. Ottaa
// parametrinaan tunnistetun komennon.
void virhe_syotteessa(string syote)
{
    cout << "Error: error in command " << syote << endl;
}

// Funktio ottaa parametrinaan käyttäjän komennon sekä tietorakenteen ja
// kutsuu oikeaa funktiota tulkittuaan komennon ja sen oikeellisuuden.
void tulkitse_komento(string komento, const Ketjumap &rakenne)
{
    vector <string> splitattu_komento = split(komento, ' ');
    unsigned int komento_size = splitattu_komento.size();

    if (splitattu_komento[0] == "chains"){
        if (komento_size == 1){
            tulosta_ketjut(rakenne);
        }else{
            virhe_syotteessa(splitattu_komento[0]);
        }
    }
    else if (splitattu_komento[0] == "stores"){
        if (komento_size == 2){
            tulosta_liikkeet(rakenne, splitattu_komento[1]);
        }else{
            virhe_syotteessa(splitattu_komento[0]);
        }
    }
    else if (splitattu_komento[0] == "selection"){
        if (komento_size == 3){
            tulosta_tarjonta(rakenne, splitattu_komento[1], splitattu_komento[2]);
        }else{
            virhe_syotteessa(splitattu_komento[0]);
        }
    }
    else if (splitattu_komento[0] == "cheapest"){
        if (komento_size == 2){
            tulosta_halvin(rakenne, splitattu_komento[1]);
        }else{
            virhe_syotteessa(splitattu_komento[0]);
        }
    }
    else if (splitattu_komento[0] == "products"){
        if (komento_size == 1){
            tulosta_tuotteet(rakenne);
        }else{
            virhe_syotteessa(splitattu_komento[0]);
        }
    }else{
        cout << "Error: unknown command: " << komento << endl;
    }
}

// Pääfunktio, kutsuu ohjelman muita funkioita ja johtaa sen toimintaa.
int main()
{
    Ketjumap tietorakenne;
    ifstream filu;
    string komento;

    if ( not tiedoston_tarkistus(filu)){
        return EXIT_FAILURE;
    }else{
        tietorakenne = tiedoston_luku(filu);
    }
    if (tietorakenne.size() == 0){
        return EXIT_FAILURE;
    }else{
        while (true){
            cout << "> ";
            getline(cin, komento);
            if (komento == "quit"){
                break;
            }
            tulkitse_komento(komento, tietorakenne);
        }
    }
    return EXIT_SUCCESS;

}
