#pragma once

// Dependencies | std
#include <vector>
#include <iostream>

// Dependencies | in_time_engine
#include <in_time_engine/InTimeEngine.h>
#include <in_time_engine/json_serializer.h>

// Dependencies | termcolor
#include <termcolor/termcolor.hpp>

// Dependencies | nlohmann
#include <nlohmann/json.hpp>

namespace test {
	class Test {
		// Object
		public:
			// Properties
			it::InTimeEngine& inTimeEngine;
			std::vector<it::GameObject*> everyGameObject = std::vector<it::GameObject*>(0);

			// Constructor / Destructor
			Test(it::InTimeEngine& inTimeEngine) : inTimeEngine(inTimeEngine) {

			}
			~Test() {

			}

			// Functions
			void test() {
				it::RGBImage rgbImage = it::RGBImage("C:/Users/chris/Downloads/jpg.jpg");
				rgbImage.saveAsPNG("C:/Users/chris/Downloads/jpg_to_png_2.png");
				const std::type_info& typeInfo = rgbImage.getTypeInfo();
				std::cout << typeInfo.name() << std::endl;

				quitFunctionality();
				createCamera2D();
				create2DGrid();

				//testComponentSharedAndWeakPointers();
				//testJsonSerializerGLMFunctions();
				//testJsonSerializerGameEngineFunctions();
				//scaleTime();
				//testParentToChildRelationships();
				//testPhysics();
				enableFrameCounter();
				//globalToLocalPosition();
				//globalToLocalOrientation();
				//globalToLocalScale();
				//createEveryComponent();
				//testGameObjectSharedAndWeakPointers();
				//testScene();
				//testComponentRegistry();
				createPyramid();
			}

