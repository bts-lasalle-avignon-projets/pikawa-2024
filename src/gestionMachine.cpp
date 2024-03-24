#include "gestionMachine.h"
#include <iostream>

using namespace std;

GestionMachine::GestionMachine(int quantiteCapsule, int numeroCapsule) :
    quantiteCapsule(quantiteCapsule), numeroCapsule(numeroCapsule)
{
}

void GestionMachine::AlerterPresenceCapsule()
{
}

int GestionMachine::getQuantiteCapsule() const
{
    return quantiteCapsule;
}

void GestionMachine::gererCapsule()
{
}
