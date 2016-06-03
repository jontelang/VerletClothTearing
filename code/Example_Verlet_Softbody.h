#ifndef Example_Verlet_Softbody_H
#define Example_Verlet_Softbody_H

#include "Allegro.h"
#include "Jvector2.h"
#include "JVerletPoint.h"
#include "JVerletConstraint.h"
#include <vector>
using namespace std;

class Example_Verlet_Softbody
{
	public:
		vector<JVerletPoint*> points;
		vector<JVerletConstraint*> constraints;
		float G;

		JVerletPoint *mouse_point;
		JVerletFixedLengthConstraint *mouse_point_constraint;
		int mouse_radius;
		bool isDown;
		vector<JVerletPoint*> grabbed_balls;
		vector<JVerletFixedLengthConstraint*> dragconstraints;

		static const int POINTS = 20;

		int snapped;

		Example_Verlet_Softbody()
		{
			// Gravity
			G = 45.667f;

			// Temp stuff for dragging
			mouse_point = new JVerletPoint(Jvector2(),10,10);
			mouse_point_constraint = new JVerletFixedLengthConstraint( mouse_point, mouse_point );
			mouse_point_constraint->restDistance = 5;
			mouse_radius = 15;
			isDown = false;

			// Skapa points
			for( int i = 0; i < POINTS; i++ )
				points.push_back( new JVerletPoint( Jvector2( 400 + cos((float)i)*50 ,400 +sin((float)i)*50 ), 2, 2 ) );
			
			// .. And then constraints
			for(int i=0;i<POINTS-1;i++)
			for(int j=POINTS-1;j>0;j--)
				constraints.push_back(new JVerletFixedLengthConstraint(points[i],points[j]));
		}

		void update( float dt )
		{
			// Clear / add forces 
			for( int i = 0; i < points.size(); i++ )
			{
				points[i]->clearForce();
				points[i]->addForce(Jvector2(0, G * points[i]->mass));

				if( key[KEY_UP] )	 points[POINTS-1]->addForce( Jvector2(0, -2) );
				if( key[KEY_DOWN] )  points[POINTS-1]->addForce( Jvector2(0,  2) );
				if( key[KEY_LEFT] )  points[POINTS-1]->addForce( Jvector2(-2, 0) );
				if( key[KEY_RIGHT] ) points[POINTS-1]->addForce( Jvector2( 2, 0) );
			}
			
			// Apply constraints
			for( int i = 0; i < constraints.size(); i++ )
			{
				constraints[i]->apply();
			}
			for( int i = 0; i < dragconstraints.size(); i++ )
			{
				dragconstraints[i]->apply();
			}

			// Mouse
			mouse_point->position.x = (int)mouse_x;
			mouse_point->position.y = (int)mouse_y;
			if( (mouse_b & 1) && !isDown )
			{
				isDown = true;
				for( int i = 0; i < points.size(); i++ )
				{
					float dist_to_current = (points[i]->position - Jvector2((int)mouse_x,(int)mouse_y)).length();
					if( dist_to_current < mouse_radius )
						grabbed_balls.push_back( points[i] );
				}
				for( int i = 0; i < grabbed_balls.size(); i++ )
					dragconstraints.push_back( new JVerletFixedLengthConstraint( grabbed_balls[i], mouse_point, 0, 0.05f, 25 ) );
					
			}
			else if( !(mouse_b & 1) && isDown )
			{
				isDown = false;
				mouse_point_constraint->a = mouse_point_constraint->a;
				dragconstraints.clear(); // borde deleta här menmen
				grabbed_balls.clear();
			}

			// Kollision
			for( int i = 0 ; i < points.size(); i++ )
			{
				if( points[i]->position.y > 600 )
				{
					points[i]->position.y = 600;
				}
			}

			// Update (STEP = 0.01f) .. Then draw
			for( int i = 0; i < points.size(); i++ )
			{
				points[i]->update( dt );
			}
		}

		BITMAP* draw( BITMAP *buf )
		{
			circle( buf, (int)mouse_x,(int)mouse_y,mouse_radius,makecol(0,0,0));
			for( int i = 0; i < constraints.size(); i++ )
			{
				if( JVerletFixedLengthConstraint* e = dynamic_cast<JVerletFixedLengthConstraint*>(constraints[i]) )
					line(buf,e->a->position.x,e->a->position.y,e->b->position.x,e->b->position.y,makecol(0,0,0));
			}
			for( int i = 0; i < dragconstraints.size(); i++ )
			{
				line(buf,dragconstraints[i]->a->position.x,dragconstraints[i]->a->position.y,dragconstraints[i]->b->position.x,dragconstraints[i]->b->position.y,makecol(0,0,0));
			}
			for( int i = 0; i < points.size(); i++ )
			{
				circle( buf, points[i]->position.x,points[i]->position.y,points[i]->radius,makecol(0,0,0));
			}
			return buf;
		}

};

#endif