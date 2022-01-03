/* Class: University
  * ----------
  * A class containning a mini Uni with its pepople and its courses.
  *
  * Program author
  * Name: Pyry Collander
  * Student number: 255284
  * UserID: collande
  * E-Mail: pyry.collander@tuni.fi
  *
  * */
#include "university.hh"


University::University():running_number_(111111)
{
}


University::~University()
{
    for ( auto course : courses_ ){
        delete course.second;
    }

    for ( auto account : accounts_ ){
        delete account.second;
    }

}


void University::add_course(Params params)
{
    if ( courses_.find(params.at(0)) != courses_.end() ){
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    } else {
        std::cout << NEW_COURSE << std::endl;
    }

    Course* n_course = new Course(params.at(0), params.at(1));
    courses_.insert({n_course->get_code(), n_course});
}


void University::print_courses(Params)
{
    for ( auto course : courses_ ){
        course.second->print_info(true);
    }
}


void University::print_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }

    courses_.at(params.at(0))->print_long_info();
}


void University::add_account(Params params)
{
    for( std::map<int, Account*>::iterator iter = accounts_.begin();
         iter != accounts_.end(); ++iter ) {
        if( iter->second->get_email() == params.at(1) ) {
            std::cout << ALREADY_EXISTS << std::endl;
            return;
        }
    }

    int account_number = running_number_++;
    Account* n_account = new Account(params.at(0), params.at(1),
                                     account_number);
    accounts_.insert({account_number, n_account});
    std::cout << NEW_ACCOUNT << std::endl;
    n_account->tulosta();
}


void University::print_accounts(Params)
{
    for ( auto account : accounts_ ){
        account.second->tulosta();
    }
}


void University::print_account_info(Params params)
{
    std::map<int, Account*>::iterator iter =
            accounts_.find(std::stoi(params.at(0)));
    if ( iter == accounts_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    iter->second->tulosta();
}


void University::add_staff_to_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    if ( accounts_.find(std::stoi(params.at(1))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;
    }

    courses_.at(params.at(0))->add_staff(accounts_.at(std::stoi(params.at(1))));
}

/*Lisää kurssille toteutuskerran ja aloituspäivämäärän, jos kurssi on olemassa
 *ja toteutuskertaa ei vielä ole olemassa. Tulostaa virheilmoituksen jos
 *sellainen on tarpeen. Ottaa parametrina kurssitunnuksen ja toteutuskerran
 *halutun ajankohdan.
 */

void University::add_instance(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }if (  courses_.at(params.at(0)) -> has_instance(params.at(1)) ){
        std::cout << INSTANCE_EXISTS << std::endl;
        return;
    } else {
        Instance* new_instance = new Instance(courses_.at(params.at(0)),
                                              params.at(1));
        courses_.at(params.at(0)) -> new_instance(new_instance);
        unsigned int paiva = utils::today.get_day();
        unsigned int kk = utils::today.get_month();
        unsigned int vuosi = utils::today.get_year();
        new_instance -> aseta_aloitus_pvm(paiva, kk, vuosi);
    }
}

/*
 *Lisää henkilön kurssille jos se on mahdollista (estävinä tekijöijä pvm,
 *tuplailmo, suoritettu jo). Tulostaa virheilmoituksen tarpeen tullen, eli kun
 *ilmo ei onnistu. Ottaa parametreina kurssin tunnuksen, toteutuskerran ja
 *henkilönumeron.
*/

void University::sign_up_on_course(Params params)
{
    if( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }if( not courses_.at(params.at(0)) -> has_instance(params.at(1)) ){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;
    }if( accounts_.find(std::stoi(params.at(2))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(2) << std::endl;
        return;
    }
    
    unsigned int paiva = utils::today.get_day();
    unsigned int kk = utils::today.get_month();
    unsigned int vuosi = utils::today.get_year();
    if( accounts_.at(std::stoi(params.at(2))) ->
            voiko_ilmoittautua(params.at(1),
                std::stoi(params.at(2)),courses_.at(params.at(0)), paiva, kk,
                               vuosi)){
        return;
    }
    accounts_.at(std::stoi(params.at(2))) -> 
            ilmoittaudu(accounts_.at(std::stoi(params.at(2))),
                    courses_.at(params.at(0)), params.at(1), 
                    std::stoi(params.at(2)));
}

/*
 *Lisää henkilölle suoritusmerkinnän kurssista jos kriteerit täyttyvät, eli 
 *kurssi on olemassa ja henkilö on ilmoittautunut onnistuneesti kurssille. Ottaa
 *parametreina kurssitunnuksen, toteutuskerran ja henkilönumeron.
 *
*/

void University::complete_course(Params params)
{
    if( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }if( not courses_.at(params.at(0)) -> has_instance(params.at(1)) ){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;
    }if( accounts_.find(std::stoi(params.at(2))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(2) << std::endl;
        return;
    }if( not accounts_.at(std::stoi(params.at(2))) ->
         onko_ilmoittautunut(params.at(1), courses_.at(params.at(0))) ){
        return;
    }
    accounts_.at(std::stoi(params.at(2))) ->
            kurssi_suoritettu(courses_.at(params.at(0)), params.at(1));
}

/*
 *Tulostaa kysytyn kurssin toteutuskerrat ja niille ilmoittautuneet
 *järjestyksessä. Ottaa parametrina kurssitunnuksen.
 *
*/

void University::print_signups(Params params)
{
    if( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    courses_.at(params.at(0)) -> print_signups();
}

/*
 *Tulostaa infon halutun opiskelijan "tilasta". Suoritetut kurssit ja niiden
 *opintopisteet sekä kurssit, joille on ilmoittauduttu. Ottaa parametrina
 *henkilönumeron (= käytännössä opiskelijanumero).
 *
*/

void University::print_study_state(Params params)
{
    if( accounts_.find(std::stoi(params.at(0))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    accounts_.at(std::stoi(params.at(0))) -> opintojen_tila();
}

/*
 *Tulostaa halutun opiskelijan suoritetut kurssit sekä summan niiden
 *opintopisteistä. Ottaa parametrina henkilönumeron.
 *
*/

void University::print_completed(Params params)
{
    if( accounts_.find(std::stoi(params.at(0))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    accounts_.at(std::stoi(params.at(0))) -> tulosta_suoritetut();

}

void University::set_date(Params params)
{
    utils::today = Date(std::stoi(params.at(0)), std::stoi(params.at(1)),
                        std::stoi(params.at(2)));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void University::advance_date(Params params)
{
    utils::today.advance_by(std::stoi(params.at(0)));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

void University::advance_by_period(Params)
{
    utils::today.advance_by_period_length();
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}
