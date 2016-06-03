#ifndef JVERLETCONSTRAINT_H
#define JVERLETCONSTRAINT_H

class JVerletConstraint
{
	public:
		virtual void apply()
		{
		}
};

class JVerletFixedLengthConstraint : public JVerletConstraint
{
	public:
		JVerletPoint *a;
		JVerletPoint *b;
		float restDistance;
		float stiffnessouter;
		float stiffnessinner;

		JVerletFixedLengthConstraint(JVerletPoint *A, JVerletPoint *B)
		{
			a				= A;
			b				= B;
			restDistance	= ( a->position - b->position ).length() + 1;	// +1 för att den inte ska SNAP! i början.
			stiffnessouter	= 0.5f;
			stiffnessinner  = 0.001f;
		}

		JVerletFixedLengthConstraint(JVerletPoint *A, JVerletPoint *B, float STIFFNESS)
		{
			a				= A;
			b				= B;
			restDistance	= ( a->position - b->position ).length();	// +1 för att den inte ska SNAP! i början.
			stiffnessouter	= STIFFNESS;
			stiffnessinner  = STIFFNESS;
		}

		JVerletFixedLengthConstraint(JVerletPoint *A, JVerletPoint *B, float STIFFNESS, int RESTLENGTH)
		{
			a				= A;
			b				= B;
			restDistance	= RESTLENGTH; // +1 för att den inte ska SNAP! i början.
			stiffnessouter	= STIFFNESS;
			stiffnessinner  = STIFFNESS;
		}

		JVerletFixedLengthConstraint(JVerletPoint *A, JVerletPoint *B, float STIFFNESSINNER, float STIFFNESSOUTER, int RESTLENGTH)
		{
			a				= A;
			b				= B;
			restDistance	= RESTLENGTH; // +1 för att den inte ska SNAP! i början.
			stiffnessouter	= STIFFNESSOUTER;
			stiffnessinner  = STIFFNESSINNER;
		}

		virtual void apply()
		{
			Jvector2 dir	= b->position - a->position;
			float distance	= dir.length();
			dir				.normalize();
			if( distance > restDistance)		dir *= (distance - restDistance) * stiffnessouter;
			else if( distance < restDistance )	dir *= (distance - restDistance) * stiffnessinner; 
			a->position		+= dir;
			b->position		-= dir;
		}
};

class JVerletTearConstraint : public JVerletFixedLengthConstraint
{
	public:

		float maxDistance;
		int curDistance;		

		JVerletTearConstraint(JVerletPoint *A, JVerletPoint *B): JVerletFixedLengthConstraint( A, B )
		{
			maxDistance	= restDistance * 2;
			curDistance	= 0;
		}

		virtual void apply()
		{
			// Now check the distance and snap if right..
			float distance	= (b->position - a->position).length();
			curDistance		= distance; // Uppdatera för att få ut den grafiska saken sen bah

			if( distance > maxDistance )
				b = a;

			// Apply the base-class's "apply"
			// .. so that the constraint sets
			// .. the right forces on the points
			this->JVerletFixedLengthConstraint::apply();
		}

		int getDistance()
		{
			if( curDistance < maxDistance )
			{
				float d = curDistance / maxDistance;
				return 255 * d;
			}
			else return 0;
		}
};

class JVerletFixedPositionConstraint : public JVerletConstraint
{
	public:
		JVerletPoint *a;

		JVerletFixedPositionConstraint(JVerletPoint *A)
		{
			a = A;
		}

		virtual void apply()
		{
			// Kan spara undan positionen annars
			// .. detta kanske är farligt?
			a->position = a->lastPosition;
		}
};

#endif