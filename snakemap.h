#ifndef SNAKEMAP_H
#define SNAKEMAP_H
#include <QtCore>
#include <set>
class SnakeMap {
   public:
    SnakeMap(int s_width, int m_quater_width);
    void generateFood();
    void eraseFood(double old_food_pos_x, double old_food_pos_y);
    const std::set<std::pair<double, double>> getFoodPosSet() const;
    bool hasFoodat(double pos_x, double pos_y);

   private:
    std::set<std::pair<double, double>> food_set;
    int snake_width;
    int map_quater_width;
};

#endif  // SNAKEMAP_H
