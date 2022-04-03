#include  "pch.h"
#include  "mem.h"
#include  "hackFunc.h"
#include "originalFunc.h"

uintptr_t  pwnAventAddr = (uintptr_t)GetModuleHandle(L"PwnAdventure3-Win32-Shipping.exe");
uintptr_t  gameLogicAddr = (uintptr_t)GetModuleHandle(L"GameLogic.dll");
uintptr_t  baseAddr = (uintptr_t)(gameLogicAddr + 0x97D7C);

//Pointer of player
vector<int>  playerAddressOffset = { 0x1c, 0x6c };
vector<int>  playerVftableAddressOffset = { 0x1c, 0x6c, 0x0 };

//Functions' offset
uintptr_t addItemFunc = 0x51BA0;
uintptr_t getItemByNameFunc = 0x1DE20;
uintptr_t chatFunc = 0x551A0;
uintptr_t giveAllFunc = 0x1E640;
uintptr_t fastTravelFunc = 0x55AE0;
uintptr_t teleportFunc = 0x54E50;

//All names of weapon and ammunition
const char* pistolAmmoN = "PistolAmmo";
const char* shotgunAmmoN = "ShotgunAmmo";
const char* revolverAmmoN = "RevolverAmmo";
const char* sniperAmmoN = "SniperAmmo";
const char* rifleAmmoN = "RifleAmmo";
const char* ropChainGunN = "ROPChainGun";
const char* akRifleN = "AKRifle";
const char* remoteExploitN = "RemoteExploit";
const char* goldMasterN = "GoldenMaster";
const char* greatBallsOfFireN = "GreatBallsOfFire";
const char* sopFireBallN = "CharStar";
const char* heapSprayN = "HeapSpray";
const char* zeroCoolN = "ZeroCool";
const char* pwnCoinN = "Coin";

// Pointers of player and playerVftable 
void*  player = (void*)findMemoryAddress(baseAddr, playerAddressOffset);
void*  playerVftable = (void*)findMemoryAddress(baseAddr, playerVftableAddressOffset);

// Pointer of Game API:  10097d80
void* gameAPI = (void*)(gameLogicAddr + 0x97d80);

void  getItems() {
    _GetItemByName GetItemByName = (_GetItemByName)(gameLogicAddr + getItemByNameFunc);
    _AddItem AddItem = (_AddItem)(gameLogicAddr + addItemFunc);
    
    //Add items and weapons
    void* ropChainGun = GetItemByName(gameAPI, ropChainGunN);
    AddItem(playerVftable, ropChainGun, 1, 0);
    void* remoteExploit = GetItemByName(gameAPI, remoteExploitN);
    AddItem(playerVftable, remoteExploit, 1, 0);
    void* heapSpray = GetItemByName(gameAPI, heapSprayN);
    AddItem(playerVftable, heapSpray, 1, 0);
    void* goldenMaster = GetItemByName(gameAPI, goldMasterN);
    AddItem(playerVftable, goldenMaster, 1, 0);
    void* akRifle = GetItemByName(gameAPI, akRifleN);
    AddItem(playerVftable, akRifle, 1, 0);
    void* zeroCool = GetItemByName(gameAPI, zeroCoolN);
    AddItem(playerVftable, zeroCool, 1, 0);
    void* sopFire = GetItemByName(gameAPI, sopFireBallN);
    AddItem(playerVftable, sopFire, 1, 0);
    void* greatBallFire = GetItemByName(gameAPI, greatBallsOfFireN);
    AddItem(playerVftable, greatBallFire, 1, 0);
    void* pwnCoin = GetItemByName(gameAPI, pwnCoinN);
    AddItem(playerVftable, pwnCoin, 100, 0);

    //Add ammunition
    void* pistolAmmo = GetItemByName(gameAPI, pistolAmmoN);
    AddItem(playerVftable, pistolAmmo, 9999, 1);
    void* revolverAmmo = GetItemByName(gameAPI, revolverAmmoN);
    AddItem(playerVftable, revolverAmmo, 9999, 1);
    void* shotgunAmmo = GetItemByName(gameAPI, shotgunAmmoN);
    AddItem(playerVftable, shotgunAmmo, 9999, 1);
    void* rifleAmmo = GetItemByName(gameAPI, rifleAmmoN);
    AddItem(playerVftable, rifleAmmo, 9999, 1);
    void* sniperAmmo = GetItemByName(gameAPI, sniperAmmoN);
    AddItem(playerVftable, sniperAmmo, 9999, 1);
}

void teleport(float x,  float y,  float z) {
    *(float*)findMemoryAddress(pwnAventAddr + 0x18FCD60, { 0x20,  0x238,  0x280,  0x90 }) = x;
    *(float*)findMemoryAddress(pwnAventAddr + 0x18FCD60, { 0x20,  0x238,  0x280,  0x94 }) = y;
    *(float*)findMemoryAddress(pwnAventAddr + 0x18FCD60, { 0x20,  0x238,  0x280,  0x98 }) = z;
}

void createActor() {
    _Chat Chat = (_Chat)(gameLogicAddr + 0x551A0);
    _ActorFactoryBear ActoryFactoryBear = (_ActorFactoryBear)(gameLogicAddr + 0x1A140);
    void* actorFactory = ActoryFactoryBear();
    cout << "ActorFactory: " << actorFactory << endl;
     _CreateActor CreateActor = (_CreateActor)(gameLogicAddr + 0x222b0);
    void* actor = CreateActor(actorFactory);
    cout << "Actor: " << actor << endl;
    _BearInit BearInit = (_BearInit)(gameLogicAddr + 0x383c0);
    BearInit(actor);
    _GetHealth GetHealth = (_GetHealth)(gameLogicAddr+ 0x1780);
    _AddToWorld AddToWorld = (_AddToWorld)(gameLogicAddr + 0x62eb0);
    AddToWorld((void*)(gameLogicAddr + 0x97d7c),  actor);
}

void showEnemiesLocation(uintptr_t baseAddr) {
    for (int i = 0x0; i < 0x1A; i += 0xC) {
        for (int j = 0x0; j <= 0x8; j += 0x4) {
            std::cout << *(float*)findMemoryAddress(baseAddr + 0x166C150, { 0xF7C, 0x378 + i, 0xD4, 0x90 + j });
            std::cout << " , ";
        }
        std::cout << "\n";
    }
}
