# Cloak
Plugin for the game Freelancer (2003) that implements the Cloak key. This allows players to cloak and decloak in Single Player, provided the ship has a cloaking device equipped.

## Installation instructions
Download the latest version of the plugin from [Releases](https://github.com/BC46/Cloak/releases). Extract all files in the zip to the `EXE` folder of your Freelancer installation. Next, open the `dacom.ini` file and append `Cloak.dll` to the `[Libraries]` section.

## Usage instructions

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

In-game you can set a custom key for the `Toggle Cloak` control. Using this key, you can cloak and uncloak when in space, provided that the ship you are flying has a cloaking device equipped. Moreover, the initial cloaking state behavior can be adjusted in the `cloak.ini` file.

## Build instructions
Build the project using the `NMAKE` tool from Microsoft Visual C++ 6.0 (VC6 or Visual Studio 98) with the included makefile.
This will output the `Cloak.dll` file in the `bin` folder.
Building the project using other compilers may require the code to be modified.
