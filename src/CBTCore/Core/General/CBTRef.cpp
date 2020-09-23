// Include CBT
#include "CBTRef.h"

NS_CBT_BEGIN

CBTManaged* CBTManaged::s_Buffer[MAX_POOL_SIZE * 2] = { 0 };
cbtU32 CBTManaged::s_ReleaseStart = 0;
cbtU32 CBTManaged::s_ReleaseCount = 0;
std::mutex CBTManaged::s_ReleaseMutex;
std::mutex CBTManaged::s_ClearMutex;

NS_CBT_END