int main() {
  /*single and multiline
  comments have been handled*/
  int a = 0, b=5; // even if they are not at the begining of a line
  int c = a+b/2;
  for(int i=0; i<5; i=i+1) {
    c = c + 1;
  }
  int 2a2=32; // 2a2 will be flagged as Invalid Identifier
  int a3 = 2*2a2;
  char c = 'h'; // 'h' and "hello" are marked as literals
  string s = "hello";
  //comment line
  /* hello
  world */
  return 0;
}
