#ifndef JVECTOR2_H
#define JVECTOR2_H

#include "math.h"

class Jvector2
{
	public:
		float x;
		float y;

		Jvector2(): x(0), y(0) {} // ?
		Jvector2(const float X, const float Y): x(X), y(Y) {}
		Jvector2(const Jvector2 &v)
		{
			x = v.x;
			y = v.y;
		}
		~Jvector2(){};
		
		void invert()
		{
			x = -x;
			y = -y;
		}

		float length() const
		{
			// Phytagoras sats
			return sqrt( x*x + y*y );
		}

		void normalize()
		{
			float l = length();
			if( l > 0 )
			{
				(*this) *= ((float)1/l);
			}
		}

		/* operatoröverlagring */
		void operator*=(const float value)
		{
			x *= value;
			y *= value;
		}

		Jvector2 operator*(const float value) const
		{
			return Jvector2(x*value,y*value);
		}

		Jvector2 increaseLength( const float value ) const
		{
			return Jvector2(x*value,y*value);
		}

		void operator+=(const Jvector2 &v)
		{
			x += v.x;
			y += v.y;
		}
		Jvector2 operator+(const Jvector2 &v) const
		{
			return Jvector2( x+v.x, y+v.y );
		}

		void operator-=(const Jvector2 &v)
		{
			x -= v.x;
			y -= v.y;
		}
		Jvector2 operator-(const Jvector2 &v) const
		{
			return Jvector2( x-v.x, y-v.y );
		}

		Jvector2 componentProduct(const Jvector2 &v) const
		{
			return Jvector2( x*v.x, y*v.y );
		}

		float scalarProduct( const Jvector2 &v ) const
		{
			return x*v.x+y*v.y;
		}
		float dotProduct( const Jvector2 &v ) const
		{
			return scalarProduct(v);
		}

		Jvector2 crossProduct( const Jvector2 &v ) const
		{
			// ?
		}

	private:
		//..
};

#endif