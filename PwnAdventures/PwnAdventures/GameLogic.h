#include <stdio.h>
#include <map>
#include <string>
#include <cstring>
#include <functional>
#include <set>
#define _GNU_SOURCE

struct Vector3
{
	float x, y, z;
};

enum DamageType { PhysicalDamage, FireDamage, ColdDamage, ShockDamage };
enum ItemRarity { ResourceItem, NormalItem, RareItem, LegendaryItem, LeetItem };
enum NPCStateTransitionType { EndConversationTransition, ContinueConversationTransition, ShopTransition };

class World
{
public:
	class ClientWorld* clientWorld; //0x0000
	char pad_0004[48]; //0x0004
}; //Size: 0x0034
static_assert(sizeof(World) == 0x34);



class ClientWorld
{
public:
	char pad_0000[4]; //0x0000
	class PlayerList* players; //0x0004
	int32_t playerLen; //0x0008
	class ActorList* actors; //0x000C
	int32_t actorsLen; //0x0010
	class N00000CB2* actorsById; //0x0014
	int32_t actorsByIdLen; //0x0018
	class N00000CC7* localPlayer; //0x001C
	int32_t nextId; //0x0020
	class AiZones* aiZones; //0x0024
	char pad_0028[4]; //0x0028
	class Player* activePlayer; //0x002C
	float timeUntilNextTick; //0x0030
}; //Size: 0x0034
static_assert(sizeof(ClientWorld) == 0x34);


class Player
{
public:
	char pad_0000[4]; //0x0000
	int32_t characterId; //0x0004
	char pad_0008[16]; //0x0008
	int32_t avatarIndex; //0x0018
	int32_t colours[4]; //0x001C
	char pad_002C[32]; //0x002C
	class Inventory* inventory; //0x004C
	char pad_0050[4]; //0x0050
	class N00000952* pickups; //0x0054
	char pad_0058[4]; //0x0058
	class N00000966* cooldowns; //0x005C
	char pad_0060[4]; //0x0060
	class N0000097A* circuitInput; //0x0064
	char pad_0068[4]; //0x0068
	class N0000098E* circuitOutput; //0x006C
	char pad_0070[4]; //0x0070
	uint8_t admin; //0x0074
	int8_t pvpEnabled; //0x0075
	uint8_t pvpDesired; //0x0076
	char pad_0077[1]; //0x0077
	float pvpChangeTimer; //0x0078
	uint32_t pvpChangeReportedTimer; //0x007C
	char pad_0080[4]; //0x0080
	char currentLocation[24]; //0x0084
	char changeRegionDestination[24]; //0x009C
	class N000009AE* aiZones; //0x00B4
	char pad_00B8[4]; //0x00B8
	int32_t mana; //0x00BC
	float manaRegenTimer; //0x00C0
	float healthRegenCooldown; //0x00C4
	float healthRegenTimer; //0x00C8
	int32_t countdown; //0x00CC
	Vector3 remoteLookPos; //0x00D0
	Vector3 remoteLookRot; //0x00DC
	char hotbarItems[10][4]; //0x00E8
	uint32_t currentSlot; //0x0110
	class N000009CF* questStates; //0x0114
	char pad_0118[4]; //0x0118
	class IQuest* currentQuest; //0x011C
	float walkingSpeed; //0x0120
	float jumpForce; //0x0124
	float jumpHoldTime; //0x0128
	class N000009FA* currentNpc; //0x012C
	char currentNpcState[4]; //0x0130
	char pad_0134[20]; //0x0134
	class N00000A39* localPlayer; //0x0148
	class N00000A8E* eventsTosend; //0x014C
	int8_t itemsUpated; //0x0150
	char pad_0151[3]; //0x0151
	float itemSyncTimer; //0x0154
	int32_t chatMessageCounter; //0x0158
	float chatFloodDecayTimer; //0x015C
	class N00000AA8* lastHitByItem; //0x0160
	float lastHitItemLeft; //0x0164
	float circuitStateCooldownTimer; //0x0168
}; //Size: 0x016C
static_assert(sizeof(Player) == 0x16C);

class IQuest
{

};
