# Sustainability File

## Meet Iteration Station 
- [TEAM](/documentation/TEAM.md)

## About Aidan
This project started as the name Stadia by Robert and Eric Pogue. They created a Interactive Rendering Tool within Unity that allowed architects to see their renders from Revit in real time without the limit of hardware. This project was very successful and sold commercially for awhile until it was abandoned a few years ago. Eric Pogue decided to bring the project back to life in a stronger 3D engine so that is where Unreal Engine 4 comes in. We are attempting to rebuild this project but with the full ability to run at build time (lighting, materials, and meshes) and not have to be tied down by the editor for each new ali file we wish to use. 

## Services Used
- [Amazon Web Services (AWS)](https://aws.amazon.com) - Host binary *.ali files
- [Unreal Engine 4(UE4)](https://www.unrealengine.com/en-US/) - Render Engine
- [Revit](https://www.autodesk.com/products/revit/overview?term=1-YEAR&tab=subscription) - Architects 3D Modeling Tool
- [Trello](https://trello.com/en-US) - Hosts the scrum stories and layout of what is needing to be done
- [GameJolt](https://gamejolt.com) - Hosting the *.zip of the latest build that users can download
- [GitHub](https://github.com) - Helps share the code with each of the group members and ensure everone is on the same page

## Important Files
- `/Aidan` - This is the directory that has everything associated with Unreal Engine
- `/Aidan/Aidan.uproject` - Opens the Unreal Project in Unreal Engine 4.27. This will build the required files that are loaded by your machine and not pushed to GitHub
- [Binary Reader](Aidan/Source/Aidan/Private/BinaryReader.cpp) - Utility class that helps read the different aspects of the .ali file
- [Reader](Aidan/Source/Aidan/Private/Reader.cpp) - The class that calls the Binary Reader functions to return the the structs that qill be used in Unreal (Mesh, Light, and Material)
- [ReaderData](Aidan/Source/Aidan/Private/ReaderData.cpp) - The default constructors of the different types that will be called in Unreal
- [ProcMesh](Aidan/Source/Aidan/Private/ProcMesh.cpp) - [UNREAL OBJECT] This class is what each mesh gets created as by passing the parameters to the CreateMesh function
- [ProcLight](Aidan/Source/Aidan/Private/ProcLight.cpp) - [UNREAL OBJECT] Tgis class is just like ProcMesh but rather than create a mesh, we are creating a PointLight if the mesh in the binary file reads as a light. 
- [ConstructionManager](Aidan/Source/Aidan/Private/ConstructionManager.cpp) - [UNREAL OBJECT] This is the main object that will be placed in the level. ConstructionManager reads the ali file (static model.ali file currently) and runs all of the reading data, and then creating the meshes, applying materials, and placing the lighting. 

## Current Progress
- Download the model.ALI file from AWS
- Read the ali file and create structs that hold the values
- Load the values of the file into create functions in Unreal Engine 
- Renders appear using Procedural Meshes since we can access the vertices and UVs
- Main Menu that has currently our only ali file as an option
- Hosted on GameJolt [Latest Build](https://gamejolt.com/games/aidan-interactive-rendering/703091)
- Basic colors applied to the meshes

## To-Do
- Fix the render issue with the Procedural Meshes that allows the buildings to render properly
- Fix the textures loading on each mesh (We ran into the issue where the image was 64 bit and we couldn't load that high in Unreal)
- Add a plugin to Revit that allows custom ali files to be exported and uploaded to the AWS cloud server
- Add a launcher that allows for automatic updating from a server (AWS, Azure, etc.)
- Find lighting solution that can be built on runtime rather than having to rebuild for every ali file
- Collision on the generated structure