#ifndef ROOM_H
#define ROOM_H

#include <bn_regular_bg_ptr.h>
#include <bn_fixed_rect.h>

namespace game
{
    // Handles a single room's background and its boundaries
    class Room
    {
    public:
        Room();
        ~Room();

        // Initialize room with a background and its position
        void create(const bn::regular_bg_ptr& bg, const bn::fixed_rect& boundaries);

        // Destroys the room resources
        void destroy();

        // Sets the collision/visibility boundaries of the room
        void set_boundaries(const bn::fixed_rect& boundaries);

        // Retrieves current boundaries
        const bn::fixed_rect& boundaries() const;

        // Update logic for this room (if any)
        void update();

        // Renders the room's background to screen
        void render() const;

    private:
        bn::regular_bg_ptr _background;
        bn::fixed_rect _boundaries;
        bool _active;
    };
}

#endif // ROOM_H
