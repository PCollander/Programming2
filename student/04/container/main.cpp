#include <iostream>
#include <vector>

using namespace std;

void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        cin >> new_integer;
        ints.push_back(new_integer);
    }
}

bool same_values(std::vector< int >& ints){
    for( long unsigned int indeksi = 0; indeksi < ints.size(); ++indeksi){
        if ((ints.front() != ints.at(indeksi))){
            return false;
        }
    }
    return true;
}


bool is_ordered_non_strict_ascending(std::vector< int >& ints){
    for( long unsigned int indeksi = 0; indeksi < ints.size() - 1; ++indeksi){
        if ((ints.at(indeksi) > ints.at(indeksi + 1))){
            return false;
        }
    }
    return true;
}

bool is_arithmetic_series(std::vector< int >& ints){
    int erotus1 = 0;
    int erotus2 = 0;
    vector<int>::size_type indeksi = 0;
    if (ints.size() == 1){
        return true;
    }else{
        while ( indeksi < ints.size() ) {
            if (indeksi == ints.size() - 2){
                return true;
            }
            erotus1 = ints.at(indeksi + 1) - ints.at(indeksi);
            erotus2 = ints.at(indeksi + 2) - ints.at(indeksi + 1);
            if (erotus1 != erotus2){
                return false;
            }

        ++ indeksi;
        }
    }
    return false;
}

bool is_geometric_series(std::vector< int >& ints){
    int jako1 = 0;
    int jako2 = 0;
    if ((ints.front() == 0) && (ints.back()==0)){
        return false;
    }
    vector<int>::size_type indeksi = 0;
    if (ints.size() == 1){
        return true;
    }else{
        while ( indeksi  < ints.size() ) {
            if ( ints.at(indeksi) == 0){
                jako1 = 0;
            }
            else{
            jako1 = ints.at(indeksi + 1) / ints.at(indeksi);
            }
            if (indeksi == ints.size() - 1){
                if (jako1 == jako2){
                    return true;
                }else{
                    return false;
                }
            }else{
                if ( ints.at(indeksi) == 0){
                    jako2 = 0;
                }
                else{
                jako2 = ints.at(indeksi + 2) / ints.at(indeksi + 1);
                }
                if (jako1 == jako2){
                    return true;
                }else{
                    return false;
                }
             ++ indeksi;
            }
        }

    }
    return false;
}
    
int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
