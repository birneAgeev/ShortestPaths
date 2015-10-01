#pragma once

struct Arc {
public:
	Arc();
	Arc(int start, int end, int weight);
	int GetStart() const;
	int GetEnd() const;
	int GetWeight() const;

	bool operator< (const Arc &arc) const;
private:
	int Start;
	int End;
	int Weight;
};

struct Link {
public:
	Link();
	Link(int target, int weight);
	int GetTarget() const;
	int GetWeight() const;

	bool operator< (const Link &link) const;
private:
	int Target;
	int Weight;
};
