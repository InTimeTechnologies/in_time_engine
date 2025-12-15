# In Time Engine
In Time Engine is custom made C/C++ 3D/2D game engine. It is designed to have the ease of use of Unity while exposing the power of C++ while remaining lightweight, be as lightweight as it can be and easy to use. Please note that this project is still in its infancy. However, it is currently being worked and more features will come in the future. The main audience of this project are other developers, specifically C/C++ developers. It is not meant for people without programming background, such as designers. This is because  at its current state the engine is missing a user interface for average nonprogramming users.

# Technologies in Use
- MSVC | C++20/C17
- GLM
- Box2D
- Vulkan
- GLFW

# Features
- Game objects
- Transforms: parent and child relationship.
- Components
- Engine events: on logic init, pre and post update , pre and post physics update, on render, on render ui, on engine pause, on engine stop, on game object destroy, on component destroy.
- Run time: the engine's realtime run time
- Core time (update time): The time at the beginning of the frame.
- Core delta tuime (update delta time): The time since last frame.
- Physics time: The time every frame the physics engine updates.
- Physics delta time: The time elapsed from the last frame the physics updated to the current frame the physics engine updated.
- Simple garbage collection one game objects and components.
- Ability to create game objects and components on the stack or on the heap while maintaining engine integrity.
- Ability to claim memory responsibility from the engine.
- Input system: powered by GLFW and expaned upon to capture current frame press and release signals for each keyboard key, joystick and mouse button.

# Features Currently Being Worked
- Vulkan renderer: This is to replace the initial OpenGL renderer. The reason behind this is to provide the latest and greatest graphics features such as ray traicing and more.
Ability to expand and replace entire parts of the engines such as the physics engine, the renderer and the windowing system by extending certain classes of the engine.

# Upcoming Features
1. Dear ImGUI
2. Audio
3. Scene / scene manager
4. Resource manager
5. 3D physics engine: the current physics engine being considered is Jolt used the open world game "Horizon".
6. Animation system
7. Engine user interface: the main focus right now is to have the runtime of the engine working 100% correctly before pursuing bigger features.
