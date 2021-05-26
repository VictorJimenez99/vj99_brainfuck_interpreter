# vj99_brainfuck_interpreter

Simple project using c

It has the slight modification that it works with ints instead of bytes
if you want to change its behaviour you can modify the defs.h file and change 

```
int content;
//to
char content;
```
and it should work as expected


brainfuck interpreter, it has "negative cells" so it can accurately represent a tape from a turing machine.

It doesnt have support for [ comments inside brackets ]
