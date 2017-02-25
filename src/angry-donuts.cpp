/* main.cpp */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <uuid/uuid.h>

#include "index.h"
#include "status.h"
#include "data.h"

int main(int argc, char *argv[]) {

    /* Test des Arguments */
    if (argc != 2) {
        std::cout << "Error: missing argument" << std::endl;
        std::cout << "Usage: angry-donuts /path/to/data" << std::endl;
        exit(EXIT_FAILURE);
    }

    Index index(argv[1]);

    /*  Un contenu de fichier   */
    std::string t = "Bla bla bla!";

    /*  Recuperer le char* a partir d'un String     */
    const char *test = t.c_str();

    /*  Recuperer le char* a partir d'un string     */
    uint64_t length = strlen(test);

    /*  Le data represente le fichier en lui meme
        Donnee en bytes + informations              */
    Data data((uint8_t*) test, length);

    /* Creation d'un uuid , la valeur par default 0 */
    uuid_t uuid;

    /*  Genere un uuid puis
        On insere le couple [cle(uuid),valeur(ObjetData)]
        un succes est attendu , car la cle n'est pas encore prise */

    /* Karim Note : Peut-etre utiliser un enum pour definir le type d'action
                    en parametre du put, pour gerer en plus : le append / et
                    l'ecrasement
    */
    if (index.put(uuid, &data) != Status::Success)
        std::cout << "error put" << std::endl;

    /* On reccupere le fichier precedant dans Data2 via sa cle uuid
        un succes est attendu car le fichier est deja reference dans l'index */
    Data data2;
    if (index.get(uuid, &data2) != Status::Success)
        std::cout << "error get" << std::endl;

    /* Test de l'exacttude des donnee recuperee */
    if (length != data2.length) {
        std::cout << "error, different content (length)" << std::endl;
    } else {
        if (memcmp(data.bytes, data2.bytes, length) != 0)
            std::cout << "error, different content (bytes)" << std::endl;
        else
            std::cout << "success on put and get!" << std::endl;
    }

    /* Suppression du fichier reference */
    if (index.del(uuid) == Status::Success)
        std::cout << "success on delete!" << std::endl;
    else
        std::cout << "delete error..." << std::endl;

    return 0;
}
