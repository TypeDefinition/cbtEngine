// Include CBT
#include "cbtMacros.h"
#include "Core/Math/cbtMathUtil.h"

// Include STD
#include <functional>
#include <vector>
#include <atomic>

NS_CBT_BEGIN

/*
class cbtJob
{
private:
    std::mutex m_Mutex;

    cbtTask* m_QueueBuffer[2048] = { 0 };
    cbtU64 m_QueueCounter = 0;

    cbtTask* m_ExecuteBuffer[2048] = { 0 };
    cbtU64 m_ExecuteCounter = 0;

    static cbtU64 GenerateTaskOrder(const std::vector<cbtU64>& _dependencies)
    {
        cbtU64 order = 0;
        for (cbtU32 i = 0; i < _dependencies.size(); ++i)
        {
            order = cbtMathUtil::Max<cbtU32>(order, _dependencies[i]);
        }
        return order + 1;
    }

public:
    cbtJob() {}
    virtual ~cbtJob() {}

    cbtU64 QueueTask(std::function<void(void)> _function, cbtU64 _runCounter = 1, std::vector<cbtU64> _dependencies = {})
    {
        cbtU64 taskOrder = GenerateTaskOrder(_dependencies);
        cbtTask* task = new cbtTask(_function, _runCounter, taskOrder);

        std::lock_guard<std::mutex> lockGuard(m_Mutex);
        m_QueueBuffer[m_QueueCounter++] = task;

        return taskOrder;
    }

    const std::function<void(void)> PopTask()
    {
        return [](){};
    }
};

class cbtTask
{
    friend class cbtJob;

private:
    const std::function<void(void)> m_Function;
    const cbtU64 m_RunCounter;
    const cbtU64 m_TaskOrder;

    std::atomic<cbtU64> m_StartCounter;
    std::atomic<cbtU64> m_EndCounter;

    cbtTask(std::function<void(void)> _function, cbtU64 _runCounter, cbtU64 _taskOrder)
        : m_Function(_function)
        , m_RunCounter(_runCounter)
        , m_TaskOrder(_taskOrder)
    {}
    cbtTask(const cbtTask& _other); /// Do not allow copying.
    ~cbtTask() {}

public:
    inline cbtU32 GetTaskOrder() const { return m_TaskOrder; }

    inline void operator()()
    {
        m_Function();
        ++m_EndCounter;
    }
};

template <typename Dependency, typename ...Dependencies>
class cbtJob : public cbtIJob
{
private:
    template <typename Dependency0>
    static cbtU32 GetExecuteOrder() { return Dependency0::GetExecuteOrder() + 1; }

    template <typename Dependency0, typename Dependency1, typename ...Args>
    static cbtU32 GetExecuteOrder() { return cbtMathUtil::Max<cbtU32>(GetExecuteOrder<Dependency0>(), GetExecuteOrder<Dependency1, Args...>()); }

    template <>
    static cbtU32 GetExecuteOrder<void>() { return 0; }

protected:
    cbtJob() {}

public:
    static cbtU32 GetExecuteOrder() { return GetExecuteOrder<Dependency, Dependencies...>(); }

    virtual ~cbtJob() {}
};
*/

NS_CBT_END