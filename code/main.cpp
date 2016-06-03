#include "Allegro.h"
#include <string>
#include <sstream>
#include "Jvector2.h"
#include "Example_Verlet_Cloth.h"
#include "Example_Verlet_Softbody.h"
using namespace std;

FONT	*myfont;
BITMAP	*buf;

const static float STEP = 0.05f;

string to_str( int i )
{
	int var = i;
	stringstream ss;
	ss << var;
	return ss.str();
}
string to_str( double i )
{
	double var = i;
	stringstream ss;
	ss << var;
	return ss.str();
}
string to_str( float i )
{
	float var = i;
	stringstream ss;
	ss << var;
	return ss.str();
}
void text( string txt, int x, int y )
{
	textout( buf, myfont, txt.c_str(), x, y, makecol( 255,255,255 ) );
}

void img( BITMAP *bmp, int x, int y )
{
	draw_sprite( buf, bmp, x, y );
}

void dot( BITMAP *bmp, int x, int y)
{
	circle(bmp, x, y, 2, makecol(255,0,0));
}
void dot( BITMAP *bmp, Jvector2 &v)
{
	circle(bmp, v.x, v.y, 2, makecol(255,0,0));
}
void dot( BITMAP *bmp, Jvector2 &v, int r, int)
{
	circle(bmp, v.x, v.y, r, makecol(255,0,0));
}
void dot( BITMAP *bmp, Jvector2 &v, int r, int COLOR, int)
{
	circle(bmp, v.x, v.y, r, COLOR);
}
void dot( BITMAP *bmp, Jvector2 &v, int COLOR)
{
	circle(bmp, v.x, v.y, 2, COLOR);
}
void linje( BITMAP *bmp, Jvector2 &v0, Jvector2 &v1 )
{
	line( bmp, v0.x, v0.y, v1.x, v1.y, makecol(255,0,0) );
}
void linje( BITMAP *bmp, Jvector2 &v0, Jvector2 &v1, int COLOR )
{
	line( bmp, v0.x, v0.y, v1.x, v1.y, COLOR );
}
void coord( BITMAP *bmp, Jvector2 &v )
{
	text("("+to_str(v.x)+","+to_str(v.y)+")",v.x+10,v.y-5);
}




int main()
{
	// initera allegrostuff
	allegro_init();										// init allegro
	install_keyboard();									// Initialize keyboard routines
	install_mouse();
	set_color_depth(32);								// Set the color depth
	set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0);	// Change res.
	show_mouse(screen);
	buf		= create_bitmap(800,600);
	myfont	= load_font("f.pcx", NULL, NULL);

	Example_Verlet_Cloth*		ExVC	= new Example_Verlet_Cloth();
	Example_Verlet_Softbody*	ExVSb	= new Example_Verlet_Softbody();
	
	// Main loop
	while( ! key[KEY_ESC] )
	{
		// Clear screen
		rectfill(buf,0,0,800,600,makecol(245,245,245));

		// Update examples
		ExVC->update( STEP );
		//ExVSb->update( STEP );
		
		// Draw
		buf = ExVC->draw(buf);
		//buf = ExVSb->draw(buf);
		
		// Rita ut
		blit(buf, screen, 0, 0, 0, 0, 800, 600);
	}
 
return 0;
}
END_OF_MAIN();