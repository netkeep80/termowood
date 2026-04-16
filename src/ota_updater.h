#ifndef OTA_UPDATER_H
#define OTA_UPDATER_H

// Инициализация системы OTA-обновлений
void initOTA();

// Проверка наличия обновлений
void checkForUpdates();

// Создание точки доступа для ручного обновления
void createOTAAP();

// Обработка OTA-обновлений
void handleOTA();

#endif