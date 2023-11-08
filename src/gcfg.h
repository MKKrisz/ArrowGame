#pragma once

typedef enum GcfgValues {
    GCFG_PLAYERCOUNT = 0,
    GCFG_ACCEL = 1,
    GCFG_ANGULAR = 2,
    GCFG_FRICTION = 3,
    GCFG_HP = 4,
    GCFG_WEAPON_TYPE = 5,
    GCFG_WEAPON_DMG = 6,
    GCFG_WEAPON_SPD = 7,
    GCFG_WEAPON_ACC = 8,
    GCFG_WEAPON_FRATE = 9,
    GCFG_WEAPON_RRATE = 10,
    GCFG_WEAPON_MAGSIZE = 11,
    GCFG_COUNT = 12
} GcfgValues;

typedef enum RangeType {
    SINGLE = 1,
    DOUBLE = 2,
} RType;

typedef struct Range {
    RType type;
    float min;
    float max;
} Range;

typedef struct GameConfig {
    Range Values[12];
} Gcfg;

Gcfg gcfg_Defaults();
Gcfg gcfg_Load(const char* path);
void gcfg_Save(const char* path, Gcfg* cfg);
