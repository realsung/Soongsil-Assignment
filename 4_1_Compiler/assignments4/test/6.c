int arr[5] = {1, 2, 3, 4, 5};
int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int *ptr;
int **ptr;
int ppp = 5;
int *pp = &ppp;
int ***ptr = &pp;
char str[] = "Hello, World!";
struct Point {
   int x;
   int y;
};
struct Point p1 = {10, 20};
enum Color { RED, GREEN, BLUE };

int main(){
   int arr[5] = {1, 2, 3, 4, 5};
   int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
   int *ptr;
   int **ptr;
   char str[] = "Hello, World!";
   struct Point {
      int x;
      int y;
   };
   struct Point p1 = {10, 20};
   enum Color { RED, GREEN, BLUE };
}