#ifndef SHADERMODE_H
#define SHADERMODE_H

enum ShaderMode
{
  NO_SHADER,
  DIRECTIONAL_PER_PIXEL,
  DIRECTIONAL_PER_PIXEL_COLOR,
  WEIGHTCOLORS,
  SCALAR,
  LBS,
  LBS_TEXTURED,
};
#define NUM_SHADER_MODE 7

#endif