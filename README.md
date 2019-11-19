# Borderlands

## Introduction

The goal of this project was to learn the usage of advanced 3D data structures (meshes, materials, skeletal animations, ...) along with the Entity Component System paradigm in Unreal Engine 4.

As of now the version **4.23** of the engine is supported and the following features are implemented : 
- Procedural assembly and animation of 3D assets (characters and guns).  
  - Characters are obtained with a combination of a body and a head.  
  - Weapons are obtained by combining 4 parts sets (accessory, body, barrel, handle) from different manufacturers (Bandit, Jakobs, Maliwan, Torgue, ...).  
    The weapon given at the start of the demo can be "rerolled" using the **1** and **2** key, the fire animation can be triggered using the **left click** and the reload animation using **R**.
   
- A very basic finite state machine AI for an Hyperion bot that inflict damage and can be shot.

More information can be found in the report given with this repository (available in french only).

## Using the project in the Unreal Engine 4 editor

Simply clone this project using the following

```bash
git clone https://github.com/yongaro/Borderlands  
cd ./Borderlands  
git submodule init  
git submodule update --remote  
```

And then just open it from the Unreal Engine 4 editor.

## Updating an existing copy

```bash
git pull  
git submodule update --remote  
```

## Release builds

In case you just whant to test this demo, some binaries are available for Linux and Windows in the release section.