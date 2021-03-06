#include "positionc.h"

#include <SDL2/SDL.h>

#include "../entity.h"
#include "../event.h"

static void update(Component *self, Entity *e, int dt) {
    SDL_Rect s = *(SDL_Rect*)self->data;
    if (s.x + s.w < 0 || s.x > 1024 || s.y + s.h < 0 || s.y > 768) {
        if (e->id == 2)
        {
            printf("ID is 2\n");
        }
        printf("Deleting %d\n", e->id);
        delete_entity(e->id);
    }
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


Component new_positionc(Entity *e, int x, int y, int w, int h) {
    Component ret = c_make(e, update, cleanup, receive, NULL);
    ret.data = malloc(sizeof(SDL_Rect));

    *(SDL_Rect*)ret.data = (SDL_Rect){.x = x, .y = y, .w = w, .h = h};
    return ret;
}