			void scaleTime() {
				it::InTimeEngine* inTimeEngine = it::InTimeEngine::s_getSingleton();
				inTimeEngine->coreTime.scale = 1.0;
				inTimeEngine->fixedTime.scale = 1.0f;
			}
			void createCamera2D() {
				// Create 2D camera
				it::GameObject& cameraGO = inTimeEngine.gameObjectManager.createGameObject("Camera 2D");
				it::Camera2D* camera2d = new it::Camera2D();
				cameraGO.addComponent(camera2d);
				camera2d->camera2D.renderTarget = glfw::Engine::getSingleton()->windowManager.windows.front().getWindow();
				camera2d->camera2D.backgroundColor = glm::vec4(0.15f, 0.15f, 0.15f, 1);
				
				// Make main camera and debug camera
				gl::Camera::mainCamera = (gl::Camera*)camera2d;
				gl::Camera::debugCamera = (gl::Camera*)camera2d;

				// Camera 2D control
				it::CameraControl2D* cameraControl = new it::CameraControl2D();
				cameraControl->camera2D = camera2d;
			}
			void quitFunctionality() {
				// Assign quit functionality
				it::KeyControl* keyControl = new it::KeyControl();
				keyControl->keysToMatch.push_back(glfw::KeyCode::ESCAPE);
				keyControl->function = []() { it::InTimeEngine::s_getSingleton()->stop(); };
			}
			void create2DGrid() {
				it::GameObject& gridGO = inTimeEngine.gameObjectManager.createGameObject("Grid");
				it::GPUTransform* gpuTransform = new it::GPUTransform();
				gridGO.addComponent(gpuTransform);

				for (int i = -10; i <= 10; i++) {
					it::GPULine* horizontalLine = new it::GPULine();
					gridGO.addComponent(horizontalLine);
					horizontalLine->line.width = 1.0f;
					horizontalLine->line.gpuData[0].position = glm::vec3(i, -10, 0);
					horizontalLine->line.gpuData[1].position = glm::vec3(i, 10, 0);
					horizontalLine->line.gpuData[0].color = glm::vec4(1.0f, 1.0f, 1.0f, 0.25f);
					horizontalLine->line.gpuData[1].color = glm::vec4(1.0f, 1.0f, 1.0f, 0.25f);

					it::GPULine* verticalLine = new it::GPULine();
					gridGO.addComponent(verticalLine);
					verticalLine->line.width = 1.0f;
					verticalLine->line.gpuData[0].position = glm::vec3(-10, i, 0);
					verticalLine->line.gpuData[1].position = glm::vec3(10, i, 0);
					verticalLine->line.gpuData[0].color = glm::vec4(1.0f, 1.0f, 1.0f, 0.25f);
					verticalLine->line.gpuData[1].color = glm::vec4(1.0f, 1.0f, 1.0f, 0.25f);
				}
			}
			void testParentToChildRelationships() {
				// Parent
				it::GameObject& parentGO = inTimeEngine.gameObjectManager.createGameObject("Parent");
				parentGO.addComponent(new it::GPUTriangleFan());
				it::PhysicsTransformation* parentTransformation = new it::PhysicsTransformation();
				parentGO.addComponent(parentTransformation);
				parentTransformation->translation.x = 0.0f;
				parentTransformation->translation.y = 0.0f;
				parentTransformation->rotation.z = 3.14f / 2.0f;

				// Child 0
				it::GameObject& childGO0 = inTimeEngine.gameObjectManager.createGameObject("Child 0");
				childGO0.transform.position.x = 1.0f;
				childGO0.transform.position.y = 1.0f;
				it::GPUTriangleFan* childTriangleFan0 = new it::GPUTriangleFan();
				childGO0.addComponent(childTriangleFan0);
				for (gl::TriangleFan::GPUData& gpuData : childTriangleFan0->triangleFan.gpuData)
					gpuData.color = glm::vec4(1, 0, 0, 1);
				it::PhysicsTransformation* childPhysicsTransformation = new it::PhysicsTransformation();
				childGO0.addComponent(childPhysicsTransformation);
				childPhysicsTransformation->rotation.z = 0.0f;

				// Child 1
				it::GameObject& childGO1 = inTimeEngine.gameObjectManager.createGameObject("Child 1");
				childGO1.transform.position.x = -1.0f;
				childGO1.transform.position.y = 1.0f;
				it::GPUTriangleFan* childTriangleFan1 = new it::GPUTriangleFan();
				childGO1.addComponent(childTriangleFan1);
				for (gl::TriangleFan::GPUData& gpuData : childTriangleFan1->triangleFan.gpuData)
					gpuData.color = glm::vec4(1, 0, 0, 1);
				it::PhysicsTransformation* childPhysicsTransformation1 = new it::PhysicsTransformation();
				childGO1.addComponent(childPhysicsTransformation1);
				childPhysicsTransformation1->rotation.z = 0.0f;

				// Child 2
				it::GameObject& childGO2 = inTimeEngine.gameObjectManager.createGameObject("Child 2");
				childGO2.transform.position.x = -1.0f;
				childGO2.transform.position.y = -1.0f;
				it::GPUTriangleFan* childTriangleFan2 = new it::GPUTriangleFan();
				childGO2.addComponent(childTriangleFan2);
				for (gl::TriangleFan::GPUData& gpuData : childTriangleFan2->triangleFan.gpuData)
					gpuData.color = glm::vec4(1, 0, 0, 1);
				it::PhysicsTransformation* childPhysicsTransformation2 = new it::PhysicsTransformation();
				childGO2.addComponent(childPhysicsTransformation2);
				childPhysicsTransformation2->rotation.z = 0.0f;

				// Child 3
				it::GameObject& childGO3 = inTimeEngine.gameObjectManager.createGameObject("Child 3");
				childGO3.transform.position.x = 1.0f;
				childGO3.transform.position.y = -1.0f;
				it::GPUTriangleFan* childTriangleFan3 = new it::GPUTriangleFan();
				childGO3.addComponent(childTriangleFan3);
				for (gl::TriangleFan::GPUData& gpuData : childTriangleFan3->triangleFan.gpuData)
					gpuData.color = glm::vec4(1, 0, 0, 1);
				it::PhysicsTransformation* childPhysicsTransformation3 = new it::PhysicsTransformation();
				childGO3.addComponent(childPhysicsTransformation3);
				childPhysicsTransformation3->rotation.z = 0.0f;

				childGO0.transform.setParent(&parentGO.transform);
				childGO1.transform.setParent(&parentGO.transform);
				childGO2.transform.setParent(&parentGO.transform);
				childGO3.transform.setParent(&parentGO.transform);
			}
			void testPhysics() {
				// Create dynamic object
				it::GameObject& dynamicGO = inTimeEngine.gameObjectManager.createGameObject("dynamic rigid body");
				dynamicGO.transform.position = glm::vec3(0.0f, 4.0f, 0.0f);
				dynamicGO.transform.orientation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
				dynamicGO.addComponent(new it::GPUTransform());
				dynamicGO.addComponent(new it::GPUTriangleFan());

				b2WorldId worldId = inTimeEngine.physicsEngine2D.getWorldId();

				b2BodyDef def = b2DefaultBodyDef();
				def.type = b2_dynamicBody;
				def.userData = nullptr;

				b2BodyId bodyId = b2CreateBody(worldId, &def);
				it::RigidBodyB2D* dynamicBody = new it::RigidBodyB2D();
				dynamicGO.addComponent(dynamicBody);
				dynamicBody->initBody(bodyId);
				b2Polygon shape = b2MakeBox(0.5f, 0.5f);

				b2ShapeDef shapeDef = b2DefaultShapeDef();
				shapeDef.density = 1.0f;
				shapeDef.material.restitution = 0.5f;

				b2ShapeId dynamicShapeId = b2CreatePolygonShape(bodyId, &shapeDef, &shape);

				it::ShapeB2D* shape2D = new it::ShapeB2D();
				dynamicGO.addComponent(shape2D);
				shape2D->initShape(dynamicShapeId);

				// Create ground object
				it::GameObject& groundGO = inTimeEngine.gameObjectManager.createGameObject("static rigid body");
				groundGO.transform.position = glm::vec3(0, -3, 0);
				it::GPUTransform* groundGPUTransform = new it::GPUTransform();
				groundGO.addComponent(groundGPUTransform);
				it::GPUTriangleFan* groundTriangleFan = new it::GPUTriangleFan();
				groundGO.addComponent(groundTriangleFan);
				groundTriangleFan->triangleFan.gpuData[0].position = glm::vec3(5.0f, -0.5, 0.0f);
				groundTriangleFan->triangleFan.gpuData[1].position = glm::vec3(-5.0f, -0.5f, 0.0f);
				groundTriangleFan->triangleFan.gpuData[2].position = glm::vec3(-5.0f, 0.5f, 0.0f);
				groundTriangleFan->triangleFan.gpuData[3].position = glm::vec3(5.0f, 0.5f, 0.0f);

				b2BodyDef groundBodyDefinition = b2DefaultBodyDef();
				groundBodyDefinition.position = b2Vec2(0.0f, -3.0f);
				groundBodyDefinition.userData = nullptr;
				b2BodyId groundBodyId = b2CreateBody(it::InTimeEngine::s_getSingleton()->physicsEngine2D.getWorldId(), &groundBodyDefinition);
				it::RigidBodyB2D* groundRigidBody = new it::RigidBodyB2D();
				groundGO.addComponent(groundRigidBody);
				groundRigidBody->initBody(groundBodyId);

				b2Polygon groundBox = b2MakeBox(5.0f, 0.5f);

				b2ShapeDef groundShapeDef = b2DefaultShapeDef();
				b2ShapeId groundShapeId = b2CreatePolygonShape(groundBodyId, &groundShapeDef, &groundBox);
				it::ShapeB2D* groundShape = new it::ShapeB2D();
				groundGO.addComponent(groundShape);
				groundShape->initShape(groundShapeId);
			}
			void testMultiParentToChildRelationships() {
				it::GameObject& go1 = inTimeEngine.gameObjectManager.createGameObject("go1");
				it::GameObject& go2 = inTimeEngine.gameObjectManager.createGameObject("go2");
				it::GameObject& go3 = inTimeEngine.gameObjectManager.createGameObject("go3");
				it::GameObject& go4 = inTimeEngine.gameObjectManager.createGameObject("go4");
				it::GameObject& go5 = inTimeEngine.gameObjectManager.createGameObject("go5");

				go2.transform.setParent(&go1.transform);
				go3.transform.setParent(&go1.transform);
				go4.transform.setParent(&go2.transform);
				go5.transform.setParent(&go3.transform);
			}
			void enableFrameCounter() {
				it::FrameCounter* frameCounter = new it::FrameCounter();
			}
			void globalToLocalPosition() {
				
				it::GameObject& parentGO = inTimeEngine.gameObjectManager.createGameObject("parent");
				parentGO.transform.position = glm::vec3(-2, 0, 0);
				parentGO.transform.calculateGlobalMatrix();
				it::GPUTransform* parentGPUTransform = new it::GPUTransform();
				parentGO.addComponent(parentGPUTransform);
				it::GPUPoint* parentPoint = new it::GPUPoint();
				parentGO.addComponent(parentPoint);
				parentPoint->point.gpuData.color = glm::vec4(1, 0, 0, 1);

				it::GameObject& childGO = inTimeEngine.gameObjectManager.createGameObject("child");
				childGO.transform.setParent(&parentGO.transform);
				childGO.transform.position = glm::vec3(2, -1, 0);
				childGO.transform.calculateGlobalMatrix();
				it::GPUTransform* childGPUTransform = new it::GPUTransform();
				childGO.addComponent(childGPUTransform);
				it::GPUPoint* childPoint = new it::GPUPoint();
				childGO.addComponent(childPoint);
				childPoint->point.gpuData.color = glm::vec4(0, 1, 0, 1);

				glm::mat4 parentMatrix = parentGO.transform.getMatrix();
				glm::mat4 childMatrix = childGO.transform.getMatrix();
				glm::mat4 parentInverse = glm::inverse(parentGO.transform.getMatrix());
				glm::mat4 childInverse = glm::inverse(childGO.transform.getMatrix());
				glm::mat4 globalChildInverse = glm::inverse(childGO.transform.getGlobalMatrix());
				glm::vec4 newPosition = glm::vec4(2, 2, 0, 1);

				glm::vec3 result = globalChildInverse * newPosition;
				result = parentGO.transform.toLocalPosition(newPosition);

				it::GameObject& otherGO = inTimeEngine.gameObjectManager.createGameObject("otherGO");
				otherGO.transform.setParent(&parentGO.transform);
				otherGO.transform.position = result;
				otherGO.transform.calculateGlobalMatrix();
				it::GPUTransform* otherGPUTransform = new it::GPUTransform();
				otherGO.addComponent(otherGPUTransform);
				it::GPUPoint* otherPoint = new it::GPUPoint();
				otherGO.addComponent(otherPoint);
				otherPoint->point.gpuData.color = glm::vec4(0, 1, 1, 1);
			}
			void globalToLocalOrientation() {
				it::GameObject& parent = inTimeEngine.gameObjectManager.createGameObject("parent");
				it::Transform& parentTransform = parent.transform;
				it::GPUTransform* parentGPUTransform = new it::GPUTransform();
				parent.addComponent(parentGPUTransform);
				it::GPUTriangle* parentTriangle = new it::GPUTriangle();
				parent.addComponent(parentTriangle);
				parentTransform.orientation = glm::quat(glm::vec3(0, 0, 3.14f / 2));

				it::GameObject& child = inTimeEngine.gameObjectManager.createGameObject("child");
				it::Transform& childTransform = child.transform;
				it::GPUTransform* childGPUTransform = new it::GPUTransform();
				child.addComponent(childGPUTransform);
				it::GPUTriangle* childTriangle = new it::GPUTriangle();
				child.addComponent(childTriangle);
				childTransform.setParent(&parentTransform);
				childTransform.position = glm::vec3(0, 2, 0);

				it::GameObject& other = inTimeEngine.gameObjectManager.createGameObject("other");
				it::Transform& otherTransform = other.transform;
				it::GPUTransform* otherGPUTransform = new it::GPUTransform();
				other.addComponent(otherGPUTransform);
				it::GPUTriangle* otherTriangle = new it::GPUTriangle();
				other.addComponent(otherTriangle);
				otherTransform.setParent(&parentTransform);
				otherTransform.position = parentTransform.toLocalPosition(glm::vec3(1, 1, 0));
				otherTransform.orientation = parentTransform.toLocalOrientation(glm::quat(glm::vec3(0, 0, 3.14f / 1.0f))); // Face right
			}
			void globalToLocalScale() {
				it::GameObject& parent = inTimeEngine.gameObjectManager.createGameObject("parent");
				it::Transform& parentTransform = parent.transform;
				it::GPUTransform* parentGPUTransform = new it::GPUTransform();
				parent.addComponent(parentGPUTransform);
				it::GPUTriangle* parentTriangle = new it::GPUTriangle();
				parent.addComponent(parentTriangle);
				parentTransform.scale.x = 2.0f;

				it::GameObject& child = inTimeEngine.gameObjectManager.createGameObject("child");
				it::Transform& childTransform = child.transform;
				it::GPUTransform* childGPUTransform = new it::GPUTransform();
				child.addComponent(childGPUTransform);
				it::GPUTriangle* childTriangle = new it::GPUTriangle();
				child.addComponent(childTriangle);
				childTransform.setParent(&parentTransform);
				childTransform.position.y = 1.0f;
				childTransform.scale.x = 2.0f;

				it::GameObject& other = inTimeEngine.gameObjectManager.createGameObject("other");
				it::Transform& otherTransform = other.transform;
				it::GPUTransform* otherGPUTransform = new it::GPUTransform();
				other.addComponent(otherGPUTransform);
				it::GPUTriangle* otherTriangle = new it::GPUTriangle();
				other.addComponent(otherTriangle);
				otherTransform.setParent(&childTransform);
				otherTransform.position.y = 1.0f;
				otherTransform.scale = otherTransform.toLocalScale(glm::vec3(5, 1, 1));
			}
			void createEveryComponent() {
				float x = -5.0f;
				for (size_t i = 0; i < 10; i++, x +=1.0f) {
					it::GameObject& gameObject = inTimeEngine.gameObjectManager.createGameObject("Every Component " + std::to_string(i));
					gameObject.transform.setPosition(glm::vec3(x, 0.0f, 0.0f));
					everyGameObject.push_back(&gameObject);
				}

				everyGameObject[0]->addComponent(new it::EmptyComponent());
				everyGameObject[1]->addComponent(new it::GPUPoint());
				everyGameObject[2]->addComponent(new it::GPULine());
				everyGameObject[3]->addComponent(new it::GPUMultiLine());
				everyGameObject[4]->addComponent(new it::GPUTriangle());
				everyGameObject[5]->addComponent(new it::GPUTriangleFan());
				everyGameObject[6]->addComponent(new it::GPUTriangleStrip());

				for (it::GameObject* gameObject : everyGameObject) {
					it::Component* component = gameObject->getFirstComponent();
					if (component == nullptr)
						continue;
					gameObject->name = gameObject->name + component->getTypeInfo().name();
				}
			}
			void testGameObjectSharedAndWeakPointers() {
				std::cout << "Testing game objects shared and weak pointers." << std::endl;

				// Weak pointers
				std::weak_ptr<it::GameObject*> weakPointerToGameObject;

				// Test: game object's weak pointer linkage to the game object
				{
					it::GameObject& gameObject = inTimeEngine.gameObjectManager.createGameObject();
					weakPointerToGameObject = gameObject.getWeakPointer();

					// Test: heap game object weak pointer
					std::cout << "Test: game object's weak pointer can lock.\nResult: ";
					std::shared_ptr<it::GameObject*> heapGameObjectLock = weakPointerToGameObject.lock();
					if (heapGameObjectLock) {
						std::cout << termcolor::green << "pass." << termcolor::reset << std::endl;

						std::cout << "Test: heap allocated game object weak pointer's data is valid.\nResult: ";
						it::GameObject* heapGameObjectFromLock = *heapGameObjectLock;
						if (heapGameObjectFromLock->name == gameObject.name)
							std::cout << termcolor::green << "pass";
						else
							std::cout << termcolor::red << "fail";
						std::cout << termcolor::reset << std::endl;
					}
					else {
						std::cout << termcolor::red << "fail" << termcolor::reset << std::endl;
					}
					inTimeEngine.gameObjectManager.destroyImmediately(gameObject);

					std::cout << "Finished testing game objects shared and weak pointers." << std::endl;
				}

				// Test: game object's weak pointer validity post destruction
				{
					// Test: heap game object's weak pointer after destruction must be invalid
					std::cout << "Test: game object's weak pointer after destruction must be invalid.\nResult: ";
					std::shared_ptr<it::GameObject*> heapGameObjectLock = weakPointerToGameObject.lock();
					if (!heapGameObjectLock)
						std::cout << termcolor::green << "pass";
					else
						std::cout << termcolor::red << "fail";
					std::cout << termcolor::reset << std::endl;
				}

				std::cout << std::endl;
			}
			void testComponentSharedAndWeakPointers() {
				std::cout << "Testing components shared and weak pointers." << std::endl;

				// Weak pointers
				std::weak_ptr<it::Component*> weakPointerToHeapEmptyComponent;

				// Test: empty components's weak pointer linkage to empty component
				{
					// Heap allocated game object and empty component
					it::GameObject& gameObject = inTimeEngine.gameObjectManager.createGameObject();
					it::EmptyComponent* heapEmptyComponent = new it::EmptyComponent();
					gameObject.addComponent(heapEmptyComponent);
					
					// Weak pointer assignment
					weakPointerToHeapEmptyComponent = heapEmptyComponent->getWeakPointer();

					// Test: heap empty component weak pointer
					std::cout << "Test: heap allocated empty component's weak pointer can lock.\nResult: ";
					std::shared_ptr<it::Component*> heapComponentLock = weakPointerToHeapEmptyComponent.lock();
					if (heapComponentLock) {
						std::cout << termcolor::green << "pass." << termcolor::reset << std::endl;

						std::cout << "Test: heap allocated empty component weak pointer's data is valid.\nResult: ";
						it::EmptyComponent* heapEmptyComponentFromLock = static_cast<it::EmptyComponent*>(*heapComponentLock);
						if (heapEmptyComponentFromLock == heapEmptyComponent)
							std::cout << termcolor::green << "pass";
						else
							std::cout << termcolor::red << "fail";
						std::cout << termcolor::reset << std::endl;
					}
					else {
						std::cout << termcolor::red << "fail" << termcolor::reset << std::endl;
					}

					std::cout << "Finished testing components shared and weak pointers." << std::endl;

					inTimeEngine.gameObjectManager.componentManager.destroyImmediately(*heapEmptyComponent);
					inTimeEngine.gameObjectManager.destroyImmediately(gameObject);
				}

				// Test: stack component's weak pointer validity post destruction
				{
					// Test: heap empty component's weak pointer after destruction must be invalid
					std::cout << "Test: heap empty component's weak pointer after destruction must be invalid.\nResult: ";
					std::shared_ptr<it::Component*> heapGameObjectLock = weakPointerToHeapEmptyComponent.lock();
					if (!heapGameObjectLock)
						std::cout << termcolor::green << "pass";
					else
						std::cout << termcolor::red << "fail";
					std::cout << termcolor::reset << std::endl;
				}
				
				std::cout << std::endl;
			}
			void testJsonSerializerGLMFunctions() {

				std::cout << "Testing json serializer glm functions." << std::endl;
				glm::vec2 vec2(1, 2);
				glm::vec3 vec3(1, 2, 3);
				glm::vec4 vec4(1, 2, 3, 4);
				glm::quat quat(1, 2, 3, 4);
				glm::mat2 mat2(1, 2, 3, 4);
				glm::mat3 mat3(1, 2, 3, 4, 5, 6, 7, 8, 9);
				glm::mat4 mat4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

				nlohmann::json vec2ToJson = vec2;
				glm::vec2 vec2FromJson = vec2ToJson;

				nlohmann::json vec3ToJson = vec3;
				glm::vec3 vec3FromJson = vec3ToJson;

				nlohmann::json vec4ToJson = vec4;
				glm::vec4 vec4FromJson = vec4ToJson;

				nlohmann::json quatToJson = quat;
				glm::quat quatFromJson = quatToJson;

				nlohmann::json mat2ToJson = mat2;
				glm::mat2 mat2FromJson = mat2ToJson;

				nlohmann::json mat3ToJson = mat3;
				glm::mat3 mat3FromJson = mat3ToJson;

				nlohmann::json mat4ToJson = mat4;
				glm::mat4 mat4FromJson = mat4ToJson;

				std::cout << "glm::vec2 implicit serialization result: ";
				if (vec2 == vec2FromJson)
					std::cout << termcolor::green << "pass";
				else
					std::cout << termcolor::red << "fail";
				std::cout << termcolor::reset << std::endl;

				std::cout << "glm::vec3 implicit serialization result: ";
				if (vec3 == vec3FromJson)
					std::cout << termcolor::green << "pass";
				else
					std::cout << termcolor::red << "fail";
				std::cout << termcolor::reset << std::endl;

				std::cout << "glm::vec4 implicit serialization result: ";
				if (vec4 == vec4FromJson)
					std::cout << termcolor::green << "pass";
				else
					std::cout << termcolor::red << "fail";
				std::cout << termcolor::reset << std::endl;

				std::cout << "glm::quat implicit serialization result: ";
				if (quat == quatFromJson)
					std::cout << termcolor::green << "pass";
				else
					std::cout << termcolor::red << "fail";
				std::cout << termcolor::reset << std::endl;

				std::cout << "glm::mat2 implicit serialization result: ";
				if (mat2 == mat2FromJson)
					std::cout << termcolor::green << "pass";
				else
					std::cout << termcolor::red << "fail";
				std::cout << termcolor::reset << std::endl;

				std::cout << "glm::mat3 implicit serialization result: ";
				if (mat3 == mat3FromJson)
					std::cout << termcolor::green << "pass";
				else
					std::cout << termcolor::red << "fail";
				std::cout << termcolor::reset << std::endl;

				std::cout << "glm::mat4 implicit serialization result: ";
				if (mat4 == mat4FromJson)
					std::cout << termcolor::green << "pass";
				else
					std::cout << termcolor::red << "fail";
				std::cout << termcolor::reset << std::endl;

				std::cout << "Finished testing json serializer glm functions." << std::endl;
			}
			void testJsonSerializerGameEngineFunctions() {
				std::cout << "Testing json serializer game inTimeEngine functions." << std::endl;

				it::GameObject& gameObject = inTimeEngine.gameObjectManager.createGameObject("test json serializer game object");
				gameObject.transform.position = glm::vec3(1, 2, 3);
				gameObject.transform.orientation = glm::quat(glm::vec3(0, 0, 3.14f / 2.0f));
				gameObject.transform.scale = glm::vec3(2, 2, 2);
				
				nlohmann::ordered_json gameObjectToJson = gameObject;
				it::GameObject& gameObjectFromJson = inTimeEngine.gameObjectManager.createGameObject();
				std::cout << gameObjectToJson.dump(4) << std::endl;
				gameObjectToJson.get_to(gameObjectFromJson);
				nlohmann::ordered_json result = gameObjectFromJson;

				std::cout << "Original data: " << gameObjectToJson.dump(4) << std::endl;
				std::cout << "Resulting json: " << result.dump(4) << std::endl;

				std::cout << "Result: ";
				if (gameObjectToJson == result) {
					std::cout << termcolor::green << "pass";
				} else {
					std::cout << termcolor::red << "fail";
				}
				std::cout << termcolor::reset << std::endl;

				inTimeEngine.gameObjectManager.destroyImmediately(gameObject);
				inTimeEngine.gameObjectManager.destroyImmediately(gameObjectFromJson);
			}
			void testScene() {
				// Create scene game objects
				std::vector<it::GameObject*> sceneGameObjects{};
				sceneGameObjects.reserve(10ULL);
				for (int i = 0; i < sceneGameObjects.capacity(); i++) {
					it::GameObject& gameObject = inTimeEngine.gameObjectManager.createGameObject(i, std::string("Scene GO ") + std::to_string(i));
					sceneGameObjects.push_back(&gameObject);
				}

				// Create parent to child relationships
				sceneGameObjects[2]->transform.setParent(&sceneGameObjects[1]->transform);
				sceneGameObjects[1]->transform.setParent(&sceneGameObjects[0]->transform);


				// Serialize scene
				it::Scene scene{};
				for (it::GameObject* gameObject : sceneGameObjects) {
					scene.gameObjects.push_back(gameObject->getWeakPointer());
				}
				inTimeEngine.gameObjectManager.destroyImmediately(*sceneGameObjects[5]);
				nlohmann::ordered_json serializedScene;
				scene.serialize(serializedScene);
				std::cout << serializedScene.dump(4) << std::endl;

				// Deserialize scene
				it::Scene deserializedScene{};
				deserializedScene.deserialize(serializedScene);
				for (size_t i = 0ULL; i < deserializedScene.gameObjects.size(); i++) {
					if (const std::shared_ptr<it::GameObject*> sharedGameObjectPtr = deserializedScene.gameObjects[i].lock()) {
						it::GameObject* gameObject = *sharedGameObjectPtr;
						nlohmann::ordered_json gameObjectData = *gameObject;
						std::cout << gameObjectData.dump(4);
						if (gameObject->transform.getParent() != nullptr)
							std::cout << "Has parent" << std::endl;
					}
				}
			}
			void testComponentRegistry() {
				it::GameObjectManager& goManager = inTimeEngine.gameObjectManager;
				it::ComponentRegistry& componentRegistry = inTimeEngine.componentRegistry;

				// Test every entry directly
				const std::vector<it::ComponentRegistry::Entry>& entries = componentRegistry.getEntries();
				it::GameObject& gameObject0 = goManager.createGameObject(0, "Component Registry Test 0");
				gameObject0.transform.setPosition(glm::vec3(2, 0, 0));
				for (size_t i = 0; i < entries.size(); i++)
					gameObject0.addComponent(entries[i].constructor());

				// Test component entry by creating components through their respective type_info
				it::GameObject& gameObject1 = goManager.createGameObject(1, "Component Registry Test 1");
				gameObject1.transform.setPosition(glm::vec3(-2, 0, 0));
				gameObject1.addComponent(componentRegistry.create(typeid(it::EmptyComponent)));
				gameObject1.addComponent(componentRegistry.create(typeid(it::Transformation)));
				gameObject1.addComponent(componentRegistry.create(typeid(it::PhysicsTransformation)));
				gameObject1.addComponent(componentRegistry.create(typeid(it::GPUTransform)));
				gameObject1.addComponent(componentRegistry.create(typeid(it::Camera2D)));
				gameObject1.addComponent(componentRegistry.create(typeid(it::Camera3D)));
				gameObject1.addComponent(componentRegistry.create(typeid(it::GPUPoint)));
				gameObject1.addComponent(componentRegistry.create(typeid(it::GPULine)));
				gameObject1.addComponent(componentRegistry.create(typeid(it::GPUMultiLine)));
				gameObject1.addComponent(componentRegistry.create(typeid(it::GPUTriangle)));
				gameObject1.addComponent(componentRegistry.create(typeid(it::GPUTriangleStrip)));
				gameObject1.addComponent(componentRegistry.create(typeid(it::GPUTriangleFan)));

				// Test Component entry by creating components through their respective id
				it::GameObject& gameObject2 = goManager.createGameObject(2, "Component Registry Test 2");
				gameObject2.transform.setPosition(glm::vec3(0, 2, 0));
				gameObject2.addComponent(componentRegistry.create(1));
				gameObject2.addComponent(componentRegistry.create(2));
				gameObject2.addComponent(componentRegistry.create(3));
				gameObject2.addComponent(componentRegistry.create(2000));
				gameObject2.addComponent(componentRegistry.create(2001));
				gameObject2.addComponent(componentRegistry.create(2002));
				gameObject2.addComponent(componentRegistry.create(2003));
				gameObject2.addComponent(componentRegistry.create(2004));
				gameObject2.addComponent(componentRegistry.create(2005));
				gameObject2.addComponent(componentRegistry.create(2006));
				gameObject2.addComponent(componentRegistry.create(2007));
				gameObject2.addComponent(componentRegistry.create(2008));

			}

