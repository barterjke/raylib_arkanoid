#pragma once

struct AABB {
    vec2 position;
    vec2 size;
};

bool check_lines_collisions(vec2 p1, vec2 p2, vec2 p3, vec2 p4) {
    float u_a = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) /
                ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));
    float u_b = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) /
                ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));
    return (u_a >= 0 && u_a <= 1 && u_b >= 0 && u_b <= 1);
}

vec2 get_lines_intersection(vec2 p1, vec2 p2, vec2 p3, vec2 p4) {
    float u_a = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) /
                ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));
    float u_b = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) /
                ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));
    if (u_a >= 0 && u_a <= 1 && u_b >= 0 && u_b <= 1)
        return vec2{p1.x + (u_a * (p2.x - p1.x)), p1.y + (u_a * (p2.y - p1.y))};
    return {numeric_limits<float>::max(),numeric_limits<float>::max()};
}

enum CollisionType{
    HORIZONTAL,
    VERTICAL,
    NONE
};

tuple<CollisionType, vec2> check_box_line_collision(const AABB &box, vec2 p1, vec2 p2) {
    auto horizontal_intersection_point = p1.x < box.position.x ?
            // left side
            get_lines_intersection(p1, p2, box.position, box.position + vec2(0, box.size.y)) :
            // right side
            get_lines_intersection(p1, p2, box.position + vec2(box.size.x, 0),box.position + vec2(box.size.x, box.size.y));
    auto vertical_intersection_point = p1.y < box.position.y ?
            // up
            get_lines_intersection(p1, p2, box.position, box.position + vec2(box.size.x, 0)) :
            // down
            get_lines_intersection(p1, p2, box.position + vec2(0, box.size.y), box.position + vec2(box.size.x, box.size.y));
    if (glm::distance(p1, vertical_intersection_point) > 20000 && glm::distance(p1, horizontal_intersection_point) > 20000){
        return {NONE, vec2(0,0)};
    }
    return glm::distance(p1, vertical_intersection_point) < glm::distance(p1, horizontal_intersection_point) ?
           tuple{VERTICAL, vertical_intersection_point} : tuple{HORIZONTAL, horizontal_intersection_point};
}


bool check_collision(const AABB &one, const AABB &two) {
    // AABB - AABB collision
    // collision x-axis?
    bool collision_x = one.position.x + one.size.x >= two.position.x &&
                       two.position.x + two.size.x >= one.position.x;
    // collision y-axis?
    bool collision_y = one.position.y + one.size.y >= two.position.y &&
                       two.position.y + two.size.y >= one.position.y;
    // collision only if on both axes
    return collision_x && collision_y;
}