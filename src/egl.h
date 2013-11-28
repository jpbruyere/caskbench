#ifndef __EGL_H__
#define __EGL_H__

typedef struct {
  Display   *dpy;
  Window     window;

  EGLDisplay egl_display;
  EGLContext egl_context;
  EGLSurface egl_surface;
} egl_state_t;

bool createEGLContextAndWindow(egl_state_t *state, int width, int height);
void destroyEGLContextAndWindow(egl_state_t *state);

#endif // __EGL_H__
