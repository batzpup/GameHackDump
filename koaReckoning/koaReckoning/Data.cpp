
#include <cstdint>
struct Vector3
{
	float x, y, z;
};

class World
{
public:
	class CameraRelated* cameraRelated; //0x0000
	char pad_0004[12]; //0x0004
	class Player* player; //0x0010
	char pad_0014[44]; //0x0014
}; //Size: 0x0040
static_assert(sizeof(World) == 0x40);

class N00000476
{
public:
	char pad_0000[4]; //0x0000
	class N0000048A* N00000478; //0x0004
	char pad_0008[60]; //0x0008
}; //Size: 0x0044
static_assert(sizeof(N00000476) == 0x44);

class N0000048A
{
public:
	char pad_0000[68]; //0x0000
}; //Size: 0x0044
static_assert(sizeof(N0000048A) == 0x44);

class Player
{
public:
	char pad_0000[4]; //0x0000
	class N00000703* CombatPart; //0x0004
	class N000004B2* TargetPart; //0x0008
	char pad_000C[16]; //0x000C
	class LocationPart* locationPart; //0x001C
	class N00000BAF* RenderingPart; //0x0020
	class N00000B1B* StatsPart; //0x0024
	class N00000AE3* InventoryPart; //0x0028
	char pad_002C[132]; //0x002C
}; //Size: 0x00B0
static_assert(sizeof(Player) == 0xB0);

class N000004B2
{
public:
	char pad_0000[4]; //0x0000
	class N000004C6* N000004B4; //0x0004
	char pad_0008[60]; //0x0008
}; //Size: 0x0044
static_assert(sizeof(N000004B2) == 0x44);

class N000004C6
{
public:
	char pad_0000[4]; //0x0000
	class HealthComponent* healtComponent; //0x0004
	char pad_0008[60]; //0x0008
}; //Size: 0x0044
static_assert(sizeof(N000004C6) == 0x44);

class HealthComponent
{
public:
	char pad_0000[72]; //0x0000
	uint32_t currentHealth; //0x0048
	uint32_t maxHealth; //0x004C
	char pad_0050[2108]; //0x0050
}; //Size: 0x088C
static_assert(sizeof(HealthComponent) == 0x88C);

class N00000703
{
public:
	char pad_0000[4]; //0x0000
	class N0000093A* N00000705; //0x0004
	char pad_0008[60]; //0x0008
}; //Size: 0x0044
static_assert(sizeof(N00000703) == 0x44);

class N00000757
{
public:
	char pad_0000[4]; //0x0000
	class N000007AC* N00000759; //0x0004
	char pad_0008[32]; //0x0008
	class N000008C1* N00000762; //0x0028
	char pad_002C[168]; //0x002C
	uint32_t N0000078D; //0x00D4
	char pad_00D8[108]; //0x00D8
}; //Size: 0x0144
static_assert(sizeof(N00000757) == 0x144);

class N000007AC
{
public:
	char pad_0000[1092]; //0x0000
}; //Size: 0x0444
static_assert(sizeof(N000007AC) == 0x444);

class N000008C1
{
public:
	char pad_0000[324]; //0x0000
}; //Size: 0x0144
static_assert(sizeof(N000008C1) == 0x144);

class N0000093A
{
public:
	char pad_0000[4]; //0x0000
	class N0000094E* N0000093C; //0x0004
	char pad_0008[784]; //0x0008
	class N00000D23* N00000C8A; //0x0318
}; //Size: 0x031C
static_assert(sizeof(N0000093A) == 0x31C);

class N0000094E
{
public:
	char pad_0000[324]; //0x0000
}; //Size: 0x0144
static_assert(sizeof(N0000094E) == 0x144);

class LocationPart
{
public:
	char pad_0000[4]; //0x0000
	class MainLocationPart* mainLocationPart; //0x0004
	char pad_0008[60]; //0x0008
}; //Size: 0x0044
static_assert(sizeof(LocationPart) == 0x44);

class MainLocationPart
{
public:
	char pad_0000[792]; //0x0000
	class PosHolder* posHolder; //0x0318
	char pad_031C[552]; //0x031C
}; //Size: 0x0544
static_assert(sizeof(MainLocationPart) == 0x544);