			void createPyramid() {
				it::GameObject& gameObject = createSimulatedSquare({ 1, 1 });

				float currentWidth = 4.0f;
				float height = currentWidth * 2.0f;
				for (float y = 0.0f; y <= height; y += 1.0f) {
					for (float x = currentWidth * -1.0f; x <= currentWidth; x += 1.0f)
						it::GameObject& square = createSimulatedSquare({ x, y });
					currentWidth -= 0.5f;
				}

				createGround({ 0.0f, -4.0f }, { 10.0f, 1.0f });
			}

			it::GameObject& createSimulatedSquare(const glm::vec2& position) {
				std::string name = "Simulated Square (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ")";

				it::GameObject& gameObject = inTimeEngine.gameObjectManager.createGameObject(name);
				gameObject.addComponent(new it::GPUTransform());
				gameObject.addComponent(new it::GPUTriangleFan());
				it::RigidBodyB2D& rigidBody2d = reinterpret_cast<it::RigidBodyB2D&>(gameObject.addComponent(new it::RigidBodyB2D()));
				it::ShapeB2D& shape2d = reinterpret_cast<it::ShapeB2D&>(gameObject.addComponent(new it::ShapeB2D()));

				b2BodyDef bodyDef = b2DefaultBodyDef();
				bodyDef.type = b2_dynamicBody;
				bodyDef.position = b2Vec2(position.x, position.y);
				b2BodyId bodyId = b2CreateBody(inTimeEngine.physicsEngine2D.getWorldId(), &bodyDef);

