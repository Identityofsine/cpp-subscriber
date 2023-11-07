#include <map>
#include <string>
#include <functional>
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
	std::function<void(args...)> func;

	template <typename... OtherArgs>
	operator SubscribeFunction<OtherArgs...>() {
		SubscribeFunction<OtherArgs...> newFunction;
		newFunction.func = [this](OtherArgs... a) {
			this->func(a...);
		};
		return newFunction;
	}
};


struct SubscribeResponseObject {
	bool success;
	void* data;
};

class Subscribable {

private:
  std::map<SubscribableEvent, std::vector<SubscribeFunction<SubscribeResponseObject>*>> subscribers;

  int addToMap(SubscribableEvent s, SubscribeFunction<SubscribeResponseObject> *event);
  template <typename... args> std::vector<SubscribeFunction<args...>*> getFromMap(SubscribableEvent s);

  bool removeFromMap(SubscribableEvent s, SubscribeFunction<SubscribeResponseObject> *event);
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
    subscribers = std::map<SubscribableEvent, std::vector<SubscribeFunction<SubscribeResponseObject> *>>();
    this->validEvents = valid_events;
  }

  // using SubscriableEvent //default event template args
  int subscribe(SubscribableEvent s, SubscribeFunction<> *event);
  int subscribe(SubscribableEvent s, SubscribeFunction<SubscribeResponseObject> *event);
  void unsubscribe(SubscribableEvent s, SubscribeFunction<SubscribeResponseObject> *event);
  void unsubscribe(SubscribableEvent s, int id);

  // using int as event id
	
  int subscribe(unsigned int id, SubscribeFunction<> *event);
  int subscribe(unsigned int id, SubscribeFunction<SubscribeResponseObject> *event);
  void unsubscribe(unsigned int id, SubscribeFunction<SubscribeResponseObject> *event);
  void unsubscribe(unsigned int id, int function_id);

  // using string as event id
	
  int subscribe(std::string id, SubscribeFunction<> *event);
  int subscribe(std::string id, SubscribeFunction<SubscribeResponseObject> *event);
  void unsubscribe(std::string id, SubscribeFunction<SubscribeResponseObject> *event);
  void unsubscribe(std::string id, int function_id);
};

class ExampleSubscribable : public Subscribable {

public:
  ExampleSubscribable() : Subscribable({SubscribableEvent{1, "test"}}) {}
  void test(); 
};

}; // namespace fofx
