## Exercise 1 - Theory questions

### Concepts

What is the difference between _concurrency_ and _parallelism_?

> Parallelle tasks run in parallelle, that is, at the same time on different prosessing units. Concurrent tasks run on the same CPU, switching between executing instructions from both of the tasks very fast, making it seem like the tasks are running at the same time, when in reality they are not.

What is the difference between a _race condition_ and a _data race_?

> A data race is the situation where two or more threads are trying to access (read and at least one write) the same resoiurce at the same time. A race condition happens when a set of instructions that should be executed atomically are intertwined with other instructions. This means that the value of the shared resource after execution will depend on the relative ordering of these intertwined instructions.

_Very_ roughly - what does a _scheduler_ do, and how does it do it?

> A scheduler is responsible for switching between execcuting instructions from different concurrent tasks. Using preemptive scheduling the switches take place at a set interval.

### Engineering

Why would we use multiple threads? What kinds of problems do threads solve?

> By using multiple threads the cpu can process multiple tasks at the same time. For example: in the case a web server handling requests. If the server only runs one thread there would be a bottleneck in the requests, where you would have to queue the requests and wait for all to be processed. With multithreading we could handle all requests at the same time, giving responses much faster.

Some languages support "fibers" (sometimes called "green threads") or "coroutines"? What are they, and why would we rather use them over threads?

> A fiber is a lightweight, user controlled concurrency model. That is (in contrast to OS threads) the thread is handled by the application itself or the runtime environment, and not the kernel. This gives more control over context switching and can simplify synchronization.

Does creating concurrent programs make the programmer's life easier? Harder? Maybe both?

> Concurrency can make a program more readable, by separating the different tasks a program is to handle. However, in some cases, the program might get harder to debug as resources must be more carefully monitored.

What do you think is best - _shared variables_ or _message passing_?

> That probably depends on the problem that is to be solved.
