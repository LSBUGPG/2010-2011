#include "state.h"

class state_machine: public object_wrapper {
     state * initial;
     class state_applicator: public applicator_object {
          state * current;
     public:
          state_applicator(void): current(0) {
          }
          void apply(const object_function & function) {
               if (current) {
                    function.call(*current);
               }
          }
          void change(state * next) {
               if (current) {
                    current->leave();
               }
               if (next) {
                    next->enter();
               }
               current = next;
          }
     } apply_to_state;
protected:
     applicator_object & applicator(void) {
          return apply_to_state;
     }
public:
     state_machine(state * first_state): initial(first_state) {
          change_state(initial);
     }

     void change_state(state * next) {
          apply_to_state.change(next);
     }

     void reset(void) {
          change_state(initial);
     }
};

static state * load_states(void)
{
     state * state_array[] = {
          legal_state(),
          logo_state(),
          title_state(),
     };
     return state_array[0];
}

static state_machine & shell_state_machine(void)
{
     static state_machine instance(load_states());
     return instance;
}

void change_state(state * next)
{
     shell_state_machine().change_state(next);
}

object * load_shell(void)
{
     return &shell_state_machine();
}
