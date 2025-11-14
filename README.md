# Cloak
Plugin for the game Freelancer (2003) that implements the Cloak key. This allows players to cloak and decloak in Single Player, provided the ship has a cloaking device equipped.

https://github.com/user-attachments/assets/ecee007e-f771-4d37-905a-2e0458f7c5fb

## Installation instructions
Freelancer players who just want to be able to use cloaking devices in Single Player (vanilla or modded) should follow the [mod installation instructions](#mod-installation-instructions). This will explain how to download the Cloak mod which in addition to making the cloaking devices work, also adds a cloaking device to every ship.

Mod creators who want to have working cloaking devices in their Single Player mod should follow the [plugin installation instructions](#plugin-installation-instructions). This will explain how to make the cloaking devices work for player ships, but mod creators will still need to make the cloaking devices available.

## Mod installation instructions
This project provides two different mod packages: a zip containing all the standalone mod files, and a Freelancer Mod Manager script. The standalone mod files are based on JFLP but should work without issues on any vanilla Freelancer installation. The FLMM script assumes FLMM version 1.31 and aims to be compatible with most basic mods.

### Standalone mod files installation

Download the latest `Cloak_mod_standalone.zip` file from [Releases](https://github.com/BC46/Cloak/releases). Extract all files in the zip to the `EXE` folder of your Freelancer installation and allow all files to be overwritten if prompted. See [usage instructions](#usage-instructions) and [troubleshooting](#troubleshooting) for more information.


### FLMM mod installation
Download the latest `Cloak_mod_flmm.zip.flmod` file from [Releases](https://github.com/BC46/Cloak/releases). Open the file with Freelancer Mod Manager 1.31 and activate the mod. See [usage instructions](#usage-instructions) and [troubleshooting](#troubleshooting) for more information.


## Plugin installation instructions
This describes how the plugin needs to be installed manually and which ini files need to be edited in order to add the Cloak key.

First, download the latest `Cloak.zip` file from [Releases](https://github.com/BC46/Cloak/releases). Extract all files in the zip to the EXE folder of your Freelancer installation. Next, open the `dacom.ini` file and append `Cloak.dll` to the `[Libraries]` section.

In `DATA/INTERFACE/keylist.ini`, add the following below the first `[Group]` entry:
```ini
[key]
id = USER_CLOAK
```

In `DATA/INTERFACE/keymap.ini`, add the following:
```ini
[KeyCmd]
nickname = USER_CLOAK
ids_name = 3007
ids_info = 2207
state = keydown
key = "C", control
```

In the same file, locate the `KeyMap` entry for `IDR_SPACE` and add this line to it:
```ini
key = USER_CLOAK
```

See [usage instructions](#usage-instructions) and [troubleshooting](#troubleshooting) for more information.

## Usage instructions

In the in-game options menu, you can set a custom key for the `Toggle Cloak` control (Ctrl + C by default). Using this key, you can cloak and uncloak when in space, provided that the ship you are flying has a cloaking device equipped and that you are in Single Player. Moreover, the initial cloaking state can be adjusted in the `cloak.ini` file.

If you installed the included mod files, keep in mind that every ship now comes with a cloaking device.
Joining vanilla servers like this will cause you to get kicked or even banned, so make sure you only use this mod in Single Player.

## Troubleshooting

If you are starting a new game with the Cloak plugin or mod activated, make sure that you delete the Restart.fl file in your saves directory. Otherwise your starting ship may have no cloaking device. If you load an existing savegame, you may need to buy a new ship in order to have a working cloaking device.

Also note that the mod files part of this project only add a cloaking device to every player-flyable ship from vanilla Freelancer. If you installed the Cloak mod files over a total-conversion mod that adds a bunch of new ships, those may not come with a cloaking device out of the box.

## Build instructions
Build the project using the `NMAKE` tool from Microsoft Visual C++ 6.0 (VC6 or Visual Studio 98) with the included makefile.
This will output the `Cloak.dll` file in the `bin` folder.
Building the project using other compilers may require the code to be modified.
