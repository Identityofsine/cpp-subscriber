#include "classes.h"
#include <iostream>

int main() {

  // demo
  fofx::ExampleSubscribable s = fofx::ExampleSubscribable();
  s.subscribe(1, new fofx::SubscribeFunction<fofx::SubscribeResponseObject>{[](fofx::SubscribeResponseObject e) { 
		printf("--[TEST OUTPUT] VALUES: %s, %d --\n", e.success ? "succesful response" : "failed response", (int)e.data); 
	}});
  s.test();

  return 0;
}
