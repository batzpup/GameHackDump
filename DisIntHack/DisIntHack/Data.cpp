#include <cstdint>


struct Vector3
{
    float x, y, z;
};

// Created with ReClass.NET 1.2 by KN4CK3R

class World
{
public:
	class Player* playerPtr; //0x0000
	char pad_0004[52]; //0x0004
}; //Size: 0x0038
static_assert(sizeof(World) == 0x38);

class N00000065
{
public:
	class N00000196* N00000067; //0x0000
	char pad_0004[52]; //0x0004
	uint32_t N00000075; //0x0038
	uint32_t N00000076; //0x003C
	char pad_0040[4]; //0x0040
	uint32_t N00000078; //0x0044
	uint32_t N00000079; //0x0048
	char pad_004C[116]; //0x004C
	Vector3 position; //0x00C0
	char pad_00CC[628]; //0x00CC
	uint32_t N00000137; //0x0340
	char pad_0344[248]; //0x0344
}; //Size: 0x043C
static_assert(sizeof(N00000065) == 0x43C);

class N00000196
{
public:
	char pad_0000[68]; //0x0000
}; //Size: 0x0044
static_assert(sizeof(N00000196) == 0x44);

class Player
{
public:
	char pad_0000[196]; //0x0000
	Vector3 position; //0x00C4
	char pad_00D0[416]; //0x00D0
	class N00000CBF* bankPtr1; //0x0270
	char pad_0274[44]; //0x0274
	class N000007B4* N00000365; //0x02A0
	char pad_02A4[160]; //0x02A4
	uint32_t curentHealth; //0x0344
	uint32_t maxHealth; //0x0348
	char pad_034C[592]; //0x034C
	class Inventory* inventory; //0x059C
	char pad_05A0[1216]; //0x05A0
	uint32_t currentMana; //0x0A60
	uint32_t maxMana; //0x0A64
	char pad_0A68[80]; //0x0A68
	float breath; //0x0AB8
	float maxBreath; //0x0ABC
	char pad_0AC0[172]; //0x0AC0
	int8_t currentAction; //0x0B6C
}; //Size: 0x0B6D


class Inventory
{
public:
	char pad_0000[188]; //0x0000
	class AmmoInventory* ammoInventory; //0x00BC
	char pad_00C0[900]; //0x00C0
}; //Size: 0x0444
static_assert(sizeof(Inventory) == 0x444);

class AmmoInventory
{
public:
	uint32_t regularBullet; //0x0000
	uint32_t maxRegBullets; //0x0004
	uint32_t explosiveBullet; //0x0008
	uint32_t maxExplosiveBullets; //0x000C
	uint32_t crossbowBolt; //0x0010
	uint32_t maxCrossbowBolt; //0x0014
	uint32_t sleepDart; //0x0018
	uint32_t maxSleepdart; //0x001C
	uint32_t incendiaryBolt; //0x0020
	uint32_t maxIncendiaryBolt; //0x0024
	uint32_t springRazor; //0x0028
	uint32_t maxSpringRazor; //0x002C
	uint32_t grenade; //0x0030
	uint32_t maxGrenade; //0x0034
	uint32_t stickyGrenade; //0x0038
	uint32_t maxSticketGrenade; //0x003C
	uint32_t explosiveBolt; //0x0040
	uint32_t maxExplosiveBolt; //0x0044
	uint32_t arcMine; //0x0048
	uint32_t maxArcMine; //0x004C
	uint32_t chokeDust; //0x0050
	uint32_t maxChokeDust; //0x0054
	uint32_t stunMine; //0x0058
	uint32_t maxStunMine; //0x005C
	char pad_0060[256]; //0x0060
}; //Size: 0x0160
static_assert(sizeof(AmmoInventory) == 0x160);

class N000007B4
{
public:
	char pad_0000[36]; //0x0000
	class Player* player; //0x0024
	char pad_0028[236]; //0x0028
	class N0000081C* N000007FA; //0x0114
	char pad_0118[44]; //0x0118
}; //Size: 0x0144
static_assert(sizeof(N000007B4) == 0x144);

class N0000081C
{
public:
	char pad_0000[112]; //0x0000
	class N00000840* N00000839; //0x0070
	char pad_0074[16]; //0x0074
}; //Size: 0x0084
static_assert(sizeof(N0000081C) == 0x84);

class N00000840
{
public:
	char pad_0000[36]; //0x0000
	class N00000854* N0000084A; //0x0024
}; //Size: 0x0028
static_assert(sizeof(N00000840) == 0x28);

