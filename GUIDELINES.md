# C programming rules
- Just use If/Else mechanism. No Switch/Case, No Tenary Operator(?).
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
- Brackets always goes to new line, not on the same line.
- Always return an INT indicating the status of the function.(is it successfull or it has errors), the caller should always check this error code.
  - by cascading showing errors in different levels of functions, you will have a trace call.
- If you want to return a char* or int** or any other pointer, you should pass it as in-out arguments to your functions.
- Never use global variables. always pass your variables to your functions down to the road.(if it's expensive to pass them by value, pass them by reference)
- Use const as much as you can.

## Links
- https://github.com/mcinglis/c-style
- https://github.com/git/git/blob/master/banned.h
