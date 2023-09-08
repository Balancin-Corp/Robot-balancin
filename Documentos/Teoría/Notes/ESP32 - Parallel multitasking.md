Created: 2023-09-08 10:38

There are a few ways multitasking is achieved depending on the execution environment. If there is only one processor core, we can execute tasks either in a **preemptive** or **cooperative** fashion. They are two of the many methods.

In **preemptive multitasking**, the currently running task is stopped after a definite interval to allow the next task to run in an interleaved fashion. The number of tasks, their priorities, and the value of the **time slice** determines how seamlessly your parallel tasks can run. If there are too many tasks to run it will slow down all tasks. 

On the other hand, **cooperative multitasking** allows each task to take its time to finish executing while **all other tasks wait in a queue to be executed next**. If the tasks do not take much time to finish, then everything runs smoothly. But if any task takes more than the expected time, all other tasks will be delayed and you will notice the delay in execution. 

We have **parallel execution** when two task are running on different cores.

## References

1. [circuitstate](https://www.circuitstate.com/tutorials/how-to-write-parallel-multitasking-applications-for-esp32-using-freertos-arduino/)

#note