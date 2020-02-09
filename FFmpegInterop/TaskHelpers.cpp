#include "pch.h"

#include "TaskHelpers.h"

// task-delay.cpp
// compile with: /EHsc
#include <ppltasks.h>
#include <agents.h>
#include <iostream>

using namespace concurrency;
using namespace std;

// Creates a task that completes after the specified delay.
task<void> task_delay(unsigned int timeoutMs)
{
	// A task completion event that is set when a timer fires.
	task_completion_event<void> tce;

	// Create a non-repeating timer.
	auto fire_once = new timer<int>(timeoutMs, 0, nullptr, false);
	// Create a call object that sets the completion event after the timer fires.
	auto callback = new call<int>([tce](int)
		{
			tce.set();
		});

	// Connect the timer to the callback and start the timer.
	fire_once->link_target(callback);
	fire_once->start();

	// Create a task that completes after the completion event is set.
	task<void> event_set(tce);
	
	// Create a continuation task that cleans up resources and
	// and return that continuation task.
	return event_set.then([callback, fire_once]()
		{
			delete callback;
			delete fire_once;
		});
}

// Cancels the provided task after the specifed delay, if the task
// did not complete.
template<typename T>
task<T> cancel_after_timeout(task<T> t, cancellation_token_source cts, unsigned int timeout)
{
	// Create a task that returns true after the specified task completes.
	task<bool> success_task = t.then([](T)
		{
			return true;
		});
	// Create a task that returns false after the specified timeout.
	task<bool> failure_task = complete_after(timeout).then([]
		{
			return false;
		});

	// Create a continuation task that cancels the overall task 
	// if the timeout task finishes first.
	return (failure_task || success_task).then([t, cts](bool success)
		{
			if (!success)
			{
				// Set the cancellation token. The task that is passed as the
				// t parameter should respond to the cancellation and stop
				// as soon as it can.
				cts.cancel();
			}

			// Return the original task.
			return t;
		});
}

// Returns a task that either completes or throws an exception on timeout.
template<typename T>
task<T> task_timeout(Concurrency::task<T> t, unsigned int timeoutInMilliseconds)
{
	task_completion_event<T> tce;

	auto timeoutTask = task_delay(timeoutInMilliseconds).then([tce]()
		{
			tce.set_exception(ref new Exception("Timeout occured."));
		});

	auto tasks = std::vector<task<T>>({ t, create_task(tce) });
	auto resultTask = when_any(tasks.begin(), tasks.end());
	return resultTask.then([](std::pair<task<T>, size_t> task) { return task.first; });
}