import tkinter as tk
import pygame
import random
running = False

def button_click():
    global running, menu
    running = True
    menu.destroy()
    game()
def menu():
    global running,menu
    running = False
    menu = tk.Tk()
    menu.title("game 1")
    menu.geometry("800x600")
    menu_label1 = tk.Label(menu, text="SSSSSSSSSS", font="Arial 30")
    menu_label1.pack()
    menu_button = tk.Button(menu, text="Start game", command=button_click )
    menu_button.pack()
    menu.mainloop()
def restart_command():
    global restart_menu
    game()
    restart_menu.destroy()
def restart():
    pygame.quit()
    restart_menu = tk.Toplevel()
    restart_menu.geometry("300x200")
    restart_menu_button = tk.Button(restart_menu, text="restart", command=restart_command)
    restart_menu_button.pack()
def game():
    global running
    pygame.init()
    screen = pygame.display.set_mode((800,600))
    clock = pygame.time.Clock()
    apple = pygame.image.load("TrueApple.png")
    limon = pygame.image.load("limon.png")
    bomb = pygame.image.load("bomb.png")
    banana = pygame.image.load("banana.png")
    gift = pygame.image.load("gift.png")
    basket = pygame.image.load("BasketTrue.png")
    basket_x = 185
    fruits = [[400, 0, apple]]
    time = 0
    hp = 3
    score = 0
    font = pygame.font.SysFont("Arial", 30)
    list_fruit = [apple, banana, bomb, limon, gift]

    while running:
        time +=1
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        buttons = pygame.key.get_pressed()

        if buttons[pygame.K_RIGHT] and basket_x < 768:
            basket_x += 5
        if buttons[pygame.K_LEFT] and basket_x > 0:
            basket_x -= 5

        if time % 98 == 0:
            fruits.append([random.randint(30, 770),
                           -40,
                           random.choice(list_fruit)])

        # 1. Очищаем экран (голубой фон)
        screen.fill((135, 206, 235))
        l = font.render(f"live:{hp}", True, (225, 0, 0))
        screen.blit(l, (30, 30))
        s = font.render(f"Score:{score}", True, (225, 225, 225))
        screen.blit(s, (30, 60))
        # 2. Наклеиваем яблоко в центр
        pygame.draw.rect(screen, (0, 255, 0), (0, 570, 800, 30))
        if hp == 0 or hp <=0:
            text = font.render("You lose", True, (255, 0, 0))
            screen.blit(text, (100, 250))
            pygame.display.flip()
            restart()
            continue
        for f in fruits:
            screen.blit(f[2], (f[0], f[1]))
            f[1] += 2
            if f[1] > 560:
                fruits.remove(f)
                hp -= 1
            hit_box = pygame.Rect(f[0], f[1], f[2].get_width(), f[2].get_height())
            hit_basket = pygame.Rect(basket_x, 550, basket.get_width(), basket.get_height())
            if hit_box.colliderect(hit_basket):
                if f[2] == gift:
                    chanse = random.randint(0,1)
                    if chanse == 0:
                        hp -=1
                    else:
                        hp+=1
                        score +=25
                if f[2] == bomb:
                    hp -=2
                fruits.remove(f)
                score += 1

        screen.blit(basket, (basket_x, 550))

        # 3. Показываем результат
        pygame.display.flip()
        clock.tick(60)  # 60 кадров в секунду


menu()
