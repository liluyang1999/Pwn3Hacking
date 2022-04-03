#pragma once

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Vector4 {
    float x;
    float y;
    float z;
    float w;
};

void getItems();

void teleport(float x, float y, float z);

void showEnemiesLocation(uintptr_t baseAddr);

void createActor();

//Original functions in the game
typedef void(__thiscall* _Chat)(void* playerVftblptr, const char* text);  
typedef bool(__thiscall* _AddItem)(void* playerVftPtr, void* IItemPtr, unsigned int count, bool allowPartial);  
typedef void(__thiscall* _GiveAll)(void* gameAPIPtr, void* iPlayerPtr);  
typedef void* (__thiscall* _GetItemByName)(void* gamePtr, const char* name);  
typedef void(__thiscall* _Teleport)(void* playerVftPtr, const char* location);  
typedef void(__thiscall* _FastTravel)(void* playerVftPtr, const char* origin, const char* dest);   
typedef void* (__thiscall* _CreateActor)(void* actorFactory);  
typedef void* (__thiscall* _ActorFactoryBear)();  
typedef void(__thiscall* _BearInit)(void* bear);
typedef char* (__thiscall* _GetDisplayName)(void*); 
typedef void(__thiscall* _SetPosition)(void* actor, Vector3* param_1);  
typedef int(__thiscall* _GetHealth)(void* actor);  
typedef void(__thiscall* _AddToWorld)(void* world, void* actor);  
typedef void* (__thiscall* _Spawn)();
