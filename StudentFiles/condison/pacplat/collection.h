#include "object.h"

class collection {
public:
     virtual void for_each_object(const object_function & function) = 0;
     virtual bool find_object(const test_function & function) = 0;
};

template <typename type> //name can be changed
class object_array: public collection {
     type * begin;
     type * end;
public:
     object_array(type * array_begin, type * array_end):
          begin(array_begin), end(array_end) {
     }
     void for_each_object(const object_function & function) {
          type * instance = begin;
          while (instance != end) {
               function.call(*instance);
               instance++;
          }
     }
     bool find_object(const test_function & function) {
          type * instance = begin;
          bool done = false;
          while (instance != end && !done) {
               done = function.test(*instance);
               instance++;
          }
          return done;
     }
};

template <typename type>
class object_pool: public collection {
     type * begin;
     type * free;
     type * end;
public:
     object_pool(type * array_begin, type * array_end):
          begin(array_begin), free(array_begin), end(array_end) {
     }
     bool add(const type & new_object) {
          bool added = false;
          if (free != end) {
               *free = new_object;
               free++;
               added = true;
          }
          return added;
     }
     void remove(type & entry) {
          if (free != begin) {
               free--;
               entry = *free;
          }
     }
     void for_each_object(const object_function & function) {
          type * instance = begin;
          type * current_end = free;
          while (instance != current_end) {
               function.call(*instance);
               if (current_end != free) {
                    current_end = free;
               } else {
                    instance++;
               }
          }
     }
     bool find_object(const test_function & function) {
          type * instance = begin;
          type * current_end = free;
          bool done = false;
          while (instance != current_end && !done) {
               done = function.test(*instance);
               if (current_end != free) {
                    current_end = free;
               } else {
                    instance++;
               }
          }
          return done;
     }
};

class collection_object: public object_wrapper {
     class collection_applicator: public applicator_object {
          collection & instance;
     public:
          collection_applicator(collection & source): instance(source) {
          }
          void apply(const object_function & function) {
               instance.for_each_object(function);
          }
     } apply_to_collection;
protected:
     applicator_object & applicator(void) {
          return apply_to_collection;
     }
public:
     collection_object(collection & source): apply_to_collection(source) {
     }
};
