#include "player.hh"

using namespace std;

Player::Player(string nimi):
    nimi_(nimi), pisteet_(0){

}

string Player::get_name() const{
    return nimi_;
}

int Player::get_points() const{
    return pisteet_;
}

bool Player::has_won() const{
    if (pisteet_ == 50){
        return true;
    }else{
        return false;
    }
}

void Player::add_points(int heiton_pisteet){
    pisteet_ += heiton_pisteet;
    if (pisteet_ > 50){
        pisteet_ = 25;
    }
}


