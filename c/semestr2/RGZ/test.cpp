#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

// Структура для хранения рекорда
struct HighScore {
    int score;
    int level;
    string date;
};

// Класс для работы с настройками
class Settings {
public:
    int field_width;
    int field_height;
    int difficulty;
    int initial_speed;
    bool special_items;
    bool two_snakes;
    
    Settings() {
        field_width = 30;
        field_height = 20;
        difficulty = 2;
        initial_speed = 150;
        special_items = true;
        two_snakes = false;
        loadFromFile();
    }
    
    void loadFromFile() {
        ifstream file("settings.txt");
        if (!file.is_open()) {
            createDefaultSettings();
            return;
        }
        
        string key;
        int value;
        while (file >> key >> value) {
            if (key == "field_width") field_width = value;
            else if (key == "field_height") field_height = value;
            else if (key == "difficulty") difficulty = value;
            else if (key == "initial_speed") initial_speed = value;
            else if (key == "special_items") special_items = value;
            else if (key == "two_snakes") two_snakes = value;
        }
        file.close();
        
        // Ограничения
        if (field_width < 10) field_width = 10;
        if (field_height < 10) field_height = 10;
        if (difficulty < 1) difficulty = 1;
        if (difficulty > 3) difficulty = 3;
    }
    
    void createDefaultSettings() {
        ofstream file("settings.txt");
        file << "# Размер поля (ширина высота)\n";
        file << "field_width 30\nfield_height 20\n\n";
        file << "# Уровни сложности: 1 - лёгкий, 2 - средний, 3 - сложный\n";
        file << "difficulty 2\n\n";
        file << "# Начальная скорость (мс между кадрами)\n";
        file << "initial_speed 150\n\n";
        file << "# Включить спецобъекты (1 - да, 0 - нет)\n";
        file << "special_items 1\n\n";
        file << "# Режим двух змей\n";
        file << "two_snakes 0\n";
        file.close();
    }
    
    int getSpeed() const {
        switch(difficulty) {
            case 1: return initial_speed;
            case 2: return initial_speed * 0.7;
            case 3: return initial_speed * 0.4;
            default: return initial_speed;
        }
    }
    
    int getScoreMultiplier() const {
        switch(difficulty) {
            case 1: return 1;
            case 2: return 2;
            case 3: return 3;
            default: return 1;
        }
    }
};

// Класс для управления рекордами
class ScoreManager {
private:
    vector<HighScore> scores;
    string filename;
    
public:
    ScoreManager() : filename("highscores.txt") {
        loadScores();
    }
    
    void loadScores() {
        ifstream file(filename);
        if (!file.is_open()) return;
        
        scores.clear();
        HighScore hs;
        while (file >> hs.score >> hs.level) {
            file.ignore();
            getline(file, hs.date);
            scores.push_back(hs);
        }
        file.close();
        
        sort(scores.begin(), scores.end(), [](const HighScore& a, const HighScore& b) {
            return a.score > b.score;
        });
        
        if (scores.size() > 10) scores.resize(10);
    }
    
    void saveScore(int score, int level) {
        HighScore hs;
        hs.score = score;
        hs.level = level;
        
        time_t now = time(nullptr);
        hs.date = ctime(&now);
        hs.date.pop_back(); // Удаляем перевод строки
        
        scores.push_back(hs);
        
        sort(scores.begin(), scores.end(), [](const HighScore& a, const HighScore& b) {
            return a.score > b.score;
        });
        
        if (scores.size() > 10) scores.resize(10);
        
        ofstream file(filename);
        for (const auto& s : scores) {
            file << s.score << " " << s.level << " " << s.date << endl;
        }
        file.close();
    }
    
    int getHighScore() const {
        if (scores.empty()) return 0;
        return scores[0].score;
    }
    
