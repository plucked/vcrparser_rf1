#ifndef Vector3_h__
#define Vector3_h__

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3() : x(0), y(0), z(0) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector3(const Vector3& other) { x = other.x; y = other.y; z = other.z; }
	Vector3& operator=(const Vector3& other) {  x = other.x; y = other.y; z = other.z; return *this; }

	static Vector3 Substract(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	static float Distance(const Vector3& a, const Vector3& b)
	{
		Vector3 s = Substract(a, b);
		return sqrtf((s.x * s.x) + (s.y * s.y) + (s.z * s.z));
	}

	bool InRange(float range)
	{
		return (x > -range && x < range &&
				y > -range && y < range &&
				z > -range && z < range);
	}
};
#endif // Vector3_h__
