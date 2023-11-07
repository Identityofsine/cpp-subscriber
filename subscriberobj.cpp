#include "classes.h"

using namespace fofx;

// Path: subscriberobj.cpp
// Purpose: Define the Subscriber class' methods

// constructor
namespace fofx {

// private stuff
int Subscribable::addToMap(SubscribableEvent s, SubscribeFunction<SubscribeResponseObject> *event) {

  bool valid = false;
  // check if event is valid
  if (this->validEvents.size() > 0) {
    for (auto &e : this->validEvents) {
      if (e == s) {
        valid = true;
        break;
      }
    }
    if (!valid) {
      return -1;
    }
  } else
    return -1;

  if (valid) {
    // check if key exists in map, if not create
    if (this->subscribers.find(s) == this->subscribers.end()) {
      this->subscribers[s] = std::vector<SubscribeFunction<SubscribeResponseObject> *>();
    }
    this->subscribers[s].push_back(event);
    return this->subscribers[s].size() - 1;
  }
  return -1;
}

bool Subscribable::removeFromMap(SubscribableEvent s, SubscribeFunction<SubscribeResponseObject> *event) {
  // check if key exists in map
  bool valid = false;
  if (this->subscribers.find(s) != this->subscribers.end()) {
    valid = true;
  } else {
    return false;
  }
  // search for event
  if (valid) {
    for (auto f : this->subscribers[s]) {
      if (f == event) {
        this->subscribers[s].erase(std::remove(this->subscribers[s].begin(), this->subscribers[s].end(), f), this->subscribers[s].end());
        return true;
      }
    }
  } else {
    return false;
  }
  return false;
}

bool Subscribable::removeFromMap(SubscribableEvent s, int function_id) {
	bool valid = false;
	// check if key exists in map
	if (this->subscribers.find(s) != this->subscribers.end()) {
		valid = true;
	} else {
		return false;
	}

	if(valid) {
		//check if table is empty 
		if(this->subscribers[s].size() <= 0) {
			return false;
		}
		// check if function_id is valid
		if(function_id < 0 || function_id >= this->subscribers[s].size()) {
			return false;
		}
		// remove function
		this->subscribers[s].erase(this->subscribers[s].begin() + function_id);
	}
	return false;
}

std::vector<SubscribeFunction<SubscribeResponseObject>*> Subscribable::getFromMap(SubscribableEvent s) {

	std::vector<SubscribeFunction<SubscribeResponseObject>*> found_functions;
	// Check if the key exists in the map
  if (this->subscribers.find(s) != this->subscribers.end()) {
   found_functions = this->subscribers[s];
  }

	return found_functions;
}


//no argument subscribe
int Subscribable::subscribe(SubscribableEvent s, SubscribeFunction<> *event) {

	//cast to SubscribeFunction<SubscribeResponseObject>
	SubscribeFunction<SubscribeResponseObject>* newFunction = (SubscribeFunction<SubscribeResponseObject>*)event;

	// subscribe
	return this->addToMap(s, newFunction);
}

int Subscribable::subscribe(unsigned int id, SubscribeFunction<> *event) {
	//cast to SubscribeFunction<SubscribeResponseObject>
	SubscribeFunction<SubscribeResponseObject>* newFunction = (SubscribeFunction<SubscribeResponseObject>*)event;

	// subscribe
	return this->addToMap(SubscribableEvent{id, ""}, newFunction);
}

int Subscribable::subscribe(std::string id, SubscribeFunction<> *event) {
	//cast to SubscribeFunction<SubscribeResponseObject>
	SubscribeFunction<SubscribeResponseObject>* newFunction = (SubscribeFunction<SubscribeResponseObject>*)event;

	// subscribe
	return this->addToMap(SubscribableEvent{0, id}, newFunction);
}

void Subscribable::unsubscribe(SubscribableEvent s, int function_id) {
	// unsubscribe
	this->removeFromMap(s, function_id);
}



int Subscribable::subscribe(SubscribableEvent s, SubscribeFunction<SubscribeResponseObject> *event) {
  // subscribe
  return this->addToMap(s, event);
}

void Subscribable::unsubscribe(SubscribableEvent s, SubscribeFunction<SubscribeResponseObject> *event) {
  // unsubscribe
  this->removeFromMap(s, event);
}

// id number for event
int Subscribable::subscribe(unsigned int id, SubscribeFunction<SubscribeResponseObject> *event) {
  // subscribe
  return this->addToMap(SubscribableEvent{id, ""}, event);
}

void Subscribable::unsubscribe(unsigned int id, SubscribeFunction<SubscribeResponseObject> *event) {
  // unsubscribe
  this->removeFromMap(SubscribableEvent{id, ""}, event);
}

// id string for event
int Subscribable::subscribe(std::string id, SubscribeFunction<SubscribeResponseObject> *event) {
  // subscribe
  return this->addToMap(SubscribableEvent{0, id}, event);
}

void Subscribable::unsubscribe(std::string id, SubscribeFunction<SubscribeResponseObject> *event) {
  // unsubscribe
  this->removeFromMap(SubscribableEvent{0, id}, event);
}

// notify hooks
template <typename... args>
void Subscribable::notify(SubscribableEvent e, args... a) {
  auto functions = this->getFromMap(e);
  if (functions.size() <= 0)
    return;

  for (auto &f : functions) {
    f->func({true, (void*)a...});
  };
}

template <typename... args>
void Subscribable::notify(unsigned int id, args... a) {
  this->notify(SubscribableEvent{id, ""}, a...);
}

template <typename... args>
void Subscribable::notify(std::string id, args... a) {
  this->notify(SubscribableEvent{0, id}, a...);
}

void Subscribable::notify(SubscribableEvent e) {
  auto functions = this->getFromMap(e);
  if (functions.size() <= 0)
    return;

  for (auto &f : functions) {
    f->func({true, 0});
  };
}

void Subscribable::notify(unsigned int id) {
  this->notify(SubscribableEvent{id, ""});
}

void Subscribable::notify(std::string id) {
  this->notify(SubscribableEvent{0, id});
}

void ExampleSubscribable::test() {
	this->notify(SubscribableEvent{this->TEST_EVENT, "test"}, 5124);
}

void ExampleSubscribable::test_2() {
	this->notify(SubscribableEvent{this->TEST_EVENT, "test_2"}, "Hey, I am 'test_2' - A String Example!");
}

}; // namespace fofx
