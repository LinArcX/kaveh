# C programming rules
- Just use If/Else mechanism. No Switch/Case, No Tenary Operator(?).
- No strcpy, strncpy, strncpy_s: use memcpy:
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
