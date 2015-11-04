#include <iostream>
#include "ConfigurationFile.h"

using namespace std;

int main() {
    ConfigurationFile *configurationFile = new ConfigurationFile();
    printf("Podaj PIN: ");
    string userPin;
    cin >> userPin;
    char *c_pin = (char *) userPin.c_str();
    if (strcmp(c_pin, configurationFile->pin) != 0) {
        cout << "Błędny pin\n";
        return -1;
    }
}