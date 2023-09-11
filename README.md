# DynamicFPS++
Some simple mods for totk

## Building
Install Devkit Pro and run make

## Mods

### FPS
FPS allows you to set your desired update interval:
- 1 = 60 FPS
- 2 = 30 FPS
- 3 = 20 FPS

By default, this is set to 1 (60 fps), however you can change it either by editing the Makefile, or by writing `PRESENT_INTERVAL=X` after the make command.

#### Cutscene fix
Alongside static fps is cutscene fix, which will limit your framerate to the movie's framerate

#### Ultrahand fix
Normally, when your framerate is not the expected value, ultrahand's Y-axis rotates too quickly, or slowly depending on your relative performance. This mod provides a simple fix for this issue.

### Dynamic FPS
Dynamic FPS allows you to run the game at any target framerate, without the game running in slow-motion, or hyper-speed. By default, this is enabled. If you would like to disable it, you can do so by editing the make file, or by writing `DYNAMIC_TIMESTEP=0` after the make command.

#### Game Update Rate
While using Dynamic FPS, you can freely change the game's internal update rate without effecting the overall game speed. If you'd like, you can change it with `GAME_UPDATE_INTERVAL`. We need to test the effects of this.

### Contributors
- The original developers of ExLaunch
- ChucksFeedAndSeed
- SomeRandomPeople
- MaxLastBreath

