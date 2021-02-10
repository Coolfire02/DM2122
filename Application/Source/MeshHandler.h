#pragma once
#include "Mesh.h"
#include "MeshBuilder.h"
#include "EntityDataHandler.h"

enum GEOMETRY_TYPE {

	//For OBJs
	GEO_OBJ_FENCE,
	GEO_SONIC_EGGMAN,
	GEO_SONIC_TAILS,

	GEO_PODIUM_1ST,
	GEO_SHOPBASE,

	GEO_SPOTLIGHT,

	//Textured Quads
	GEO_RUNNINGFLOOR,
	GEO_TEXTBACKDROP,

	//For non-OBJs

	//Coin
	GEO_COIN,

	//Sonic
	GEO_SONIC_HEAD,
	GEO_SONIC_EYEBALL,
	GEO_SONIC_GREENEYE,
	GEO_SONIC_BLACKEYE,
	GEO_SONIC_EARS,
	GEO_SONIC_INNERSONICEARS,
	GEO_SONIC_MOUTHTORUS,
	GEO_SONIC_MOUTHSPHERE,
	GEO_SONIC_NOSESPHERE,

	GEO_SONIC_NOSE_HEMISPHERE,

	GEO_SONIC_HAIRHEMISPHERE,
	GEO_SONIC_HAIRHEMISPHEREFRUSTUM,
	GEO_SONIC_HAIRCONE,
	GEO_SONIC_HAIRHALFCONE,
	GEO_SONIC_HAIRCONICALFRUSTUM,

	GEO_SONIC_BODY_BACK_HEMISPHERE,
	GEO_SONIC_BODY_FRONT_BLUE_HEMISPHERE_FRUSTUM,
	GEO_SONIC_BODY_FRONT_ORANGE_HEMISPHERE,

	GEO_SONIC_ARMCYLINDER,
	GEO_SONIC_ARMHEMISPHERE,
	GEO_SONIC_ARMSPHERE,
	GEO_SONIC_HANDTORUS,
	GEO_SONIC_HANDCYLINDER,
	GEO_SONIC_HANDHEMISPHERE,

	GEO_SONIC_LEGCYLINDER,
	GEO_SONIC_LEGTORUS,
	GEO_SONIC_LEGHEMISPHERE,
	GEO_SONIC_LEGSPHERE,

	GEO_SONIC_BOOTSQUATERSPHERE,
	GEO_SONIC_BOOTSLACEHALFTORUS,
	GEO_SONIC_BOOTSFEETTORUS,
	GEO_SONIC_BOOTSLACEHOOK,

	//END
	NUM_GEOMETRY
};

class MeshHandler
{
	static Mesh* meshList[NUM_GEOMETRY];
	static bool isLoaded;

public:
	static bool loadMeshes();
	static bool unloadMeshes();

	static Mesh* getMesh(GEOMETRY_TYPE);
};

