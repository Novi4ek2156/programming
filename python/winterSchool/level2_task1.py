import pygame
import random

pygame.init()
screen = pygame.display.set_mode((800, 600))
clock = pygame.time.Clock()

font = pygame.font.SysFont(None, 30)  # ИСПРАВЛЕННАЯ СТРОКА

# Загружаем картинку
apple = pygame.image.load("TrueApple.png")
banana = pygame.image.load("banana.png")
orange = pygame.image.load("orange.png")
gift = pygame.image.load("gift.png")
basket = pygame.image.load("BasketTrue.png")

basket_x = 185
fruits = [[400, 0, apple]]
time_spavn = 98
time= 0
hp = 3
score = 0
list_fruit = [apple, banana, orange, gift]
running = True
while running:
    time +=1
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    buttons = pygame.key.get_pressed()

    if buttons[pygame.K_RIGHT] and basket_x<768:
            basket_x +=5
    if buttons[pygame.K_LEFT] and basket_x> 0:
            basket_x -=5

    if time %98 == 0:
        fruits.append([random.randint(30,770),
                       -40,
                       random.choice(list_fruit)])




    # 1. Очищаем экран (голубой фон)
    screen.fill((135, 206, 235))

    # 2. Наклеиваем яблоко в центр
    pygame.draw.rect(screen, (0, 255, 0), (0, 570, 800, 30))
    if hp == 0:
        text = font.render("You lose", True ,(255,0,0))
        screen.blit(text, (100, 250))
        pygame.display.flip()
        continue
    for f in fruits:
        screen.blit(f[2],(f[0], f[1]))
        f[1] +=2
        if f[1] > 560:
            fruits.remove(f)
            hp -=1
        hit_box = pygame.Rect(f[0], f[1], f[2].get_width(), f[2].get_height())
        hit_basket = pygame.Rect(basket_x, 550, basket.get_width(), basket.get_height())
        if hit_box.colliderect(hit_basket):
            if f[2] == gift:
                hp+=1
            fruits.remove(f)
            score +=1


    screen.blit(basket, (basket_x,550))




    # 3. Показываем результат
    pygame.display.flip()
    clock.tick(60)  # 60 кадров в секунду

pygame.quit()