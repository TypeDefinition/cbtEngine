#pragma once

// Include CBT
#include "CBTMacros.h"
#include "Core/General/CBTFamily.h"
#include "CBTEventListener.h"

// Include STD
#include <unordered_map>
#include <unordered_set>
#include <vector>

NS_CBT_BEGIN

/**
    \brief An EventDispatcher is used to dispatch Event(s) to EventListener(s) that are subscribed to this dispatcher. This uses the publisher-subscriber pattern.
*/
class CBTEventDispatcher
{
private:
    /*
    struct QueuedEvent
    {
        cbtBool m_DeleteUponDispatch = true;
        CBTEvent* m_Event = nullptr;
        // std::function<void(Event*, cbtBool)> m_DispatchFunction = nullptr;
    };

    std::vector<QueuedEvent> m_EventQueue;
    */

    /// The EventListener(s) added to this EventDispatcher is sorted by the Event type they are subscribed to.
    std::unordered_map<cbtS32, std::unordered_set<CBTEventListener*>> m_Listeners;

public:
    /**
        \brief Default Constructor.

        \return A CBTEventDispatcher.
    */
    CBTEventDispatcher() {}
    /**
        \brief Destructor. Subscribed listeners are removed.
    */
    ~CBTEventDispatcher() { RemoveAllListeners(); }

    /*
        \brief Dispatches an Event of type T. Only EventListener(s) subscribed to Event(s) of type T will receive the event.
        
        \param _event The Event to dispatch.
        \param _deleteAfterDispatch If set to true, the event will be deleted after dispatching. This means that the ownership of the event is given to the dispatcher. The default value is set to true.

        \return Returns true if the Event is successfully dispatched.
    */
    template <typename T>
    CBT_ENABLE_IF_DERIVED_1(cbtBool, CBTEvent, T) DispatchEvent(CBTEvent* _event, cbtBool _deleteAfterDispatch = true)
    {
        std::unordered_map<cbtS32, std::unordered_set<CBTEventListener*>>::iterator iter = m_Listeners.find(CBTFamily<CBTEvent>::GetID<T>());
        if (iter == m_Listeners.end()) { return true; }

        for (std::unordered_set<CBTEventListener*>::iterator i = iter->second.begin(); i != iter->second.end(); ++i)
        {
            if (_event->IsHandled()) { break; }
            (*i)->InvokeCallback(_event);
        }

        if (_deleteAfterDispatch) { delete _event; }

        return true;
    }

    /**
        \brief Subscribes an EventListener to Event(s) of type T from this EventDispatcher. Only Event(s) of type T will be received from this EventDispatcher. It is possible use AddListener multiple times to listen for multiple types of Event(s).

        \param _listener The EventListener to add.

        \return Returns true if the EventListener is successfully added. Returns false if the EventListener has already been previously added for T.
    */
    template <typename T>
    CBT_ENABLE_IF_DERIVED_1(cbtBool, CBTEvent, T) AddListener(CBTEventListener* _listener)
    {
        std::unordered_map<cbtS32, std::unordered_set<CBTEventListener*>>::iterator iter = m_Listeners.find(CBTFamily<CBTEvent>::GetID<T>());
        if (iter == m_Listeners.end())
        {
            // Add the listener.
            std::unordered_set<CBTEventListener*> listenerList;
            listenerList.insert(_listener);
            m_Listeners.insert(std::pair<cbtS32, std::unordered_set<CBTEventListener*>>(CBTFamily<CBTEvent>::GetID<T>(), listenerList));
        }
        else
        {
            // Return false if _listener has already been added for an event of type T.
            if (iter->second.find(_listener) != iter->second.end()) { return false; }

            // Add the listener.
            iter->second.insert(_listener);
        }

        return true;
    }

    /**
        \brief Unsubscribes an EventListener to Event(s) of type T from this EventDispatcher. RemoveListener must be called for each event type that the EventListener is subscribed to.

        \param _listener The EventListener to remove.

        \return Returns true if the EventListener is successfully removed. Returns false if the EventListener was not found for T.
    */
    template <typename T>
    CBT_ENABLE_IF_DERIVED_1(cbtBool, CBTEvent, T) RemoveListener(CBTEventListener* _listener)
    {
        std::unordered_map<cbtS32, std::unordered_set<CBTEventListener*>>::iterator iter = m_Listeners.find(CBTFamily<CBTEvent>::GetID<T>());

        // Check that the listener has been added.
        if (iter == m_Listeners.end()) { return false; }
        if (iter->second.find(_listener) == iter->second.end()) { return false; }

        iter->second.erase(_listener);
        if (iter->second.size() == 0) { m_Listeners.erase(iter); }

        return true;
    }

    /**
        \brief Unsubscribe all EventListener(s) listening to this EventDispatcher.
    */
    void RemoveAllListeners() { m_Listeners.clear(); }

    /*
    template <typename T>
    CBT_ENABLE_IF_DERIVED_1(void, Event, T) QueueEvent(Event* _event, cbtBool _deleteUponDispatch = true)
    {
        m_EventQueue.push_back(QueuedEvent());
        m_EventQueue.back().m_Event = _event;
        m_EventQueue.back().m_DispatchFunction = CBT_CALLBACK_2(EventDispatcher::DispatchEvent<T>, this);
        m_EventQueue.back().m_DeleteUponDispatch = _deleteUponDispatch;
    }

    void DispatchQueuedEvents()
    {
        for (vector<QueuedEvent>::iterator iter = m_EventQueue.begin(); iter != m_EventQueue.end(); ++iter)
        {
            iter->m_DispatchFunction(iter->m_Event, iter->m_DeleteUponDispatch);
        }

        m_EventQueue.clear();
    }
    */
};

NS_CBT_END