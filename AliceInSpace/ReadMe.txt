========================================================================
    CONSOLE APPLICATION : Alice in Space
========================================================================

Game.cpp
Class that contains Init() , Update(), Render() and Shutdown().
Init: The player and the first set of monsters are spawned.
Update: Contains methods to spawn collectibles, monsters, bullets, and detect object collision. The game object positions are also updated within this method.
Render: Displays title screen, end screen and renders game objects
Shutdown: Deallocates all allocated memory

GameStateManager.h 
Stores information about the current state of the game.

Update.cpp
Spawns game objects, updates their position and detects collisions.
Spawn Collectibles: Collectibles are randomly spawned. The total number of collectibles present in the game at a time is 2. 
Spawn Monsters: A random number of new monsters are spawned when the number of monsters in the game drops below 5. 
Collision:
1.	Player – Monster Collision:
a.	Evil Monster: Player loses one life
b.	Shrink Monster: Player shrinks by one size
c.	Grow Monster: Player grows by one size
d.	In all cases, the monsters are destroyed immediately
2.	Monster – Bullet Collision: the monster loses a life. 
3.	Player – Collectible Collision: the player gains a life or 20 bullets. The collectible object is destroyed once collected. 

Entity.cpp
Parent class of all the game objects. It contains information about the entity’s position, lives. Screen wrapping is implemented here.

Bullet.cpp
Contains bullet specific information like the velocity of the bullet

Collectibles.cpp
Contains collectible specific information like the collectible type
ShrinkMonster.cpp
Contains Shrink Monster specific information

GrowMonster.cpp
Contains Grow Monster specific information

EvilMonster.cpp
Contains Evil Monster specific information

Player.cpp
Contains player-specific information like bullets, bullet count


AliceInSpace.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

AliceInSpace.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

AliceInSpace.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Game.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
