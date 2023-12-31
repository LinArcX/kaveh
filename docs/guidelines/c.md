# C programming rules
- Just use If/Else mechanism. No Switch/Case, No Tenary Operator(?). 
  - Maybe you say switch cases are faster than If/Else. but if you use highest omptimizations, compiler will optimize your If/else. if you are still in doubt,
    compare the assembly output of highly optimized if/else with switch/case. which version is faster? choose that one.
- No /* */ comment, just //
- No strcpy, strncpy, strncpy_s. use memcpy like this:
  int copymem(struct err *err)
  {
      static const char oom[] = "out of memory";
      if(sizeof(err->message) >= sizeof(oom))
      {
        memcpy(err->message, oom, sizeof(oom));
        return 0;
      }
      return -1;
  }
- Every function should return 0(or NULL for pointers) as error or 1 as success. (except main() that returns 0 as success and anything else as failure.)
  - There is no need to return error code. errors should write to log file or stdout when errors happens.
  - Caller code should always check if the callee was successfull or not.
- Brackets always goes to new line, not on the same line.
- Always return an INT indicating the status of the function.(is it successfull or it has errors), the caller should always check this error code.
  - by cascading showing errors in different levels of functions, you will have a trace call.
- If you want to return a char* or int** or any other pointer, you should pass it as in-out arguments to your functions.
- Never use global variables. always pass your variables to your functions down to the road.(if it's expensive to pass them by value, pass them by reference)
- Use const as much as you can.

## Links
- https://github.com/mcinglis/c-style
- https://github.com/git/git/blob/master/banned.h
