#include <iostream>
#include "ConfigurationFile.h"
#include "MusicFileFactory.h"
#include "KeyChain.h"

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

    KeyChain *keyChain = new KeyChain((unsigned char *) configurationFile->path,
                                      (unsigned char *) configurationFile->password, configurationFile->keyId);
    unsigned char *key = keyChain->key;

    ISoundEngine *engine = createIrrKlangDevice();

    if (!engine)
        return 0; // error starting up the engine

    // create an instance of the file factory and let
    // irrKlang know about it. irrKlang will drop() the
    // factory itself if it doesn't need it any longer.

    MusicFileFactory *factory = new MusicFileFactory(key);
    engine->addFileFactory(factory);
    factory->drop(); // we don't need it anymore, delete it

    // that's it, play some sounds with our overriden
    // file access methods:

    printf("\nDemonstrating file access overriding.\n");
    printf("Press any key to start playing sounds, then press escape to cancel\n");

    getchar();

    engine->play2D("/Users/marian/Desktop/ssl/encoded.wav", true);

    while (true) // endless loop until user exits
    {
//        // play some wave sound
//        engine->play2D("../../media/explosion.wav");
//
        if (getchar() == 'q')
            break; // user pressed ESCAPE key, cancel
    }

    engine->drop(); // delete engine
    return 0;
}