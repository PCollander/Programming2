#include <iostream>
#include <string>

using namespace std;

bool tarkistus (int tot, int draw) {
    if ( tot <= 0 or draw <= 0) {
        cout << "The number of balls must be a positive number." << endl;
        return false;
    }
    else if ( draw > tot ){
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return false;
    }
    else {
        return true;
    }

}

unsigned long int mahdollisuuksia( unsigned long int n,  unsigned long int p, unsigned long  int np)
{
    unsigned long int m = (n / (np * p));
    return m ;

}

unsigned long int factorial(unsigned long int n)
{
    if(n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}


int main()
{

    unsigned long int tot_amount = 0;
    cout << "Enter the total number of lottery balls: ";
    std::cin >> tot_amount;

    unsigned long int drawn = 0;
    cout << "Enter the number of drawn balls: ";
    std::cin >> drawn;

    if ( tarkistus(tot_amount, drawn) ) {
        unsigned long int n = factorial(tot_amount);
        unsigned long int p = factorial(drawn);
        unsigned long int np = factorial(tot_amount - drawn);
        cout << "The probability of guessing all " << drawn << " balls correctly is 1/" << mahdollisuuksia(n, p, np) << endl;
    }



    return 0;
}
