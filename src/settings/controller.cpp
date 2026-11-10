#include "controller.h"

String sort_function(String gogogaga)
{
    
}

Controller::Controller()
{
    lv_fs_drv_init(&drive);
    drive.letter = 'S';
    drive.cache_size = 256;
}

std::string Controller::set_stations()
{
    return std::string();
}

void Controller::save_settings(char* selected_station_option, char* selected_transport_option, uint32_t buff_size)
{
    lv_fs_file_t file;
    lv_fs_res_t file_writer;

    // Save Station Option
    file_writer = lv_fs_open(&file, "S:folder/station.txt", LV_FS_MODE_RD);
    lv_fs_write(&file, selected_station_option,buff_size, NULL);
    lv_fs_close(&file);

    // Save Transport Option
    file_writer = lv_fs_open(&file, "S:folder/vehicle.txt", LV_FS_MODE_RD);
    lv_fs_write(&file, selected_transport_option,buff_size, NULL);
    lv_fs_close(&file);
}

void Controller::load_settings(char* selected_station_option, char* selected_transport_option, uint32_t buff_size)
{
    lv_fs_file_t file;
    lv_fs_res_t file_reader;

    // Load Station Option
    file_reader = lv_fs_open(&file, "S:folder/station.txt", LV_FS_MODE_RD);
    lv_fs_read(&file, selected_station_option, buff_size, NULL);
    lv_fs_close(&file);

    // Load Transport Option
    file_reader = lv_fs_open(&file, "S:folder/station.txt", LV_FS_MODE_RD);
    lv_fs_read(&file, selected_transport_option, buff_size, NULL);
    lv_fs_close(&file);
}
