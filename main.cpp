#include "classes.h"
#include <iostream>
#include "debug.h"

int main() {

	using namespace fofx;
  // demo
  ExampleSubscribable s = ExampleSubscribable();
  
	//very important to know what the data pointer is
	s.subscribe(1, new SubscribeFunction<SubscribeResponseObject>{[](SubscribeResponseObject e) {
		DEBUGPRINT("Subscribe Test 1 with int example: %d\n", *((int *)e.data));
	}});

	s.subscribe(2, new SubscribeFunction<SubscribeResponseObject>{[](SubscribeResponseObject e) {
		DEBUGPRINT("Subscribe Test 2 with string example: %s\n", (char*)e.data);
	}});


	s.subscribe(3, new SubscribeFunction<SubscribeResponseObject>{[](SubscribeResponseObject e) {
		DEBUGPRINT("Subscribe Test 3 with Struct Example...");

		//cast to struct
		ExampleStruct *s = (ExampleStruct*)e.data;

		//print struct
		DEBUGPRINT("field_1: %d", s->field_1);
		DEBUGPRINT("field_2: %d", s->field_2);
		DEBUGPRINT("field_3: %s", s->field_3);
		DEBUGPRINT("PTR->field_4: %d", s->field_4->field_number);
		DEBUGPRINT("PTR->field_5: %s", s->field_4->field_name);
	}});

  s.test();
	s.test_2();
	s.test_3();

  return 0;
}
