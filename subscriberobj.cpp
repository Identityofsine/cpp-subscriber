#include "classes.h"

using namespace fofx;

// Path: subscriberobj.cpp
// Purpose: Define the Subscriber class' methods

// constructor
namespace fofx {

// private stuff
int Subscribable::addToMap(SubscribableEvent s, SubscribeFunction<> *event) {

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
      this->subscribers[s] = std::vector<SubscribeFunction<> *>();
    }
    this->subscribers[s].push_back(event);
    return this->subscribers[s].size() - 1;
  }
  return -1;
}

bool Subscribable::removeFromMap(SubscribableEvent s,
                                 SubscribeFunction<> *event) {
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

std::vector<SubscribeFunction<>*> Subscribable::getFromMap(SubscribableEvent s) {

	std::vector<SubscribeFunction<>*> found_functions;
	// check if key exists in map
	if (this->subscribers.find(s) != this->subscribers.end()) {
		found_functions = this->subscribers[s];
	} 

	return found_functions;
}

int Subscribable::subscribe(SubscribableEvent s, SubscribeFunction<> *event) {
  // subscribe
  return this->addToMap(s, event);
}

void Subscribable::unsubscribe(SubscribableEvent s,
                               SubscribeFunction<> *event) {
  // unsubscribe
  this->removeFromMap(s, event);
}

// id number for event
int Subscribable::subscribe(unsigned int id, SubscribeFunction<> *event) {
  // subscribe
  return this->addToMap(SubscribableEvent{id, ""}, event);
}

void Subscribable::unsubscribe(unsigned int id, SubscribeFunction<> *event) {
  // unsubscribe
  this->removeFromMap(SubscribableEvent{id, ""}, event);
}

// id string for event
int Subscribable::subscribe(std::string id, SubscribeFunction<> *event) {
  // subscribe
  return this->addToMap(SubscribableEvent{0, id}, event);
}

void Subscribable::unsubscribe(std::string id, SubscribeFunction<> *event) {
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
    f.func(a...);
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
    f->func();
  };
}

void Subscribable::notify(unsigned int id) {
  this->notify(SubscribableEvent{id, ""});
}

void Subscribable::notify(std::string id) {
  this->notify(SubscribableEvent{0, id});
}



void ExampleSubscribable::test() {
	this->notify(SubscribableEvent{1, "test"});
}

}; // namespace fofx
