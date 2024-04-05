struct Point {
   int x, y;
};

int main() {
   struct Point p;
   p.x = 10;
   p.y = 20;
   printf("x : %d, y : %d\n", p.x, p.y);
}