    void showHighScores(WINDOW* win) const {
        werase(win);
        box(win, 0, 0);
        mvwprintw(win, 0, 2, " HIGH SCORES ");
        
        if (scores.empty()) {
            mvwprintw(win, 2, 2, "No scores yet!");
        } else {
            mvwprintw(win, 1, 2, "Rank  Score  Level  Date");
            for (size_t i = 0; i < scores.size(); i++) {
                mvwprintw(win, i + 2, 2, "%d.    %d     %d     %s",
                         i + 1, scores[i].score, scores[i].level, scores[i].date.c_str());
            }
        }
        
        wrefresh(win);
    }
    
    bool isNewHighScore(int score) const {
        return scores.empty() || score > scores.back().score;
    }
};

// Типы объектов на поле
enum ObjectType {
    OBJ_EMPTY = 0,
    OBJ_WALL = 1,
    OBJ_SNAKE_BODY = 2,
    OBJ_SNAKE_HEAD = 3,
    OBJ_FOOD_NORMAL = 4,
    OBJ_FOOD_SPECIAL = 5
};

// Класс специального объекта
class SpecialItem {
public:
    int x, y;
    int duration;
    int type; // 0 - замедление, 1 - ускорение, 2 - очки x2
    
    SpecialItem() : x(-1), y(-1), duration(0), type(0) {}
    
    void generate(int width, int height, const vector<vector<bool>>& occupied) {
        do {
            x = rand() % width;
            y = rand() % height;
        } while (occupied[y][x]);
        duration = 100; // 100 кадров ~ 5-10 секунд
        type = rand() % 3;
    }
    
    bool isActive() const { return duration > 0 && x >= 0 && y >= 0; }
    
    void update() { if (duration > 0) duration--; }
    
    char getSymbol() const {
        switch(type) {
            case 0: return 'S'; // Slow
            case 1: return 'F'; // Fast
            case 2: return '2'; // Double score
            default: return '?';
        }
    }
};

// Класс змейки
class Snake {
public:
    vector<pair<int, int>> body;
    int dx, dy;
    bool alive;
    int score_multiplier;
    int speed_boost;
    
    Snake(int start_x, int start_y) {
        body.push_back({start_x, start_y});
        body.push_back({start_x - 1, start_y});
        body.push_back({start_x - 2, start_y});
        dx = 1;
        dy = 0;
        alive = true;
        score_multiplier = 1;
        speed_boost = 0;
    }
    
    void move() {
        if (!alive) return;
        
        int new_x = body[0].first + dx;
        int new_y = body[0].second + dy;
        body.insert(body.begin(), {new_x, new_y});
        body.pop_back();
    }
    
    void grow() {
        if (!alive) return;
        int tail_x = body.back().first;
        int tail_y = body.back().second;
        body.push_back({tail_x, tail_y});
    }
    
    bool checkCollision(int width, int height) {
        int head_x = body[0].first;
        int head_y = body[0].second;
        
        // Столкновение со стеной
        if (head_x <= 0 || head_x >= width - 1 || head_y <= 0 || head_y >= height - 1) {
            alive = false;
            return true;
        }
        
        // Столкновение с собой
        for (size_t i = 1; i < body.size(); i++) {
            if (body[i].first == head_x && body[i].second == head_y) {
                alive = false;
                return true;
            }
        }
        
        return false;
    }
    
    void changeDirection(int new_dx, int new_dy) {
        // Запрещаем движение назад
        if ((new_dx != 0 || new_dy != 0) && (dx != -new_dx || dy != -new_dy)) {
            dx = new_dx;
            dy = new_dy;
        }
    }
    
    pair<int, int> getHead() const { return body[0]; }
    int getLength() const { return body.size(); }
};

// Основной класс игры
class SnakeGame {
private:
    Settings settings;
    ScoreManager scoreManager;
    Snake* snake;
    vector<vector<char>> field;
    int food_x, food_y;
    int special_x, special_y;
    bool special_active;
    int special_timer;
    int score;
    int level;
    int frame_count;
    int current_speed;
    bool game_over;
    WINDOW* game_win;
    WINDOW* info_win;
    WINDOW* score_win;
    
public:
    SnakeGame() {
        srand(time(nullptr));
        game_over = false;
        score = 0;
        level = 1;
        frame_count = 0;
        special_active = false;
        special_timer = 0;
        special_x = special_y = -1;
        
        initField();
        snake = new Snake(settings.field_width / 2, settings.field_height / 2);
        generateFood();
        current_speed = settings.getSpeed();
    }
    
