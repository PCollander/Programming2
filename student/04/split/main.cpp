#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string str, char token, bool truth=false){
    vector<string>result;
    while(str.size()){
        unsigned long int index = str.find(token);
        unsigned long int a = string::npos;
        if(index!= a){
            result.push_back(str.substr(0,index));
            str = str.substr(index+1);
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    if(truth){
        int b = (result.size());
        vector <string> withoutspaces;
        for(int i=0; i<b; ++i){
            string word = result.at(i);
            if(word == ""){
            }else{
                withoutspaces.push_back(result.at(i));
            }
        }
        return withoutspaces;
    }
    return result;
}



int main()
{
    string line = "";
    cout << "Enter a string: ";
    getline(cin, line);
    cout << "Enter the separator character: ";
    char separator = getchar();

    vector< string > parts  = split(line, separator);
    cout << "Splitted string including empty parts: " << endl;
    for( auto part : parts ) {
        cout << part << endl;
    }

    vector< string > parts_no_empty  = split(line, separator, true);
    cout << "Splitted string ignoring empty parts: " << endl;
    for( auto part : parts_no_empty ) {
        cout << part << endl;
    }
}
