#include "classes.h"
#include <iostream>

int main() {

  // demo
  fofx::ExampleSubscribable s = fofx::ExampleSubscribable();
  
	//very important to know what the data pointer is
	s.subscribe(1, new fofx::SubscribeFunction<fofx::SubscribeResponseObject>{[](fofx::SubscribeResponseObject e) { 
		printf("--[TEST OUTPUT] VALUES: %s, %d --\n", e.success ? "succesful response" : "failed response", (int)e.data); 
	}});

	s.subscribe(2, new fofx::SubscribeFunction<fofx::SubscribeResponseObject>{[](fofx::SubscribeResponseObject e) {
		printf("--[TEST_2 OUTPUT] VALUES :%s, %d --\n", e.success ? "succesful response" : "failed response", (int)e.data);
	}});

  s.test();
	s.test_2();

  return 0;
}
