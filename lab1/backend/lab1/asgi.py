"""
КОНСПЕКТ ПРО ФАЙЛИК:
# Asynchronous Server Gateway Interface - новый, старый - WSGI (WEB и_и)
# Интерфейс асинхронный, для связи скриптов с HTTP сервером
# 
"""

import os

from django.core.asgi import get_asgi_application

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'lab1.settings')

application = get_asgi_application()
