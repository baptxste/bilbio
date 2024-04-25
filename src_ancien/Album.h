#ifndef ALBUM_H
#define ALBUM_H

#include <iostream>

#include "Livre.h"

using namespace std;

class Album : public Livre {

private:
    string illustration;

public:
            Album  (int code, string auteur, string titre, string editeur, string isbn, string public_vise, string etats, string illustration)    ;
    string  getIllustration()                                                                                                                  ;
    void    setIllustration(string illustration)                                                                                                                  ;
    void    affiche ()                                                                                                                  ;
};

#endif /* ALBUM_H */