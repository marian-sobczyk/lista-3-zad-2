#include <iostream>
#include "ConfigurationFile.h"
#include "MusicFileFactory.h"
#include "KeyChain.h"

using namespace std;

int main() {
    ConfigurationFile *configurationFile = new ConfigurationFile();
    char *c_pin = getpass("Podaj pin: ");
    if (strcmp(c_pin, configurationFile->pin) != 0) {
        cout << "Błędny pin\n";
        return -1;
    }

    KeyChain *keyChain = new KeyChain((unsigned char *) configurationFile->path,
                                      (unsigned char *) configurationFile->password, configurationFile->keyId);
    unsigned char *key = keyChain->key;

    ISoundEngine *engine = createIrrKlangDevice();

    if (!engine)
        return 0;

    MusicFileFactory *factory = new MusicFileFactory(key);
    engine->addFileFactory(factory);
    factory->drop();
    cout << "Aby rozpocząć odtwarzanie naciśnij enter\n";
    getchar();
    cout << "Odtwarzanie rozpoczęte. Aby przerwać, naciśnij enter\n";

    engine->play2D("/Users/marian/Desktop/ssl/encoded", true);

    getchar();

    engine->drop();
    return 0;
}