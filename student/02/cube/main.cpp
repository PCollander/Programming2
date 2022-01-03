#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    unsigned long int kerrottava = 0;
    cout << "Enter a number: ";
    cin >> kerrottava;
    
    int POTENSSI = 3;
    int tarkastettava = pow(kerrottava, POTENSSI);

    if ( kerrottava == 0  or kerrottava == (tarkastettava / kerrottava) / kerrottava) {
        cout << "The cube of "<< kerrottava << " is " << tarkastettava << "." << endl;
    }
    else {
        cout << "Error! The cube of " << kerrottava << " is not " << tarkastettava << "." << endl;
    }
    
}
