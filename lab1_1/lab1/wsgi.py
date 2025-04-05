"""
КОНСПЕКТ ПРО ФАЙЛИК:
# старый - WSGI (WEB SERVER GATEWAY INTERFACE)
# Интерфейс, для связи скриптов с HTTP сервером
Веб-сервер исполняет код и отправляет связанную с http-запросом информацию и callback-функцию в веб-приложение. 
Затем запрос на стороне приложения обрабатывается и высылается ответ на веб-сервер.
"""
import os

from django.core.wsgi import get_wsgi_application

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'lab1.settings')

application = get_wsgi_application()
