#pragma once

#include <GChar.h>
#include <Dice.h>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/back/state_machine.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/none.hpp>
#include <iostream>

// states
struct Alive;
struct Dying;
struct Dead;

// events
struct damaged {};
struct healed {};
struct saving_throw_failure {};
struct saving_throw_success {};
struct saving_throw_critical_success {};

inline std::ostream& operator<<(std::ostream& os, const damaged& event)
{
  os << "damaged";
  return os;
}

inline std::ostream& operator<<(std::ostream& os, const healed& event)
{
  os << "healed";
  return os;
}

inline std::ostream& operator<<(std::ostream& os, const saving_throw_success& event)
{
  os << "saved by a throw";
  return os;
}

inline std::ostream& operator<<(std::ostream& os, const saving_throw_critical_success& event)
{
  os << "saved by a critical successefull throw";
  return os;
}

inline std::ostream& operator<<(std::ostream& os, const saving_throw_failure& event)
{
  os << "failed a throw";
  return os;
}

// flag
struct is_dying {};
struct is_alive {};
struct is_dead {};

// states
struct Alive : boost::msm::front::state<>
{
  using flag_list = boost::mpl::vector<is_alive>;
  template <typename Event, typename Fsm>
  void on_entry(const Event& event, Fsm&)
  {
    std::cout << "Alive::on_entry. Your personage " << event << std::endl;
  }
  template <typename Event, typename Fsm>
  void on_exit(const Event&, Fsm&)
  {
    std::cout << "Alive::on_exit" << std::endl;
  }
};

struct Dying : boost::msm::front::state<>
{
  using flag_list = boost::mpl::vector<is_dying>;
  template <typename Event, typename Fsm>
  void on_entry(const Event& event, Fsm&)
  {
    std::cout << "Dying::on_entry. You personage " << event << std::endl;
  }
  template <typename Event, typename Fsm>
  void on_exit(const Event&, Fsm&)
  {
    std::cout << "Dying::on_exit" << std::endl;
  }
};

struct Dead : boost::msm::front::state<>
{
  using flag_list = boost::mpl::vector<is_dead>;
  template <typename Event, typename Fsm>
  void on_entry(const Event& event, Fsm&)
  {
    std::cout << "Dead::on_entry. Your personage " << event << std::endl;
  }
  template <typename Event, typename Fsm>
  void on_exit(const Event&, Fsm&)
  {
    std::cout << "Dead::on_exit" << std::endl;
  }
};


class DeathStateMachineFrontend : public boost::msm::front::state_machine_def<DeathStateMachineFrontend>
{
  using Self = DeathStateMachineFrontend;

public:
  using initial_state = Alive;

  /// @note Carefully. You chould pass an object to backend ctor by using @c std::ref or @c boost::ref
  explicit DeathStateMachineFrontend(const GPersonage& pers) : m_pers(pers) { }

private:
  // actions
  template <typename Event> void become_dead(const Event&);
  void become_dying(const damaged&);
  void dying(const saving_throw_success&);
  void dying(const saving_throw_failure&);
  template <typename Event> void become_alive(const Event&);

  // guards
  bool have_more_attempts(const saving_throw_failure&);
  bool no_more_attempts(const saving_throw_failure&);
  bool too_bad_damage(const damaged&);
  bool not_too_bad_damage(const damaged&);

protected:
  /// @todo I think it's better to use more generic @c Row frontend
  /*
  template <typename ... T>
  using Row = boost::msm::front::Row<T...>;
  */

  struct transition_table : boost::mpl::vector<
    //       Start            Event                Next         Action                  Guard
    // -----+-----+------------------------------+------+--------------------+---------------------------+
        row< Alive, damaged,                       Dead,  &Self::become_dead,  &Self::too_bad_damage     >
    ,   row< Alive, damaged,                       Dying, &Self::become_dying, &Self::not_too_bad_damage >
    , a_row< Dying, saving_throw_success,          Dying, &Self::dying                                   >
    ,   row< Dying, saving_throw_failure,          Dying, &Self::dying,        &Self::have_more_attempts >
    ,   row< Dying, saving_throw_failure,          Dead,  &Self::become_dead,  &Self::no_more_attempts   >
    , a_row< Dying, saving_throw_critical_success, Alive, &Self::become_alive                            >
    ,   row< Dying, damaged,                       Dead,  &Self::become_dead,  &Self::too_bad_damage     >
    , a_row< Dying, healed,                        Alive, &Self::become_alive                            >
  > {};

  static const unsigned MAX_ATTEMPTS = 2; // 3 saving throws (note: 2 is a counter)
  unsigned short m_attempts = MAX_ATTEMPTS;
  const GPersonage& m_pers;

};


template <typename Event>
inline void DeathStateMachineFrontend::become_dead(const Event&)
{
  std::cout << "    Oops! Your personage is dead" << std::endl;
}

inline void DeathStateMachineFrontend::become_dying(const damaged&)
{
  std::cout << "    Carefully! Your personage is dying" << std::endl;
}

inline void DeathStateMachineFrontend::dying(const saving_throw_success&)
{
  std::cout << "    Your personage still dying" << std::endl;
}

inline void DeathStateMachineFrontend::dying(const saving_throw_failure&)
{
  m_attempts -= 1;
  std::cout << "    Your personage is on one step closer to death" << std::endl;
}

template <typename Event>
inline void DeathStateMachineFrontend::become_alive(const Event&)
{
  m_attempts = MAX_ATTEMPTS;
  std::cout << "    Wow! You personage is stable again" << std::endl;
}

inline bool DeathStateMachineFrontend::have_more_attempts(const saving_throw_failure&)
{
  std::cout << "More attempts: " << m_attempts << std::endl;
  return 0 != m_attempts;
}

inline bool DeathStateMachineFrontend::no_more_attempts(const saving_throw_failure&)
{
  std::cout << "No more attempts: " << m_attempts << std::endl;
  return 0 == m_attempts;
}

inline bool DeathStateMachineFrontend::too_bad_damage(const damaged&)
{
  std::cout << "is_too_bad: " << (m_pers.hp() <= (-int(m_pers.bloodied_hp()))) << std::endl;
  std::cout << "hp: " << m_pers.hp() << std::endl;
  std::cout << "bhp: " << m_pers.bloodied_hp() << std::endl;
  std::cout << "mhp: " << m_pers.max_hp() << std::endl;
  return m_pers.hp() <= -int(m_pers.bloodied_hp());
}

inline bool DeathStateMachineFrontend::not_too_bad_damage(const damaged&)
{
  std::cout << "is_not_too_bad: " << (m_pers.hp() > (-int(m_pers.bloodied_hp()))) << std::endl;
  std::cout << "hp: " << m_pers.hp() << std::endl;
  std::cout << "bhp: " << m_pers.bloodied_hp() << std::endl;
  std::cout << "mhp: " << m_pers.max_hp() << std::endl;
  return m_pers.hp() > -int(m_pers.bloodied_hp());
}


using DeathStateMachine = boost::msm::back::state_machine<DeathStateMachineFrontend>;
