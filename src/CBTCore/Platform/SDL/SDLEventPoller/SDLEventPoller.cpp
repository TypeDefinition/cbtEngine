// Include CBT
#include "SDLEventPoller.h"

#ifdef CBT_SDL

NS_CBT_BEGIN

std::vector<SDLEventListener*> SDLEventPoller::m_Listeners;

NS_CBT_END

#endif // CBT_SDL