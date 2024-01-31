#pragma once
#include <functional>
#include <array>
#include "Keys.hpp"

namespace SimpleEngine {
  enum class EventType {
    WindowResize = 0,
    WindowClose,

    KeyPressed,
    KeyReleased,

    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,

    EventsCount
  };

  struct BaseEvent {
    virtual ~BaseEvent() noexcept = default;
    virtual EventType get_type() const noexcept = 0;
  };


  class EventDispatcher {
  public:
    template<typename EventType>
    void add_event_listener(std::function<void(EventType&)> callback) noexcept {
      auto baseCallback = [func = std::move(callback)](BaseEvent &e) {
        if(e.get_type() == EventType::type) {
          func(static_cast<EventType &>(e));
        }
      };
      m_eventCallbacks[static_cast<size_t>(EventType::type)] = std::move(baseCallback);
    }

    void dispatch(BaseEvent &event) noexcept {
      auto &callback = m_eventCallbacks[static_cast<size_t>(event.get_type())];
      if(callback) {
        callback(event);
      }
    }

  private:
    std::array<std::function<void(BaseEvent&)>, static_cast<size_t>(EventType::EventsCount)> m_eventCallbacks;
  };


  struct EventMouseMoved : public BaseEvent {
    EventMouseMoved(const double new_x, const double new_y) noexcept : x(new_x), y(new_y) {
    }

    virtual EventType get_type() const noexcept override {
      return type;
    }

    double x;
    double y;

    static const EventType type = EventType::MouseMoved;
  };

  struct EventWindowResize : public BaseEvent {
    EventWindowResize(const unsigned int new_width, const unsigned int new_height) noexcept:
			width(new_width),
			height(new_height) {
		}

    virtual EventType get_type() const noexcept override {
      return type;
    }

    unsigned int width;
    unsigned int height;

    static const EventType type = EventType::WindowResize;
  };

  struct EventWindowClose : public BaseEvent {
    virtual EventType get_type() const noexcept override {
      return type;
    }

    static const EventType type = EventType::WindowClose;
  };

	struct EventKeyPressed: public BaseEvent {
		EventKeyPressed(const KeyCode _key_code, const bool _repeated) noexcept : 
			key_code(_key_code), repeated(_repeated) {
		}

		virtual EventType get_type() const noexcept override {
			return type;
		}

		KeyCode key_code;
		bool repeated;
		static const EventType type = EventType::KeyPressed;
	};

	struct EventKeyReleased: public BaseEvent {
		EventKeyReleased(const KeyCode _key_code) noexcept :
			key_code(_key_code) {
		}

		virtual EventType get_type() const noexcept override {
			return type;
		}

		KeyCode key_code;
		static const EventType type = EventType::KeyReleased;
	};

	struct EventMouseButtonPressed: public BaseEvent {
		EventMouseButtonPressed(const MouseButton _mouse_button, const double _x_pos, const double _y_pos) noexcept :
			mouse_button(_mouse_button), x_pos(_x_pos), y_pos(_y_pos) {
		}

		virtual EventType get_type() const noexcept override {
			return type;
		}

		MouseButton mouse_button;
		double x_pos; 
		double y_pos;
		static const EventType type = EventType::MouseButtonPressed;
	};

	struct EventMouseButtonReleased: public BaseEvent {
		EventMouseButtonReleased(const MouseButton _mouse_button, const double _x_pos, const double _y_pos) noexcept :
			mouse_button(_mouse_button), x_pos(_x_pos), y_pos(_y_pos) {
		}

		virtual EventType get_type() const noexcept override {
			return type;
		}

		MouseButton mouse_button;
		double x_pos;
		double y_pos;
		static const EventType type = EventType::MouseButtonReleased;
	};
}