#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>

class Device {
public:
    Device(const std::string &name) : m_name(name) {}

    virtual void poll() const = 0;

protected:
    std::string m_name;
};

class EnergyMeter : public Device {
public:
    EnergyMeter(const std::string &name) : Device(name) {}

    void poll() const override {
        std::cout << "Polling energy meter: " << m_name << std::endl;
    }
};

class InputBlock : public Device {
public:
    InputBlock(const std::string &name) : Device(name) {}

    void poll() const override {
        std::cout << "Polling input block: " << m_name << std::endl;
    }
};

class HeatingControlBlock : public Device {
public:
    HeatingControlBlock(const std::string &name) : Device(name) {}

    void poll() const override {
        std::cout << "Polling heating control block: " << m_name << std::endl;
    }
};

class SmartHome {
public:
    void addDevice(Device *device) {
        devices.push_back(device);
    }

    void pollAllDevices() const {
        for (const auto &device: devices) {
            device->poll();
        }
    }

private:
    std::vector<Device *> devices;
};

void readConfiguration(const std::string &filename, SmartHome &smartHome) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            if (!line.empty()) {
                if (line == "Меркурий 230") {
                    smartHome.addDevice(new EnergyMeter(line));
                } else if (line == "Нева МТ314") {
                    smartHome.addDevice(new EnergyMeter(line));
                } else if (line == "Энергомера CE308") {
                    smartHome.addDevice(new EnergyMeter(line));
                } else if (line == "Reallab NL-16HV") {
                    smartHome.addDevice(new InputBlock(line));
                } else if (line == "Приборэлектро PRE-16") {
                    smartHome.addDevice(new InputBlock(line));
                } else if (line == "Энергосервис ЭНМВ-1-24") {
                    smartHome.addDevice(new InputBlock(line));
                } else if (line == "Ouman S203") {
                    smartHome.addDevice(new HeatingControlBlock(line));
                } else if (line == "Овен ТРМ232") {
                    smartHome.addDevice(new HeatingControlBlock(line));
                } else {
                    std::cout << "Not find" << line << std::endl;
                }
            }
        }
        file.close();
    } else {
        std::cout << "Not open file" << filename << std::endl;
    }
}

int main() {
    SmartHome smartHome;
    SetConsoleOutputCP(CP_UTF8);
    readConfiguration("config.txt", smartHome);
    smartHome.pollAllDevices();
    return 0;
}