#include <iostream>

int main()
{
    int number = 0;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> number;

    for ( int nmbr = 1; nmbr < number + 1; ++nmbr ){
        if ( nmbr % 3 == 0 ){
             if ( nmbr % 7 == 0 )
                  std::cout << "zip boing" << std::endl;
             else {
             std::cout << "zip" << std::endl;
             }
         }
        else if ( nmbr % 7 == 0 ){
             std::cout << "boing" << std::endl;
        }else {
             std::cout << nmbr << std::endl;
         }
    }

}
