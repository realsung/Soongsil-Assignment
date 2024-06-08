int main() {
    case 1: // Error: case label not within a switch statement
        break;
}
/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/40.c                                  1 ↵ root@vultr
test/40.c: In function ‘main’:
test/40.c:4:5: error: case label not within a switch statement
    4 |     case 1: // Error: case label not within a switch statement
      |     ^~~~
test/40.c:5:9: error: break statement not within loop or switch
    5 |         break;
      |         ^~~~~
*/