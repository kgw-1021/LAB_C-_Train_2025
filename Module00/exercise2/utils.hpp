#include <termios.h>
#include <stdio.h>

//Get Keyboard input without Enter for Linux 
int getch(void) {
  int ch;
  struct termios buf, save;

  tcgetattr(0, &save);
  buf = save;

  buf.c_lflag &= ~(ICANON | ECHO);
  buf.c_cc[VMIN] = 1;
  buf.c_cc[VTIME] = 0;

  tcsetattr(0, TCSAFLUSH, &buf);
  
  ch = getchar();

  if (ch == 27) { 
      if (getchar() == '[') {
          ch = getchar(); 
         
          switch (ch) {
              case '3': getchar(); ch = 127; break; 
              case 'A': ch = -1; break; 
              case 'B': ch = -2; break; 
              case 'C': ch = -3; break;
              case 'D': ch = -4; break; 
              default: break; 
          }
      }
  }
  
  tcsetattr(0, TCSAFLUSH, &save);
  
  return ch;
}