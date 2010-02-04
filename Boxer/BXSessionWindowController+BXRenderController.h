/* 
 Boxer is copyright 2009 Alun Bestor and contributors.
 Boxer is released under the GNU General Public License 2.0. A full copy of this license can be
 found in this XCode project at Resources/English.lproj/GNU General Public License.txt, or read
 online at [http://www.gnu.org/licenses/gpl-2.0.txt].
 */


//The BXRenderController category separates off rendering-specific functionality from general
//window controller housework. The methods herein liaise between BXRenderView and BXEmulator, pass UI
//signals back to BXEmulator, and manage resizing to ensure that the view size and rendering size
//are consistent.

#import <Cocoa/Cocoa.h>
#import "BXSessionWindowController.h"

@class BXSessionWindow;
@class BXEmulator;
@class BXRenderView;

@interface BXSessionWindowController (BXRenderController)

//Notification observers
//----------------------

//These listen for any time an NSMenu opens or closes, and warn the active emulator
//to pause or resume emulation. In practice this means muting it to avoid hanging
//music and sound effects while the menu is blocking the thread.
//TODO: BXEmulator itself should handle this at a lower level by watching out for
//whenever a new event loop gets created.
- (void) menuDidOpen:	(NSNotification *) notification;
- (void) menuDidClose:	(NSNotification *) notification;


//Window sizing methods
//---------------------

- (NSSize) renderViewSize;

//Returns the view size that should be used for rendering the specified DOSBox output size.
//This information is used by BXEmulator for telling SDL how big a surface to create.
- (NSSize) viewSizeForRenderedSize: (NSSize)renderedSize minSize: (NSSize)minViewSize;

//Resize the window to accomodate the specified view size. Returns YES if a resize was possible,
//or NO if there is not enough room onscreen to do so.
//Currently this is called when choosing a new filter to resize the window if it is smaller than
//the filter's minimum size.
- (BOOL) resizeToAccommodateViewSize: (NSSize) minViewSize;

//Zoom in and out of fullscreen mode with a smooth window sizing animation.
- (void) setFullScreenWithZoom: (BOOL) fullScreen;

@end


//Methods in this category are not intended to be called outside of BXSessionWindowController.
@interface BXSessionWindowController (BXSessionWindowControllerInternals)

//Performs the slide animation used to toggle the status bar and program panel on or off
- (void) _slideView: (NSView *)view shown: (BOOL)show;

//Resize the window frame to fit the new render size.
- (void) _resizeWindowForRenderViewSize: (NSSize)newSize animate: (BOOL)performAnimation;


//Responding to SDL's entreaties
//------------------------------
- (NSOpenGLView *) SDLView;
- (NSWindow *) SDLWindow;
- (NSOpenGLContext *) SDLOpenGLContext;

- (void) prepareSDLViewForFullscreen;
- (void) prepareSDLOpenGLContextForTeardown;
- (void) prepareSDLViewForFrame: (NSRect)frame;
- (void) prepareSDLOpenGLContextWithFormat: (NSOpenGLPixelFormat *)format;
- (BOOL) handleSDLKeyboardEvent: (NSEvent *)event;

@end