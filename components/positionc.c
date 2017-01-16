#include "positionc.h"

#include <SDL2/SDL.h>

#include "../entity.h"
#include "../event.h"

static void update(Component *self, Entity *e, int dt) {
    
}

static void cleanup(Component *self) {
    free(self->data);
}

static void move(Component *self, EventData d) {
    SDL_Rect *r = (SDL_Rect*)d.data;
        SDL_Rect *s = (SDL_Rect*)self->data;
    s->x = r->x;
    s->y = r->y;
}

static void move_rel(Component *self, EventData d) {
    SDL_Rect *r = (SDL_Rect*)d.data;

    SDL_Rect *s = (SDL_Rect*)self->data;
    s->x += r->x;
    s->y += r->y;
    s->w += r->w;
    s->h += r->h;
}

static void receive(Component *self, Event e) {
    receivecb callbacks[] = {move, move_rel};

    callbacks[e.t](self, e.d);
}


Component new_positionc(int x, int y, int w, int h) {
    Component ret = {.update = update, .cleanup = cleanup, .receive = receive};
    ret.data = malloc(sizeof(SDL_Rect));

    *(SDL_Rect*)ret.data = (SDL_Rect){.x = x, .y = y, .w = w, .h = h};
    return ret;
}