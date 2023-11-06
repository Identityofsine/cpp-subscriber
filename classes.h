#include <map>
#include <string>
#include <vector>

namespace fofx {
// abstract class called Subscribable

// define below structs
struct SubscribableEvent {
   unsigned int id;
  std::string name;

  // equal operator
  bool operator==(const SubscribableEvent &other) const {
    return (this->id == other.id || this->name == other.name);
  }
	//define operators
	bool operator!=(const SubscribableEvent &other) const {
		return !(*this == other);
	}
	bool operator<(const SubscribableEvent &other) const {
		return (this->id < other.id && this->name < other.name);
	}
	bool operator>(const SubscribableEvent &other) const {
		return (this->id > other.id && this->name > other.name);
	}
	bool operator<=(const SubscribableEvent &other) const {
		return (this->id <= other.id && this->name <= other.name);
	}
	bool operator>=(const SubscribableEvent &other) const {
		return (this->id >= other.id && this->name >= other.name);
	}

};

// generic subscriber class
template <typename... args> struct SubscribeFunction {
  void (*func)(args...);
};

class Subscribable {

private:
  std::map<SubscribableEvent, std::vector<SubscribeFunction<> *>> subscribers;
  int addToMap(SubscribableEvent s, SubscribeFunction<> *event);
  std::vector<SubscribeFunction<>*> getFromMap(SubscribableEvent s);
  bool removeFromMap(SubscribableEvent s, SubscribeFunction<> *event);
  bool removeFromMap(SubscribableEvent s, int function_id);
  std::vector<SubscribableEvent> validEvents;

protected:
  template <typename... args> void notify(SubscribableEvent s, args...);
  template <typename... args> void notify(unsigned int id, args...);
  template <typename... args> void notify(std::string id, args...);

  void notify(SubscribableEvent s);
  void notify(unsigned int id);
  void notify(std::string id);

public:
  Subscribable(std::vector<SubscribableEvent> valid_events = {}) {
    // init map
    subscribers =
        std::map<SubscribableEvent, std::vector<SubscribeFunction<> *>>();
    this->validEvents = valid_events;
  }

  // using SubscriableEvent
  int subscribe(SubscribableEvent s, SubscribeFunction<> *event);
  void unsubscribe(SubscribableEvent s, SubscribeFunction<> *event);
  void unsubscribe(SubscribableEvent s, int id);

  // using int as event id
  int subscribe(unsigned int id, SubscribeFunction<> *event);
  void unsubscribe(unsigned int id, SubscribeFunction<> *event);
  void unsubscribe(unsigned int id, int function_id);

  // using string as event id
  int subscribe(std::string id, SubscribeFunction<> *event);
  void unsubscribe(std::string id, SubscribeFunction<> *event);
  void unsubscribe(std::string id, int function_id);
};

class ExampleSubscribable : public Subscribable {

public:
  ExampleSubscribable() : Subscribable({SubscribableEvent{1, "test"}}) {}
  void test(); 
};

}; // namespace fofx
