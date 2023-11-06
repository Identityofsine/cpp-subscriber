#include "classes.h"

using namespace fofx;

// Path: subscriberobj.cpp
// Purpose: Define the Subscriber class' methods

// constructor
namespace fofx {

int Subscribable::subscribe(SubscribableEvent s,
                            SubscribeFunction<void> *event) {
  // subscribe
  return this->addToMap(s, event);
}

void Subscribable::unsubscribe(SubscribableEvent s,
                               SubscribeFunction<void> *event) {
  // unsubscribe
  this->removeFromMap(s, event);
}

// id number for event
int Subscribable::subscribe(unsigned int id, SubscribeFunction<void> *event) {
  // subscribe
  return this->addToMap(SubscribableEvent{id, ""}, event);
}

void Subscribable::unsubscribe(unsigned int id,
                               SubscribeFunction<void> *event) {
  // unsubscribe
  this->removeFromMap(SubscribableEvent{id, ""}, event);
}

// id string for event
int Subscribable::subscribe(std::string id, SubscribeFunction<void> *event) {
  // subscribe
  return this->addToMap(SubscribableEvent{0, id}, event);
}

void Subscribable::unsubscribe(std::string id, SubscribeFunction<void> *event) {
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

}; // namespace fofx
