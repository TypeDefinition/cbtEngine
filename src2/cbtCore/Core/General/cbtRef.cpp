// Include CBT
#include "cbtRef.h"

NS_CBT_BEGIN

cbtManaged* cbtManaged::s_Buffer[MAX_POOL_SIZE * 2] = { 0 };
cbtU32 cbtManaged::s_ReleaseStart = 0;
cbtU32 cbtManaged::s_ReleaseCount = 0;
std::mutex cbtManaged::s_ReleaseMutex;
std::mutex cbtManaged::s_ClearMutex;

NS_CBT_END