class N00000854
{
public:
	char pad_0000[44]; //0x0000
	uint32_t N00000860; //0x002C
	char pad_0030[20]; //0x0030
	uint32_t N0000091D; //0x0044
	char pad_0048[332]; //0x0048
	class InventoryPotions* N00000977; //0x0194
	char pad_0198[172]; //0x0198
}; //Size: 0x0244
static_assert(sizeof(N00000854) == 0x244);

class InventoryPotions
{
public:
	char pad_0000[36]; //0x0000
	class Player* player; //0x0024
	char pad_0028[172]; //0x0028
	uint32_t healthPotions; //0x00D4
	uint32_t manaPotions; //0x00D8
}; //Size: 0x00DC
static_assert(sizeof(InventoryPotions) == 0xDC);

class N00000A13
{
public:
	char pad_0000[88]; //0x0000
	class N00000A39* ammoPtr2; //0x0058
	char pad_005C[48]; //0x005C
}; //Size: 0x008C
static_assert(sizeof(N00000A13) == 0x8C);

class N00000A39
{
public:
	char pad_0000[36]; //0x0000
	class N00000A4D* ammoPtr3; //0x0024
	char pad_0028[28]; //0x0028
}; //Size: 0x0044
static_assert(sizeof(N00000A39) == 0x44);

class N00000A4D
{
public:
	char pad_0000[84]; //0x0000
	class N00000A71* ammoPtr4; //0x0054
	char pad_0058[44]; //0x0058
}; //Size: 0x0084
static_assert(sizeof(N00000A4D) == 0x84);

class N00000A71
{
public:
	char pad_0000[188]; //0x0000
	class AmmoInventory* ammoInventory; //0x00BC
	char pad_00C0[900]; //0x00C0
}; //Size: 0x0444
static_assert(sizeof(N00000A71) == 0x444);

class N00000BF2
{
public:
	char pad_0000[36]; //0x0000
	class N00000C06* N00000BFC; //0x0024
	char pad_0028[28]; //0x0028
}; //Size: 0x0044
static_assert(sizeof(N00000BF2) == 0x44);

class N00000C06
{
public:
	char pad_0000[84]; //0x0000
	class N00000C20* N00000C1C; //0x0054
	char pad_0058[4]; //0x0058
}; //Size: 0x005C
static_assert(sizeof(N00000C06) == 0x5C);

class N00000C20
{
public:
	char pad_0000[200]; //0x0000
	class N00000C56* N00000C53; //0x00C8
}; //Size: 0x00CC
static_assert(sizeof(N00000C20) == 0xCC);

class N00000C56
{
public:
	char pad_0000[88]; //0x0000
	uint32_t coins; //0x0058
	char pad_005C[212]; //0x005C
	uint32_t runes; //0x0130
	char pad_0134[80]; //0x0134
}; //Size: 0x0184
static_assert(sizeof(N00000C56) == 0x184);

class N00000CBF
{
public:
	char pad_0000[56]; //0x0000
	class N00000CD3* bankPtr2; //0x0038
	char pad_003C[8]; //0x003C
}; //Size: 0x0044
static_assert(sizeof(N00000CBF) == 0x44);

class N00000CD3
{
public:
	char pad_0000[32]; //0x0000
	class N00000CE7* bankPtr3; //0x0020
	char pad_0024[32]; //0x0024
}; //Size: 0x0044
static_assert(sizeof(N00000CD3) == 0x44);

class N00000CE7
{
public:
	char pad_0000[36]; //0x0000
	class N00000CFB* bankPtr4; //0x0024
	char pad_0028[28]; //0x0028
}; //Size: 0x0044
static_assert(sizeof(N00000CE7) == 0x44);

class N00000CFB
{
public:
	char pad_0000[336]; //0x0000
	class N00000D62* bankPtr5; //0x0150
	char pad_0154[48]; //0x0154
}; //Size: 0x0184
static_assert(sizeof(N00000CFB) == 0x184);

class N00000D62
{
public:
	char pad_0000[200]; //0x0000
	class bank* bank; //0x00C8
	char pad_00CC[120]; //0x00CC
}; //Size: 0x0144
static_assert(sizeof(N00000D62) == 0x144);

class bank
{
public:
	char pad_0000[88]; //0x0000
	uint32_t coins; //0x0058
	char pad_005C[212]; //0x005C
	uint32_t runes; //0x0130
	char pad_0134[4]; //0x0134
}; //Size: 0x0138
static_assert(sizeof(bank) == 0x138);