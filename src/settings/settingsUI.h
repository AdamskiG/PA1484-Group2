static void on_settings_btn_clicked(lv_event_t* e) {
    LV_UNUSED(e);
    Serial.println("Settings button clicked.");
    // Here you can implement the logic to navigate to the settings page or open a settings dialog.
}


static void draw_settings_ui(lv_obj_t* parent) {
    // Create a label for the settings UI
    lv_obj_t* settings_label = lv_label_create(parent);
    lv_label_set_text(settings_label, "Settings page, change stations here");
    lv_obj_set_style_text_font(settings_label, &lv_font_montserrat_28, 0);
    lv_obj_set_align(settings_label, LV_ALIGN_OUT_TOP_MID);
    // apply_tile_colors(parent, settings_label, /*dark=*/false);

    //create a dropdown with station options
    lv_obj_t* settings_options = lv_dropdown_create(parent);
    lv_obj_set_align(settings_options, LV_ALIGN_CENTER);
    lv_dropdown_set_options(settings_options, "Campus Gräsvik\nKarlskrona Centralstation\nYour mom's house");
}
