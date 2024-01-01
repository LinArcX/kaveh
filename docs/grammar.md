statements: statement
          | statement statements
          ;

statement: 'print' expression ';'
         ;

expression: number
          | expression '*' expression
          | expression '/' expression
          | expression '+' expression
          | expression '-' expression
          ;

number: T_INTLIT
      ;
