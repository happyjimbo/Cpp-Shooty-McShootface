# Shooty McShootface

Basic C++ 14 vertical shooter, built using [SFML](https://www.sfml-dev.org) and using the STL.

C++ 14 Requirements:
- `std::make_unique` -- used instead of `new` in ResourceHolder
- `constexpr` marked functions

_Note: To compile against C++11, adjust the above features accordingly._

Code Highlights:

- **Memory Management**: Deliberate mixture of smart and raw pointers with RAII (Resource Acquisition Is Initialization) in mind. Initially relied more on `shared_ptr` and `unique_ptr`, but opted to mostly focus on raw pointers in certain areas to manage memory manually. 
- **Template-Based Object Pool**: Efficient management of game objects. 
- **Visual Effects**: Parallax scrolling for ground and clouds.
- **Animation**: Sprite sheet for frame-based animations.
- **Entity System**: A basic system to manage game entities.
- **ECS-Inspired Architecture**: Systems inspired by Entity-Component-System (ECS) architecture, although not fully component-based.
- **Controllers**: Used for spawning and ticking entities, with tick logic gradually being migrated into the system.



![plot](./public/shooty.gif)