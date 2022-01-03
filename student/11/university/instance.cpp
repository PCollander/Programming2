/* Class: Instance
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * A class that contains operations applicable to an instance.
 *
 * Program author
 * Name: Pyry Collander
 * Student number: 255284
 * UserID: collande
 * E-Mail: pyry.collander@tuni.fi
 * */

#include "instance.hh"

Instance::Instance(Course* kurssi_info, std::string nimi):
    kurssi_info(kurssi_info), instanssin_nimi(nimi)
{

}


void Instance::aseta_aloitus_pvm(unsigned int pv, unsigned int kk,
                                 unsigned int vuosi)
{
   aloitus_vuosi_ = vuosi;
   aloitus_kk_ = kk;
   aloitus_pv_ = pv;
}


bool Instance::onko_sama(std::string kysytty_arvo)
{
    if( instanssin_nimi == kysytty_arvo ){
        return true;
    }
    return false;
}


bool Instance::tarkista_ilmo(int henk_nro)
{
    for( auto osallistuja : osallistujat_ ){
        int tunnus = osallistuja.first;
        if( tunnus == henk_nro ){
            std::cout << ALREADY_REGISTERED << std::endl;
            return true;
        }
    }
    return false;
}


bool Instance::tarkista_ilmon_pvm(unsigned int pv, unsigned int kk,
                            unsigned int vuosi)
{
    Date now = Date(pv, kk, vuosi);
    if( now.operator ==(Date(aloitus_pv_, aloitus_kk_, aloitus_vuosi_)) ){
        return false;
    }
    else if( not now.operator <(Date(aloitus_pv_, aloitus_kk_,
                                     aloitus_vuosi_)) ){
        std::cout << LATE << std::endl;
        return true;
    }
    return false;
}


void Instance::ilmoittaudu(Account* osallistuja, int henk_nro)
{
    osallistujat_.insert({henk_nro, osallistuja});
}


void Instance::tulosta()
{
    std::cout << instanssin_nimi << std::endl;
    std::cout << INDENT << "Starting date: " << aloitus_pv_ << "." <<
                 aloitus_kk_ << "." << aloitus_vuosi_ << std::endl;

    std::cout << INDENT << "Amount of students: " << osallistujat_.size()
              << std::endl;
}


void Instance::tulosta_osallistujat()
{
    for(auto opiskelija : osallistujat_){
        Account* osallistuja = opiskelija.second;
        std::cout << INDENT;
        osallistuja->tulosta();
    }
}


Course *Instance::hae_kurssi()
{
    return kurssi_info;
}

