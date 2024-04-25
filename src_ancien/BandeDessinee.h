#ifndef BANDEDESSINEE_H_
#define BANDEDESSINEE_H_

#include <iostream>

#include "Livre.h"

using namespace std;

class BandeDessinee : public Livre {

private :

    string dessinateur;

public :
    BandeDessinee (int code, string auteur, string titre, string editeur, string isbn, string public_vise, string etats, string dessinateur);

    string getDessinateur ();

    void setDessinateur (string dessinateur);

    void affiche ();
    



};

#endif /* BANDEDESSINEE*/