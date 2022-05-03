**Table of Contents**

[TOCM]

[TOC]

### About Aidan
This project started as the name Stadia by Robert and Eric Pogue. They created a Interactive Rendering Tool within Unity that allowed architects to see their renders from [Revit](https://www.autodesk.com/products/revit/overview?term=1-YEAR&tab=subscription) in real time without the limit of hardware. This project was very successful and sold commercially for awhile until it was abandoned a few years ago. Eric Pogue decided to bring the project back to life in a stronger 3D engine so that is where Unreal Engine 4 comes in. We are attempting to rebuild this project but with the full ability to run at build time (lighting, materials, and meshes) and not have to be tied down by the editor for each new ali file we wish to use. 

## Important Files
- [Binary Reader](Aidan/Source/Aidan/Private/BinaryReader.cpp)

#Current Progress
- Download the model.ALI file from AWS
- Read the ali file and create structs that hold the values
- Load the values of the file into create functions in Unreal Engine 
- Renders appear using Procedural Meshes since we can access the vertices and UVs
- Main Menu that has currently our only ali file as an option
- Hosted on GameJolt [Latest Build](https://gamejolt.com/games/aidan-interactive-rendering/703091)
- Basic colors applied to the meshes


#To-Do
- Fix the render issue with the Procedural Meshes that allows the buildings to render properly
- Fix the textures loading on each mesh (We ran into the issue where the image was 64 bit and we couldn't load that high in Unreal)
- Add a plugin to Revit that allows custom ali files to be exported and uploaded to the AWS cloud server
- Add a launcher that allows for automatic updating from a server (AWS, Azure, etc.)
- Find lighting solution that can be built on runtime rather than having to rebuild for every ali file
- Collision on the generated structure


