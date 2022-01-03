#include <iostream>

// Write here a function counting the mean value

int main()
{
    int sum = 0;

    double amount = 0;
    std::cout << "From how many integer numbers you want to count the mean value? ";
    std::cin >> amount;

    if ( amount == 0 ){
        std::cout << "Cannot count mean value from 0 numbers" << std::endl;
    }
    else {
        for ( int nmbr = 1; nmbr < amount + 1; ++nmbr ) {

            double variab =0;
            std::cout << "Input "<< nmbr << ". number: ";
            std::cin >> variab;
            sum += variab;
        }
        double mean = 0;
        mean = sum / amount;
        std::cout << "Mean value of the given numbers is " << mean << std::endl;

    }
}
