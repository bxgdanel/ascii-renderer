#include "Camera.h"
#include "domain.h"
#include "renderer.h"
#include <unistd.h>
#include <termios.h>
#include <thread>
float ls[3] = {0, 2, -10};
  float cam_position[3] = {0, 0, 0};
Camera camera = Camera(cam_position);
  Renderer r = Renderer(160, 80, ls, camera);
Torus t, t2;
  Cube c;

char readKey(){
  struct termios oldt, newt;
  char ch;
  tcgetattr(STDIN_FILENO,&oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO,TCSANOW, &newt);
  ch = getchar();
  tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
  return ch;
}
float input_buf[3];
int input_rot;
void thread_input(){
  while(true){
    char c = readKey();
    if( c == 'w')
      input_buf[2]+=1;
    else if(c == 's')
      input_buf[2]-=1;
    else if(c=='a')
      input_buf[0]-=1;
    else if(c=='d')
      input_buf[0]+=1;
    else if(c==' ')
      input_buf[1]+=1;
    else if(c=='m')
      input_buf[1]-=1;
    else if(c=='[')
      input_rot-=15;
    else if(c==']')
      input_rot += 15;
    r.getCamera().setPosition(input_buf);
    r.getCamera().rotation_angle = input_rot;
  }
}
void thread_output(){
  while(true){
r.display();
    t.rotate_x(10 * 3.14 / 180);
    t2.rotate_x(-10 * 3.14 / 180);

  }
}
int main() {
    c.generate(40, 4, 40);
  t.generate(6, 3);
  t2.generate(6, 3);
  r.add_shape(&t);
  r.add_shape(&t2);
  r.add_shape(&c);
  t.translate(-10, 0, 30);
  t2.translate(10, 0, 30);
  std::thread t_in(thread_input);
  std::thread t_out(thread_output);

  t_in.join();
  t_out.join();
}
