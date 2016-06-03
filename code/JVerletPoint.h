#ifndef JVERLETPOINT_H
#define JVERLETPOINT_H

class JVerletPoint
{
	public:
		Jvector2	position;
		Jvector2	lastPosition;
		Jvector2	force;
		float		mass;
		int			radius;

		JVerletPoint()
		{
		}

		JVerletPoint(Jvector2 P, float M, int R)
		{
			position		= P;
			lastPosition	= position;
			mass			= M;
			radius			= R;
		}

		void addForce( Jvector2 f )
		{
			force += f;
		}

		void clearForce()
		{
			force = Jvector2();
		}

		void update( float step )
		{
			// F = ma
			// a = F / m
			Jvector2 temp = position;
			// x += x-oldx+a*fTimeStep*fTimeStep;
			//		2x - x* + a * step^2
			//		s(t+d)=2*s(t)-s(t-d)+s''(t)*t*t
			float damp = 0.9975f;
			position += (position - lastPosition) * damp + force * step * step;
			lastPosition = temp;
		}
};

#endif