# Roguelike game
OOP project
[This](https://github.com/mchlebosz/ConsoleRoguelike) is a link to the repository.
[Documentation](https://mchlebosz.github.io/ConsoleRoguelike/) is available here.

## IMPORTANT!
When commiting to main (and other branches too) please follow given structure:
[Commit Guidelines](https://github.com/angular/angular.js/blob/master/DEVELOPERS.md#-git-commit-guidelines)

## About
Goal of the game is to go thru the dungeons and kill enemies. You can move around the map using WASD keys. You can attack enemies by pressing Space. You can exit the level by going to the Door. You can exit the game by pressing Esc.

using C++ 17
Compiler [MinGW64](https://winlibs.com/#download-release)
Console application
For UML using [PlantUML](https://plantuml.com/)
For documentation using [Doxygen](https://www.doxygen.nl/index.html)

## Controls
- <kbd>W</kbd>  - Move Up
- <kbd>S</kbd>  - Move Down
- <kbd>A</kbd>  - Move Left
- <kbd>D</kbd>  - Move Right
- <kbd>Space</kbd>  - Attack
- <kbd>Esc</kbd>  - Exit Game


## Prerequisites
1. MinGW64 v12 with C++ 17 support
2. Powershell v7 or Windows Terminal or any other terminal with font that supports UTF Emojis (For convinience in `src` folder there is a font that supports emojis)

## How to run
1. Clone repository
2. Make sure you have minGW64 v12 installed with C++ 17 support
3. Run `make` in root directory
4. Run `./bin/roguelike.exe` in root directory


## Annotations
Sometimes on Debug Run there is an error:
```
ParserError:
Line |
   1 |  … bugLauncher.exe' '--stdin=Microsoft-MIEngine-In-oyx014aa.frb' '--stdo …
     |                     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     | Unexpected token ''--stdin=Microsoft-MIEngine-In-oyx014aa.frb'' in expression
     | or statement.
```
This is a bug in VSCode and can be ignored. It is caused by the fact that VSCode tries to debug the program and it is not a debuggable program. To fix this error, just run the program again.



## TODO
- [x] Create basic structure of the game
- [x] Add enemies to Levels entries
- [x] Atack Enemy
- [ ] (Optional) Ranged atack
- [x] Enemy Die
- [x] Dropping items
- [x] Enemy folow player
- [x] Exiting levels
## Authors
* [Mateusz Chlebosz](https://github.com/mchlebosz)