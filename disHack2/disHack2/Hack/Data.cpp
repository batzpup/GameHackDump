#include <cstdint>


struct Vector3
{
	float x, y, z;
};

// Created with ReClass.NET 1.2 by KN4CK3R

class PlayerManager
{
public:
	class Player* playerPtr; //0x0000
}; //Size: 0x0004
static_assert(sizeof(PlayerManager) == 0x4);

class Player
{
public:
	char pad_0000[56]; //0x0000
	class PowerList* powerList; //0x0038
	char pad_003C[136]; //0x003C
	Vector3 position; //0x00C4
	char pad_00D0[60]; //0x00D0
	class CameraRelated* cameraRelated; //0x010C
	char pad_0110[164]; //0x0110
	float xVel; //0x01B4
	float yVel; //0x01B8
	float zVel; //0x01BC
	char pad_01C0[388]; //0x01C0
	int32_t currentHealth; //0x0344
	int32_t maxHealth; //0x0348
	char pad_034C[148]; //0x034C
	class CameraCrouchRelated* cameraCrouchRelated; //0x03E0
	char pad_03E4[440]; //0x03E4
	class Inventory* inventoryPtr; //0x059C
	char pad_05A0[1216]; //0x05A0
	uint32_t currentMana; //0x0A60
	uint32_t maxMana; //0x0A64
	uint32_t regenToMana; //0x0A68
	char pad_0A6C[76]; //0x0A6C
	float currentBreath; //0x0AB8
	float maxBreath; //0x0ABC
	char pad_0AC0[172]; //0x0AC0
	int32_t isSwimming; //0x0B6C
}; //Size: 0x0B70
static_assert(sizeof(Player) == 0xB70);

class PowerList
{
public:
	char pad_0000[56]; //0x0000
	class PowerThisPtr* powerThisPtr; //0x0038
	class BlinkPower* blink; //0x003C
	char pad_0040[4]; //0x0040
	class BendTimePower* bendTime; //0x0044
	class WindBlastPower* windBlast; //0x0048
	class PossessionPower* possession; //0x004C
	class DarkSensePower* darkSense; //0x0050
	class DevouringSwarmPower* devouringSwarm; //0x0054
}; //Size: 0x0058
static_assert(sizeof(PowerList) == 0x58);

class BlinkPower
{
public:
	char pad_0000[108]; //0x0000
	uint32_t powerId; //0x006C
	char pad_0070[24]; //0x0070
	int32_t level; //0x0088
	char pad_008C[156]; //0x008C
	class BlinkConstants* blinkConstant; //0x0128
	char pad_012C[96]; //0x012C
}; //Size: 0x018C
static_assert(sizeof(BlinkPower) == 0x18C);

class BlinkConstants
{
public:
	float blink1Max; //0x0000
	float blink1HorizontalMax; //0x0004
	float blink1VericalMax; //0x0008
	float blink1StepSize; //0x000C
	float blink1TimeBetweenSteps; //0x0010
	float blinkSlowStrength; //0x0014
	float blinkSlowDuration; //0x0018
	float blink1FovWobbleDampener; //0x001C
	float blink1Cooldown; //0x0020
	float blink1fovBlurSqueezeSpeed; //0x0024
	float blink1FovWobbleSpeed; //0x0028
	float blink1fovBlurReboundSpeed; //0x002C
	float blink1HorizontalBlurStrength; //0x0030
	float blink1VerticalBlurStrength; //0x0034
	float blink1VericalBlurLengthDivisor; //0x0038
	char pad_003C[4]; //0x003C
}; //Size: 0x0040
static_assert(sizeof(BlinkConstants) == 0x40);

class BendTimePower
{
public:
	char pad_0000[108]; //0x0000
	uint32_t powerId; //0x006C
	char pad_0070[24]; //0x0070
	int32_t level; //0x0088
	char pad_008C[12]; //0x008C
	float duration; //0x0098
	char pad_009C[64]; //0x009C
}; //Size: 0x00DC
static_assert(sizeof(BendTimePower) == 0xDC);

class WindBlastPower
{
public:
	char pad_0000[108]; //0x0000
	uint32_t powerId; //0x006C
	char pad_0070[24]; //0x0070
	int32_t level; //0x0088
}; //Size: 0x008C
static_assert(sizeof(WindBlastPower) == 0x8C);

class PossessionPower
{
public:
	char pad_0000[108]; //0x0000
	uint32_t powerId; //0x006C
	char pad_0070[24]; //0x0070
	int32_t level; //0x0088
}; //Size: 0x008C
static_assert(sizeof(PossessionPower) == 0x8C);

class DarkSensePower
{
public:
	char pad_0000[108]; //0x0000
	uint32_t powerId; //0x006C
	char pad_0070[24]; //0x0070
	int32_t level; //0x0088
	char pad_008C[8]; //0x008C
	float activeTimeReamining; //0x0094
	float cooldown; //0x0098
	float deactiveCooldown; //0x009C
	char pad_00A0[4]; //0x00A0
	int32_t numberOfEntsRendered; //0x00A4
	char pad_00A8[8]; //0x00A8
}; //Size: 0x00B0
static_assert(sizeof(DarkSensePower) == 0xB0);

