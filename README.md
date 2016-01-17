# LambdaLifetimeTest
Test of the C++ lambda object lifetime, when used in a scheduler.

# Test case
When implementing a callback-based system, the general approach is to use lambda functions for the callbacks. However, there's a concern that such a lambda object, when constructed on stack, will no longer be valid if used in a scheduler system:
  1. Construct a scheduler object
  2. Construct a lambda object on stack
  3. Register the lambda with the scheduler, to be called later
  4. Destroy the lambda object on the stack (RAII)
  5. Scheduler calls the lambda

The questions are:
  1. Does this work on major C++ compilers? If so, how exactly?
  2. Does this constitute Undefined behavior?
  3. Does this require object copying / moving?
  4. If this doesn't work, is there a way to make it work (with copying / moving)?
