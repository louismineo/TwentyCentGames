#include "pch.hpp"


s8 fontId = -1;

s8 fontLarge = -1;

Maze_Struct* Maze;

int maze_init_flag = 0;
int curr_X_GRIDposition;
int curr_Y_GRIDposition;
float global_maze_cam_x;
float global_maze_cam_y;
int duck_dir = DD_UP;
bool is_focused;

FMOD::Channel* bgm_channel;
FMOD::Channel* sfx_channel;
FMOD::ChannelGroup* bgm_group;
FMOD::ChannelGroup* sfx_group;
FMOD::ChannelGroup* master_fader;

// test bench
int level_iter;