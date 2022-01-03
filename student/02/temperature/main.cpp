#include <iostream>

using namespace std;

int main()
{
    double temperature = 0;
    cout << "Enter a temperature: ";
    cin >> temperature;

    double fahren = temperature * 1.8 + 32;
    double celsius = (temperature - 32) / 1.8 ;

    cout << temperature << " degrees Celsius is " << fahren << " degrees Fahrenheit" << endl;
    cout << temperature << " degrees Fahrenheit is " << celsius << " degrees Celsius" << endl;

    return 0;
}
