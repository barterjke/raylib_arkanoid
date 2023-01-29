#pragma once

void scale_texture(Texture &texture, float scale_factor) {
    texture.width *= scale_factor;
    texture.height *= scale_factor;
}

Color random_color() {
    return Color{(unsigned char) (rand() % 256), (unsigned char) (rand() % 256),
                 (unsigned char) (rand() % 256), 255};
}