				b2Polygon box = b2MakeBox(0.5f, 0.5f);
				b2ShapeDef shapeDef = b2DefaultShapeDef();
				shapeDef.density = 1.0f;
				shapeDef.material.restitution = 0.5f;
				b2ShapeId shapeId = b2CreatePolygonShape(bodyId, &shapeDef, &box);

				rigidBody2d.initBody(bodyId);
				shape2d.initShape(shapeId);

				return gameObject;
			}
			
			it::GameObject& createGround(const glm::vec2& position, const glm::vec2& size) {
				float halfWidth = size.x / 2.0f;
				float halfHeight = size.y / 2.0f;

				// Create ground object
				it::GameObject& gameObject = inTimeEngine.gameObjectManager.createGameObject("static rigid body");
				gameObject.transform.position = glm::vec3(position.x, position.y, 0);

				// Add components
				it::GPUTransform* groundGPUTransform = new it::GPUTransform();
				it::GPUTriangleFan* groundTriangleFan = new it::GPUTriangleFan();
				gameObject.addComponent(groundGPUTransform);
				gameObject.addComponent(groundTriangleFan);
				it::RigidBodyB2D* groundRigidBody = new it::RigidBodyB2D();
				gameObject.addComponent(groundRigidBody);
				it::ShapeB2D* groundShape = new it::ShapeB2D();
				gameObject.addComponent(groundShape);

				// Set visual representation to match size
				groundTriangleFan->triangleFan.gpuData[0].position = glm::vec3(halfWidth, -halfHeight, 0.0f);
				groundTriangleFan->triangleFan.gpuData[1].position = glm::vec3(-halfWidth, -halfHeight, 0.0f);
				groundTriangleFan->triangleFan.gpuData[2].position = glm::vec3(-halfWidth, halfHeight, 0.0f);
				groundTriangleFan->triangleFan.gpuData[3].position = glm::vec3(halfWidth, halfHeight, 0.0f);

				// Create physics body and shape
				b2BodyDef groundBodyDefinition = b2DefaultBodyDef();
				groundBodyDefinition.position = b2Vec2(position.x, position.y);
				b2BodyId groundBodyId = b2CreateBody(it::InTimeEngine::s_getSingleton()->physicsEngine2D.getWorldId(), &groundBodyDefinition);

				b2Polygon groundBox = b2MakeBox(halfWidth, halfHeight);
				b2ShapeDef groundShapeDef = b2DefaultShapeDef();
				b2ShapeId groundShapeId = b2CreatePolygonShape(groundBodyId, &groundShapeDef, &groundBox);

				// Link physics body and shape to components
				groundRigidBody->initBody(groundBodyId);
				groundShape->initShape(groundShapeId);

				return gameObject;
			}
	};
}

