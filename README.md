# Scrap

Scrap is a 2D C++ game developed using SFML.

The project was created by modifying the Timber!! base project and redesigning its original chopping mechanic into a scrapyard simulation where the player sorts cars using a mechanical claw.

The game keeps the simple input, logic and drawing structure of Timber!! while introducing new gameplay systems including multiple car types, scoring, sound effects, randomisation, animations and multiple endings.

## Gameplay

The player works in a scrapyard and must decide what to do with each vehicle before the timer runs out.

Cars can be:

- Rust
- Salvageable
- Blueprint

Each type rewards or penalises the player differently depending on whether it is scrapped or salvaged.

The aim is to earn as many points as possible before the two-minute timer reaches zero.

## Controls

| Key | Action |
| --- | --- |
| A | Scrap car |
| D | Salvage car |
| W / S | Move the claw |
| R | Replenish the car pile |
| Space | Call Wibby |

## Features

- Mechanical claw system
- Randomised car selection
- Multiple car types and texture variations
- Scrap and salvage mechanics
- Score and penalty system
- Two-minute countdown timer
- Multiple endings based on final score
- Sound effects
- Animated UI feedback
- Random bonus and penalty events
- Cat helper character named Wibby

## Scoring

- Scrap a Rust car: **+10**
- Salvage a Salvageable car: **+20**
- Salvage a Blueprint car: **+10**
- Scrap a Blueprint car: **-25**
- Incorrect action: **-5**

Wibby can also be called using the walkie-talkie when dealing with Blueprint cars, with a chance of receiving either bonus or penalty points.

## Endings

The player's final score determines the ending shown when the timer expires:

- Low score - broken project car
- Medium score - repaired but faulty car
- High score - fully restored vehicle

## Technologies Used

- C++
- SFML
- Visual Studio

## Programming Concepts

The project uses a range of introductory C++ and SFML concepts, including:

- Event handling
- If/else game logic
- Randomisation
- SFML sprites and textures
- Sprite movement and scaling
- Delta time
- `sf::Clock` timers
- `sf::SoundBuffer` and `sf::Sound`
- Boolean game states
- Score management

## Development

One of the main challenges during development was managing timing and animation logic.

The game originally experienced issues where the timer decreased too quickly and the mechanical claw could freeze after moving. This was resolved by separating the clocks used for the main game timer and gameplay movement.

The project also involved managing sprite layering, scaling and draw order to ensure the game displayed correctly.

## Project Files

The repository includes:

- C++ source code
- Visual Studio solution and project files
- Graphics
- Fonts
- Sound assets
- Design documentation

The Visual Studio solution can be opened using:

`Scrap.sln`

## Future Improvements

Possible future additions include:

- Main menu with Play and Tutorial options
- Multi-day gameplay system
- Different car randomisation for each day
- In-game shop
- Save/load system
- High score tracking

## Academic Project

Scrap was developed as an academic C++ and SFML project.

It demonstrates how a simple existing game structure can be expanded and redesigned into a different gameplay concept while maintaining a beginner-friendly event-driven game loop.
