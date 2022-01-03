#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\n P = print id\n"
                              "C = count id\n D = depth id";


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}


void network_depth(std::map<std::string, std::vector<std::string>> network, std::string id, int& depth, int counter = 0){
    for (std::string name : network.at(id)){
        ++ counter;
        if (!network.at(name).empty()){
            network_depth(network, name, depth, counter);
            --counter;
        }
        else{
            if (counter > depth){
                depth = counter;
                counter = 0;
            }
            else{
            counter = 0;
            }
        }

    }
}


void calculate(std::map<std::string, std::vector<std::string>> network, std::string id, int& sum){
    for (std::string name : network.at(id)){
        ++sum;
        if (!network.at(name).empty()){
            calculate(network, name, sum);
        }
    }
}


void print_network(std::map<std::string, std::vector<std::string>> network, std::string id, std::string dots){
    for (std::string name : network.at(id)){
        std::cout << dots << name << std::endl;
        if (!network.at(name).empty()){
            dots += ".." ;
            print_network(network, name, dots);
            dots = dots.substr(0, dots.length()-2);
        }
        else if(network.at(id).size() <= 1){
            dots = "..";
        }

    }
}


int main()
{
    // TODO: Implement the datastructure here
    std::map<std::string, std::vector<std::string>> network;


    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);
            if (network.count(id1)>0){
                network.at(id1).push_back(id2);
                network.insert({id2,{}});
            }
            else{
                std::vector <std::string> name = {id2};
                network.insert({id1,name});
                network.insert({id2,{}});
            }

            // TODO: Implement the command here!

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);
            std::cout << id << std::endl;
            print_network(network,id,"..");

            // TODO: Implement the command here!

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);
            int sum = 0;
            calculate(network, id, sum);
            std::cout << sum << std::endl;


            // TODO: Implement the command here!

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);
            int depth = 0;
            network_depth(network, id, depth);
            std::cout << depth+1 << std::endl;

            // TODO: Implement the command here!

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
