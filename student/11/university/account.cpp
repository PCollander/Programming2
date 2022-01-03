/* Class: Account
  * ----------
  * Defines a student or a staff account in the university system.
  *
  * Program author
  * Name: Pyry Collander
  * Student number: 255284
  * UserID: collande
  * E-Mail: pyry.collander@tuni.fi
  * */

#include "account.hh"
#include "utils.hh"
#include "instance.hh"
#include "course.hh"

Account::Account(std::string full_name, std::string email, int account_number):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    email_(email),
    account_number_(account_number)
{
    std::vector<std::string> name = utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();
}


void Account::tulosta() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}


std::string Account::get_email()
{
    return email_;
}


bool Account::voiko_ilmoittautua(std::string instanssi, int henk_nro,
                                 Course *kurssi, unsigned int pv,
                                 unsigned int kk, unsigned int vuosi)
{
    for( auto inst : current_ ){
        if( inst->instanssin_nimi == instanssi ){
            if( inst->kurssi_info -> get_code() != kurssi -> get_code() ){
                return false;
            }
            else if( inst -> tarkista_ilmo(henk_nro) ){
                return true;
            }
        }
    }
    Instance* inst = kurssi->get_instance(instanssi);
    if( inst->tarkista_ilmon_pvm(pv, kk, vuosi) ){
        return true;
    }
    return false;
}


bool Account::onko_ilmoittautunut(std::string instanssi, Course *kurssitunnus)
{
    for( auto inst : current_ ){
        if( inst -> instanssin_nimi == instanssi ){
            if( inst -> kurssi_info -> get_code() != kurssitunnus ->
                    get_code() ){
                continue;
            }
            return true;
        }
    }
    std::cout << NO_SIGNUPS << std::endl;
    return false;
}


void Account::ilmoittaudu(Account* osallistuja, Course* kurssi,
                          std::string toteutus, int henk_nro)
{
   Instance* inst = kurssi -> get_instance(toteutus);
   inst->ilmoittaudu(osallistuja, henk_nro);
   current_.push_back(inst);
   std::cout << SIGNED_UP << std::endl;
}


void Account::kurssi_suoritettu(Course *kurssi, std::string instanssi)
{
    completed_.push_back(kurssi);
    std::vector<Instance*> apuvektori;
    for( auto inst : current_ ){
        if( inst -> instanssin_nimi == instanssi ){
            if( inst -> kurssi_info -> get_code() == kurssi ->
                    get_code() ){
            continue;
            }
        }
        apuvektori.push_back(inst);
    }
    current_.empty();
    current_ = apuvektori;
    std::cout << COMPLETED << std::endl;
}


void Account::tulosta_suoritetut()
{
    int total = 0;
    for (auto course : completed_){
        course -> print_info(true);
        total += course -> get_credits();
    }
    std::cout << "Total credits: " << total << std::endl;
}


void Account::opintojen_tila()
{
    std::cout << "Current: " << std::endl;
    for( auto inst : current_ ){
        Course* current_course = inst->hae_kurssi();
        current_course->print_info(false) ;
        std::cout << " " << inst -> instanssin_nimi << std::endl;
    }
    std::cout << "Completed: " << std::endl;
    int total = 0;
    for ( auto course : completed_ ){
        course -> print_info(true);
        total += course -> get_credits();
    }
    std::cout << "Total credits: " << total << std::endl;
}




