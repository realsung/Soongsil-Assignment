enum Example {
    A = 1.5
};
/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/44.c                                130 ↵ root@vultr
test/44.c:3:9: error: enumerator value for ‘A’ is not an integer constant
    3 |     A = 1.5 // Error: integer type expression required in enumerator
      |         ^~~
*/