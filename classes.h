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
};

// generic subscriber class
template <typename... args> struct SubscribeFunction {
  void (*func)(args...);
};

class Subscribable {

private:
  std::map<SubscribableEvent, std::vector<SubscribeFunction<void>>> subscribers;
  int addToMap(SubscribableEvent s, SubscribeFunction<void> *event);
  std::vector<SubscribeFunction<void>> getFromMap(SubscribableEvent s);
  void removeFromMap(SubscribableEvent s, SubscribeFunction<void> *event);
  std::vector<SubscribableEvent> validEvents;

protected:
  template <typename... args> void notify(SubscribableEvent s, args...);
  template <typename... args> void notify(unsigned int id, args...);
  template <typename... args> void notify(std::string id, args...);

public:
  Subscribable(std::vector<SubscribableEvent> valid_events = {}) {
    // init map
    subscribers =
        std::map<SubscribableEvent, std::vector<SubscribeFunction<void>>>();
    this->validEvents = valid_events;
  }

  // using SubscriableEvent
  int subscribe(SubscribableEvent s, SubscribeFunction<void> *event);
  void unsubscribe(SubscribableEvent s, SubscribeFunction<void> *event);
  void unsubscribe(SubscribableEvent s, int id);

  // using int as event id
  int subscribe(unsigned int id, SubscribeFunction<void> *event);
  void unsubscribe(unsigned int id, SubscribeFunction<void> *event);
  void unsubscribe(unsigned int id, int function_id);

  // using string as event id
  int subscribe(std::string id, SubscribeFunction<void> *event);
  void unsubscribe(std::string id, SubscribeFunction<void> *event);
  void unsubscribe(std::string id, int function_id);
};

class ExampleSubscribable : public Subscribable {

public:
  ExampleSubscribable() : Subscribable({SubscribableEvent{1, "test"}}) {}
  void test() { this->notify(1); }
};

}; // namespace fofx
