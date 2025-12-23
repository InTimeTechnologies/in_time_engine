# TODO:
- JoystickManager has large chunk of data. It needs to be set for every connected joystick each frame. Make a struct to transfer data chunks instead of fragmantating it.
- Implement GLFW backend: it must forward its input to In Time Engine
- Test GLFW backend data forwarding to In Time Engine

# Milestones
- Scene
- Resource manager
- Review how you are handling imgui context ownership.
- Serialize game engine settings.
- Finish integrating othed features of Box2D:
  - Standardize physics components
  - Implement serialization for Box2D world
  - Integrate physics callbacks with engine events
  - Finalize Box2D components
- Create Vulkan renderer and replace the current OpenGL engine.
- Implement UI engine that can target multiple windows.
- Continous integration with engine settings through views.

All removed code:
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