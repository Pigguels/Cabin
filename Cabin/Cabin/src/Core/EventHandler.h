#pragma once
#include "Data/Stack.h"
#include "Data/Dict.h"
#include "Data/String.h"
#include "Data/Algorithms.h"


/*
Summary:
	The Core EventHandler.
	Allows you to map functions to listen for event calls.

	Mapped EventFunctions take a context pointer, that being the object that wants to actually listen.
	Aswell as the context the EventFunctions take a data pointer, that being the data object that is passed on the event being called.

	You can only map one context and function per event type, meaning no stacking multiple calls on a single context per event call.
*/
class EventHandler
{
public:
	typedef void(*EventFunction)(void* context, void* data);

private:
	struct Event
	{
		bool operator==(const Event& that) const { return (context == that.context && function == that.function); }
		void* context;
		EventFunction function;
	};

public:

	bool AddEventListener(const String& event, void* context, EventFunction function)
	{
		Stack<Event>* events;
		if (!eventMap.TryGet(event, events))
		{
			events = new Stack<Event>();
			eventMap.Add(event, events);
		}
		Event potential = { context, function };
		if (!events->Contains(potential))
		{
			events->Add(potential);
			return true;
		}
		return false;
	}

	bool RemoveEventListener(const String& event, void* context, EventFunction function)
	{
		Stack<Event>* events;
		if (eventMap.TryGet(event, events))
		{
			if (events->Remove({ context, function }))
			{
				if (events->Count() == 0)
				{
					delete events;
					eventMap.Remove(event);
				}
				return true;
			}
		}
		return false;
	}

	void CallEvent(const String& event, void* data) const
	{
		Stack<Event>* events;
		if (eventMap.TryGet(event, events))
		{
			for (Event& event : *events) event.function(event.context, data);
		}
	}

private:
	Dict<String, Stack<Event>*> eventMap;
};
