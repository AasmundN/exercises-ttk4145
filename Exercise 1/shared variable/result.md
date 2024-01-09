The task of incrementing a variable consists of three steps:

- Reading the variable
- Incrementing/decrement the value
- Writing the new value back to memory.

The thread system here uses preemptive scheduling, this means that the threads are switched at a constant interval. 

This means that: say the first thread starts and it executes the read and increment operations (from 0 to 1), then the thread switches. The next thread reads the variable (which still hasn't changed its value) and then decrements the value (from 0 to -1). The thread now switches again. The first thread writes its value (1), then after reading again the threads change and the second thread wirtes its value (-1). The result is that incrementing and decrementing 0 once is equal to -1, when it should be 0.