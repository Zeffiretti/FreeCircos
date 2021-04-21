//
// Created by Hiesh on 2021/4/15.
//

#ifndef FREECIRCOS_SETTINGS_WINSCALE_H_
#define FREECIRCOS_SETTINGS_WINSCALE_H_

const static qreal g_scale = 1.5;
const static int g_app_base_width = 900;
const static int g_app_base_height = 350;
const static int left_margin = 5;
const static int right_margin = 5;
const static int top_margin = 5;
const static int bottom_margin = 5;
const static int button_box_pos_x = left_margin;
const static int button_box_pos_y = top_margin;
const static int button_box_width = 68;
const static int button_box_height = 20;
const static int button_gap_x = 6;
const static int button_gap_y = 5;

const static int canvas_pos_x = left_margin;
const static int canvas_pos_gap_y = 5;
const static int canvas_width =
    g_app_base_height - bottom_margin - 2 * button_box_height - button_gap_y - top_margin - canvas_pos_gap_y;
const static int canvas_height = canvas_width;

const static int config_widget_margin_x = 10;
const static int config_widget_pos_y = top_margin;
const static int config_widget_pos_x = canvas_pos_x + canvas_width + config_widget_margin_x;
const static int config_widget_height = g_app_base_height - bottom_margin - config_widget_pos_y;
const static int
    config_widget_width = g_app_base_width - left_margin - right_margin - canvas_width - config_widget_margin_x;

// variables below are referenced in config_widget
const static int page_margin = 0;
const static int page_label_margin = 30;
const static int switch_button_pos_x = page_margin;
const static int switch_button_pos_y = page_margin;
const static int switch_button_height = 15;
const static int switch_button_width = config_widget_width / 2;
const static int table_pos_x = page_margin;
const static int table_pos_y = page_margin + switch_button_height;
const static int table_width = switch_button_width;
const static int table_height = (config_widget_height - table_pos_y - switch_button_height) / 30 * 30;
const static int color_dialog_pos_x = table_width;
const static int color_dialog_pos_y = page_margin;
const static int color_dialog_width = config_widget_width - table_width;
const static int color_dialog_height = table_height - page_label_margin;
const static int label_margin_y = 5;
const static int label_margin_x = 3;
const static int label_state_pos_x = color_dialog_pos_x + label_margin_x;
const static int label_state_pos_y = color_dialog_pos_y + color_dialog_height + label_margin_y;
//const static int label_state_width = 10;
const static int label_state_width = (color_dialog_width - 2 * label_margin_x) / 4;
//const static int label_state_height = 5;
const static int label_state_height = (config_widget_height - label_state_pos_y - label_margin_y)/3;
#endif //FREECIRCOS_SETTINGS_WINSCALE_H_
