#include "classes.h"
#include <iostream>
#include "debug.h"

int main() {

  // demo
  fofx::ExampleSubscribable s = fofx::ExampleSubscribable();
  
	//very important to know what the data pointer is
	s.subscribe(1, new fofx::SubscribeFunction<fofx::SubscribeResponseObject>{[](fofx::SubscribeResponseObject e) { 
		DEBUGPRINT("test 1\n");
	}});

	s.subscribe(2, new fofx::SubscribeFunction<fofx::SubscribeResponseObject>{[](fofx::SubscribeResponseObject e) {
		DEBUGPRINT("test %s\n", (char*)e.data);
	}});

  s.test();
	s.test_2();

  return 0;
}
