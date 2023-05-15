#pragma once
#include <cstdio>
#include <cstdint>
#include <Windows.h>
struct vec3
{
	float x, y, z;
};
using Vector3 = vec3;
class Ent
{
public:
	char pad_0000[4]; //0x0000
	Vector3 headPos; //0x0004
	Vector3 velocity; //0x0010
	char pad_001C[24]; //0x001C
	Vector3 bodypos; //0x0034
	Vector3 camerPitchYawRoll; //0x0040
	char pad_004C[8]; //0x004C
	int32_t timeSinceGrounded; //0x0054
	char pad_0058[4]; //0x0058
	float currentHeadOffset; //0x005C
	float maxHeadOffset; //0x0060
	char pad_0064[5]; //0x0064
	bool isGrounded; //0x0069
	char pad_006A[1]; //0x006A
	bool isJumping; //0x006B
	char pad_006C[2]; //0x006C
	bool isCrouching; //0x006E
	char pad_006F[19]; //0x006F
	uint8_t playerMode; //0x0082
	uint8_t isInvisible; //0x0083
	char pad_0084[116]; //0x0084
	int16_t health; //0x00F8
	char pad_00FA[2]; //0x00FA
	int16_t armour; //0x00FC
	char pad_00FE[294]; //0x00FE
	bool isFiring; //0x0224
	char name[16]; //0x0225
	char pad_0235[247]; //0x0235
	uint8_t teamId; //0x032C
	char pad_032D[11]; //0x032D
	uint8_t canFly5; //0x0338
	char pad_0339[59]; //0x0339
	class Weapon* currentWeapon; //0x0374
	char pad_0378[388]; //0x0378


}; 



class Weapon
{
public:
public:
	char pad_0000[4]; //0x0000
	uint32_t weaponId; //0x0004
	class Ent* owner; //0x0008
	class WeaponData* weaponDataPtr; //0x000C
	class AmmoPointer* ammoPointer; //0x0010
	char pad_0014[8]; //0x0014
	uint8_t bulletsShotThisPress; //0x001C
	char pad_001D[2071]; //0x001D
}; //Size: 0x0834
static_assert(sizeof(Weapon) == 0x834);


class WeaponData
{
public:
	char pad_0000[260]; //0x0000
	int16_t soundId; //0x0104
	int16_t reloadSoundId; //0x0106
	int16_t reloadSpeed; //0x0108
	int16_t timeBetweenShots; //0x010A
	int16_t damage; //0x010C
	int16_t N00000660; //0x010E
	int16_t N0000060E; //0x0110
	int16_t N00000662; //0x0112
	int16_t spreadArea; //0x0114
	int16_t knockBack; //0x0116
	int16_t clipSize; //0x0118
	int16_t zHandMovement; //0x011A
	int16_t yHandMovement; //0x011C
	int16_t xHandMovement; //0x011E
	int16_t initialRecoil; //0x0120
	int16_t recoil; //0x0122
	int16_t dragDownForce; //0x0124
	int16_t N0000066C; //0x0126
	int16_t isAuto; //0x0128
	int16_t N0000066E; //0x012A
	int16_t N00000600; //0x012C
	int16_t N00000670; //0x012E
	int16_t N00000616; //0x0130
}; //Size: 0x0132
static_assert(sizeof(WeaponData) == 0x132);


class AmmoPointer
{
public:
	int32_t reserveAmmo; //0x0000
	char pad_0004[36]; //0x0004
	int32_t currentAmmo; //0x0028
	char pad_002C[24]; //0x002C
}; //Size: 0x0044
