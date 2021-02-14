The difference between fork(), vfork(), exec() and clone()

The fork call basically makes a duplicate of the current process, identical in almost every way (not everything is copied over, for example, resource limits in some implementations but the idea is to create as close a copy as possible).
The new process (child) gets a different process ID (PID) and has the the PID of the old process (parent) as its parent PID (PPID). 
The child gets PID 0, the parent gets the PID of the child.


The basic difference between vfork and fork is that when a new process is created with vfork(), the parent process is temporarily suspended, and 
the child process might borrow the parent’s address space.
vfork( ) is obsolete.


When the child process is created with clone, it executes the function application fn(arg). (This differs from fork, where execution continues in the child from the point 
of the original fork call.) The fn argument is a pointer to a function that is called by the child process at the beginning of its execution. 
The arg argument is passed to the fn function. When the fn(arg) function application returns, the child process terminates.


https://man7.org/linux/man-pages/man2/clone.2.html
