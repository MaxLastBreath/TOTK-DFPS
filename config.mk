#----------------------------- User configuration -----------------------------

# Common settings
#------------------------

# Scale the in-game time to your current framerate. 'Dynamic FPS'
DYNAMIC_TIMESTEP ?= 1

# Set the internal framerate cap. The `present` or `vsync` interval. The framerate this results in is 60 / interval.
PRESENT_INTERVAL ?= 1 # 1 = 60 fps, 2 = 30, 3 = 20, etc.

# Set the interval that the game uses to update certain internal timers. Need to test the positive and negative effects of this
GAME_UPDATE_INTERVAL ?= 1

# How you're loading your module. Used to determine how to find the target module. (AsRtld/Module/Kip)
LOAD_KIND := Module

# Program you're targetting. Used to determine where to deploy your files.
PROGRAM_ID := 0100F2C0115B6000

# Optional path to copy the final ELF to, for convenience.
ELF_EXTRACT :=

# Python command to use. Must be Python 3.4+.
PYTHON := python3

# JSON to use to make .npdm
NPDM_JSON := qlaunch.json

D_FLAGS := -DDYNAMIC_TIMESTEP=$(DYNAMIC_TIMESTEP) -DPRESENT_INTERVAL=$(PRESENT_INTERVAL) -DGAME_UPDATE_INTERVAL=$(GAME_UPDATE_INTERVAL)

# Additional C/C++ flags to use.
C_FLAGS := -Oz $(D_FLAGS)
CXX_FLAGS := -Oz $(D_FLAGS)

# AsRtld settings
#------------------------

# Path to the SD card. Used to mount and deploy files on SD, likely with hekate UMS.
MOUNT_PATH := /mnt/k

# Module settings
#------------------------

# Settings for deploying over FTP. Used by the deploy-ftp.py script.
FTP_IP := 192.168.0.235
FTP_PORT := 5000
FTP_USERNAME := anonymous
FTP_PASSWORD :=

# Settings for deploying to Ryu. Used by the deploy-ryu.sh script.
RYU_PATH := /mnt/c/Users/shado/AppData/Roaming/Ryujinx
