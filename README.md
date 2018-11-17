# functon_parser
A very simple recursive function parameter parser.
## example
### input
```
"fun1(1234,qwe , [3334)],fun2(),fun3(1,[2],3),abc)"
```
### output
```
code: fun1(1234,qwe , [3334)],fun2(),fun3(1,[2],3),abc)
********** my name is fun1 ***********
**** para 1 is 1234 ****
**** para 2 is qwe ****
**** para 3 is  [3334)] ****
**** para 4 is fun2() ****
**** para 5 is fun3(1,[2],3) ****
**** para 6 is abc ****
********* fun1 end *********
```
