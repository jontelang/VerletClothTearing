#ifndef Example_Verlet_Cloth_H
#define Example_Verlet_Cloth_H

#include "Allegro.h"
#include "Jvector2.h"
#include "JVerletPoint.h"
#include "JVerletConstraint.h"
#include <vector>
using namespace std;

class Example_Verlet_Cloth
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

		static const int POINTS = 25;

		int snapped;

		Example_Verlet_Cloth()
		{
			// Gravity
			G = 30.0f;

			// Temp stuff for dragging
			mouse_point = new JVerletPoint(Jvector2(),10,10);
			mouse_point_constraint = new JVerletFixedLengthConstraint( mouse_point, mouse_point );
			mouse_point_constraint->restDistance = 5;
			mouse_radius = 50;
			isDown = false;

			// Skapa points
			JVerletPoint* map[POINTS][POINTS];
			for( int i = 0; i < POINTS; i++ ) 
				for( int j = 0; j < POINTS; j++ ) 
				{
					map[i][j] = new JVerletPoint( Jvector2(150+10*i,50+10*j), 0.5f, 1 );
					points.push_back( map[i][j] );
				}
			// .. And then constraints
			for( int i = 0; i < POINTS; i++ )
			{
				for( int j = 0; j < POINTS-1; j++ )
				{
					constraints.push_back( new JVerletTearConstraint( map[i][j], map[i][j+1] ) );
					constraints.push_back( new JVerletTearConstraint( map[j][i], map[j+1][i] ) );
				}
			}
			for( int i = 0; i < POINTS-1; i++ )
			{
				for( int j = 0; j < POINTS-1; j++ )
				{
					constraints.push_back( new JVerletTearConstraint( map[i][j], map[i+1][j+1] ) );
					constraints.push_back( new JVerletTearConstraint( map[i+1][j], map[i][j+1] ) );
				}
			}
			/*for( int i = 0; i < POINTS-2; i++ )
			{
				for( int j = 0; j < POINTS-2; j++ )
				{
					constraints.push_back( new JVerletTearConstraint( map[i][j], map[i][j+2] ) );
					constraints.push_back( new JVerletTearConstraint( map[j][i], map[j+2][i] ) );
				}
			}*/
					
			/*constraints.push_back( new JVerletFixedPositionConstraint( map[0][0] ) );
			constraints.push_back( new JVerletFixedPositionConstraint( map[0][POINTS*POINTS-POINTS] ) );
			constraints.push_back( new JVerletFixedPositionConstraint( map[0][POINTS*POINTS/2] ) );
			constraints.push_back( new JVerletFixedPositionConstraint( map[0][POINTS*POINTS/4] ) );
			constraints.push_back( new JVerletFixedPositionConstraint( map[0][POINTS*POINTS/4+POINTS*POINTS/2] ) );
			*/for( int i = 0; i < POINTS; i++ )
				constraints.push_back( new JVerletFixedPositionConstraint( map[i][0] ) );

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

			// Update (STEP = 0.01f) .. Then draw
			for( int i = 0; i < points.size(); i++ )
			{
				points[i]->update( dt );
			}
		}

		BITMAP* draw( BITMAP *buf )
		{
			for( int i = 0; i < points.size(); i++ )
			{
				circle( buf, points[i]->position.x, points[i]->position.y, points[i]->radius, makecol(0,0,0) );
			}
			circle( buf, (int)mouse_x,(int)mouse_y,mouse_radius,makecol(0,0,0));
			for( int i = 0; i < constraints.size(); i++ )
			{
				if( JVerletTearConstraint* e = dynamic_cast<JVerletTearConstraint*>(constraints[i]) )
				{
					line(buf,e->a->position.x,e->a->position.y,e->b->position.x,e->b->position.y,makecol(e->getDistance(),255-e->getDistance(),255-e->getDistance()));
				}
			}
			//for( int i = 0; i < dragconstraints.size(); i++ )
			//{
			//	line(buf,dragconstraints[i]->a->position.x,dragconstraints[i]->a->position.y,dragconstraints[i]->b->position.x,dragconstraints[i]->b->position.y,makecol(0,0,0));
			//}
			return buf;
		}

};

#endif