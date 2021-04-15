//
// Created by Hiesh on 2021/4/15.
//

#ifndef FREECIRCOS_SETTINGS_WINSCALE_H_
#define FREECIRCOS_SETTINGS_WINSCALE_H_

const static qreal g_scale = 1.5;
const static int g_app_base_width = 800;
const static int g_app_base_height = 350;
const static int button_box_pos_x = 5;
const static int button_box_pos_y = 5;
const static int button_box_width = 50;
const static int button_box_height = 20;
const static int button_gap_x = 5;
const static int button_gap_y = 5;

const static int bottom_margin = 5;
const static int canvas_pos_x = 5;
const static int canvas_pos_gap_y = 5;
const static int canvas_width =
    g_app_base_height - bottom_margin - 2 * button_box_height - button_gap_y - button_box_pos_y - canvas_pos_gap_y;
const static int canvas_height = canvas_width;
#endif //FREECIRCOS_SETTINGS_WINSCALE_H_
