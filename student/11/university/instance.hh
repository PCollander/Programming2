/* Class: Instance
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class that represent a single instance.
 *
 * Note: Students should make changes to this class, and add their info and
 * specifics of the class to this comment.
 *
 * Program author
 * Name: Pyry Collander
 * Student number: 255284
 * UserID: collande
 * E-Mail: pyry.collander@tuni.fi
 * 
 * */

#ifndef INSTANCE_HH
#define INSTANCE_HH

#include "account.hh"
#include "date.hh"
#include "utils.hh"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

// Forward-declaration of Course, so that instance can point to the course it belongs to.
class Course;

const std::string ALREADY_REGISTERED = "Error: Student has already registered on this course.";
const std::string LATE = "Error: Can't sign up on instance after the starting date.";
const std::string INDENT = "    ";

class Instance
{
public:
    /* Rakentaja, joka tallentaa kyseisen kurssin tiedot asianmukaisiin 
     * muuttujiin siten, että ne ovat ohjelman käytettävissä.
     */
    Instance(Course* kurssi_info, std::string nimi);

    /* Tallentaa uuden kurssin päivämäärän kun sellainen luodaan. */
    void aseta_aloitus_pvm(unsigned int pv, unsigned int kk, unsigned int vuosi);

    /* Tarkistaa onko ilmoittautuminen vielä auki pvm mielessä. */
    bool tarkista_ilmon_pvm(unsigned int pv, unsigned int kk,
                            unsigned int vuosi);

    /* Tarkistaa täsmääkö toteutuskerran nimi haluttun. */
    bool onko_sama(std::string kysytty_arvo);

    /* Tarksitaa, onko ilmoitettu henkilö jo ilmoittautunut toteutuskerralle. */
    bool tarkista_ilmo(int henk_nro);

    /* Lisää henkilön kurssille. */
    void ilmoittaudu(Account* osallistuja, int henk_nro);

    /* Tulostaa kurssin halutun toteutuskerran tiedot. */
    void tulosta();

    /* Tulostaa halutun kurssin halutun toteutuskerran osallistujat. */
    void tulosta_osallistujat();

    /* Palauttaa toteutuskerran kurssin. */
    Course *hae_kurssi();

    /* Asetetaan toteutuskerralle kurssi rakentajassa. */
    Course* kurssi_info;

    /* Annetaan muuttujalle nimi rakentajassa. */
    std::string instanssin_nimi;

private:
    /* Toteutuskerran tiedot ja tietorakenne toteutuskerran ilmoittautuneille */
    unsigned int aloitus_pv_;
    unsigned int aloitus_kk_;
    unsigned int aloitus_vuosi_;

    std::map<int, Account*> osallistujat_;
};

#endif // INSTANCE_HH
    
