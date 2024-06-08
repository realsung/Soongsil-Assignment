int main() {
    default:
        break;
    return 0;
}
/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/41.c                                  1 ↵ root@vultr
test/41.c: In function ‘main’:
test/41.c:4:5: error: ‘default’ label not within a switch statement
    4 |     default: // Error: default label not within a switch statement
      |     ^~~~~~~
test/41.c:5:9: error: break statement not within loop or switch
    5 |         break;
      |         ^~~~~
*/