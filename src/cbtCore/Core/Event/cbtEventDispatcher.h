#pragma once

// Include CBT
#include "cbtMacros.h"
#include "Core/General/cbtFamily.h"
#include "cbtEventListener.h"

// Include STD
#include <unordered_map>
#include <unordered_set>
#include <vector>

NS_CBT_BEGIN

/**
    \brief An cbtEventDispatcher is used to dispatch cbtEvent(s) to cbtEventListener(s) that are subscribed to this dispatcher. This uses the publisher-subscriber pattern.
*/
    class cbtEventDispatcher
    {
    private:
        /// The cbtEventListener(s) added to this cbtEventDispatcher is sorted by the cbtEvent type they are subscribed to.
        std::unordered_map<cbtS32, std::unordered_set<cbtEventListener*>> m_Listeners;

    public:
        /**
            \brief Default Constructor.

            \return A CBTEventDispatcher.
        */
        cbtEventDispatcher()
        {
        }

        /**
            \brief Destructor. Subscribed listeners are removed.
        */
        ~cbtEventDispatcher()
        {
            RemoveAllListeners();
        }

        /*
            \brief Dispatches an cbtEvent of type T. Only cbtEventListener(s) subscribed to cbtEvent(s) of type T will receive the event.

            \param _event The cbtEvent to dispatch.
            \param _deleteAfterDispatch If set to true, the event will be deleted after dispatching. This means that the ownership of the event is given to the dispatcher. The default value is set to true.

            \return Returns true if the cbtEvent is successfully dispatched.
        */
        template<typename T>
        CBT_ENABLE_IF_DERIVED_1(cbtBool, cbtEvent, T)
        DispatchEvent(cbtEvent* _event, cbtBool _deleteAfterDispatch = true)
        {
            std::unordered_map<cbtS32, std::unordered_set<cbtEventListener*>>::iterator iter = m_Listeners.find(
                    cbtFamily<cbtEvent>::GetID<T>());
            if (iter == m_Listeners.end())
            { return true; }

            for (std::unordered_set<cbtEventListener*>::iterator i = iter->second.begin();
                 i != iter->second.end(); ++i)
            {
                if (_event->IsHandled())
                { break; }
                (*i)->InvokeCallback(_event);
            }

            if (_deleteAfterDispatch)
            { delete _event; }

            return true;
        }

        /**
            \brief Subscribes an cbtEventListener to cbtEvent(s) of type T from this cbtEventDispatcher. Only cbtEvent(s) of type T will be received from this cbtEventDispatcher. It is possible use AddListener multiple times to listen for multiple types of cbtEvent(s).

            \param _listener The cbtEventListener to add.

            \return Returns true if the cbtEventListener is successfully added. Returns false if the cbtEventListener has already been previously added for T.
        */
        template<typename T>
        CBT_ENABLE_IF_DERIVED_1(cbtBool, cbtEvent, T) AddListener(cbtEventListener* _listener)
        {
            std::unordered_map<cbtS32, std::unordered_set<cbtEventListener*>>::iterator iter = m_Listeners.find(
                    cbtFamily<cbtEvent>::GetID<T>());
            if (iter == m_Listeners.end())
            {
                // Add the listener.
                std::unordered_set<cbtEventListener*> listenerList;
                listenerList.insert(_listener);
                m_Listeners.insert(
                        std::pair<cbtS32, std::unordered_set<cbtEventListener*>>(cbtFamily<cbtEvent>::GetID<T>(),
                                listenerList));
            }
            else
            {
                // Return false if _listener has already been added for an event of type T.
                if (iter->second.find(_listener) != iter->second.end())
                { return false; }

                // Add the listener.
                iter->second.insert(_listener);
            }

            return true;
        }

        /**
            \brief Unsubscribes an cbtEventListener to cbtEvent(s) of type T from this cbtEventDispatcher. RemoveListener must be called for each event type that the cbtEventListener is subscribed to.

            \param _listener The cbtEventListener to remove.

            \return Returns true if the cbtEventListener is successfully removed. Returns false if the cbtEventListener was not found for T.
        */
        template<typename T>
        CBT_ENABLE_IF_DERIVED_1(cbtBool, cbtEvent, T) RemoveListener(cbtEventListener* _listener)
        {
            std::unordered_map<cbtS32, std::unordered_set<cbtEventListener*>>::iterator iter = m_Listeners.find(
                    cbtFamily<cbtEvent>::GetID<T>());

            // Check that the listener has been added.
            if (iter == m_Listeners.end())
            { return false; }
            if (iter->second.find(_listener) == iter->second.end())
            { return false; }

            iter->second.erase(_listener);
            if (iter->second.size() == 0)
            { m_Listeners.erase(iter); }

            return true;
        }

        /**
            \brief Unsubscribe all cbtEventListener(s) listening to this cbtEventDispatcher.
        */
        void RemoveAllListeners()
        {
            m_Listeners.clear();
        }
    };

NS_CBT_END