class DevouringSwarmPower
{
public:
	char pad_0000[92]; //0x0000
	Vector3 spawnLocation; //0x005C
	char pad_0068[4]; //0x0068
	uint32_t powerId; //0x006C
	char pad_0070[24]; //0x0070
	int32_t level; //0x0088
	char pad_008C[88]; //0x008C
}; //Size: 0x00E4
static_assert(sizeof(DevouringSwarmPower) == 0xE4);

class Inventory
{
public:
	char pad_0000[188]; //0x0000
	class AmmoInventory* ammoInventory; //0x00BC
	char pad_00C0[8]; //0x00C0
	class ResourceInventory* resourceInventory; //0x00C8
	char pad_00CC[8]; //0x00CC
	uint32_t healthPotions; //0x00D4
	uint32_t manaPotions; //0x00D8
	char pad_00DC[72]; //0x00DC
}; //Size: 0x0124
static_assert(sizeof(Inventory) == 0x124);

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
	uint32_t maxStickyGrenade; //0x003C
	uint32_t explosiveBolt; //0x0040
	uint32_t maxExplosiveBolt; //0x0044
	uint32_t arcMine; //0x0048
	uint32_t maxArcMine; //0x004C
	uint32_t chokeDust; //0x0050
	uint32_t maxChokeDust; //0x0054
	uint32_t stunMine; //0x0058
	uint32_t maxStunMine; //0x005C
}; //Size: 0x0060
static_assert(sizeof(AmmoInventory) == 0x60);

class PowerThisPtr
{
public:
	char pad_0000[68]; //0x0000
}; //Size: 0x0044
static_assert(sizeof(PowerThisPtr) == 0x44);

class ResourceSlot
{
public:
	class ItemInfo* itemInfo; //0x0000
	uint32_t amount; //0x0004
	uint32_t isHidden; //0x0008
}; //Size: 0x000C
static_assert(sizeof(ResourceSlot) == 0xC);

class ResourceInventory
{
public:
	class ResourceSlot resourceSlots[64]; //0x0000
	char pad_0300[2116]; //0x0300
}; //Size: 0x0B44
static_assert(sizeof(ResourceInventory) == 0xB44);

class ItemInfo
{
public:
	char pad_0000[56]; //0x0000
	wchar_t* itemName; //0x0038
	char pad_003C[56]; //0x003C
}; //Size: 0x0074
static_assert(sizeof(ItemInfo) == 0x74);

class CameraCrouchRelated
{
public:
	char pad_0000[224]; //0x0000
	float CameraUncrouchedOffset; //0x00E0
	char pad_00E4[32]; //0x00E4
}; //Size: 0x0104
static_assert(sizeof(CameraCrouchRelated) == 0x104);

class CameraRelated
{
public:
	char pad_0000[900]; //0x0000
	class Camera* camera; //0x0384
	char pad_0388[188]; //0x0388
}; //Size: 0x0444
static_assert(sizeof(CameraRelated) == 0x444);

class Camera
{
public:
	char pad_0000[816]; //0x0000
	float cameraX; //0x0330
	float cameraY; //0x0334
	float cameraZ; //0x0338
	char pad_033C[72]; //0x033C
}; //Size: 0x0384
static_assert(sizeof(Camera) == 0x384);
class EnhancementBase
{
public:
	class EnhancmentListPointer1* enhancmentListPointer1; //0x0000
}; //Size: 0x0004
static_assert(sizeof(EnhancementBase) == 0x4);

class EnhancmentListPointer1
{
public:
	char pad_0000[500]; //0x0000
	class EnhancmentListPointer2* enhancmentListPointer2; //0x01F4
}; //Size: 0x01F8
static_assert(sizeof(EnhancmentListPointer1) == 0x1F8);

class EnhancmentListPointer2
{
public:
	char pad_0000[84]; //0x0000
	class EnhancementList* enhancementList; //0x0054
}; //Size: 0x0058
static_assert(sizeof(EnhancmentListPointer2) == 0x58);

class EnhancementInfo
{
public:
	int32_t id; //0x0000
	char pad_0004[20]; //0x0004
	int32_t level; //0x0018
}; //Size: 0x001C
static_assert(sizeof(EnhancementInfo) == 0x1C);

class EnhancementList
{
public:
	class EnhancementInfo EnhancementArray[4]; //0x0000
}; //Size: 0x0070
static_assert(sizeof(EnhancementList) == 0x70);

class EnemyEnt
{
public:
	class N0000017C* vTable; //0x0000
	char pad_0004[192]; //0x0004
	Vector3 position; //0x00C4
	char pad_00D0[628]; //0x00D0
	int32_t currentHealth; //0x0344
	int32_t maxHealth; //0x0348
}; //Size: 0x034C
static_assert(sizeof(EnemyEnt) == 0x34C);

class unknown2
{
public:
	char pad_0000[788]; //0x0000
	class MasterManager* mangers; //0x0314
	char pad_0318[1324]; //0x0318
}; //Size: 0x0844
static_assert(sizeof(unknown2) == 0x844);

class MasterManager
{
public:
	class LevelManager* levelManager; //0x0000
	char pad_0004[64]; //0x0004
}; //Size: 0x0044
static_assert(sizeof(MasterManager) == 0x44);

class LevelManager
{
public:
	char pad_0000[56]; //0x0000
	int32_t currentLevelId; //0x0038
	char pad_003C[8]; //0x003C
}; //Size: 0x0044
static_assert(sizeof(LevelManager) == 0x44);
