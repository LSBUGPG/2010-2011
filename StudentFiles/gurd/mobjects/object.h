class object {
public:
	virtual void reset() = 0;
	virtual void update(float time) = 0;
	virtual void draw() = 0;
};

class object_function {
public:
	virtual void call(object & instance) = 0;
};

class object_collection: public object {
	
protected:
	virtual void for_each_object(object_function & function) = 0;
public:
	void reset();
	void update(float time);
	void draw();
};
