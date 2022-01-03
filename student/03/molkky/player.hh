#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>

using namespace std;

class Player
{
public:
    Player(string nimi);
    string get_name() const;
    int get_points() const;
    bool has_won() const;
    void add_points(int pisteet_);
private:
    string nimi_;
    int pisteet_;
};

#endif // PLAYER_HH
