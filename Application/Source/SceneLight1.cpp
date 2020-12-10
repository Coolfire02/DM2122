#include "SceneLight1.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include <Windows.h>

#include "shader.hpp"
#include "Utility.h"


SceneLight1::SceneLight1()
{
	rotateAngle = 0;
	rotateAngle2 = 0;
	translateZ = 1;
	scaleAll = 1;

	elapsed = 0.0;

	rotateAngleFWD = true;
	translateZFWD = true;
	scaleALLFWD = true;

	//inAnimation = false;
	endAnimation = 0;
	currentAnimation = NO_ANIMATION;
	stackedAnimations = 0;
}

SceneLight1::~SceneLight1()
{
}

void SceneLight1::Init() {

	// Init VBO here
	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//LightSource.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");



	glUseProgram(m_programID);

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 8.0f / 6.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);

	//Camera init(starting pos, where it looks at, up
	camera.Init(Vector3(10, 7, 3), Vector3(0,-10,0), Vector3(0,1,0));

	//Light init
	light[0].type = Light::LIGHT_POINT;
	light[0].position.set(0, 20, 0); 
	light[0].color.set(1, 1, 1); //set to white light
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	// Make sure you pass uniform parameters after glUseProgram()
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);



	glUniform1i(m_parameters[U_NUMLIGHTS], 1);



	meshList[GEO_CUBE] = MeshBuilder::GenerateHalfCone("cube", Color(0.9f, 0.6f, 0.3f), 3, 10);
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1, 1, 1);
	//meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", 1, 1);
	//meshList[GEO_SUN] = MeshBuilder::GenerateSphere("sun", Color(0.956f, 0.5f, 0.215f), 3);
	meshList[GEO_SONICHEAD] = MeshBuilder::GenerateSphere("sonichead", Color(0.188f, 0.3804f, 0.89019f));
	meshList[GEO_SONICEYEBALL] = MeshBuilder::GenerateSphere("soniceyeball", Color(0.95f, 0.95f, 0.95f));
	meshList[GEO_SONICGREENEYE] = MeshBuilder::GenerateSphere("sonicgreeneyeball", Color(0.482f, 0.7686f, 0.235f));
	meshList[GEO_SONICBLACKEYE] = MeshBuilder::GenerateSphere("sonicblackeyeball", Color(0.05f, 0.05f, 0.05f));
	meshList[GEO_SONICEARS] = MeshBuilder::GenerateTetahedron("sonicears", Color(0.188f, 0.3804f, 0.89019f));
	meshList[GEO_INNERSONICEARS] = MeshBuilder::GenerateTetahedron("sonicinnerears", Color(0.9647f, 0.7843f, 0.5176f));

	meshList[GEO_MOUTHTORUS] = MeshBuilder::GenerateTorus("sonictorus", Color(0.98039f, 0.8392f, 0.62745f), 0.2, 0.4);
	meshList[GEO_MOUTHSPHERE] = MeshBuilder::GenerateHemiSphere("sonicsphere", Color(0.98039f, 0.8392f, 0.62745f));

	meshList[GEO_HAIRHEMISPHERE] = MeshBuilder::GenerateHemiSphere("sonichairhemi", Color(0.188f, 0.3804f, 0.89019f));
	meshList[GEO_HAIRHEMISPHEREFRUSTUM] = MeshBuilder::GenerateHemiSphereFrustum("sonichairhemifrustum", Color(0.188f, 0.3804f, 0.89019f), 120);
	meshList[GEO_HAIRCONE] = MeshBuilder::GenerateCone("sonichaircone", Color(0.188f, 0.3804f, 0.89019f), 1, 2);
	meshList[GEO_HAIRHALFCONE] = MeshBuilder::GenerateHalfCone("sonichairhalfcone", Color(0.188f, 0.3804f, 0.89019f), 1, 2);
	meshList[GEO_HAIRCONICALFRUSTUM] = MeshBuilder::GenerateConicalFrustum("sonichairconicalfrustum", Color(0.188f, 0.3804f, 0.89019f), 0.5, 1, 2);
	
	meshList[GEO_BODY_BACK_HEMISPHERE] = MeshBuilder::GenerateHemiSphere("sonicbodybackhemi", Color(0.188f, 0.3804f, 0.89019f));
	meshList[GEO_BODY_FRONT_BLUE_HEMISPHERE_FRUSTUM] = MeshBuilder::GenerateHemiSphereFrustum("sonicbodyfronthemifrustum", Color(0.188f, 0.3804f, 0.89019f), 80);
	meshList[GEO_BODY_FRONT_ORANGE_HEMISPHERE] = MeshBuilder::GenerateHemiSphere("sonicbodyfront", Color(0.9647f, 0.7843f, 0.5176f));
	
	meshList[GEO_ARMCYLINDER] = MeshBuilder::GenerateCylinder("sonicarm", Color(0.9647f, 0.7843f, 0.5176f), 1);
	meshList[GEO_ARMHEMISPHERE] = MeshBuilder::GenerateHemiSphere("sonicarmhemisphere", Color(0.9647f, 0.7843f, 0.5176f));
	meshList[GEO_HANDTORUS] = MeshBuilder::GenerateTorus("sonichandtorus", Color(1.0f, 1.0f, 1.0f), 1.2, 2.2);
	meshList[GEO_HANDCYLINDER] = MeshBuilder::GenerateCylinder("sonichandcylinder", Color(1.0f, 1.0f, 1.0f), 2);
	meshList[GEO_HANDHEMISPHERE] = MeshBuilder::GenerateHemiSphere("sonichandhemisphere", Color(1.0f, 1.0f, 1.0f));

	meshList[GEO_LEGCYLINDER] = MeshBuilder::GenerateCylinder("soniclegcylinder", Color(0.188f, 0.3804f, 0.89019f), 1);
	meshList[GEO_LEGTORUS] = MeshBuilder::GenerateTorus("soniclegtorus", Color(1.0f, 1.0f, 1.0f), 1.2, 2.2);
	meshList[GEO_LEGHEMISPHERE] = MeshBuilder::GenerateHemiSphere("sonicleghemisphere", Color(0.188f, 0.3804f, 0.89019f));
	meshList[GEO_LEGSPHERE] = MeshBuilder::GenerateSphere("soniclegsphere", Color(0.188f, 0.3804f, 0.89019f));

	meshList[GEO_BOOTSQUATERSPHERE] = MeshBuilder::GenerateQuaterSphere("sonicquatersphere", Color(0.855f, 0.14509f, 0.15686f));
	meshList[GEO_BOOTSFEETTORUS] = MeshBuilder::GenerateTorus("sonicfeettorus", Color(1.0f, 1.0f, 1.0f), 0.2, 1.1);
	meshList[GEO_BOOTSLACEHALFTORUS] = MeshBuilder::GenerateHalfTorus("soniclacehalftorus", Color(1.0f, 1.0f, 1.0f), 0.03,1.2);


	//meshList[GEO_PLANET2] = MeshBuilder::GenerateSphere("planet2", Color(0.8f, 0.82f, 0.8f), 1);
	//meshList[GEO_PLANET3] = MeshBuilder::GenerateSphere("planet3", Color(0.4f, 0.9f, 0.77f), 1);
	//meshList[GEO_PLANET4] = MeshBuilder::GenerateSphere("planet4", Color(0.88f, 0.4f, 0.123f), 1);
	//meshList[GEO_PLANET5] = MeshBuilder::GenerateSphere("planet5", Color(0.88f, 0.88f, 0.65f), 1);
	//meshList[GEO_PLANET6] = MeshBuilder::GenerateSphere("planet6", Color(0.8f, 1.0f, 0.85f), 1);
	//meshList[GEO_PLANET7] = MeshBuilder::GenerateSphere("planet7", Color(0.2f, 0.0f, 0.2f), 1);
	//meshList[GEO_PLANET8] = MeshBuilder::GenerateSphere("planet8", Color(0.05f, 0.05f, 0.05f), 1);
	
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightbulll", Color(1.0f, 1.0f, 1.0f));

	//Universal material template used for testing
	Material mat;
	mat.kAmbient.Set(0.3f, 0.3f, 0.3f);
	mat.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	mat.kSpecular.Set(0.3f, 0.3f, 0.3f);
	mat.kShininess = 1.0f;

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

	meshList[GEO_CUBE]->material = mat;
	meshList[GEO_SONICHEAD]->material = mat;
	meshList[GEO_SONICEYEBALL]->material = eyeMat;
	meshList[GEO_SONICGREENEYE]->material = mat;
	meshList[GEO_SONICBLACKEYE]->material = mat;

	meshList[GEO_MOUTHTORUS]->material = mat;
	meshList[GEO_MOUTHSPHERE]->material = mat;

	meshList[GEO_SONICEARS]->material = mat;
	meshList[GEO_INNERSONICEARS]->material = mat;

	meshList[GEO_HAIRHEMISPHERE]->material = hairMat;
	meshList[GEO_HAIRHEMISPHEREFRUSTUM]->material = hairMat;
	meshList[GEO_HAIRCONE]->material = hairMat;
	meshList[GEO_HAIRHALFCONE]->material = hairMat;
	meshList[GEO_HAIRCONICALFRUSTUM]->material = hairMat;

	meshList[GEO_BODY_BACK_HEMISPHERE]->material = mat;
	meshList[GEO_BODY_FRONT_BLUE_HEMISPHERE_FRUSTUM]->material = mat;
	meshList[GEO_BODY_FRONT_ORANGE_HEMISPHERE]->material = mat;

	meshList[GEO_ARMCYLINDER]->material = mat;
	meshList[GEO_ARMHEMISPHERE]->material = mat;
	meshList[GEO_HANDTORUS]->material = mat;
	meshList[GEO_HANDCYLINDER]->material = mat;
	meshList[GEO_HANDHEMISPHERE]->material = mat;

	meshList[GEO_LEGCYLINDER]->material = mat;
	meshList[GEO_LEGTORUS]->material = mat;
	meshList[GEO_LEGHEMISPHERE]->material = mat;
	meshList[GEO_LEGSPHERE]->material = mat;

	meshList[GEO_BOOTSQUATERSPHERE]->material = mat;
	meshList[GEO_BOOTSFEETTORUS]->material = mat;
	meshList[GEO_BOOTSLACEHALFTORUS]->material = mat;

	for (int i = 0; i < ANIMATION_TOTAL; i++) {
		animation_offset[i] = 0.0;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void SceneLight1::animationUpdater(double dt) {
	double totalAnimationTime = endAnimation - startAnimation;
	double aniTime = elapsed - startAnimation;
	//Run 1.5s
	//Walk 2s
	//RunJump 3s
	if (aniTime >= totalAnimationTime) {
		resetAnimation();
		stackedAnimations = 0; //debug
		if (stackedAnimations > 0) {
			stackedAnimations--;
			switch (currentAnimation) { //Continuation of animation
			case WALK:
				resetAnimation();
				startAnimation = elapsed - 0.56;
				endAnimation = startAnimation + 2.3;
			}
		}
		else {
			currentAnimation = NO_ANIMATION;
			return;
		}
	}
	switch (currentAnimation) {
	case WALK:
		double animationStart;
		double animationLength;
		float degreeTilt;
		ANIMATION_OFFSET type;

		animationStart = 0.0;
		animationLength = 0.45;
		degreeTilt = 0.7;
		type = ANIMATION_OFFSET::LEFT_LEG_ORIGIN_PITCH;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);
		
		animationStart = 0.08;
		animationLength = 0.45;
		degreeTilt = -5;
		type = ANIMATION_OFFSET::LEFT_LEG_KNEE_TILT;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.40;
		animationLength = 0.80;
		degreeTilt = 1.2;
		type = ANIMATION_OFFSET::LEFT_LEG_ORIGIN_PITCH;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.60;
		animationLength = 1.00;
		degreeTilt = 5;
		type = ANIMATION_OFFSET::LEFT_LEG_KNEE_TILT;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.1;
		animationLength = 2.0;
		degreeTilt = -1.9;
		type = ANIMATION_OFFSET::LEFT_LEG_ORIGIN_PITCH;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.15;
		animationLength = 1.7;
		degreeTilt = -3;
		type = ANIMATION_OFFSET::LEFT_LEG_KNEE_TILT;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.95;
		animationLength = 2.3;
		degreeTilt = 2.6;
		type = ANIMATION_OFFSET::LEFT_LEG_ORIGIN_PITCH;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.95;
		animationLength = 2.3;
		degreeTilt = 4;
		type = ANIMATION_OFFSET::LEFT_LEG_KNEE_TILT;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);
		
		animationStart = 0.6;
		animationLength = 1.2;
		degreeTilt = -1.3;
		type = ANIMATION_OFFSET::RIGHT_LEG_ORIGIN_PITCH;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.70;
		animationLength = 1.2;
		degreeTilt = -2;
		type = ANIMATION_OFFSET::RIGHT_LEG_KNEE_TILT;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.15;
		animationLength = 1.8;
		degreeTilt = 2.8;
		type = ANIMATION_OFFSET::RIGHT_LEG_ORIGIN_PITCH;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.15;
		animationLength = 1.9;
		degreeTilt = 1.3;
		type = ANIMATION_OFFSET::RIGHT_LEG_KNEE_TILT;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.75;
		animationLength = 2.3;
		degreeTilt = -1.75;
		type = ANIMATION_OFFSET::RIGHT_LEG_ORIGIN_PITCH;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

	}
}