/*
#pragma once

// Dependencies | std
#include <vector>
#include <iostream>

// Dependencies | in_time_engine
#include <in_time_engine/InTimeEngine.h>
#include <in_time_engine/json_serializer.h>

// Dependencies | ui_engine
#include <ui_engine/UIEngine.h>

// Dependencies | termcolor
#include <termcolor/termcolor.hpp>

// Dependencies | nlohmann
#include <nlohmann/json.hpp>

namespace test {
	class Test {
		// Object
		public:
			// Properties
			std::vector<it::GameObject*> gameObjects = std::vector<it::GameObject*>(0);
			std::vector<it::GameObject*> everyGameObject = std::vector<it::GameObject*>(0);

			// Constructor / Destructor
			Test() {

			}
			~Test() {
				for (it::GameObject* gameObject : gameObjects)
					gameObject->destroyImmediately();
				gameObjects.clear();
			}

			// Functions
			void test() {
				//it::Image::Format type = it::Image::Format::UNKNOWN;
				//type = it::Image::s_getFileFormat("C:/Users/chris/Downloads/png.png");
				//type = it::Image::s_getFileFormat("C:/Users/chris/Downloads/jpg.jpg");
				//it::Image::Info info = it::Image::s_getInfo("C:/Users/chris/Downloads/png.png");

				it::RGBImage rgbImage = it::RGBImage("C:/Users/chris/Downloads/jpg.jpg");
				rgbImage.saveAsPNG("C:/Users/chris/Downloads/jpg_to_png_2.png");
				const std::type_info& typeInfo = rgbImage.getTypeInfo();
				std::cout << typeInfo.name() << std::endl;

				testComponentSharedAndWeakPointers();
				testJsonSerializerGLMFunctions();
				testJsonSerializerGameEngineFunctions();
				//scaleTime();
				quitFunctionality();
				createCamera2D();
				create2DGrid();
				testParentToChildRelationships();
				testPhysics();
				enableFrameCounter();
				//globalToLocalPosition();
				//globalToLocalOrientation();
				//globalToLocalScale();
				testUI();
				createEveryComponent();
				testGameObjectSharedAndWeakPointers();
			}

			void scaleTime() {
				it::InTimeEngine* inTimeEngine = it::InTimeEngine::s_getSingleton();
				inTimeEngine->coreTime.scale = 0.10f;
				inTimeEngine->physicsTime.scale = 0.10f;
			}
			void createCamera2D() {
				// Create 2D camera
				it::GameObject* cameraGO = new it::GameObject("Camera 2D");
				it::Camera2D* camera2d = new it::Camera2D(*cameraGO);
				camera2d->camera2d.renderTarget = glfw::Window::getWindowList().front()->getWindow();
				camera2d->camera2d.backgroundColor = glm::vec4(0.15f, 0.15f, 0.15f, 1);

				// Make main camera and debug camera
				gl::Camera::mainCamera = (gl::Camera*)camera2d;
				gl::Camera::debugCamera = (gl::Camera*)camera2d;

				// Camera 2D control
				it::CameraControl2D* cameraControl = new it::CameraControl2D();
				cameraControl->camera2d = camera2d;

				gameObjects.push_back(cameraGO);
			}
			void quitFunctionality() {
				// Assign quit functionality
				it::KeyControl* keyControl = new it::KeyControl();
				keyControl->keysToMatch.push_back(glfw::KeyCode::ESCAPE);
				keyControl->function = []() { it::InTimeEngine::s_getSingleton()->stop(); };
			}
			void create2DGrid() {
				it::GameObject* gridGO = new it::GameObject("grid");
				it::GPUTransform* gpuTransform = new it::GPUTransform(*gridGO);

				for (int i = -10; i <= 10; i++) {
					it::GPULine* horizontalLine = new it::GPULine(*gridGO);
					horizontalLine->line.width = 1.0f;
					horizontalLine->line.gpuData[0].position = glm::vec3(i, -10, 0);
					horizontalLine->line.gpuData[1].position = glm::vec3(i, 10, 0);
					horizontalLine->line.gpuData[0].color = glm::vec4(1.0f, 1.0f, 1.0f, 0.25f);
					horizontalLine->line.gpuData[1].color = glm::vec4(1.0f, 1.0f, 1.0f, 0.25f);

					it::GPULine* verticalLine = new it::GPULine(*gridGO);
					verticalLine->line.width = 1.0f;
					verticalLine->line.gpuData[0].position = glm::vec3(-10, i, 0);
					verticalLine->line.gpuData[1].position = glm::vec3(10, i, 0);
					verticalLine->line.gpuData[0].color = glm::vec4(1.0f, 1.0f, 1.0f, 0.25f);
					verticalLine->line.gpuData[1].color = glm::vec4(1.0f, 1.0f, 1.0f, 0.25f);
				}

				gameObjects.push_back(gridGO);
			}
			void testParentToChildRelationships() {
				// Parent
				it::GameObject* parentGO = new it::GameObject("Parent");
				it::GPUTriangleFan* parentTriangleFan = new it::GPUTriangleFan(*parentGO);
				it::PhysicsTransformation* parentTransformation = new it::PhysicsTransformation(*parentGO);
				parentTransformation->translation.x = 0.0f;
				parentTransformation->translation.y = 0.0f;
				parentTransformation->rotation.z = 3.14f / 2.0f;

				// Child 0
				it::GameObject* childGO0 = new it::GameObject("Child 0");
				childGO0->transform.position.x = 1.0f;
				childGO0->transform.position.y = 1.0f;
				it::GPUTriangleFan* childTriangleFan0 = new it::GPUTriangleFan(*childGO0);
				for (gl::TriangleFan::GPUData& gpuData : childTriangleFan0->triangleFan.gpuData)
					gpuData.color = glm::vec4(1, 0, 0, 1);
				it::PhysicsTransformation* childPhysicsTransformation = new it::PhysicsTransformation(*childGO0);
				childPhysicsTransformation->rotation.z = 0.0f;

				// Child 1
				it::GameObject* childGO1 = new it::GameObject("Child 1");
				childGO1->transform.position.x = -1.0f;
				childGO1->transform.position.y = 1.0f;
				it::GPUTriangleFan* childTriangleFan1 = new it::GPUTriangleFan(*childGO1);
				for (gl::TriangleFan::GPUData& gpuData : childTriangleFan1->triangleFan.gpuData)
					gpuData.color = glm::vec4(1, 0, 0, 1);
				it::PhysicsTransformation* childPhysicsTransformation1 = new it::PhysicsTransformation(*childGO1);
				childPhysicsTransformation1->rotation.z = 0.0f;

				// Child 2
				it::GameObject* childGO2 = new it::GameObject("Child 2 ");
				childGO2->transform.position.x = -1.0f;
				childGO2->transform.position.y = -1.0f;
				it::GPUTriangleFan* childTriangleFan2 = new it::GPUTriangleFan(*childGO2);
				for (gl::TriangleFan::GPUData& gpuData : childTriangleFan2->triangleFan.gpuData)
					gpuData.color = glm::vec4(1, 0, 0, 1);
				it::PhysicsTransformation* childPhysicsTransformation2 = new it::PhysicsTransformation(*childGO2);
				childPhysicsTransformation2->rotation.z = 0.0f;

				// Child 3
				it::GameObject* childGO3 = new it::GameObject("Child 3");
				childGO3->transform.position.x = 1.0f;
				childGO3->transform.position.y = -1.0f;
				it::GPUTriangleFan* childTriangleFan3 = new it::GPUTriangleFan(*childGO3);
				for (gl::TriangleFan::GPUData& gpuData : childTriangleFan3->triangleFan.gpuData)
					gpuData.color = glm::vec4(1, 0, 0, 1);
				it::PhysicsTransformation* childPhysicsTransformation3 = new it::PhysicsTransformation(*childGO3);
				childPhysicsTransformation3->rotation.z = 0.0f;

				childGO0->transform.setParent(&parentGO->transform);
				childGO1->transform.setParent(&parentGO->transform);
				childGO2->transform.setParent(&parentGO->transform);
				childGO3->transform.setParent(&parentGO->transform);


				// Assign kinematic rigid boadies
				//{
				//	b2WorldId worldId = it::PhysicsEngineB2D::s_getSingleton()->getWorldId();

				//	b2BodyDef def = b2DefaultBodyDef();
				//	def.type = b2_kinematicBody;

				//	b2BodyId bodyId = b2CreateBody(worldId, &def);
				//	it::RigidBody2D* dynamicBody = new it::RigidBody2D(*parentGO, bodyId);
				//	b2Polygon shape = b2MakeBox(0.5f, 0.5f);

				//	b2ShapeDef shapeDef = b2DefaultShapeDef();
				//	shapeDef.density = 1.0f;

				//	b2ShapeId dynamicShapeId = b2CreatePolygonShape(bodyId, &shapeDef, &shape);

				//	it::Shape2D* shape2D = new it::Shape2D(*parentGO, dynamicShapeId);
				//}
				//{
				//	b2WorldId worldId = it::PhysicsEngineB2D::s_getSingleton()->getWorldId();

				//	b2BodyDef def = b2DefaultBodyDef();
				//	def.type = b2_kinematicBody;

				//	b2BodyId bodyId = b2CreateBody(worldId, &def);
				//	it::RigidBody2D* dynamicBody = new it::RigidBody2D(*childGO0, bodyId);
				//	b2Polygon shape = b2MakeBox(0.5f, 0.5f);

				//	b2ShapeDef shapeDef = b2DefaultShapeDef();
				//	shapeDef.density = 1.0f;

				//	b2ShapeId dynamicShapeId = b2CreatePolygonShape(bodyId, &shapeDef, &shape);

				//	it::Shape2D* shape2D = new it::Shape2D(*childGO0, dynamicShapeId);
				//}
				//{
				//	b2WorldId worldId = it::PhysicsEngineB2D::s_getSingleton()->getWorldId();

				//	b2BodyDef def = b2DefaultBodyDef();
				//	def.type = b2_kinematicBody;

				//	b2BodyId bodyId = b2CreateBody(worldId, &def);
				//	it::RigidBody2D* dynamicBody = new it::RigidBody2D(*childGO1, bodyId);
				//	b2Polygon shape = b2MakeBox(0.5f, 0.5f);

				//	b2ShapeDef shapeDef = b2DefaultShapeDef();
				//	shapeDef.density = 1.0f;

				//	b2ShapeId dynamicShapeId = b2CreatePolygonShape(bodyId, &shapeDef, &shape);

				//	it::Shape2D* shape2D = new it::Shape2D(*childGO1, dynamicShapeId);
				//}
				//{
				//	b2WorldId worldId = it::PhysicsEngineB2D::s_getSingleton()->getWorldId();

				//	b2BodyDef def = b2DefaultBodyDef();
				//	def.type = b2_kinematicBody;

				//	b2BodyId bodyId = b2CreateBody(worldId, &def);
				//	it::RigidBody2D* dynamicBody = new it::RigidBody2D(*childGO2, bodyId);
				//	b2Polygon shape = b2MakeBox(0.5f, 0.5f);

				//	b2ShapeDef shapeDef = b2DefaultShapeDef();
				//	shapeDef.density = 1.0f;

				//	b2ShapeId dynamicShapeId = b2CreatePolygonShape(bodyId, &shapeDef, &shape);

				//	it::Shape2D* shape2D = new it::Shape2D(*childGO2, dynamicShapeId);
				//}
				//{
				//	b2WorldId worldId = it::PhysicsEngineB2D::s_getSingleton()->getWorldId();

				//	b2BodyDef def = b2DefaultBodyDef();
				//	def.type = b2_kinematicBody;

				//	b2BodyId bodyId = b2CreateBody(worldId, &def);
				//	it::RigidBody2D* dynamicBody = new it::RigidBody2D(*childGO3, bodyId);
				//	b2Polygon shape = b2MakeBox(0.5f, 0.5f);

				//	b2ShapeDef shapeDef = b2DefaultShapeDef();
				//	shapeDef.density = 1.0f;

				//	b2ShapeId dynamicShapeId = b2CreatePolygonShape(bodyId, &shapeDef, &shape);

				//	it::Shape2D* shape2D = new it::Shape2D(*childGO3, dynamicShapeId);
				//}

				// Register game obbjects
				gameObjects.push_back(parentGO);
				gameObjects.push_back(childGO0);
				gameObjects.push_back(childGO1);
				gameObjects.push_back(childGO2);
				gameObjects.push_back(childGO3);
			}
			void testPhysics() {
				// Create dynamic object
				it::GameObject* dynamicGO = new it::GameObject("dynamic rigid body");
				dynamicGO->transform.position = glm::vec3(0.0f, 4.0f, 0.0f);
				dynamicGO->transform.orientation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
				it::GPUTransform* dynamicGPUTransform = new it::GPUTransform(*dynamicGO);
				it::GPUTriangleFan* dynamicTriangleFan = new it::GPUTriangleFan(*dynamicGO);

				b2WorldId worldId = it::PhysicsEngineB2D::s_getSingleton()->getWorldId();

				b2BodyDef def = b2DefaultBodyDef();
				def.type = b2_dynamicBody;

				b2BodyId bodyId = b2CreateBody(worldId, &def);
				it::RigidBody2D* dynamicBody = new it::RigidBody2D(*dynamicGO, bodyId);
				b2Polygon shape = b2MakeBox(0.5f, 0.5f);

				b2ShapeDef shapeDef = b2DefaultShapeDef();
				shapeDef.density = 1.0f;
				shapeDef.material.restitution = 0.5f;

				b2ShapeId dynamicShapeId = b2CreatePolygonShape(bodyId, &shapeDef, &shape);

				it::Shape2D* shape2D = new it::Shape2D(*dynamicGO, dynamicShapeId);

				// Create ground object
				it::GameObject* gameObject = new it::GameObject("static rigid body");
				gameObject->transform.position = glm::vec3(0, -3, 0);
				it::GPUTransform* groundGPUTransform = new it::GPUTransform(*gameObject);
				it::GPUTriangleFan* groundTriangleFan = new it::GPUTriangleFan(*gameObject);
				groundTriangleFan->triangleFan.gpuData[0].position = glm::vec3(5.0f, -0.5, 0.0f);
				groundTriangleFan->triangleFan.gpuData[1].position = glm::vec3(-5.0f, -0.5f, 0.0f);
				groundTriangleFan->triangleFan.gpuData[2].position = glm::vec3(-5.0f, 0.5f, 0.0f);
				groundTriangleFan->triangleFan.gpuData[3].position = glm::vec3(5.0f, 0.5f, 0.0f);

				b2BodyDef groundBodyDefinition = b2DefaultBodyDef();
				b2BodyId groundBodyId = b2CreateBody(it::InTimeEngine::s_getSingleton()->physicsEngine2D.getWorldId(), &groundBodyDefinition);
				it::RigidBody2D* groundRigidBody = new it::RigidBody2D(*gameObject, groundBodyId);

				b2Polygon groundBox = b2MakeBox(5.0f, 0.5f);

				b2ShapeDef groundShapeDef = b2DefaultShapeDef();
				b2ShapeId groundShapeId = b2CreatePolygonShape(groundBodyId, &groundShapeDef, &groundBox);
				it::Shape2D* groundShape = new it::Shape2D(*gameObject, groundShapeId);

				// Register game objects
				gameObjects.push_back(gameObject);
				gameObjects.push_back(dynamicGO);
			}
			void testMultiParentToChildRelationships() {
				it::GameObject* go1 = new it::GameObject("go1");
				it::GameObject* go2 = new it::GameObject("go2");
				it::GameObject* go3 = new it::GameObject("go3");
				it::GameObject* go4 = new it::GameObject("go4");
				it::GameObject* go5 = new it::GameObject("go5");

				go2->transform.setParent(&go1->transform);
				go3->transform.setParent(&go1->transform);
				go4->transform.setParent(&go2->transform);
				go5->transform.setParent(&go3->transform);
			}
			void enableFrameCounter() {
				it::FrameCounter* frameCounter = new it::FrameCounter();
			}
			void globalToLocalPosition() {

				it::GameObject* parentGO = new it::GameObject("parent");
				parentGO->transform.position = glm::vec3(-2, 0, 0);
				parentGO->transform.calculateGlobalMatrix();
				it::GPUTransform* parentGPUTransform = new it::GPUTransform(*parentGO);
				it::GPUPoint* parentPoint = new it::GPUPoint(*parentGO);
				parentPoint->point.gpuData.color = glm::vec4(1, 0, 0, 1);

				it::GameObject* childGO = new it::GameObject("child");
				childGO->transform.setParent(&parentGO->transform);
				childGO->transform.position = glm::vec3(2, -1, 0);
				childGO->transform.calculateGlobalMatrix();
				it::GPUTransform* childGPUTransform = new it::GPUTransform(*childGO);
				it::GPUPoint* childPoint = new it::GPUPoint(*childGO);
				childPoint->point.gpuData.color = glm::vec4(0, 1, 0, 1);

				glm::mat4 parentMatrix = parentGO->transform.getMatrix();
				glm::mat4 childMatrix = childGO->transform.getMatrix();
				glm::mat4 parentInverse = glm::inverse(parentGO->transform.getMatrix());
				glm::mat4 childInverse = glm::inverse(childGO->transform.getMatrix());
				glm::mat4 globalChildInverse = glm::inverse(childGO->transform.getGlobalMatrix());
				glm::vec4 newPosition = glm::vec4(2, 2, 0, 1);

				glm::vec3 result = globalChildInverse * newPosition;
				result = parentGO->transform.toLocalPosition(newPosition);

				it::GameObject* otherGO = new it::GameObject("otherGO");
				otherGO->transform.setParent(&parentGO->transform);
				otherGO->transform.position = result;
				otherGO->transform.calculateGlobalMatrix();
				it::GPUTransform* otherGPUTransform = new it::GPUTransform(*otherGO);
				it::GPUPoint* otherPoint = new it::GPUPoint(*otherGO);
				otherPoint->point.gpuData.color = glm::vec4(0, 1, 1, 1);
			}
			void globalToLocalOrientation() {
				it::GameObject* parent = new it::GameObject("parent");
				it::Transform& parentTransform = parent->transform;
				it::GPUTransform* parentGPUTransform = new it::GPUTransform(*parent);
				it::GPUTriangle* parentTriangle = new it::GPUTriangle(*parent);
				parentTransform.orientation = glm::quat(glm::vec3(0, 0, 3.14f / 2));

				it::GameObject* child = new it::GameObject("child");
				it::Transform& childTransform = child->transform;
				it::GPUTransform* childGPUTransform = new it::GPUTransform(*child);
				it::GPUTriangle* childTriangle = new it::GPUTriangle(*child);
				childTransform.setParent(&parentTransform);
				childTransform.position = glm::vec3(0, 2, 0);

				it::GameObject* other = new it::GameObject("other");
				it::Transform& otherTransform = other->transform;
				it::GPUTransform* otherGPUTransform = new it::GPUTransform(*other);
				it::GPUTriangle* otherTriangle = new it::GPUTriangle(*other);
				otherTransform.setParent(&parentTransform);
				otherTransform.position = parentTransform.toLocalPosition(glm::vec3(1, 1, 0));
				otherTransform.orientation = parentTransform.toLocalOrientation(glm::quat(glm::vec3(0, 0, 3.14f / 1.0f))); // Face right
			}
			void globalToLocalScale() {
				it::GameObject* parent = new it::GameObject("parent");
				it::Transform& parentTransform = parent->transform;
				it::GPUTransform* parentGPUTransform = new it::GPUTransform(*parent);
				it::GPUTriangle* parentTriangle = new it::GPUTriangle(*parent);
				parentTransform.scale.x = 2.0f;

				it::GameObject* child = new it::GameObject("child");
				it::Transform& childTransform = child->transform;
				it::GPUTransform* childGPUTransform = new it::GPUTransform(*child);
				it::GPUTriangle* childTriangle = new it::GPUTriangle(*child);
				childTransform.setParent(&parentTransform);
				childTransform.position.y = 1.0f;
				childTransform.scale.x = 2.0f;

				it::GameObject* other = new it::GameObject("other");
				it::Transform& otherTransform = other->transform;
				it::GPUTransform* otherGPUTransform = new it::GPUTransform(*other);
				it::GPUTriangle* otherTriangle = new it::GPUTriangle(*other);
				otherTransform.setParent(&childTransform);
				otherTransform.position.y = 1.0f;
				otherTransform.scale = otherTransform.toLocalScale(glm::vec3(5, 1, 1));
			}
			void testUI() {
				//it::HierarchyUI* hierarchyUI = new it::HierarchyUI();
				//hierarchyUI->windowTarget = glfw::Window::getWindowList().front()->getWindow();

				it::InTimeEditor* editor = new it::InTimeEditor();
			}
			void createEveryComponent() {
				float x = -5.0f;
				for (size_t i = 0; i < 10; i++, x +=1.0f) {
					it::GameObject* gameObject = new it::GameObject();
					gameObject->transform.setPosition(glm::vec3(x, 0.0f, 0.0f));
					everyGameObject.push_back(gameObject);
				}

				new it::EmptyComponent(*everyGameObject[0]);
				new it::GPUPoint(*everyGameObject[1]);
				new it::GPULine(*everyGameObject[2]);
				new it::GPUMultiLine(*everyGameObject[3]);
				new it::GPUTriangle(*everyGameObject[4]);
				new it::GPUTriangleFan(*everyGameObject[5]);
				new it::GPUTriangleStrip(*everyGameObject[6]);

				for (it::GameObject* gameObject : everyGameObject) {
					it::Component* component = gameObject->getFirstComponent();
					if (component == nullptr)
						continue;
					gameObject->name = component->getTypeInfo().name();
				}
			}
			void testGameObjectSharedAndWeakPointers() {
				std::cout << "Testing game objects shared and weak pointers." << std::endl;

				// Weak pointers
				std::weak_ptr<it::GameObject*> weakPointerToGameObject;

				// Test: game object's weak pointer linkage to the game object
				{
					it::GameObject* heapGameObject = new it::GameObject("heapGameObject");
					weakPointerToGameObject = heapGameObject->getWeakPointer();

					// Test: heap game object weak pointer
					std::cout << "Test: heap allocated game object's weak pointer can lock.\nResult: ";
					std::shared_ptr<it::GameObject*> heapGameObjectLock = weakPointerToGameObject.lock();
					if (heapGameObjectLock) {
						std::cout << termcolor::green << "pass." << termcolor::reset << std::endl;

						std::cout << "Test: heap allocated game object weak pointer's data is valid.\nResult: ";
						it::GameObject* heapGameObjectFromLock = *heapGameObjectLock;
						if (heapGameObjectFromLock->name == heapGameObject->name)
							std::cout << termcolor::green << "pass";
						else
							std::cout << termcolor::red << "fail";
						std::cout << termcolor::reset << std::endl;
					}
					else {
						std::cout << termcolor::red << "fail" << termcolor::reset << std::endl;
					}

					std::cout << "Finished testing game objects shared and weak pointers." << std::endl;

					heapGameObject->destroyImmediately();
				}

				// Test: game object's weak pointer validity post destruction
				{
					// Test: heap game object's weak pointer after destruction must be invalid
					std::cout << "Test: heap game object's weak pointer after destruction must be invalid.\nResult: ";
					std::shared_ptr<it::GameObject*> heapGameObjectLock = weakPointerToGameObject.lock();
					if (!heapGameObjectLock)
						std::cout << termcolor::green << "pass";
					else
						std::cout << termcolor::red << "fail";
					std::cout << termcolor::reset << std::endl;
				}

				std::cout << std::endl;
			}
			void testComponentSharedAndWeakPointers() {
				std::cout << "Testing components shared and weak pointers." << std::endl;

				// Weak pointers
				std::weak_ptr<it::Component*> weakPointerToHeapEmptyComponent;

				// Test: empty components's weak pointer linkage to empty component
				{
					// Heap allocated game object and empty component
					it::GameObject* heapGameObject{ new it::GameObject("heap allocated game object") };
					it::EmptyComponent* heapEmptyComponent{ new it::EmptyComponent(*heapGameObject) };

					// Weak pointer assignment
					weakPointerToHeapEmptyComponent = heapEmptyComponent->getWeakPointer();

					// Test: heap empty component weak pointer
					std::cout << "Test: heap allocated empty component's weak pointer can lock.\nResult: ";
					std::shared_ptr<it::Component*> heapComponentLock = weakPointerToHeapEmptyComponent.lock();
					if (heapComponentLock) {
						std::cout << termcolor::green << "pass." << termcolor::reset << std::endl;

						std::cout << "Test: heap allocated empty component weak pointer's data is valid.\nResult: ";
						it::EmptyComponent* heapEmptyComponentFromLock = static_cast<it::EmptyComponent*>(*heapComponentLock);
						if (heapEmptyComponentFromLock == heapEmptyComponent)
							std::cout << termcolor::green << "pass";
						else
							std::cout << termcolor::red << "fail";
						std::cout << termcolor::reset << std::endl;
					}
					else {
						std::cout << termcolor::red << "fail" << termcolor::reset << std::endl;
					}

					std::cout << "Finished testing components shared and weak pointers." << std::endl;

					delete heapEmptyComponent;
					heapGameObject->destroyImmediately();
				}

				// Test: stack component's weak pointer validity post destruction
				{
					// Test: heap empty component's weak pointer after destruction must be invalid
					std::cout << "Test: heap empty component's weak pointer after destruction must be invalid.\nResult: ";
					std::shared_ptr<it::Component*> heapGameObjectLock = weakPointerToHeapEmptyComponent.lock();
					if (!heapGameObjectLock)
						std::cout << termcolor::green << "pass";
					else
						std::cout << termcolor::red << "fail";
					std::cout << termcolor::reset << std::endl;
				}

				std::cout << std::endl;
			}
			void testJsonSerializerGLMFunctions() {

				std::cout << "Testing json serializer glm functions." << std::endl;
				glm::vec2 vec2(1, 2);
				glm::vec3 vec3(1, 2, 3);
				glm::vec4 vec4(1, 2, 3, 4);
				glm::quat quat(1, 2, 3, 4);
				glm::mat2 mat2(1, 2, 3, 4);
				glm::mat3 mat3(1, 2, 3, 4, 5, 6, 7, 8, 9);
				glm::mat4 mat4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

				nlohmann::json vec2ToJson = vec2;
				glm::vec2 vec2FromJson = vec2ToJson;

				nlohmann::json vec3ToJson = vec3;
				glm::vec3 vec3FromJson = vec3ToJson;

				nlohmann::json vec4ToJson = vec4;
				glm::vec4 vec4FromJson = vec4ToJson;

				nlohmann::json quatToJson = quat;
				glm::quat quatFromJson = quatToJson;

				nlohmann::json mat2ToJson = mat2;
				glm::mat2 mat2FromJson = mat2ToJson;

				nlohmann::json mat3ToJson = mat3;
				glm::mat3 mat3FromJson = mat3ToJson;

				nlohmann::json mat4ToJson = mat4;
				glm::mat4 mat4FromJson = mat4ToJson;

				std::cout << "glm::vec2 implicit serialization result: ";
				if (vec2 == vec2FromJson)
					std::cout << termcolor::green << "pass";
				else
					std::cout << termcolor::red << "fail";
				std::cout << termcolor::reset << std::endl;

				std::cout << "glm::vec3 implicit serialization result: ";
				if (vec3 == vec3FromJson)
					std::cout << termcolor::green << "pass";
				else
					std::cout << termcolor::red << "fail";
				std::cout << termcolor::reset << std::endl;

				std::cout << "glm::vec4 implicit serialization result: ";
				if (vec4 == vec4FromJson)
					std::cout << termcolor::green << "pass";
				else
					std::cout << termcolor::red << "fail";
				std::cout << termcolor::reset << std::endl;

				std::cout << "glm::quat implicit serialization result: ";
				if (quat == quatFromJson)
					std::cout << termcolor::green << "pass";
				else
					std::cout << termcolor::red << "fail";
				std::cout << termcolor::reset << std::endl;

				std::cout << "glm::mat2 implicit serialization result: ";
				if (mat2 == mat2FromJson)
					std::cout << termcolor::green << "pass";
				else
					std::cout << termcolor::red << "fail";
				std::cout << termcolor::reset << std::endl;

				std::cout << "glm::mat3 implicit serialization result: ";
				if (mat3 == mat3FromJson)
					std::cout << termcolor::green << "pass";
				else
					std::cout << termcolor::red << "fail";
				std::cout << termcolor::reset << std::endl;

				std::cout << "glm::mat4 implicit serialization result: ";
				if (mat4 == mat4FromJson)
					std::cout << termcolor::green << "pass";
				else
					std::cout << termcolor::red << "fail";
				std::cout << termcolor::reset << std::endl;

				std::cout << "Finished testing json serializer glm functions." << std::endl;
			}
			void testJsonSerializerGameEngineFunctions() {
				std::cout << "Testing json serializer game inTimeEngine functions." << std::endl;

				it::GameObject* gameObject = new it::GameObject(100, "test json serializer game object");
				gameObject->transform.position = glm::vec3(1, 2, 3);
				gameObject->transform.orientation = glm::quat(glm::vec3(0, 0, 3.14f / 2.0f));
				gameObject->transform.scale = glm::vec3(2, 2, 2);

				nlohmann::ordered_json gameObjectToJson = gameObject;
				it::GameObject* gameObjectFromJson = new it::GameObject();
				it::GameObject& temp = *gameObjectFromJson;
				temp = gameObjectToJson;
				nlohmann::ordered_json result = gameObject;

				std::cout << "Original data: " << gameObjectToJson.dump(4) << std::endl;
				std::cout << "Resulting json: " << result.dump(4) << std::endl;

				std::cout << "Result: ";
				if (gameObjectToJson == result) {
					std::cout << termcolor::green << "pass";
				} else {
					std::cout << termcolor::red << "fail";
				}
				std::cout << termcolor::reset << std::endl;

			}
	};
}
*/
