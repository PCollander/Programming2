/* Class: Account
  * ----------
  * Defines a student or a staff account in the university system.
  *
  * In the project, this class should be expanded to
  * include study history of the account.
  *
  * Program author
  * Name: Pyry Collander
  * Student number: 255284
  * UserID: collande
  * E-Mail: pyry.collander@tuni.fi
  *
  * */

#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include "date.hh"
#include <string>
#include <vector>
#include <map>
#include <iostream>

class Instance;
class Course;

const std::string NO_SIGNUPS = "No signups found on this instance.";
const std::string SIGNED_UP = "Signed up on the course instance.";
const std::string COMPLETED = "Course completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "frontname lastname"
     * @param email
     * @param account_number
     */
    Account(std::string full_name, std::string email, int account_number);

    /**
     * @brief print account info on one line
     */
    void tulosta() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email();

    /* Tarkistaa onko henkilö jo ilmoittautunut ja onko ilmoittautuminen vielä
     * ok pvm puolesta. */
    bool voiko_ilmoittautua(std::string instanssi, int henk_nro, Course* kurssi,
                            unsigned int pv, unsigned int kk,
                            unsigned int vuosi);

    /* Lisää henkilön ilmoittautuneisiin.*/
    void ilmoittaudu(Account* osallistuja, Course* kurssi, std::string toteutus,
                     int henk_nro);

    /* Tarkistaa onko henkilö ilmoittautunut kurssille. */
    bool onko_ilmoittautunut(std::string instanssi, Course* kurssitunnus);

    /* Lisää kurssin henkilön suoritettuihin kursseihin. */
    void kurssi_suoritettu(Course* kurssi, std::string instanssi);

    /* Tulostaa henkilön suoritetu kurssit ja niiden op-määrän sekä ilmotut
     * kurssit. */
    void opintojen_tila();

    /* Tulostaa henkilön suoritetut kurssit ja niiden op-määrän. */
    void tulosta_suoritetut();

private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;
    std::vector<Instance*> current_;
    std::vector<Course*> completed_;
};

#endif // ACCOUNT_HH
