# Roguelike game
OOP project

## IMPORTANT!
When commiting to main (and other branches too) please follow given structure:
[Commit Guidelines](https://github.com/angular/angular.js/blob/master/DEVELOPERS.md#-git-commit-guidelines)

## About
using C++ 17
Compiler [MinGW64](https://winlibs.com/#download-release)
Console application
For UML using [PlantUML](https://plantuml.com/)
For documentation using [Doxygen](https://www.doxygen.nl/index.html)

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
