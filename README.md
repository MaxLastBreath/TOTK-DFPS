# DynamicFPS++
Repository for DFPS++, note this isn't the official DFPS (made by ChucksFeedAndSeed), this respository is cloned from [here](https://bitbucket.org/totk-fpsplusplus/dynamicfps/src/main/). I will be updating this to future version releases, if i had the source for DFPS 1.5.5, I would update it instead. As this is currently the only source for any sort of DFPS, it will be the one getting updated to work with future releases by me.

## Building
- Clone repo and run actions build.
- Install devkit pro and use make.

## Mods

### FPS - Config File.
FPS allows you to set your desired update interval:
- Edit the default.ini file included in the romfs folder.
- By default its set to 60
- Supports, 20, 30 and 60 FPS cap.

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