class N000009CA
{
public:
	char pad_0000[36]; //0x0000
	Vector3 PositionReadOnly; //0x0024
	char pad_0030[36]; //0x0030
	Vector3 N000009DF; //0x0054
	char pad_0060[36]; //0x0060
	Vector3 N000009E9; //0x0084
	char pad_0090[892]; //0x0090
	Vector3 N00000AC9; //0x040C
	char pad_0418[36]; //0x0418
	Vector3 N00000AD3; //0x043C
	char pad_0448[36]; //0x0448
}; //Size: 0x046C
static_assert(sizeof(N000009CA) == 0x46C);

class N00000AE3
{
public:
	char pad_0000[4]; //0x0000
	class N00000AF7* N00000AE5; //0x0004
	char pad_0008[60]; //0x0008
}; //Size: 0x0044
static_assert(sizeof(N00000AE3) == 0x44);

class N00000AF7
{
public:
	char pad_0000[132]; //0x0000
}; //Size: 0x0084
static_assert(sizeof(N00000AF7) == 0x84);

class N00000B1B
{
public:
	char pad_0000[4]; //0x0000
	class N00000B2F* N00000B1D; //0x0004
	char pad_0008[60]; //0x0008
}; //Size: 0x0044
static_assert(sizeof(N00000B1B) == 0x44);

class N00000B2F
{
public:
	char pad_0000[4]; //0x0000
	class N00000B43* N00000B31; //0x0004
	char pad_0008[60]; //0x0008
}; //Size: 0x0044
static_assert(sizeof(N00000B2F) == 0x44);

class N00000B43
{
public:
	char pad_0000[324]; //0x0000
}; //Size: 0x0144
static_assert(sizeof(N00000B43) == 0x144);

class N00000BAF
{
public:
	char pad_0000[4]; //0x0000
	class N00000BC3* N00000BB1; //0x0004
	char pad_0008[60]; //0x0008
}; //Size: 0x0044
static_assert(sizeof(N00000BAF) == 0x44);

class N00000BC3
{
public:
	char pad_0000[68]; //0x0000
}; //Size: 0x0044
static_assert(sizeof(N00000BC3) == 0x44);

class N00000D23
{
public:
	char pad_0000[68]; //0x0000
}; //Size: 0x0044
static_assert(sizeof(N00000D23) == 0x44);

class PosHolder
{
public:
	char pad_0000[36]; //0x0000
	Vector3 Pos; //0x0024
	char pad_0030[28]; //0x0030
}; //Size: 0x004C
static_assert(sizeof(PosHolder) == 0x4C);

class CameraRelated
{
public:
	char pad_0000[68]; //0x0000
	class CameraRelated1* cameraRelated1; //0x0044
}; //Size: 0x0048
static_assert(sizeof(CameraRelated) == 0x48);

class N000009DB
{
public:
	char pad_0000[68]; //0x0000
}; //Size: 0x0044
static_assert(sizeof(N000009DB) == 0x44);

class CameraRelated1
{
public:
	char pad_0000[8]; //0x0000
	class CameraRelated2* cameraRelated2; //0x0008
	char pad_000C[56]; //0x000C
}; //Size: 0x0044
static_assert(sizeof(CameraRelated1) == 0x44);

class CameraRelated2
{
public:
	char pad_0000[200]; //0x0000
	class cameraRelated3* cameraRelated3; //0x00C8
}; //Size: 0x00CC
static_assert(sizeof(CameraRelated2) == 0xCC);

class cameraRelated3
{
public:
	char pad_0000[260]; //0x0000
	class Camera* camera; //0x0104
	char pad_0108[60]; //0x0108
}; //Size: 0x0144
static_assert(sizeof(cameraRelated3) == 0x144);

class Camera
{
public:
	char pad_0000[12]; //0x0000
	Vector3 CameraPos; //0x000C
	char pad_0018[52]; //0x0018
}; //Size: 0x004C
static_assert(sizeof(Camera) == 0x4C);