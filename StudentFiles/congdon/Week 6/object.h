class object {                 
public:
	virtual void reset() = 0;
	virtual void update(float time) = 0;
	virtual void draw() = 0;          // all this is abstract object, virtual, dont exsists yet, place holder, anything based on these must has these 3 things
};

class object_function {                  // serves as an intermediate, represents the function
public:
	virtual void call(object & instance) = 0;   //call fuction does something
};

class object_collection: public object {           
	
protected:
	virtual void for_each_object(object_function & function) = 0;      //goes through and calls a function on each item
public:
	void reset();
	void update(float time);
	void draw();
};