    ~SnakeGame() {
        delete snake;
    }
    
    void initField() {
        field.resize(settings.field_height, vector<char>(settings.field_width, ' '));
        
        // Рисуем границы
        for (int i = 0; i < settings.field_width; i++) {
            field[0][i] = '#';
            field[settings.field_height - 1][i] = '#';
        }
        for (int i = 0; i < settings.field_height; i++) {
            field[i][0] = '#';
            field[i][settings.field_width - 1] = '#';
        }
    }
    
    void generateFood() {
        do {
            food_x = rand() % (settings.field_width - 2) + 1;
            food_y = rand() % (settings.field_height - 2) + 1;
        } while (isOccupied(food_x, food_y));
    }
    
    bool isOccupied(int x, int y) {
        if (field[y][x] != ' ') return true;
        for (const auto& segment : snake->body) {
            if (segment.first == x && segment.second == y) return true;
        }
        return false;
    }
    
    void generateSpecialItem() {
        if (!settings.special_items) return;
        if (special_active) return;
        
        if (rand() % 200 < 5 && !special_active) { // 5% шанс каждый кадр
            do {
                special_x = rand() % (settings.field_width - 2) + 1;
                special_y = rand() % (settings.field_height - 2) + 1;
            } while (isOccupied(special_x, special_y));
            special_active = true;
            special_timer = 150; // Активен в течение ~10 секунд
        }
    }
    
    void processInput() {
        int ch = wgetch(game_win);
        switch(ch) {
            case KEY_UP:
            case 'w':
            case 'W':
                snake->changeDirection(0, -1);
                break;
            case KEY_DOWN:
            case 's':
            case 'S':
                snake->changeDirection(0, 1);
                break;
            case KEY_LEFT:
            case 'a':
            case 'A':
                snake->changeDirection(-1, 0);
                break;
            case KEY_RIGHT:
            case 'd':
            case 'D':
                snake->changeDirection(1, 0);
                break;
            case 'p':
            case 'P':
                pause();
                break;
            case 'q':
            case 'Q':
                game_over = true;
                break;
        }
    }
    
    void pause() {
        mvwprintw(info_win, 0, 0, "PAUSED - Press any key to continue");
        wrefresh(info_win);
        wgetch(game_win);
        mvwprintw(info_win, 0, 0, "                      ");
        wrefresh(info_win);
    }
    
    void update() {
        snake->move();
        
        // Проверка столкновений
        if (snake->checkCollision(settings.field_width, settings.field_height)) {
            game_over = true;
            return;
        }
        
        // Проверка на еду
        pair<int, int> head = snake->getHead();
        if (head.first == food_x && head.second == food_y) {
            int points = 10 * settings.getScoreMultiplier() * snake->score_multiplier;
            score += points;
            snake->grow();
            generateFood();
            
            // Увеличение скорости при росте
            if (current_speed > 30) {
                current_speed = max(30, current_speed - 2);
            }
        }
        
        // Проверка на спецобъект
        if (special_active && head.first == special_x && head.second == special_y) {
            // Эффект зависит от типа спецобъекта
            if (special_timer > 0) {
                // В реальной игре нужно хранить тип спецобъекта
                // Для простоты даём двойные очки на 10 ходов
                snake->score_multiplier = 2;
            }
            special_active = false;
            special_timer = 0;
        }
        
        // Обновление таймера спецэффектов
        if (snake->score_multiplier > 1) {
            frame_count++;
            if (frame_count > 100) {
                snake->score_multiplier = 1;
                frame_count = 0;
            }
        }
        
        // Обновление спецобъекта
        if (special_active) {
            special_timer--;
            if (special_timer <= 0) {
                special_active = false;
            }
        }
        
        generateSpecialItem();
        
        // Прогрессивное усложнение
        if (score > 0 && score % 100 == 0 && level < 10) {
            level++;
            current_speed = max(30, current_speed - 10);
        }
    }
    
