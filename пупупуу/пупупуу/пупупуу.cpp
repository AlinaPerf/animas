#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

vector<string> readFramesFromFile(const string& filename, const string& delimiter) {
    vector<string> frames;
    ifstream file(filename);

    if (!file) {
        cerr << "Не удалось открыть файл " << filename << endl;
        return frames;
    }

    string line, frame;
    while (getline(file, line)) {
        if (line == delimiter) {
            if (!frame.empty()) {
                frames.push_back(frame);
                frame.clear();
            }
        }
        else {
            frame += line + "\n";
        }
    }
    if (!frame.empty()) {
        frames.push_back(frame);
    }

    return frames;
}

void animate(const vector<string>& frames) {
    const int numFrames = frames.size();
    for (int i = 0; i < numFrames; ++i) {
        clearScreen();
        cout << frames[i] << endl;
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

int main() {
    setlocale(0, "ru");
    string filename;
    string delimiter;

    cout << "Введите имя файла с кадрами анимации: ";
    cin >> filename;
    cout << "Введите разделитель кадров: ";
    cin >> delimiter;

    vector<string> frames = readFramesFromFile(filename, delimiter);

    if (!frames.empty()) {
        animate(frames);
    }
    else {
        cout << "Нет кадров для анимации." << endl;
    }

    cin >> delimiter;
    return 0;
}