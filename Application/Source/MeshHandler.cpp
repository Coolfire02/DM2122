#include "MeshHandler.h"

bool MeshHandler::isLoaded = false;

bool MeshHandler::loadMeshes() {
	if (isLoaded)
		return false;

	//Mesh loading
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


	isLoaded = true;
	return true;
}

bool MeshHandler::unloadMeshes() {
	if (!isLoaded)
		return false;

	//Delete meshes

	isLoaded = false;
	return true;
}