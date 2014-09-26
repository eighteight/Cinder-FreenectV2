#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderFreenectV2App : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void CinderFreenectV2App::setup()
{
}

void CinderFreenectV2App::mouseDown( MouseEvent event )
{
}

void CinderFreenectV2App::update()
{
}

void CinderFreenectV2App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( CinderFreenectV2App, RendererGl )
