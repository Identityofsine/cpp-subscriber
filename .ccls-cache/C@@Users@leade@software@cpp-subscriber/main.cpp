#include "classes.h"
#include <iostream>

int main() {

  // demo
  fofx::ExampleSubscribable s = fofx::ExampleSubscribable();
  s.subscribe(1, new fofx::SubscribeFunction<int>{[]() { printf("test\n"); }});
  s.test();

  return 0;
}
