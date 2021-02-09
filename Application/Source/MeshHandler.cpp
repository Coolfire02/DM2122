#include "MeshHandler.h"
#include "GL\glew.h"
#include "LoadTGA.h"

bool MeshHandler::isLoaded = false;
Mesh* MeshHandler::meshList[NUM_GEOMETRY];

//Currently found in Application cpp
bool MeshHandler::loadMeshes() {
	if (isLoaded)
		return false;

	//Mesh loading

	//OBJS

	//Sonic characters
	meshList[GEO_SONIC_EGGMAN] = MeshBuilder::GenerateOBJMTL("Eggman", "OBJ//Eggman.obj", "MTL//Eggman.mtl");
	meshList[GEO_SONIC_TAILS] = MeshBuilder::GenerateOBJMTL("Tails", "OBJ//Tails.obj", "MTL//Tails.mtl");

	//Spotlight
	meshList[GEO_SPOTLIGHT] = MeshBuilder::GenerateOBJMTL("SpotLight", "OBJ//Spotlight.obj", "MTL//Spotlight.mtl");


	// Zip Library OBJS
	//Podium taken from the Kenney Space Kit
	meshList[GEO_PODIUM_1ST] = MeshBuilder::GenerateOBJMTL("Podium1st", "OBJ//hangar_roundB.obj", "MTL//hangar_roundB.mtl");

	//Kenney Platform Kit
	meshList[GEO_SHOPBASE] = MeshBuilder::GenerateOBJMTL("shopBase", "OBJ//shopBase.obj", "MTL//shopBase.mtl");

	//Textured Quads
	meshList[GEO_RUNNINGFLOOR] = MeshBuilder::GenerateQuad("floor", Color(1, 1, 1));
	meshList[GEO_RUNNINGFLOOR]->textureID = LoadTGA("Image//SonicFloor.tga");


	//NON-OBJS

	//Coin
	meshList[GEO_COIN] = MeshBuilder::GenerateTorus("cointorus", Color(0.95f, 0.8431f, 0.f), 0.7f, 2.8f);

	//Sonic
	meshList[GEO_SONIC_HEAD] = MeshBuilder::GenerateSphere("sonichead", Color(0.188f, 0.3804f, 0.89019f));
	meshList[GEO_SONIC_EYEBALL] = MeshBuilder::GenerateSphere("soniceyeball", Color(0.95f, 0.95f, 0.95f));
	meshList[GEO_SONIC_GREENEYE] = MeshBuilder::GenerateSphere("sonicgreeneyeball", Color(0.482f, 0.7686f, 0.235f));
	meshList[GEO_SONIC_BLACKEYE] = MeshBuilder::GenerateSphere("sonicblackeyeball", Color(0.05f, 0.05f, 0.05f));
	meshList[GEO_SONIC_EARS] = MeshBuilder::GenerateTetahedron("sonicears", Color(0.188f, 0.3804f, 0.89019f));
	meshList[GEO_SONIC_INNERSONICEARS] = MeshBuilder::GenerateTetahedron("sonicinnerears", Color(0.9647f, 0.7843f, 0.5176f));

	meshList[GEO_SONIC_MOUTHTORUS] = MeshBuilder::GenerateTorus("sonictorus", Color(0.98039f, 0.8392f, 0.62745f), 0.2f, 0.4f);
	meshList[GEO_SONIC_MOUTHSPHERE] = MeshBuilder::GenerateHemiSphere("sonicsphere", Color(0.98039f, 0.8392f, 0.62745f));
	meshList[GEO_SONIC_NOSESPHERE] = MeshBuilder::GenerateSphere("sonicnose", Color(0.01f, 0.01f, 0.01f));

	meshList[GEO_SONIC_HAIRHEMISPHERE] = MeshBuilder::GenerateHemiSphere("sonichairhemi", Color(0.188f, 0.3804f, 0.89019f));
	meshList[GEO_SONIC_HAIRHEMISPHEREFRUSTUM] = MeshBuilder::GenerateHemiSphereFrustum("sonichairhemifrustum", Color(0.188f, 0.3804f, 0.89019f), 120);
	meshList[GEO_SONIC_HAIRCONE] = MeshBuilder::GenerateCone("sonichaircone", Color(0.188f, 0.3804f, 0.89019f), 1, 2);
	meshList[GEO_SONIC_HAIRHALFCONE] = MeshBuilder::GenerateHalfCone("sonichairhalfcone", Color(0.188f, 0.3804f, 0.89019f), 1, 2);
	meshList[GEO_SONIC_HAIRCONICALFRUSTUM] = MeshBuilder::GenerateConicalFrustum("sonichairconicalfrustum", Color(0.188f, 0.3804f, 0.89019f), 0.5, 1, 2);

	meshList[GEO_SONIC_BODY_BACK_HEMISPHERE] = MeshBuilder::GenerateHemiSphere("sonicbodybackhemi", Color(0.188f, 0.3804f, 0.89019f));
	meshList[GEO_SONIC_BODY_FRONT_BLUE_HEMISPHERE_FRUSTUM] = MeshBuilder::GenerateHemiSphereFrustum("sonicbodyfronthemifrustum", Color(0.188f, 0.3804f, 0.89019f), 80);
	meshList[GEO_SONIC_BODY_FRONT_ORANGE_HEMISPHERE] = MeshBuilder::GenerateHemiSphere("sonicbodyfront", Color(0.9647f, 0.7843f, 0.5176f));

	meshList[GEO_SONIC_ARMCYLINDER] = MeshBuilder::GenerateCylinder("sonicarm", Color(0.9647f, 0.7843f, 0.5176f), 1);
	meshList[GEO_SONIC_ARMHEMISPHERE] = MeshBuilder::GenerateHemiSphere("sonicarmhemisphere", Color(0.9647f, 0.7843f, 0.5176f));
	meshList[GEO_SONIC_ARMSPHERE] = MeshBuilder::GenerateSphere("sonicarmhemisphere", Color(0.9647f, 0.7843f, 0.5176f));
	meshList[GEO_SONIC_HANDTORUS] = MeshBuilder::GenerateTorus("sonichandtorus", Color(1.0f, 1.0f, 1.0f), 1.2f, 2.2f);
	meshList[GEO_SONIC_HANDCYLINDER] = MeshBuilder::GenerateCylinder("sonichandcylinder", Color(1.0f, 1.0f, 1.0f), 2);
	meshList[GEO_SONIC_HANDHEMISPHERE] = MeshBuilder::GenerateHemiSphere("sonichandhemisphere", Color(1.0f, 1.0f, 1.0f));

	meshList[GEO_SONIC_LEGCYLINDER] = MeshBuilder::GenerateCylinder("soniclegcylinder", Color(0.188f, 0.3804f, 0.89019f), 1);
	meshList[GEO_SONIC_LEGTORUS] = MeshBuilder::GenerateTorus("soniclegtorus", Color(1.0f, 1.0f, 1.0f), 1.2f, 2.2f);
	meshList[GEO_SONIC_LEGHEMISPHERE] = MeshBuilder::GenerateHemiSphere("sonicleghemisphere", Color(0.188f, 0.3804f, 0.89019f));
	meshList[GEO_SONIC_LEGSPHERE] = MeshBuilder::GenerateSphere("soniclegsphere", Color(0.188f, 0.3804f, 0.89019f));

	meshList[GEO_SONIC_BOOTSQUATERSPHERE] = MeshBuilder::GenerateQuaterSphere("sonicquatersphere", Color(0.855f, 0.14509f, 0.15686f));
	meshList[GEO_SONIC_BOOTSFEETTORUS] = MeshBuilder::GenerateTorus("sonicfeettorus", Color(1.0f, 1.0f, 1.0f), 0.2f, 1.1f);
	meshList[GEO_SONIC_BOOTSLACEHALFTORUS] = MeshBuilder::GenerateHalfTorus("soniclacehalftorus", Color(1.0f, 1.0f, 1.0f), 0.03f, 1.2f);

	Material mat;
	mat.kAmbient.Set(0.3f, 0.3f, 0.3f);
	mat.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	mat.kSpecular.Set(0.3f, 0.3f, 0.3f);
	mat.kShininess = 1.0f;

	Material coinMat;
	coinMat.kAmbient.Set(0.4f, 0.4f, 0.4f);
	coinMat.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	coinMat.kSpecular.Set(0.5f, 0.5f, 0.5f);
	coinMat.kShininess = 20.0f;

	Material floorMat;
	floorMat.kAmbient.Set(0.26f, 0.26f, 0.26f);
	floorMat.kDiffuse.Set(0.3f, 0.3f, 0.3f);
	floorMat.kSpecular.Set(0.03f, 0.03f, 0.03f);
	floorMat.kShininess = 0.01f;

	Material hairMat;
	hairMat.kAmbient.Set(0.3f, 0.3f, 0.3f);
	hairMat.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	hairMat.kSpecular.Set(0.3f, 0.3f, 0.3f);
	hairMat.kShininess = 2.0f;

	Material eyeMat;
	eyeMat.kAmbient.Set(0.3f, 0.3f, 0.3f);
	eyeMat.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	eyeMat.kSpecular.Set(0.5f, 0.5f, 0.5f);
	eyeMat.kShininess = 2.0f;

	Material noseMat;
	noseMat.kAmbient.Set(0.3f, 0.3f, 0.3f);
	noseMat.kDiffuse.Set(0.3f, 0.3f, 0.3f);
	noseMat.kSpecular.Set(0.5f, 0.5f, 0.5f);
	noseMat.kShininess = 3.5f;

	meshList[GEO_COIN]->material = coinMat;

	meshList[GEO_RUNNINGFLOOR]->material = floorMat;

	meshList[GEO_SONIC_HEAD]->material = mat;
	meshList[GEO_SONIC_EYEBALL]->material = eyeMat;
	meshList[GEO_SONIC_GREENEYE]->material = mat;
	meshList[GEO_SONIC_BLACKEYE]->material = mat;

	meshList[GEO_SONIC_MOUTHTORUS]->material = mat;
	meshList[GEO_SONIC_MOUTHSPHERE]->material = mat;

	meshList[GEO_SONIC_NOSESPHERE]->material = noseMat;

	meshList[GEO_SONIC_EARS]->material = mat;
	meshList[GEO_SONIC_INNERSONICEARS]->material = mat;

	meshList[GEO_SONIC_HAIRHEMISPHERE]->material = hairMat;
	meshList[GEO_SONIC_HAIRHEMISPHEREFRUSTUM]->material = hairMat;
	meshList[GEO_SONIC_HAIRCONE]->material = hairMat;
	meshList[GEO_SONIC_HAIRHALFCONE]->material = hairMat;
	meshList[GEO_SONIC_HAIRCONICALFRUSTUM]->material = hairMat;

	meshList[GEO_SONIC_BODY_BACK_HEMISPHERE]->material = mat;
	meshList[GEO_SONIC_BODY_FRONT_BLUE_HEMISPHERE_FRUSTUM]->material = mat;
	meshList[GEO_SONIC_BODY_FRONT_ORANGE_HEMISPHERE]->material = mat;

	meshList[GEO_SONIC_ARMCYLINDER]->material = mat;
	meshList[GEO_SONIC_ARMHEMISPHERE]->material = mat;
	meshList[GEO_SONIC_ARMSPHERE]->material = mat;
	meshList[GEO_SONIC_HANDTORUS]->material = mat;
	meshList[GEO_SONIC_HANDCYLINDER]->material = mat;
	meshList[GEO_SONIC_HANDHEMISPHERE]->material = mat;

	meshList[GEO_SONIC_LEGCYLINDER]->material = mat;
	meshList[GEO_SONIC_LEGTORUS]->material = mat;
	meshList[GEO_SONIC_LEGHEMISPHERE]->material = mat;
	meshList[GEO_SONIC_LEGSPHERE]->material = mat;

	meshList[GEO_SONIC_BOOTSQUATERSPHERE]->material = mat;
	meshList[GEO_SONIC_BOOTSFEETTORUS]->material = mat;
	meshList[GEO_SONIC_BOOTSLACEHALFTORUS]->material = mat;

	isLoaded = true;
	return true;
}

Mesh* MeshHandler::getMesh(GEOMETRY_TYPE type) {
	return meshList[type];
}

//Found in application CPP
bool MeshHandler::unloadMeshes() {
	if (!isLoaded)
		return false;

	//Delete meshes
	for (int i = 0; i < NUM_GEOMETRY; i++) {
		delete meshList[i];
	}

	isLoaded = false;
	return true;
}