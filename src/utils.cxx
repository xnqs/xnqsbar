#include <cstdio>
#include <cstring>
#include <X11/Xutil.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

namespace xnqs {
// finds the "index" of the msb, or floor(log2(val)) if you will
// O(log(logN))
int msb(int val) {
	int ret = 0;
	for (int step = 16; step > 0; step >>= 1) {
		if (val>>(ret+step)) {
			ret += step;
		}
	}
	return ret;
}

void set_wm_name(const char* new_name) {
    Display *display;
    Window root;
    XTextProperty text_prop;

    // Open display
    display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "Unable to open X display\n");
        return;
    }

    // Get the root window
    root = DefaultRootWindow(display);

    // Set the new name
    text_prop.value = (unsigned char *)new_name;
    text_prop.encoding = XA_STRING;
    text_prop.format = 8;
    text_prop.nitems = strlen(new_name);

    XSetTextProperty(display, root, &text_prop, XA_WM_NAME);

    // Flush and close display
    XFlush(display);
    XCloseDisplay(display);
}
} // namespace xnqs