void SceneLight1::processAnimation(double aniTime, double animationStart, double animationLength, float degreeTilt, ANIMATION_OFFSET type) {
	if (aniTime >= animationStart && aniTime <= animationLength)
		animation_offset[type] = animation_offset[type] + (aniTime - animationStart) / (animationLength-animationStart) * degreeTilt;
}

void SceneLight1::resetAnimation() {
	for (int i = 0; i < ANIMATION_TOTAL; i++) {
		animation_offset[i] = 0.0;
	}
}

void SceneLight1::Update(double dt)
{
	elapsed += dt;
	camera.Update(dt);
	rotateAngle += 10*dt;
	rotateAngle2 += 50 * dt;
		
	if (translateZFWD) {
		translateZ += 0.2;
		if (translateZ >= 5) {
			translateZFWD = false;
		}
	}
	else {
		translateZ -= 0.2;
		if (translateZ <= 1) {
			translateZFWD = true;
		}
	}

	if (GetAsyncKeyState('1') & 0x8001) {
		glEnable(GL_CULL_FACE);
	}
	else if (GetAsyncKeyState('2') & 0x8001) {
		glDisable(GL_CULL_FACE);
	}
	else if (GetAsyncKeyState('3') & 0x8001) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (GetAsyncKeyState('4') & 0x8001) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (currentAnimation != NO_ANIMATION) {
		animationUpdater(dt);

		if (stackedAnimations < 1) {
			if (Application::IsKeyPressed('T') && currentAnimation == ANIMATION::WALK) {
				stackedAnimations++;
			}
			else if (Application::IsKeyPressed('B') && Application::IsKeyPressed('G') && currentAnimation == ANIMATION::RUNJUMP) {
				stackedAnimations++;
			}
			else if (Application::IsKeyPressed('B') && currentAnimation == ANIMATION::RUN) {
				stackedAnimations++;
			}
		}

	} else { //No animation
		//T = walk
		//G = jump
		//B = run
		if (Application::IsKeyPressed('T')) {
			currentAnimation = ANIMATION::WALK;
			startAnimation = elapsed;
			endAnimation = startAnimation + 2.3;

		}
		else if (Application::IsKeyPressed('B') && Application::IsKeyPressed('G')) {
			currentAnimation = ANIMATION::RUNJUMP;
			startAnimation = elapsed;
			endAnimation = startAnimation + 3.0;
		}
		else if (Application::IsKeyPressed('B')) {
			currentAnimation = ANIMATION::RUN;
			startAnimation = elapsed;
			endAnimation = startAnimation + 1.5;
		}
	}

	const float LSPEED = 10.f;
	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);
	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
}


