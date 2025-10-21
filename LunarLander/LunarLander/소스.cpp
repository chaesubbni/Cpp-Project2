#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

class LunarLander {
private:
    double x, y;        // 현재 위치
    double velocity;    // 수직 속도(+ 아래로)
    double xVelocity;   // 수평 속도
    double fuel;        // 연료
    string status;      // 현재 상태

    Texture t1, t2;     // 텍스처
    Sprite  spaceship, burst; // 스프라이트
    Font    font;       // 폰트
    Text    text;       // 상태 표시

    SoundBuffer buffer_booster, buffer_moving, buffer_fail;
    Sound        sound_booster, sound_moving, sound_fail;

    int land = 0;       // 착륙 성공(1)/실패(0) 플래그

public:
    // 생성자
    LunarLander(double h, double v, double f) {
        x = 100;
        y = h;
        velocity = v;
        xVelocity = 0.0;
        fuel = f;

        // 텍스처 로드
        t1.loadFromFile("doraemong_1.jpg");
        t2.loadFromFile("doraemong_2.jpg");
        spaceship.setTexture(t1);
        burst.setTexture(t2);
        spaceship.setPosition((float)x, (float)y);
        burst.setPosition((float)x + 20, (float)y + 50);

        // 폰트/사운드 로드
        if (!font.loadFromFile("nanum.ttf")) {
            cout << "폰트 파일을 오픈할 수 없음!" << endl;
        }
        if (!buffer_booster.loadFromFile("booster_sound.mp3")) {
            cout << "오디오 파일을 오픈할 수 없음!" << endl;
        }
        if (!buffer_moving.loadFromFile("move_sound.mp3")) {
            cout << "오디오 파일을 오픈할 수 없음!" << endl;
        }
        if (!buffer_fail.loadFromFile("fail_sound.mp3")) {
            cout << "오디오 파일을 오픈할 수 없음!" << endl;
        }
        text.setFont(font);
        sound_booster.setBuffer(buffer_booster);
        sound_moving.setBuffer(buffer_moving);
        sound_fail.setBuffer(buffer_fail);
    }

    string out_status() { return status; }

    // 게임 상태 업데이트
    void update(double amount) {
        // 연료/추력
        if (fuel <= 0) { fuel = 0; amount = 0; }
        fuel = fuel - amount;

        // 중력(+), 추력(-)
        velocity = velocity - amount + 0.8;
        y = y + velocity;

        // 상하 경계
        if (y <= 0)  y = 0;
        if (y >= 650) y = 650;

        // 착륙대 위쪽 경계(평평한 지면 470)
        if (x >= 385 && x <= 595 && y >= 470) y = 470;

        // 좌우 이동(키보드)
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            xVelocity = -5.0;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            xVelocity = 5.0;
        }
        else {
            xVelocity = 0.0;
        }

        // x 위치 갱신 및 경계
        x += xVelocity;
        if (x < 0)    x = 0;
        if (x > 1100) x = 1100;

        // 이동 사운드
        if (velocity != 0 || xVelocity != 0) sound_moving.play();

        // 스프라이트 위치 동기화
        spaceship.setPosition((float)x, (float)y);
        burst.setPosition((float)x + 20, (float)y + 120);

        // 착륙 판정
        if (fabs(velocity) >= 15.0 && y >= 650) {
            land = 0; // 바닥에 빠르게 충돌
        }
        else if (fabs(velocity) < 15.0 && y >= 650) {
            velocity = 0; // 바닥에 안전 착륙
        }
        else if (fabs(velocity) >= 15.0 && y >= 470 && x >= 385 && x <= 595) {
            land = 0; // 착륙대에 급충돌
        }
        else if (fabs(velocity) < 15.0 && y >= 470 && x >= 385 && x <= 595) {
            land = 1; // 착륙대에 안전 착륙
            velocity = 0;
        }

        // 상태 문자열
        status = "Press up key!  height: " + to_string(650 - (int)round(y))
            + "  x: " + to_string((int)round(x))
            + "  speed: " + to_string((int)round(fabs(velocity)))
            + "  fuel: " + to_string((int)round(fuel));

        if (land == 1) {
            status = "success!!!";
        }
        else if (land == 0 || fuel == 0) {
            status = "failed!!";
            sound_fail.play();
        }
    }

    // 그리기
    void draw(RenderWindow& window, int flag) {
        window.draw(spaceship);
        if (flag == 1 && fuel > 0) {
            window.draw(burst);
            sound_booster.play();
        }
        text.setString(status);
        text.setCharacterSize(40);
        text.setPosition(10, 100);
        window.draw(text);
    }
};

int main() {
    RenderWindow window(VideoMode(1175, 855), "LUNAR LANDER");
    window.setFramerateLimit(60);

    // 배경
    Texture t;
    Sprite background;
    t.loadFromFile("Luanar_drawing.png"); // 스크린샷 표기 그대로
    background.setTexture(t);

    // 착륙선
    LunarLander lander(300.0, 1.0, 100.0);
    int flag = 0;
    string result;

    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            lander.update(3.0); // 추력
            flag = 1;
        }
        else {
            lander.update(0.0);
            flag = 0;
        }

        window.clear();
        window.draw(background);
        lander.draw(window, flag);
        window.display();

        result = lander.out_status();
        if (result == "failed!!") {
            Sleep(4000);
            break;
        }

        Sleep(100); // 0.1초 대기
    }

    return 0;
}
