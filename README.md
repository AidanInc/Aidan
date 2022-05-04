# Aidan - Main Branch

**For future teams look at [Sustainability.md](/documentation/Sustainability.md) has a good breakdown on the project files and the services that are being for this project and more...**

## About 
Aidan Interactive Rendering is a rendering tool that uses Unreal Engine 4 to bring acritical designs to life. Using this software will allow you the chance to show off your designs that have been built in Revit and exported to the cloud that hosts all the current designs.

This project started as the name Stadia by Robert and Eric Pogue. They created a Interactive Rendering Tool within Unity that allowed architects to see their renders from Revit in real time without the limit of hardware. This project was very successful and sold commercially for awhile until it was abandoned a few years ago. Eric Pogue decided to bring the project back to life in a stronger 3D engine so that is where Unreal Engine 4 comes in. We are attempting to rebuild this project but with the full ability to run at build time (lighting, materials, and meshes) and not have to be tied down by the editor for each new ali file we wish to use. 

[For more about the intial efforts click here](https://www.lewis.education/?cpsc=sp22-cpsc-49200-001&hide-nav=y#/activity/aidan)
## Set Up 
### Downloading Executable
[Link to teams gamejolt](https://gamejolt.com/games/aidan-interactive-rendering/703091)
go to the teams gamejolt website, this is where the packaged executable file is host. Once the program has finished downloading open it (you will need to unzip it first), you should then see the exe file called `Aidan.exe` and run the program.

When the program is running first go to `Model Options` and click on the `Defalut` so it can download the need file, after the wall of text in blue has stoped you can go back to the home screen and click on `Start` and the rendering should start

*Note:
At the moment to download the program from gamejolt a invite has to made and sent to you  

### Run from GitHub
*this will go over building and running the project, this is also the process to start devlopment on the project*

**Requiuments**
- Have a Epic Game account (sign up is free) to download the Unreal Engine 4.27
- Download the plugin [run-time-files-downloader](https://www.unrealengine.com/marketplace/en-US/product/runtime-files-downloader)
- Visual Studio 2019

The core project files are in `/Adian` this should have: 
- `Config/`
- `Content/`
- `Source/`
- `Aidan.uproject`

You should be able to right click on the file `Aidan.uproject` to generate the other folders and files that are needed, once that is done you can double click on the `Aidan.uproject` to start developing or right click to `Launch Game` 

After generating it should have these folders and files:
- `Binaries/`
- `Config/`
- `Content/`
- `DerivedDataCache/`
- `Intermediate/`
- `Saved/`
- `Source/`
- `Aidan.sln`
- `Aidan.uproject`

*Note: If for some reason the download of the ali file is not working you can paste the file. First make the dir `ali/` under the root project and paste the `model.ALI` in there [model ali file in github](/other-resources/alifiles/model.ALI)  

## Project Info
The Team Minimum Viable Product [Learn more here](/documentation/MVP.md)

Learn about our Continuous Intergration and Continuous Delivery [click here for CI-CD](/documentation/CI-CD.md)

How is the team interacted and worked [click here](/documentation/PROCESS.md)
## Credits
To see who is on the time or to contact them [click here](/documentation/TEAM.md)

Learn more about the team by going to our website [Link: ITERATION STATION](https://witty-meadow-055b73d10.1.azurestaticapps.net/)

*if the website is down the code [is here](/other-resources/team-spring2022)