void SceneLight1::Render()
{

	glEnableVertexAttribArray(0); // 1st attribute buffer: vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer: color

	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 model;
	Mtx44 view;

	Mtx44 MVP;

	/* First Triangle
	*/

	//Safe to initialize values as identity matrix (not a zero matrix!)
	//view.SetToIdentity(); //no need camera matrix, set to origin
	//projection.SetToOrtho(-80.0, 80.0, -60.0, 60.0, -10.0, 10.0);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, 
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);

	modelStack.LoadIdentity();


	modelStack.PushMatrix();
		modelStack.Translate(0, 0, 0);
		modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
		modelStack.Scale(1, 1, 1);
		this->RenderMesh(meshList[GEO_AXES], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
		RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	//modelStack.PushMatrix(); //pushing identity
	//	modelStack.Translate(0.0f, 0.0f, 0.0f);
	//	modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
	//	modelStack.Scale(3.0f, 1.8f, 1.0f);
	//	this->RenderMesh(meshList[GEO_CUBE], true);
	//modelStack.PopMatrix();


	if (light[0].type == Light::LIGHT_DIRECTIONAL) {
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDir_cameraSpace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDir_cameraSpace.x);

	}
	else if (light[0].type == Light::LIGHT_SPOT) {
		Position lightPos_cameraSpace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPos_cameraSpace.x);
		Vector3 spotDir_cameraSpace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDir_cameraSpace.x);

	}
	else { //Point light
		Position lightPos_cameraSpace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPos_cameraSpace.x);
	}
	
	//Main model: head
	modelStack.PushMatrix();
		modelStack.Translate(0.0f, 0.0f, 0.0f);
		modelStack.Rotate(-10, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(4.0f, 4.0f, 4.0f);
		this->RenderMesh(meshList[GEO_SONICHEAD], true);

		//Body
		modelStack.PushMatrix();
			modelStack.Rotate(10, 1.0f, 0.0f, 0.0f);
			modelStack.Translate(0.0f, -1.2f, 0.0); //Center of body

			modelStack.PushMatrix();
				modelStack.Rotate(-90, 1.0f, 0.0f, 0.0f);
				modelStack.Translate(0.0f, 0.0f, 0.0f);
				modelStack.Scale(0.4f, 0.5f, 0.6f);
				this->RenderMesh(meshList[GEO_BODY_BACK_HEMISPHERE], true);
			modelStack.PopMatrix();

			//Front of body
			modelStack.PushMatrix();
				modelStack.Rotate(90, 1.0f, 0.0f, 0.0f);
				modelStack.Translate(0.0f, 0.0f, 0.0f);
				modelStack.Scale(0.4f, 0.5f, 0.6f);
				this->RenderMesh(meshList[GEO_BODY_FRONT_BLUE_HEMISPHERE_FRUSTUM], true);

				modelStack.PushMatrix();
					modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
					modelStack.Translate(0.0f, 0.5f, 0.0f);
					modelStack.Scale(0.8f, 0.5f, 0.8f);
					this->RenderMesh(meshList[GEO_BODY_FRONT_ORANGE_HEMISPHERE], true);
				modelStack.PopMatrix();
			modelStack.PopMatrix();
			
			//Legs
			//Right Leg
			modelStack.PushMatrix();
				
				modelStack.Translate(0.2f * RIGHT, -0.4f, 0.0f);
				modelStack.Rotate(10 * RIGHT, 0.0f, 0.0f, 1.0f);
				
				modelStack.Rotate(-animation_offset[RIGHT_LEG_ORIGIN_PITCH], 1.0f, 0.0f, 0.0f); //to go back

				modelStack.Scale(0.12f, 0.12f, 0.12f);
				this->RenderMesh(meshList[GEO_LEGHEMISPHERE], true);

				modelStack.PushMatrix();

					modelStack.Translate(0.f, -2.8f, 0.0f);
					modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
					modelStack.Scale(1.0, 5.6f, 1.0f);
					this->RenderMesh(meshList[GEO_LEGCYLINDER], true);

					modelStack.PushMatrix();

						modelStack.Scale(1.0, 0.1785f, 1.0f);
						
						modelStack.Translate(0.f, -2.9f, 0.0f);
						modelStack.Rotate(-animation_offset[RIGHT_LEG_KNEE_TILT], 1.0f, 0.0f, 0.0f);
						
						this->RenderMesh(meshList[GEO_LEGSPHERE], true);

						modelStack.PushMatrix();

							modelStack.Translate(0.f, -3.2f, 0.0f);
							modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
							modelStack.Scale(0.85, 5.6f, 0.85f);
							this->RenderMesh(meshList[GEO_LEGCYLINDER], true);

							modelStack.PushMatrix();
							
								modelStack.Translate(0.f, -0.5f, 0.0f);
								modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
								modelStack.Scale(0.8f, 0.12f, 0.8f);
								modelStack.Rotate(-10 * RIGHT, 0.0f, 0.0f, 1.0f);
								this->RenderMesh(meshList[GEO_LEGTORUS], true);

								modelStack.PushMatrix();

									modelStack.Translate(0.f, -1.4f, 0.0f);
									modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
									modelStack.Scale(1.0f, 0.8f, 1.0f);
									this->RenderMesh(meshList[GEO_LEGTORUS], true);

									//Front shoe
									modelStack.PushMatrix();

										modelStack.Translate(0.4f * RIGHT, -8.0f, 0.0f);
										modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										modelStack.Scale(5.0f, 8.f, 10.f);
										this->RenderMesh(meshList[GEO_BOOTSQUATERSPHERE], true);

										//Lace
										modelStack.PushMatrix();

											modelStack.Rotate(90, 0.0f, 1.0f, 0.0f);
											modelStack.Translate(-0.3f, 0.0f, 0.0f);
											
											modelStack.Rotate(-83, 0.0f, 0.0f, 1.0f);
											
											modelStack.Scale(0.75f, 4.f, 0.8f); //x is tallness, y value is width, 
											this->RenderMesh(meshList[GEO_BOOTSLACEHALFTORUS], true);

										modelStack.PopMatrix();

										modelStack.PushMatrix();
											modelStack.Translate(0.f, -0.12f, 0.25f);
											modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
											modelStack.Scale(0.8f, 0.8f, 0.6f);
											this->RenderMesh(meshList[GEO_BOOTSFEETTORUS], true);
										modelStack.PopMatrix();

									modelStack.PopMatrix();

									//Back shoe
									modelStack.PushMatrix();
										modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
										modelStack.Translate(-0.4f * RIGHT, -8.0f, -0.3f);
										modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										modelStack.Scale(5.0f, 8.f, 4.f);
										this->RenderMesh(meshList[GEO_BOOTSQUATERSPHERE], true);

									modelStack.PopMatrix();

								modelStack.PopMatrix();

							modelStack.PopMatrix();

						modelStack.PopMatrix();

					modelStack.PopMatrix();

				modelStack.PopMatrix();

			modelStack.PopMatrix();


			//Left Leg
			modelStack.PushMatrix();
				
				modelStack.Translate(0.2f * LEFT, -0.4f, 0.0f);
				modelStack.Rotate(10 * LEFT, 0.0f, 0.0f, 1.0f);
				
				modelStack.Rotate(-animation_offset[LEFT_LEG_ORIGIN_PITCH], 1.0f, 0.0f, 0.0f); //to go back

				modelStack.Scale(0.12f, 0.12f, 0.12f);
				this->RenderMesh(meshList[GEO_LEGHEMISPHERE], true);

				modelStack.PushMatrix();

					modelStack.Translate(0.f, -2.8f, 0.0f);
					modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
					modelStack.Scale(1.0, 5.6f, 1.0f);
					this->RenderMesh(meshList[GEO_LEGCYLINDER], true);

					modelStack.PushMatrix();

						modelStack.Scale(1.0, 0.1785f, 1.0f);
						
						modelStack.Translate(0.f, -2.9f, 0.0f);
						modelStack.Rotate(-animation_offset[LEFT_LEG_KNEE_TILT], 1.0f, 0.0f, 0.0f);
						
						this->RenderMesh(meshList[GEO_LEGSPHERE], true);

						modelStack.PushMatrix();

							modelStack.Translate(0.f, -3.2f, 0.0f);
							modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
							modelStack.Scale(0.85, 5.6f, 0.85f);
							this->RenderMesh(meshList[GEO_LEGCYLINDER], true);

							modelStack.PushMatrix();
							
								modelStack.Translate(0.f, -0.5f, 0.0f);
								modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
								modelStack.Scale(0.8f, 0.12f, 0.8f);
								modelStack.Rotate(-10 * LEFT, 0.0f, 0.0f, 1.0f);
								this->RenderMesh(meshList[GEO_LEGTORUS], true);

								modelStack.PushMatrix();

									modelStack.Translate(0.f, -1.4f, 0.0f);
									modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
									modelStack.Scale(1.0f, 0.8f, 1.0f);
									this->RenderMesh(meshList[GEO_LEGTORUS], true);

									//Front shoe
									modelStack.PushMatrix();

										modelStack.Translate(0.4f * LEFT, -8.0f, 0.0f);
										modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										modelStack.Scale(5.0f, 8.f, 10.f);
										this->RenderMesh(meshList[GEO_BOOTSQUATERSPHERE], true);

										//Lace
										modelStack.PushMatrix();

											modelStack.Rotate(90, 0.0f, 1.0f, 0.0f);
											modelStack.Translate(-0.3f, 0.0f, 0.0f);
											
											modelStack.Rotate(-83, 0.0f, 0.0f, 1.0f);
											
											modelStack.Scale(0.75f, 4.f, 0.8f); //x is tallness, y value is width, 
											this->RenderMesh(meshList[GEO_BOOTSLACEHALFTORUS], true);

										modelStack.PopMatrix();

										modelStack.PushMatrix();
											modelStack.Translate(0.f, -0.12f, 0.25f);
											modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
											modelStack.Scale(0.8f, 0.8f, 0.6f);
											this->RenderMesh(meshList[GEO_BOOTSFEETTORUS], true);
										modelStack.PopMatrix();

									modelStack.PopMatrix();

									//Back shoe
									modelStack.PushMatrix();
										modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
										modelStack.Translate(-0.4f * LEFT, -8.0f, -0.3f);
										modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										modelStack.Scale(5.0f, 8.f, 4.f);
										this->RenderMesh(meshList[GEO_BOOTSQUATERSPHERE], true);

									modelStack.PopMatrix();

								modelStack.PopMatrix();

							modelStack.PopMatrix();

						modelStack.PopMatrix();

					modelStack.PopMatrix();

				modelStack.PopMatrix();

			modelStack.PopMatrix();
			

			//Arms
			//Right arm

			modelStack.PushMatrix();
				//modelStack.Rotate(60, 0.0f, 1.0f, 0.0f); //to go back
				modelStack.Translate(0.42f, 0.2f, 0.0f);

				modelStack.Rotate(90, 0.0f, 0.0f, 1.0f);
				modelStack.Scale(0.08f, 0.12f, 0.08f);
				this->RenderMesh(meshList[GEO_ARMHEMISPHERE], true);
				
				modelStack.PushMatrix();
					modelStack.Translate(0.0f, -4.1f, 0.0f);
					
					modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
					modelStack.Scale(1.0f, 8.3f, 1.0f);
					this->RenderMesh(meshList[GEO_ARMCYLINDER], true);
					
					//Arm Torus Outter
					modelStack.PushMatrix();
						modelStack.Translate(0.0f, -0.40f, 0.0f);

						modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
						modelStack.Scale(0.8f, 0.07f, 0.8f);
						this->RenderMesh(meshList[GEO_HANDTORUS], true);

						//Arm Torus Inner
						modelStack.PushMatrix();
							modelStack.Translate(0.0f, -0.8f, 0.0f);

							modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
							modelStack.Scale(1.0f, 0.8f, 1.0f);
							this->RenderMesh(meshList[GEO_HANDTORUS], true);
						modelStack.PopMatrix();

					modelStack.PopMatrix();

					//Hand
					modelStack.PushMatrix();
						modelStack.Translate(-1.3f, -0.61f, 0.0f);

						modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
						modelStack.Scale(0.20f, 3.f, 2.5f); //z fatter x is longer
						this->RenderMesh(meshList[GEO_HANDHEMISPHERE], true);

						//Thumb
						modelStack.PushMatrix();
							modelStack.Rotate(-71, 0.0f, 1.0f, 0.0f); //Angle of finger on the hemisphere
							modelStack.Translate(1.4f, 0.3f, 0.0f);
							modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
							modelStack.Scale(0.20f, 0.5f, 0.26f); //y is for length
							this->RenderMesh(meshList[GEO_HANDCYLINDER], true);

							modelStack.PushMatrix();
								modelStack.Translate(0.0f, 1.0f, 0.0f);
								modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
								modelStack.Scale(1.0f, 0.3f, 1.0f);
								this->RenderMesh(meshList[GEO_HANDHEMISPHERE], true);
							modelStack.PopMatrix();

						modelStack.PopMatrix();

						//Index
						modelStack.PushMatrix();
							modelStack.Rotate(-20, 0.0f, 1.0f, 0.0f);
							modelStack.Rotate(1, 0.0f, 0.0f, 1.0f); //Tilting upwards angle
							modelStack.Translate(1.4f, 0.3f, 0.0f);
							modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
							modelStack.Scale(0.15f, 0.8f, 0.22f); //y is for length
							this->RenderMesh(meshList[GEO_HANDCYLINDER], true);

							modelStack.PushMatrix();
								modelStack.Translate(0.0f, 1.0f, 0.0f);
								modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
								modelStack.Scale(1.0f, 0.3f, 1.0f);
								this->RenderMesh(meshList[GEO_HANDHEMISPHERE], true);
							modelStack.PopMatrix();

						modelStack.PopMatrix();

						//Middle
						modelStack.PushMatrix();
							modelStack.Rotate(5, 0.0f, 1.0f, 0.0f);
							modelStack.Rotate(3, 0.0f, 0.0f, 1.0f); //Tilting upwards angle
							modelStack.Translate(1.4f, 0.3f, 0.0f);
							modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
							modelStack.Scale(0.15f, 0.85f, 0.22f); //y is for length
							this->RenderMesh(meshList[GEO_HANDCYLINDER], true);

							modelStack.PushMatrix();
								modelStack.Translate(0.0f, 1.0f, 0.0f);
								modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
								modelStack.Scale(1.0f, 0.3f, 1.0f);
								this->RenderMesh(meshList[GEO_HANDHEMISPHERE], true);
							modelStack.PopMatrix();
						modelStack.PopMatrix();

						//Ring
						modelStack.PushMatrix();
							modelStack.Rotate(30, 0.0f, 1.0f, 0.0f);
							modelStack.Rotate(2, 0.0f, 0.0f, 1.0f); //Tilting upwards angle
							modelStack.Translate(1.4f, 0.3f, 0.0f);
							modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
							modelStack.Scale(0.15f, 0.75f, 0.22f); //y is for length
							this->RenderMesh(meshList[GEO_HANDCYLINDER], true);

							modelStack.PushMatrix();
								modelStack.Translate(0.0f, 1.0f, 0.0f);
								modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
								modelStack.Scale(1.0f, 0.3f, 1.0f);
								this->RenderMesh(meshList[GEO_HANDHEMISPHERE], true);
							modelStack.PopMatrix();
						modelStack.PopMatrix();

						//Pinky
						modelStack.PushMatrix();
							modelStack.Rotate(60, 0.0f, 1.0f, 0.0f);
							modelStack.Translate(1.2f, 0.3f, 0.0f);
							modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
							modelStack.Scale(0.15f, 0.35f, 0.22f); //y is for length
							this->RenderMesh(meshList[GEO_HANDCYLINDER], true);

							modelStack.PushMatrix();
								modelStack.Translate(0.0f, 1.0f, 0.0f);
								modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
								modelStack.Scale(1.0f, 0.3f, 1.0f);
								this->RenderMesh(meshList[GEO_HANDHEMISPHERE], true);
							modelStack.PopMatrix();
						modelStack.PopMatrix();

					modelStack.PopMatrix();

				modelStack.PopMatrix();

			modelStack.PopMatrix();
		


			//Left arm

			modelStack.PushMatrix();
				modelStack.Rotate(180, 0.0f, 1.0f, 0.0f); //FLIP RIGHTHAND
				modelStack.Translate(0.42f, 0.2f, 0.0f);

				modelStack.Rotate(90, 0.0f, 0.0f, 1.0f);
				modelStack.Scale(0.08f, 0.12f, 0.08f);
				this->RenderMesh(meshList[GEO_ARMHEMISPHERE], true);

				modelStack.PushMatrix();
					modelStack.Translate(0.0f, -4.1f, 0.0f);

					modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
					modelStack.Scale(1.0f, 8.3f, 1.0f);
					this->RenderMesh(meshList[GEO_ARMCYLINDER], true);

					//Arm Torus Outter
					modelStack.PushMatrix();
						modelStack.Translate(0.0f, -0.40f, 0.0f);

						modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
						modelStack.Scale(0.8f, 0.07f, 0.8f);
						this->RenderMesh(meshList[GEO_HANDTORUS], true);

						//Arm Torus Inner
						modelStack.PushMatrix();
							modelStack.Translate(0.0f, -0.8f, 0.0f);

							modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
							modelStack.Scale(1.0f, 0.8f, 1.0f);
							this->RenderMesh(meshList[GEO_HANDTORUS], true);
						modelStack.PopMatrix();

					modelStack.PopMatrix();

					//Hand
					modelStack.PushMatrix();
						modelStack.Translate(-1.3f, -0.61f, 0.0f);

						modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
						modelStack.Scale(0.20f, 3.f, 2.5f); //z fatter x is longer
						this->RenderMesh(meshList[GEO_HANDHEMISPHERE], true);

						//Thumb
						modelStack.PushMatrix();
							modelStack.Rotate(-71 * -1, 0.0f, 1.0f, 0.0f); //Angle of finger on the hemisphere
							modelStack.Translate(1.4f, 0.3f, 0.0f);
							modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
							modelStack.Scale(0.20f, 0.5f, 0.26f); //y is for length
							this->RenderMesh(meshList[GEO_HANDCYLINDER], true);

							modelStack.PushMatrix();
								modelStack.Translate(0.0f, 1.0f, 0.0f);
								modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
								modelStack.Scale(1.0f, 0.3f, 1.0f);
								this->RenderMesh(meshList[GEO_HANDHEMISPHERE], true);
							modelStack.PopMatrix();

						modelStack.PopMatrix();

						//Index
						modelStack.PushMatrix();
							modelStack.Rotate(-20 * -1, 0.0f, 1.0f, 0.0f);
							modelStack.Rotate(1, 0.0f, 0.0f, 1.0f); //Tilting upwards angle
							modelStack.Translate(1.4f, 0.3f, 0.0f);
							modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
							modelStack.Scale(0.15f, 0.8f, 0.22f); //y is for length
							this->RenderMesh(meshList[GEO_HANDCYLINDER], true);

							modelStack.PushMatrix();
								modelStack.Translate(0.0f, 1.0f, 0.0f);
								modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
								modelStack.Scale(1.0f, 0.3f, 1.0f);
								this->RenderMesh(meshList[GEO_HANDHEMISPHERE], true);
							modelStack.PopMatrix();

						modelStack.PopMatrix();

						//Middle
						modelStack.PushMatrix();
							modelStack.Rotate(5 * -1, 0.0f, 1.0f, 0.0f);
							modelStack.Rotate(3, 0.0f, 0.0f, 1.0f); //Tilting upwards angle
							modelStack.Translate(1.4f, 0.3f, 0.0f);
							modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
							modelStack.Scale(0.15f, 0.85f, 0.22f); //y is for length
							this->RenderMesh(meshList[GEO_HANDCYLINDER], true);

							modelStack.PushMatrix();
								modelStack.Translate(0.0f, 1.0f, 0.0f);
								modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
								modelStack.Scale(1.0f, 0.3f, 1.0f);
								this->RenderMesh(meshList[GEO_HANDHEMISPHERE], true);
							modelStack.PopMatrix();
						modelStack.PopMatrix();

						//Ring
						modelStack.PushMatrix();
							modelStack.Rotate(30 * -1, 0.0f, 1.0f, 0.0f);
							modelStack.Rotate(2, 0.0f, 0.0f, 1.0f); //Tilting upwards angle
							modelStack.Translate(1.4f, 0.3f, 0.0f);
							modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
							modelStack.Scale(0.15f, 0.75f, 0.22f); //y is for length
							this->RenderMesh(meshList[GEO_HANDCYLINDER], true);

							modelStack.PushMatrix();
								modelStack.Translate(0.0f, 1.0f, 0.0f);
								modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
								modelStack.Scale(1.0f, 0.3f, 1.0f);
								this->RenderMesh(meshList[GEO_HANDHEMISPHERE], true);
							modelStack.PopMatrix();
						modelStack.PopMatrix();

						//Pinky
						modelStack.PushMatrix();
							modelStack.Rotate(60 * -1, 0.0f, 1.0f, 0.0f);
							modelStack.Translate(1.2f, 0.3f, 0.0f);
							modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
							modelStack.Scale(0.15f, 0.35f, 0.22f); //y is for length
							this->RenderMesh(meshList[GEO_HANDCYLINDER], true);

							modelStack.PushMatrix();
								modelStack.Translate(0.0f, 1.0f, 0.0f);
								modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
								modelStack.Scale(1.0f, 0.3f, 1.0f);
								this->RenderMesh(meshList[GEO_HANDHEMISPHERE], true);
							
							modelStack.PopMatrix();
						modelStack.PopMatrix();

					modelStack.PopMatrix();

				modelStack.PopMatrix();

			//Push out of arms
			modelStack.PopMatrix();



		//Push out of body
		modelStack.PopMatrix();



		//Eyes
		modelStack.PushMatrix();
			modelStack.Rotate(10, 0.0f, 0.0f, 1.0f);
			modelStack.Translate(-0.3f, -0.15f, 0.94f);
			modelStack.Rotate(-10, 0.0f, 1.0f, 0.0f);
			modelStack.Scale(0.135f, 0.3f, 0.135f);
			this->RenderMesh(meshList[GEO_SONICEYEBALL], true);

			modelStack.PushMatrix();
				modelStack.Rotate(-5, 0.0f, 0.0f, 1.0f);
				modelStack.Translate(0.35f, -0.4f, 0.7f);
				modelStack.Rotate(17, 1.0f, 0.0f, 0.0f);
				modelStack.Scale(0.3f, 0.3f, 0.3f);
				this->RenderMesh(meshList[GEO_SONICGREENEYE], true);

				modelStack.PushMatrix();
					modelStack.Translate(0.10f, 0.0f, 0.7f);
					modelStack.Rotate(0, 1.0f, 1.0f, 1.0f);
					modelStack.Scale(0.7f, 0.58f, 0.7f);
					this->RenderMesh(meshList[GEO_SONICBLACKEYE], true);
				
					modelStack.PopMatrix();
			modelStack.PopMatrix();
		modelStack.PopMatrix();
		
		//Eyes 2
		modelStack.PushMatrix();
			modelStack.Rotate(-10, 0.0f, 0.0f, 1.0f);
			modelStack.Translate(0.3f, -0.15f, 0.94f);
			modelStack.Rotate(10, 0.0f, 1.0f, 0.0f);
			modelStack.Scale(0.135f, 0.3f, 0.135f);
			this->RenderMesh(meshList[GEO_SONICEYEBALL], true);

			modelStack.PushMatrix();
				modelStack.Rotate(-5, 0.0f, 1.0f, 0.0f);
				modelStack.Translate(-0.35f, -0.4f, 0.7f);
				modelStack.Rotate(-17, 0.0f, 1.0f, 0.0f);
				modelStack.Rotate(17, 1.0f, 0.0f, 0.0f);
				modelStack.Scale(0.3f, 0.3f, 0.3f);
				this->RenderMesh(meshList[GEO_SONICGREENEYE], true);

				modelStack.PushMatrix();
					modelStack.Translate(0.10f, 0.0f, 0.7f);
					modelStack.Rotate(0, 1.0f, 1.0f, 1.0f);
					modelStack.Scale(0.7f, 0.58f, 0.7f);
					this->RenderMesh(meshList[GEO_SONICBLACKEYE], true);

				modelStack.PopMatrix();
			modelStack.PopMatrix();
		modelStack.PopMatrix();

		//Ears 1
		modelStack.PushMatrix();
			modelStack.Translate(0.55f, 0.8f, 0.3f);
			modelStack.Rotate(10, 1.0f, 0.0f, 0.0f);
			modelStack.Rotate(-27, 0.0f, 0.0f, 1.0f);
			modelStack.Rotate(-5, 0.0f, 1.0f, 0.0f);
			modelStack.Scale(0.55f, 0.55f, 0.75f);
			this->RenderMesh(meshList[GEO_SONICEARS], true);

			modelStack.PushMatrix();
				modelStack.Translate(0.0f, 0.0f, 0.06f);
				modelStack.Scale(0.8f, 0.8f, 0.8f);
				this->RenderMesh(meshList[GEO_INNERSONICEARS], true);

			modelStack.PopMatrix();

		modelStack.PopMatrix();


		//Ears 2
		modelStack.PushMatrix();
			modelStack.Translate(-0.55f, 0.8f, 0.3f);
			modelStack.Rotate(10, 1.0f, 0.0f, 0.0f);
			modelStack.Rotate(27, 0.0f, 0.0f, 1.0f);
			modelStack.Rotate(5, 0.0f, 1.0f, 0.0f);
			modelStack.Scale(0.55f, 0.55f, 0.75f);
			this->RenderMesh(meshList[GEO_SONICEARS], true);

			modelStack.PushMatrix();
				modelStack.Translate(0.0f, 0.0f, 0.06f);
				modelStack.Scale(0.8f, 0.8f, 0.8f);
				this->RenderMesh(meshList[GEO_INNERSONICEARS], true);

			modelStack.PopMatrix();

		modelStack.PopMatrix();

		//Mouth
		modelStack.PushMatrix();
			modelStack.Rotate(10, 1.0f, 0.0f, 0.0f);
			modelStack.Translate(0.0f, -0.4f, 0.1f);
			modelStack.Rotate(20, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(1.4f, 0.55f, 1.4f);
			this->RenderMesh(meshList[GEO_MOUTHTORUS], true);

			modelStack.PushMatrix();
				modelStack.Translate(0.0f, 0.0f, 0.53f);
				//modelStack.Rotate(30, 1.0f, 0.0f, 0.0f);
				modelStack.Scale(0.2f, 0.3f, 0.08f);
				this->RenderMesh(meshList[GEO_MOUTHSPHERE], true);
			modelStack.PopMatrix();

		modelStack.PopMatrix();

		


		//Hair 1 (top left hair)
		modelStack.PushMatrix();
			modelStack.Rotate(-10, 0.0f, 1.0f, 0.0f); //turn to left side
			modelStack.Translate(0.7f, 0.4f, -0.7f);
			//modelStack.Rotate(30, 1.0f, 0.0f, 0.0f); //look upwards
			modelStack.Rotate(20, 1.0f, 0.0f, 0.0f); //slant to left side
			modelStack.Scale(0.3825f, 0.5525f, 1.19f);
			//modelStack.Scale(0.45f, 1.4f, 0.65f);
			this->RenderMesh(meshList[GEO_HAIRHEMISPHERE], true);

			modelStack.PushMatrix();
				modelStack.Translate(0.f, 0.0f, 0.0f);
				modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);
				modelStack.Scale(1.0f, 0.3f, 1.0f);
				this->RenderMesh(meshList[GEO_HAIRHEMISPHERE], true);

				
					
				modelStack.Translate(0.f, 0.0f, -0.75f);
				modelStack.Scale(0.6f, 1.0f, 0.3f);
				//modelStack.Rotate(20, 1.0f, 0.0f, 0.0f);
				modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);
					
					

				modelStack.PushMatrix();
					modelStack.Scale(0.6f, 0.8f, 0.5f);
					modelStack.Translate(0.f, 0.3f, -0.8f);

					modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
					modelStack.Rotate(90 + 15, 1.0f, 0.0f, 0.0f);
					modelStack.Scale(1.0f, 1.0f, 1.0f);
					this->RenderMesh(meshList[GEO_HAIRHEMISPHEREFRUSTUM], true);

					modelStack.PushMatrix();
						modelStack.Translate(0.0f, 1.1f, 0.2f); //1.1move front 0.2 movedown

						modelStack.Rotate(5, 1.0f, 0.0f, 0.0f);
						modelStack.Scale(0.8f, 0.5f, 0.5f);
						this->RenderMesh(meshList[GEO_HAIRHALFCONE], true);


						modelStack.PopMatrix();

					modelStack.PushMatrix();
					//modelStack.Translate(0.0f, 0.0f, -0.1f); //-0.5 moveup

					//modelStack.Rotate(5, 1.0f, 0.0f, 0.0f); //tilt down
					//modelStack.Scale(1.f, 1.0f, 1.0f);

						modelStack.Translate(0.0f, 1.1f, 0.25f); //1.1move front -0.2 moveup
						modelStack.Rotate(180, 0.0f, 1.0f, 0.0f); //flip
						modelStack.Rotate(-2, 1.0f, 0.0f, 0.0f);
						modelStack.Scale(0.8f, 0.5f, 1.0f);
						this->RenderMesh(meshList[GEO_HAIRHALFCONE], true);


					modelStack.PopMatrix();

				modelStack.PopMatrix();

			modelStack.PopMatrix();

		modelStack.PopMatrix();

		//Hair 2 (top right hair)
		modelStack.PushMatrix();
			modelStack.Rotate(10, 0.0f, 1.0f, 0.0f); //turn to left side
			modelStack.Translate(-0.7f, 0.4f, -0.7f);
			//modelStack.Rotate(30, 1.0f, 0.0f, 0.0f); //look upwards
			modelStack.Rotate(20, 1.0f, 0.0f, 0.0f); //slant to left side
			modelStack.Scale(0.3825f, 0.5525f, 1.19f);
			//modelStack.Scale(0.45f, 1.4f, 0.65f);
			this->RenderMesh(meshList[GEO_HAIRHEMISPHERE], true);

			modelStack.PushMatrix();
			modelStack.Translate(0.f, 0.0f, 0.0f);
			modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);
			modelStack.Scale(1.0f, 0.3f, 1.0f);
			this->RenderMesh(meshList[GEO_HAIRHEMISPHERE], true);



			modelStack.Translate(0.f, 0.0f, -0.75f);
			modelStack.Scale(0.6f, 1.0f, 0.3f);
			//modelStack.Rotate(20, 1.0f, 0.0f, 0.0f);
			modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);



			modelStack.PushMatrix();
			modelStack.Scale(0.6f, 0.8f, 0.5f);
			modelStack.Translate(0.f, 0.3f, -0.8f);

			modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
			modelStack.Rotate(90 + 15, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(1.0f, 1.0f, 1.0f);
			this->RenderMesh(meshList[GEO_HAIRHEMISPHEREFRUSTUM], true);

			modelStack.PushMatrix();
			modelStack.Translate(0.0f, 1.1f, 0.2f); //1.1move front 0.2 movedown

			modelStack.Rotate(5, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(0.8f, 0.5f, 0.5f);
			this->RenderMesh(meshList[GEO_HAIRHALFCONE], true);


			modelStack.PopMatrix();

			modelStack.PushMatrix();
			//modelStack.Translate(0.0f, 0.0f, -0.1f); //-0.5 moveup

			//modelStack.Rotate(5, 1.0f, 0.0f, 0.0f); //tilt down
			//modelStack.Scale(1.f, 1.0f, 1.0f);

			modelStack.Translate(0.0f, 1.1f, 0.25f); //1.1move front -0.2 moveup
			modelStack.Rotate(180, 0.0f, 1.0f, 0.0f); //flip
			modelStack.Rotate(-2, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(0.8f, 0.5f, 1.0f);
			this->RenderMesh(meshList[GEO_HAIRHALFCONE], true);


			modelStack.PopMatrix();

			modelStack.PopMatrix();

			modelStack.PopMatrix();

		modelStack.PopMatrix();

		//Hair 3 (top hair)
		modelStack.PushMatrix();
			modelStack.Rotate(15, 1.0f, 0.0f, 0.0f); //turn to up side
			modelStack.Translate(0.0f, 0.6f, -0.7f);
			//modelStack.Rotate(30, 1.0f, 0.0f, 0.0f); //look upwards
			modelStack.Rotate(20, 1.0f, 0.0f, 0.0f); //slant to left side
			modelStack.Scale(0.3525f, 0.5025f, 1.1f);
			//modelStack.Scale(0.45f, 1.4f, 0.65f);
			this->RenderMesh(meshList[GEO_HAIRHEMISPHERE], true);

			modelStack.PushMatrix();
			modelStack.Translate(0.f, 0.0f, 0.0f);
			modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);
			modelStack.Scale(1.0f, 0.3f, 1.0f);
			this->RenderMesh(meshList[GEO_HAIRHEMISPHERE], true);



			modelStack.Translate(0.f, 0.0f, -0.75f);
			modelStack.Scale(0.6f, 1.0f, 0.3f);
			//modelStack.Rotate(20, 1.0f, 0.0f, 0.0f);
			modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);



			modelStack.PushMatrix();
			modelStack.Scale(0.6f, 0.8f, 0.5f);
			modelStack.Translate(0.f, 0.3f, -0.8f);

			modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
			modelStack.Rotate(90 + 15, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(1.0f, 1.0f, 1.0f);
			this->RenderMesh(meshList[GEO_HAIRHEMISPHEREFRUSTUM], true);

			modelStack.PushMatrix();
			modelStack.Translate(0.0f, 1.1f, 0.2f); //1.1move front 0.2 movedown

			modelStack.Rotate(5, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(0.8f, 0.5f, 0.5f);
			this->RenderMesh(meshList[GEO_HAIRHALFCONE], true);


			modelStack.PopMatrix();

			modelStack.PushMatrix();
			//modelStack.Translate(0.0f, 0.0f, -0.1f); //-0.5 moveup

			//modelStack.Rotate(5, 1.0f, 0.0f, 0.0f); //tilt down
			//modelStack.Scale(1.f, 1.0f, 1.0f);

			modelStack.Translate(0.0f, 1.1f, 0.25f); //1.1move front -0.2 moveup
			modelStack.Rotate(180, 0.0f, 1.0f, 0.0f); //flip
			modelStack.Rotate(-2, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(0.8f, 0.5f, 1.0f);
			this->RenderMesh(meshList[GEO_HAIRHALFCONE], true);


			modelStack.PopMatrix();

			modelStack.PopMatrix();

			modelStack.PopMatrix();

		modelStack.PopMatrix();

		//Hair 4 (Middle hair)
		modelStack.PushMatrix();
			modelStack.Rotate(-15, 1.0f, 0.0f, 0.0f); //turn to down side
			modelStack.Translate(0.0f, 0.3f, -0.7f);
			//modelStack.Rotate(30, 1.0f, 0.0f, 0.0f); //look upwards
			modelStack.Rotate(20, 1.0f, 0.0f, 0.0f); //slant to left side
			modelStack.Scale(0.3525f, 0.5025f, 1.1f);
			//modelStack.Scale(0.45f, 1.4f, 0.65f);
			this->RenderMesh(meshList[GEO_HAIRHEMISPHERE], true);

			modelStack.PushMatrix();
			modelStack.Translate(0.f, 0.0f, 0.0f);
			modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);
			modelStack.Scale(1.0f, 0.3f, 1.0f);
			this->RenderMesh(meshList[GEO_HAIRHEMISPHERE], true);



			modelStack.Translate(0.f, 0.0f, -0.75f);
			modelStack.Scale(0.6f, 1.0f, 0.3f);
			//modelStack.Rotate(20, 1.0f, 0.0f, 0.0f);
			modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);



			modelStack.PushMatrix();
			modelStack.Scale(0.6f, 0.8f, 0.5f);
			modelStack.Translate(0.f, 0.3f, -0.8f);

			modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
			modelStack.Rotate(90 + 15, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(1.0f, 1.0f, 1.0f);
			this->RenderMesh(meshList[GEO_HAIRHEMISPHEREFRUSTUM], true);

			modelStack.PushMatrix();
			modelStack.Translate(0.0f, 1.1f, 0.2f); //1.1move front 0.2 movedown

			modelStack.Rotate(5, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(0.8f, 0.5f, 0.5f);
			this->RenderMesh(meshList[GEO_HAIRHALFCONE], true);


			modelStack.PopMatrix();

			modelStack.PushMatrix();
			//modelStack.Translate(0.0f, 0.0f, -0.1f); //-0.5 moveup

			//modelStack.Rotate(5, 1.0f, 0.0f, 0.0f); //tilt down
			//modelStack.Scale(1.f, 1.0f, 1.0f);

			modelStack.Translate(0.0f, 1.1f, 0.25f); //1.1move front -0.2 moveup
			modelStack.Rotate(180, 0.0f, 1.0f, 0.0f); //flip
			modelStack.Rotate(-2, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(0.8f, 0.5f, 1.0f);
			this->RenderMesh(meshList[GEO_HAIRHALFCONE], true);


			modelStack.PopMatrix();

			modelStack.PopMatrix();

			modelStack.PopMatrix();

		modelStack.PopMatrix();

		//Hair 5 (bottom left hair)
		modelStack.PushMatrix();
			modelStack.Rotate(-10, 0.0f, 1.0f, 0.0f); //turn to left side
			modelStack.Rotate(-25, 1.0f, 0.0f, 0.0f); //turn to down side
			modelStack.Translate(0.55f, 0.0f, -0.7f);
			//modelStack.Rotate(30, 1.0f, 0.0f, 0.0f); //look upwards
			modelStack.Rotate(20, 1.0f, 0.0f, 0.0f); //slant to left side
			modelStack.Scale(0.3825f, 0.5525f, 1.19f);
			//modelStack.Scale(0.45f, 1.4f, 0.65f);
			this->RenderMesh(meshList[GEO_HAIRHEMISPHERE], true);

			modelStack.PushMatrix();
			modelStack.Translate(0.f, 0.0f, 0.0f);
			modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);
			modelStack.Scale(1.0f, 0.3f, 1.0f);
			this->RenderMesh(meshList[GEO_HAIRHEMISPHERE], true);



			modelStack.Translate(0.f, 0.0f, -0.75f);
			modelStack.Scale(0.6f, 1.0f, 0.3f);
			//modelStack.Rotate(20, 1.0f, 0.0f, 0.0f);
			modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);



			modelStack.PushMatrix();
			modelStack.Scale(0.6f, 0.8f, 0.5f);
			modelStack.Translate(0.f, 0.3f, -0.8f);

			modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
			modelStack.Rotate(90 + 15, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(1.0f, 1.0f, 1.0f);
			this->RenderMesh(meshList[GEO_HAIRHEMISPHEREFRUSTUM], true);

			modelStack.PushMatrix();
			modelStack.Translate(0.0f, 1.1f, 0.2f); //1.1move front 0.2 movedown

			modelStack.Rotate(5, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(0.8f, 0.5f, 0.5f);
			this->RenderMesh(meshList[GEO_HAIRHALFCONE], true);


			modelStack.PopMatrix();

			modelStack.PushMatrix();
			//modelStack.Translate(0.0f, 0.0f, -0.1f); //-0.5 moveup

			//modelStack.Rotate(5, 1.0f, 0.0f, 0.0f); //tilt down
			//modelStack.Scale(1.f, 1.0f, 1.0f);

			modelStack.Translate(0.0f, 1.1f, 0.25f); //1.1move front -0.2 moveup
			modelStack.Rotate(180, 0.0f, 1.0f, 0.0f); //flip
			modelStack.Rotate(-2, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(0.8f, 0.5f, 1.0f);
			this->RenderMesh(meshList[GEO_HAIRHALFCONE], true);


			modelStack.PopMatrix();

			modelStack.PopMatrix();

			modelStack.PopMatrix();

		modelStack.PopMatrix();

		//Hair 6 (bottom right hair)
		modelStack.PushMatrix();
			modelStack.Rotate(10, 0.0f, 1.0f, 0.0f); //turn to left side
			modelStack.Rotate(-25, 1.0f, 0.0f, 0.0f); //turn to down side
			modelStack.Translate(-0.55f, 0.0f, -0.7f);
			//modelStack.Rotate(30, 1.0f, 0.0f, 0.0f); //look upwards
			modelStack.Rotate(20, 1.0f, 0.0f, 0.0f); //slant to left side
			modelStack.Scale(0.3825f, 0.5525f, 1.19f);
			//modelStack.Scale(0.45f, 1.4f, 0.65f);
			this->RenderMesh(meshList[GEO_HAIRHEMISPHERE], true);

			modelStack.PushMatrix();
			modelStack.Translate(0.f, 0.0f, 0.0f);
			modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);
			modelStack.Scale(1.0f, 0.3f, 1.0f);
			this->RenderMesh(meshList[GEO_HAIRHEMISPHERE], true);



			modelStack.Translate(0.f, 0.0f, -0.75f);
			modelStack.Scale(0.6f, 1.0f, 0.3f);
			//modelStack.Rotate(20, 1.0f, 0.0f, 0.0f);
			modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);



			modelStack.PushMatrix();
			modelStack.Scale(0.6f, 0.8f, 0.5f);
			modelStack.Translate(0.f, 0.3f, -0.8f);

			modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
			modelStack.Rotate(90 + 15, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(1.0f, 1.0f, 1.0f);
			this->RenderMesh(meshList[GEO_HAIRHEMISPHEREFRUSTUM], true);

			modelStack.PushMatrix();
			modelStack.Translate(0.0f, 1.1f, 0.2f); //1.1move front 0.2 movedown

			modelStack.Rotate(5, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(0.8f, 0.5f, 0.5f);
			this->RenderMesh(meshList[GEO_HAIRHALFCONE], true);


			modelStack.PopMatrix();

			modelStack.PushMatrix();
			//modelStack.Translate(0.0f, 0.0f, -0.1f); //-0.5 moveup

			//modelStack.Rotate(5, 1.0f, 0.0f, 0.0f); //tilt down
			//modelStack.Scale(1.f, 1.0f, 1.0f);

			modelStack.Translate(0.0f, 1.1f, 0.25f); //1.1move front -0.2 moveup
			modelStack.Rotate(180, 0.0f, 1.0f, 0.0f); //flip
			modelStack.Rotate(-2, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(0.8f, 0.5f, 1.0f);
			this->RenderMesh(meshList[GEO_HAIRHALFCONE], true);


			modelStack.PopMatrix();

			modelStack.PopMatrix();

			modelStack.PopMatrix();

		modelStack.PopMatrix();

	modelStack.PopMatrix();


	//scale.SetToScale(1, 1, 1);
	//rotate.SetToRotation(0, 0.0f, 0.0f, 1.0f);
	//translate.SetToTranslation(0, 0, 0.0);
	//model = translate * rotate * scale;
	//MVP = projection * view * model;
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	//meshList[GEO_SPHERE]->Render();
	//
	//
	//
	//translate.SetToIdentity();
	//rotate.SetToIdentity();
	//scale.SetToIdentity();

	//scale.SetToScale(1, 1, 1);
	//rotate.SetToRotation(rotateAngle, 0.0f, 0.0f, 1.0f);
	//translate.SetToTranslation(0, 0, translateZ);
	//model = translate * rotate * scale;
	//MVP = projection * view * model;
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	//meshList[GEO_CONE]->Render();

	//translate.SetToIdentity();
	//rotate.SetToIdentity();
	//scale.SetToIdentity();

	//scale.SetToScale(1, 1, -1);
	//rotate.SetToRotation(rotateAngle, 0.0f, 0.0f, 1.0f);
	//translate.SetToTranslation(0, 0, -translateZ);
	//model = translate * rotate * scale;
	//MVP = projection * view * model;
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	//meshList[GEO_CYLINDER]->Render();
	

	

	
}

void SceneLight1::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	mesh->Render();
}

void SceneLight1::Exit()
{
	// Cleanup VBO here

	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
