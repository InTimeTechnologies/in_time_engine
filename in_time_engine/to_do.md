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
