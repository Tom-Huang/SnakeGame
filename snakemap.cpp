#include "snakemap.h"

SnakeMap::SnakeMap(int s_width, int m_quater_map)
    : snake_width(s_width), map_quater_width(m_quater_map) {
    // initialize the food pos
    generateFood();
}

void SnakeMap::generateFood() {
    int food_pos_x = 0;
    int food_pos_y = 0;
    if (qrand() % 1) {
        food_pos_x = (qrand() % map_quater_width) * snake_width;
    } else {
        food_pos_x = (qrand() % -map_quater_width) * snake_width;
    }
    if (qrand() % 1) {
        food_pos_y = (qrand() % map_quater_width) * snake_width;
    } else {
        food_pos_y = (qrand() % -map_quater_width) * snake_width;
    }
    food_set.emplace(std::pair<double, double>(food_pos_x, food_pos_y));
}

void SnakeMap::eraseFood(double old_food_pos_x, double old_food_pos_y) {
    std::pair<double, double> pos(old_food_pos_x, old_food_pos_y);
    food_set.erase(pos);
}

const std::set<std::pair<double, double>> SnakeMap::getFoodPosSet() const {
    return food_set;
}

bool SnakeMap::hasFoodat(double pos_x, double pos_y) {
    std::pair<int, int> pos(pos_x, pos_y);
    return food_set.find(pos) != food_set.end() ? true : false;
}
