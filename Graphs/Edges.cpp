#include "Edges.h"

Arc::Arc() {
	Start = End = Weight = -1;
}

Arc::Arc(int start, int end, int weight) {
	Start = start;
	End = end;
	Weight = weight;
}

int Arc::GetStart() const {
	return Start;
}

int Arc::GetEnd() const {
	return End;
}

int Arc::GetWeight() const {
	return Weight;
}

bool Arc::operator<(const Arc& arc) const {
	return Start < arc.Start;
}

Link::Link() {
	Target = Weight = 0;
}

Link::Link(int target, int weight) {
	Target = target;
	Weight = weight;
}

int Link::GetTarget() const {
	return Target;
}

int Link::GetWeight() const {
	return Weight;
}

bool Link::operator<(const Link& link) const {
	return Target < link.Target;
}
