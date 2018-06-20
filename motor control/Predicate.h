class Predicate {
public:
	virtual Predicate() {};
	virtual ~Predicate() {};

	virtual bool check() const = 0;
}

class WallPredicate : public Predicate {
	virtual bool check() override {
		return sensor.distance() < 10;
	};	
}