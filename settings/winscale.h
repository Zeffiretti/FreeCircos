//
// Created by Hiesh on 2021/4/15.
//

#ifndef FREECIRCOS_SETTINGS_WINSCALE_H_
#define FREECIRCOS_SETTINGS_WINSCALE_H_

//static qreal g_scale = 1.2;
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
//const static int canvas_dpi_ratio = 1;
const static int canvas_line_width = 1;

const static int config_widget_margin_x = 10;
const static int config_widget_pos_y = top_margin;
const static int config_widget_pos_x = canvas_pos_x + canvas_width + config_widget_margin_x;
const static int config_widget_height = g_app_base_height - bottom_margin - config_widget_pos_y;
const static int
  config_widget_width = g_app_base_width - left_margin - right_margin - canvas_width - config_widget_margin_x;

// variables below are referenced in config_widget(backbone & category)
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
const static int bb_label_state_pos_x = color_dialog_pos_x + label_margin_x;
const static int bb_label_state_pos_y = color_dialog_pos_y + color_dialog_height + label_margin_y;
const static int bb_label_state_width = (color_dialog_width - 2 * label_margin_x) / 4;
const static int bb_label_state_height = (config_widget_height - bb_label_state_pos_y - label_margin_y) / 3;
const static int cat_label_state_pos_x = bb_label_state_pos_x;
const static int cat_label_state_pos_y = bb_label_state_pos_y + bb_label_state_height + label_margin_y;
const static int cat_label_state_width = bb_label_state_width;
const static int cat_label_state_height = bb_label_state_height;

// variables below are referenced in config_widget(link)
const static int lk_config_pos_x = color_dialog_pos_x;
const static int lk_config_pos_y = color_dialog_pos_y;
const static int lk_config_width = color_dialog_width;
const static int lk_config_height = table_height;
const static int lk_text_pos_x1 = label_margin_x;
const static int lk_text_pos_y1 = page_margin + label_margin_y + table_pos_y;
const static int lk_label_width = bb_label_state_width;
const static int lk_label_height = bb_label_state_height;
const static int lk_combobox_pos_x1 = lk_text_pos_x1 + lk_label_width;
const static int lk_text_pos_x2 = lk_combobox_pos_x1 + lk_label_width;
const static int lk_combobox_pos_x2 = lk_text_pos_x2 + lk_label_width;
const static int thermometer_pos_x = lk_text_pos_x1 + label_margin_x;
const static int thermometer_pos_y = lk_text_pos_y1 + 5 * (lk_label_height + label_margin_y);
const static int thermometer_width = lk_config_width - 4 * label_margin_x;
const static int thermometer_height = 2 * lk_label_height;
const static int thermometer_canvas_pos_x = 0.86 * canvas_width;
const static int thermometer_canvas_pos_y = 0.7 * canvas_width;
const static int thermometer_canvas_width = 0.12 * canvas_width;
const static int thermometer_canvas_height = 0.3 * canvas_width;
const static int link_cm_button_width = 16;
const static int link_cm_button_height = 25;
const static int link_cm_button_pos_x1 = thermometer_pos_x;
const static int link_cm_button_pos_y = thermometer_pos_y + thermometer_height;

// arrow widget
const static int arrow_config_pos_x = color_dialog_pos_x;
const static int arrow_config_pos_y = color_dialog_pos_y;
const static int arrow_config_width = color_dialog_width;
const static int arrow_config_height = table_height;
const static int arrow_label_pos_x1 = label_margin_x;
const static int arrow_label_pos_y1 = page_margin + label_margin_y + table_pos_y;
const static int arrow_label_width = bb_label_state_width;
const static int arrow_label_height = bb_label_state_height;
const static int arrow_combobox_pos_x1 = lk_text_pos_x1 + lk_label_width;
const static int arrow_label_pos_x2 = lk_combobox_pos_x1 + lk_label_width;
const static int arrow_combobox_pos_x2 = lk_text_pos_x2 + lk_label_width;

const static int arrow_canvas_margin_y = label_margin_y * 3;
const static int arrow_canvas_label_pos_x1 = arrow_label_pos_x1;
const static int arrow_canvas_label_pos_y1 = arrow_label_pos_y1 + arrow_label_height + arrow_canvas_margin_y;
const static int arrow_canvas_label_width = arrow_label_width;
const static int arrow_canvas_label_height = arrow_label_height;
const static int arrow_canvas_slider_pos_x1 = arrow_canvas_label_pos_x1;
const static int arrow_canvas_slider_pos_y = arrow_canvas_label_pos_y1 + arrow_canvas_label_height;
const static int arrow_canvas_slider_width = 0.1 * arrow_canvas_label_width;
const static int arrow_canvas_slider_height = 3 * arrow_label_height;
const static int arrow_canvas_pos_x = arrow_canvas_slider_pos_x1 + arrow_canvas_slider_width;
const static int arrow_canvas_pos_y = arrow_canvas_slider_pos_y;
const static int arrow_canvas_width = 4 * arrow_label_width - 2 * arrow_canvas_slider_width;
const static int arrow_canvas_height = arrow_canvas_slider_height;
const static int arrow_canvas_slider_pos_x2 = arrow_canvas_pos_x + arrow_canvas_width + 1;
const static int arrow_canvas_label_pos_x2 = 4 * arrow_label_width - arrow_canvas_label_width;
const static int arrow_canvas_label_pos_x3 = arrow_canvas_pos_x;
const static int arrow_canvas_label_pos_y3 = arrow_canvas_pos_y + arrow_canvas_height;

const static int arrow_canvas_slider_pos_x3 = arrow_canvas_pos_x;
const static int arrow_canvas_slider_pos_y3 = arrow_canvas_label_pos_y3+arrow_canvas_label_height;
const static int arrow_canvas_slider_width3 = arrow_canvas_width;
const static int arrow_canvas_slider_height3 = arrow_canvas_slider_width;

const static int arrow_canvas_number_pos_x1 = arrow_canvas_label_pos_x1;
const static int arrow_canvas_number_pos_x2 = arrow_canvas_label_pos_x2;
const static int arrow_canvas_number_pos_x3 = arrow_canvas_label_pos_x3;
const static int arrow_canvas_number_pos_y = arrow_canvas_slider_pos_y3 + arrow_canvas_slider_height3;
// canvas setting
const static int canvas_scale = 1000;
#endif //FREECIRCOS_SETTINGS_WINSCALE_H_
