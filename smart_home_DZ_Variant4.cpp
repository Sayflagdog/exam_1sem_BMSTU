#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Light {
    bool isOn;
public:
    Light() : isOn(false) {}
    void turnOn() { isOn = true; }
    void turnOff() { isOn = false; }
    string getStatus() const { return isOn ? "Вкл" : "Выкл"; }
    bool getState() const { return isOn; }
    void setState(bool state) { isOn = state; }
};

class Thermostat {
    int temperature;
public:
    Thermostat() : temperature(20) {}
    void setTemperature(int t) { temperature = t; }
    int getTemperature() const { return temperature; }
};

class SecuritySystem {
    bool isArmed;
public:
    SecuritySystem() : isArmed(false) {}
    void arm() { isArmed = true; }
    void disarm() { isArmed = false; }
    string getStatus() const { return isArmed ? "Включён" : "Отключён"; }
    bool getState() const { return isArmed; }
    void setState(bool state) { isArmed = state; }
};

class Curtains {
    bool isUp;
public:
    Curtains() : isUp(false) {}
    void raise() { isUp = true; }
    void lower() { isUp = false; }
    string getStatus() const { return isUp ? "Подняты" : "Опущены"; }
    bool getState() const { return isUp; }
    void setState(bool state) { isUp = state; }
};

class AirConditioner {
    bool isOn;
public:
    AirConditioner() : isOn(false) {}
    void turnOn() { isOn = true; }
    void turnOff() { isOn = false; }
    string getStatus() const { return isOn ? "Вкл" : "Выкл"; }
    bool getState() const { return isOn; }
    void setState(bool state) { isOn = state; }
};

class SmartHome {
    Light light;
    Thermostat thermostat;
    SecuritySystem securitySystem;
    Curtains curtains;
    AirConditioner airConditioner;
    string stateFile;

public:
    SmartHome(const string& file = "home_state.txt") : stateFile(file) {
        loadState();
    }

    void controlLight(bool state) {
        if (state) light.turnOn();
        else light.turnOff();
    }

    void setTemperature(int temp) {
        thermostat.setTemperature(temp);
    }

    void controlSecurity(bool state) {
        if (state) securitySystem.arm();
        else securitySystem.disarm();
    }

    void controlCurtains(bool state) {
        if (state) curtains.raise();
        else curtains.lower();
    }

    void controlAirConditioner(bool state) {
        if (state) airConditioner.turnOn();
        else airConditioner.turnOff();
    }

    void displayStatus() const {
        cout << "Текущие параметры:\n";
        cout << "Свет: " << light.getStatus() << "\n";
        cout << "Температура: " << thermostat.getTemperature() << "°C\n";
        cout << "Система безопасности: " << securitySystem.getStatus() << "\n";
        cout << "Шторы: " << curtains.getStatus() << "\n";
        cout << "Кондиционер: " << airConditioner.getStatus() << "\n";
    }

    void saveState() const {
        ofstream outFile(stateFile);
        if (outFile.is_open()) {
            outFile << light.getState() << "\n";
            outFile << thermostat.getTemperature() << "\n";
            outFile << securitySystem.getState() << "\n";
            outFile << curtains.getState() << "\n";
            outFile << airConditioner.getState() << "\n";
            outFile.close();
            cout << "Состояние сохранено в " << stateFile << ". Выход...\n";
        } else {
            cerr << "Ошибка при сохранении состояния в файл.\n";
        }
    }

    void loadState() {
        ifstream inFile(stateFile);
        if (inFile.is_open()) {
            bool lightState, securityState, curtainsState, acState;
            int temp;
            inFile >> lightState >> temp >> securityState >> curtainsState >> acState;
            light.setState(lightState);
            thermostat.setTemperature(temp);
            securitySystem.setState(securityState);
            curtains.setState(curtainsState);
            airConditioner.setState(acState);
            inFile.close();
            cout << "Состояние загружено из файла.\n";
        } else {
            cout << "Файл состояния отсутствует. Используются параметры по умолчанию.\n";
        }
    }
};

int main() {
    SmartHome home;
    int choice, temp;
    bool state;

    while (true) {
        home.displayStatus();
        cout << "Выберите действие:\n";
        cout << "1. Включить свет\n";
        cout << "2. Выключить свет\n";
        cout << "3. Установить температуру\n";
        cout << "4. Включить систему безопасности\n";
        cout << "5. Отключить систему безопасности\n";
        cout << "6. Поднять шторы\n";
        cout << "7. Опустить шторы\n";
        cout << "8. Включить кондиционер\n";
        cout << "9. Выключить кондиционер\n";
        cout << "10. Выход\n";
        cin >> choice;

        switch (choice) {
            case 1:
                home.controlLight(true);
                break;
            case 2:
                home.controlLight(false);
                break;
            case 3:
                cout << "Введите температуру: ";
                cin >> temp;
                home.setTemperature(temp);
                break;
            case 4:
                home.controlSecurity(true);
                break;
            case 5:
                home.controlSecurity(false);
                break;
            case 6:
                home.controlCurtains(true);
                break;
            case 7:
                home.controlCurtains(false);
                break;
            case 8:
                home.controlAirConditioner(true);
                break;
            case 9:
                home.controlAirConditioner(false);
                break;
            case 10:
                home.saveState();
                return 0;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}
