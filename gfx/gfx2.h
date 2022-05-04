// gfx2.h

#ifndef GFX2_H
#define GFX2_H

#include <X11/Xlib.h>
#include <X11/cursorfont.h> 

// Open a new graphics window. 
void gfx_open( int width, int height, const char *title );

// Flush all previous output to the window. 
void gfx_flush();

// Change the current drawing color. 
void gfx_color( int red, int green, int blue );

// Clear the graphics window to the background color. 
void gfx_clear();

// Change the current background color. 
void gfx_clear_color( int red, int green, int blue );

// Check to see if an event is waiting. 
int gfx_event_waiting();

// Wait for the user to press a key or mouse button. 
char gfx_wait();

// Return the X and Y coordinates of the last event. 
int gfx_xpos();
int gfx_ypos();

// Return the X and Y dimensions of the screen (monitor). 
int gfx_xsize();
int gfx_ysize();

// Draw a point at (x,y) 
void gfx_point( int x, int y );

// Draw a line from (x1,y1) to (x2,y2) 
void gfx_line( int x1, int y1, int x2, int y2 );

// Draw a circle centered at (xc,yc) with radius r 
void gfx_circle( int xc, int yc, int r );

// Display a string at (x,y) 
void gfx_text( int x, int y , const char *text );

// -----------------------------
// new functions added 4/15/22:
// -----------------------------

// Draw a filled circle centered at (xc,yc) with radius r 
void gfx_fill_circle( int xc, int yc, int r );

// Draw an ellipse centered at (xc,yc) with radii r1 and r2 
void gfx_ellipse( int xc, int yc, int r1, int r2 );
 
// Draw an arc whose top left corner of its bounding rectangle is at (x,y),
//  with width w and height h, starting at angle a1 and sweeping an angle of a2 (degrees);
//  a1 of 0 is at the 3 O'Clock position, and the a2 sweep is positive counter-clockwise 
void gfx_arc( int x, int y, int w, int h, int a1, int a2 );

// Draw a filled arc (similar description to gfx_arc)
void gfx_fill_arc( int x, int y, int w, int h, int a1, int a2 );

// Draw a rectangle with top-left corner at (x,y) with width w and height h 
void gfx_rectangle( int x, int y, int w, int h );

// Draw a filled rectangle (similar description to gfx_rectangle)
void gfx_fill_rectangle( int x, int y, int w, int h );

// Draw a polygon whose "num_pts" number of corners are in the "pointsarr" array
//  (note: uses Xlib's XPoint struct) 
void gfx_polygon( XPoint *pointsarr, int num_pts );

// Draw a filled polygon (similar description to gfx_polygon)
void gfx_fill_polygon( XPoint *pointsarr, int num_pts );

// Change the font that gfx_text will use 
//  (see the file /usr/share/X11/fonts/misc/fonts.alias for possible fonts)
void gfx_changefont( char * );

// change the cursor (mouse pointer)
//  (see the file /usr/include/X11/cursorfont.h for possible cursors)
void gfx_changecursor( int );

#endif

