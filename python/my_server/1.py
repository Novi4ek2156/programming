import socket
import struct
import threading
import cv2
import time

# Настройки
IP = '0.0.0.0'  # Слушать на всех интерфейсах
CMD_PORT = 5001
VIDEO_PORT = 8001


def handle_command_client(conn, addr):
    print(f"[COMMAND] Подключен клиент: {addr}")
    with conn:
        while True:
            try:
                data = conn.recv(1024)
                if not data:
                    break
                message = data.decode('utf-8').strip()
                print(f"[COMMAND] Получена команда: {message}")
            except ConnectionResetError:
                break
    print(f"[COMMAND] Клиент {addr} отключен")


def handle_video_client(conn, addr):
    print(f"[VIDEO] Подключен клиент: {addr}")
    # Используем камеру (0) или создаем пустое изображение, если камеры нет
    cap = cv2.VideoCapture(0)

    with conn:
        try:
            while True:
                ret, frame = cap.read()
                if not ret:
                    # Если камеры нет, генерируем шум или цветной фон
                    import numpy as np
                    frame = np.zeros((480, 640, 3), np.uint8)
                    cv2.putText(frame, f"Server Time: {time.time()}", (50, 240),
                                cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)

                # Сжимаем кадр в JPEG
                result, frame_encoded = cv2.imencode('.jpg', frame, [int(cv2.IMWRITE_JPEG_QUALITY), 50])
                if not result:
                    continue

                data = frame_encoded.tobytes()
                size = len(data)

                # Отправляем размер кадра в Little-Endian (как в вашем Kotlin коде: Integer.reverseBytes)
                # 'I' - unsigned int, '<' - Little-Endian
                conn.sendall(struct.pack('<I', size))

                # Отправляем сам кадр
                conn.sendall(data)

                # Ограничиваем FPS (~30 кадров в секунду)
                time.sleep(0.03)

        except (ConnectionResetError, BrokenPipeError):
            print(f"[VIDEO] Клиент {addr} разорвал соединение")
        finally:
            cap.release()


def start_server(port, handler):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((IP, port))
    server.listen(5)
    print(f"[*] Сервер запущен на порту {port}")
    while True:
        conn, addr = server.accept()
        thread = threading.Thread(target=handler, args=(conn, addr))
        thread.start()


if __name__ == "__main__":
    # Запускаем командный сервер в отдельном потоке
    cmd_thread = threading.Thread(target=start_server, args=(CMD_PORT, handle_command_client))
    cmd_thread.daemon = True
    cmd_thread.start()

    # Запускаем видео сервер в основном потоке
    try:
        start_server(VIDEO_PORT, handle_video_client)
    except KeyboardInterrupt:
        print("\nСервер остановлен.")
