#ifndef object_h
#define object_h

class object {
public:
     virtual void reset(void) = 0;
     virtual void update(float time) = 0;
     virtual void draw(void) = 0;
};

class object_function {
public:
     virtual void call(object & instance) const = 0;
};

class test_function {
public:
     virtual bool test(object & instance) const = 0;
};

class applicator_object {
public:
     virtual void apply(const object_function & function) = 0;
};

class object_wrapper: public object {
     class reset_function: public object_function {
     public:
          void call(object & instance) const {
               instance.reset();
          }
     };

     class update_function: public object_function {
          float time;
     public:
          update_function(float elapsed_time): time(elapsed_time) {
          }
          void call(object & instance) const {
               instance.update(time);
          }
     };

     class draw_function: public object_function {
     public:
          void call(object & instance) const {
               instance.draw();
          }
     };
protected:
     virtual applicator_object & applicator(void) = 0;
public:
     void reset(void) {
          applicator().apply(reset_function());
     }
     void update(float time) {
          applicator().apply(update_function(time));
     }
     void draw(void) {
          applicator().apply(draw_function());
     }
};

class abstract_object: public object_wrapper {
     class instance_applicator: public applicator_object {
          object & instance;
     public:
          instance_applicator(object & source): instance(source) {
          }
          void apply(const object_function & function) {
               function.call(instance);
          }
     } apply_to_instance;
protected:
     applicator_object & applicator(void) {
          return apply_to_instance;
     }
public:
     abstract_object(object & instance): apply_to_instance(instance) {
     }
};

#endif
