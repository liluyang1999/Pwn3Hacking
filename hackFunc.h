#pragma once
#include "mem.h"
#include "originalFunc.h"

//Improve walking speed
void speedHackFunc(uintptr_t baseAddr, bool flag);
void speedHackOnFunc();

//Immune to any damage from outside
void immuneDamageHackFunc(uintptr_t baseAddr, bool flag);

//Unlimited mana
void manaHackFunc(uintptr_t baseAddr, bool flag);
void manaHackOnFunc();

//Great damage to enemies
void greatDamageHackFunc(uintptr_t baseAddr, bool flag);
void greatDamageHackOnFunc();

//Stop bear's attack
void bearHackFunc(uintptr_t baseAddr, bool flag);
void bearRadiusHackOnFunc();
void bearNameHackOnFunc();
