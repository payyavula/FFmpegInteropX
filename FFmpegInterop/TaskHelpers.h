#pragma once

#include <ppltasks.h>

Concurrency::task<void> task_delay(unsigned int timeoutMs);

template<typename T>
Concurrency::task<T> cancel_after_timeout(Concurrency::task<T> t, Concurrency::cancellation_token_source cts, unsigned int timeoutInMilliseconds);

template<typename T>
Concurrency::task<T> task_timeout(Concurrency::task<T> t, unsigned int timeoutInMilliseconds);