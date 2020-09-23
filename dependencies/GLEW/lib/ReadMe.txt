Only either glew32.lib or glew32s.lib is needed to run the program.

glew32.lib requires glew32.dll to be in the Release/Debug folder to run.

glew32s.lib does not require glew32.dll, but #define GLEW_STATIC is needed before using #include <glew.h>.