    void draw() {
        werase(game_win);
        
        // Рисуем поле
        for (int i = 0; i < settings.field_height; i++) {
            for (int j = 0; j < settings.field_width; j++) {
                mvwaddch(game_win, i, j, field[i][j]);
            }
        }
        
        // Рисуем змейку
        for (size_t i = 0; i < snake->body.size(); i++) {
            char ch = (i == 0) ? '@' : 'o';
            mvwaddch(game_win, snake->body[i].second, snake->body[i].first, ch);
        }
        
        // Рисуем еду
        mvwaddch(game_win, food_y, food_x, '*');
        
        // Рисуем спецобъект
        if (special_active) {
            mvwaddch(game_win, special_y, special_x, '$');
        }
        
        box(game_win, 0, 0);
        wrefresh(game_win);
        
        // Обновляем информационную панель
        werase(info_win);
        box(info_win, 0, 0);
        mvwprintw(info_win, 1, 2, "SNAKE GAME");
        mvwprintw(info_win, 2, 2, "Score: %d", score);
        mvwprintw(info_win, 3, 2, "High Score: %d", scoreManager.getHighScore());
        mvwprintw(info_win, 4, 2, "Level: %d", level);
        mvwprintw(info_win, 5, 2, "Length: %d", snake->getLength());
        mvwprintw(info_win, 6, 2, "Multiplier: x%d", snake->score_multiplier);
        
        const char* diff_text[] = {"Easy", "Medium", "Hard"};
        mvwprintw(info_win, 7, 2, "Difficulty: %s", diff_text[settings.difficulty - 1]);
        
        mvwprintw(info_win, 9, 2, "Controls:");
        mvwprintw(info_win, 10, 2, "WASD or Arrows");
        mvwprintw(info_win, 11, 2, "P - Pause");
        mvwprintw(info_win, 12, 2, "Q - Quit");
        
        wrefresh(info_win);
        
        // Показываем рекорды
        scoreManager.showHighScores(score_win);
    }
    
    void run() {
        // Инициализация ncurses
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(0);
        nodelay(stdscr, TRUE);
        
        // Создаем окна
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        
        int game_h = settings.field_height + 2;
        int game_w = settings.field_width + 2;
        int info_w = 30;
        
        game_win = newwin(game_h, game_w, 0, 0);
        info_win = newwin(15, info_w, 0, game_w);
        score_win = newwin(15, info_w, 15, game_w);
        
        keypad(game_win, TRUE);
        nodelay(game_win, TRUE);
        
        // Главный игровой цикл
        while (!game_over) {
            processInput();
            update();
            draw();
            
            napms(current_speed);
        }
        
        // Конец игры
        if (scoreManager.isNewHighScore(score)) {
            scoreManager.saveScore(score, settings.difficulty);
        }
        
        // Показываем сообщение о конце игры
        WINDOW* end_win = newwin(5, 40, (max_y - 5) / 2, (max_x - 40) / 2);
        box(end_win, 0, 0);
        mvwprintw(end_win, 1, 2, "GAME OVER!");
        mvwprintw(end_win, 2, 2, "Final Score: %d", score);
        mvwprintw(end_win, 3, 2, "Press any key to exit...");
        wrefresh(end_win);
        nodelay(stdscr, FALSE);
        getch();
        
        // Очистка
        delwin(game_win);
        delwin(info_win);
        delwin(score_win);
        delwin(end_win);
        endwin();
        
        cout << "Game Over! Final Score: " << score << endl;
        if (scoreManager.isNewHighScore(score)) {
            cout << "New High Score!" << endl;
        }
    }
};

int main() {
    SnakeGame game;
    game.run();
    return 0;
}